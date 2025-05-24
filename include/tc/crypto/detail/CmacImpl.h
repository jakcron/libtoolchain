	/**
	 * @file CmacImpl.h
	 * @brief Declaration of tc::crypto::detail::CmacImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2024/12/10
	 **/
#pragma once
#include <tc/types.h>

#include <tc/crypto/detail/BlockUtilImpl.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

#include <tc/cli/FormatUtil.h>
#include <fmt/core.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class CmacImpl
	 * @brief This class implements the CMAC (<b>C</b>ipher based <b>MAC</b>) algorithm as a template class.
	 * 
	 * @tparam BlockCipher The class that implements the block cipher used for CBC encryption for generating MAC.
	 * 
	 * @details
	 * The implementation of <var>BlockCipher</var> must satisfies the following conditions.
	 * 
	 * -# Has a <tt>kBlockSize</tt> constant that defines the size of the block to process.
	 * -# Has a <tt>kKeySize</tt> constant that defines the required key size to initialize the block cipher.
	 * -# Has an <tt>initialize</tt> method that initializes the state of the block cipher.
	 * -# Has an <tt>encrypt</tt> method that encrypts a block of input data.
	 * -# Has a <tt>decrypt</tt> method that decrypts a block of input data.
	 */
template <class BlockCipher>
class CmacImpl
{
public:
	static_assert(BlockCipher::kBlockSize == 8 || BlockCipher::kBlockSize == 16, "CmacImpl only supports BlockCiphers with block size 8 or 16.");

	static const size_t kKeySize = BlockCipher::kKeySize;
	static const size_t kMacSize = BlockCipher::kBlockSize;
	static const size_t kBlockSize = BlockCipher::kBlockSize;

	CmacImpl() :
		mBlockSize(kBlockSize),
		mState(State::None),
		mCipher()
	{

	}

	void initialize(const byte_t* key, size_t key_size) 
	{
		if (key == nullptr) { throw tc::ArgumentNullException("CmacImpl::initialize()", "key was null."); }
		if (key_size != kKeySize) { throw tc::ArgumentOutOfRangeException("CmacImpl::initialize()", "key_size did not equal kKeySize."); }
		
		// 1) initialise BlockCipher
		mCipher.initialize(key, key_size);

		// 2) generate K1, K2
		derive_cmac_keys(mCipher, mK1, mK2);
		
		// 3) clear MAC
		memset(mMac.data(), 0, mMac.size());

		// 4) clear Unprocessed Block
		memset(mUnprocessedBlock.data(), 0, mUnprocessedBlock.size());
		mUnprocessedBlockPos = 0;

		mState = State::Initialized;
	}

	void update(const byte_t* data, size_t data_size)
	{
		// the final block in CMAC has special processing, so it's important that update() 
		// only processes up-to but not including the last block provided by the user so that
		// getMac() can do the special case processing

		// only process data if the state is initialized (e.g. ready for processing)
		if (mState == State::Initialized)
		{
			// exit early if there is no data to process
			if (data == nullptr || data_size == 0)
			{
				return;
			}

			// where update was called and there is data in mUnprocessedBlock (from previous call to update()), this must be handled first before processing new data
			if (mUnprocessedBlockPos > 0)
			{
				// try to complete block (with data if required)
				size_t remaining_block_len = mUnprocessedBlock.size() - std::min<size_t>(mUnprocessedBlock.size(), mUnprocessedBlockPos);
				size_t data_to_add_len = std::min<size_t>(remaining_block_len, data_size);

				// only update block if there is data to add
				if (data_to_add_len > 0)
				{
					memcpy(mUnprocessedBlock.data() + mUnprocessedBlockPos, data, data_to_add_len);
					mUnprocessedBlockPos += data_to_add_len;

					// update data & data_size
					data_size -= data_to_add_len;
					data += data_to_add_len;
				}

				// if unprocessed block is now complete, and there is more data to process -> update MAC and clear unprocessed block
				// otherwise leave unprocessed block to be processed later
				if (mUnprocessedBlockPos >= mUnprocessedBlock.size() && data_size > 0)
				{
					// update MAC
					update_cbc_mac(mUnprocessedBlock.data());

					// clear unprocessed block
					mUnprocessedBlockPos = 0;
					memset(mUnprocessedBlock.data(), 0, mUnprocessedBlock.size());
				}
			}

			// calculate blocks to process
			size_t block_num = data_size / kBlockSize + ((data_size % kBlockSize) > 0);
			if (block_num > 0)
			{
				// process all but the last block
				for (size_t blk = 0; blk < block_num-1; blk++)
				{
					// update MAC
					update_cbc_mac(data);

					data_size -= kBlockSize;
					data += kBlockSize;
				}

				// process last block, however don't update the MAC, it needs to be preserved needs to be saved 
				// mUnprocessedBlockPos will always be zero/empty by this point as it must be cleared during the start of update
				memcpy(mUnprocessedBlock.data(), data, std::min<size_t>(mBlockSize, data_size));
				mUnprocessedBlockPos = std::min<size_t>(mBlockSize, data_size);
			}
		}
	}

	void getMac(byte_t* mac)
	{
		if (mState == State::Initialized)
		{
			// finalise mac, and tranisition to done state
			std::array<byte_t, kBlockSize> M_last;
	
			// 1) transform last unprocessed to M_last block
			if (mUnprocessedBlockPos == kBlockSize)
			{
				// XOR unprocessed block with K1 to get M_last
				xor_block<kBlockSize>(M_last.data(), mUnprocessedBlock.data(), mK1.data());
			}
			else if (mUnprocessedBlockPos < kBlockSize)
			{
				// pad mUnprocessedBlock since it was less than the block size
				cmac_pad_block(mUnprocessedBlock.data(), mUnprocessedBlock.data(), mUnprocessedBlockPos);

				// XOR unprocessed block with K2 to get M_last
				xor_block<kBlockSize>(M_last.data(), mUnprocessedBlock.data(), mK2.data());
			}

			// 2) update MAC with final block
			// update MAC
			update_cbc_mac(M_last.data());

			mState = State::Done;
		}
		if (mState == State::Done)
		{
			// return finalised mac
			std::memcpy(mac, mMac.data(), mMac.size());
		}		
	}

private:
	const uint64_t kR64 = 0x1B;
	const uint64_t kR128 = 0x87;

	enum class State
	{
		None,
		Initialized,
		Done
	};

	const size_t mBlockSize;

	// MAC state
	State mState;
	
	// cipher/key storage
	BlockCipher mCipher;
	std::array<byte_t, kBlockSize> mK1;
	std::array<byte_t, kBlockSize> mK2;
	
	// storage for MAC
	std::array<byte_t, kMacSize> mMac;

	// note the last processed block
	std::array<byte_t, kBlockSize> mUnprocessedBlock;
	size_t mUnprocessedBlockPos;

	inline void derive_cmac_keys(BlockCipher& cipher, std::array<byte_t, kBlockSize>& K1, std::array<byte_t, kBlockSize>& K2)
	{
		// generate input zero block
		std::array<byte_t, kBlockSize> kZerosBlock;
		memset(kZerosBlock.data(), 0, kZerosBlock.size());

		// generate L block
		std::array<byte_t, kBlockSize> L;
		cipher.encrypt(L.data(), kZerosBlock.data());

		// generate K1 block
		galois_func(K1.data(), L.data());

		// generate K1 block
		galois_func(K2.data(), K1.data());
	}

	inline void cmac_pad_block(byte_t* output, const byte_t* input, size_t input_len)
	{
		// copy input to output
		size_t input_len_to_copy = std::min<size_t>(mBlockSize, input_len);
		memcpy(output, input, input_len_to_copy);

		// write padding 0x80 byte
		if (input_len_to_copy < kBlockSize)
		{
			output[input_len_to_copy] = 0x80;
		}

		// write padding trailing zeros
		for (size_t i = input_len_to_copy+1; i < kBlockSize; i++)
		{
			output[i] = 0x00;
		}
	}

	inline void galois_func(byte_t* output, const byte_t* input)
	{
		const tc::bn::be64<uint64_t>* input_u64 = (const tc::bn::be64<uint64_t>*)input;
		tc::bn::be64<uint64_t>* output_u64 = (tc::bn::be64<uint64_t>*)output;

		if (kBlockSize == 8)
		{
			uint64_t tmpA = input_u64[0].unwrap();

			// is MSB not set
			if ((tmpA >> 63) == 0)
			{
				tmpA = (tmpA << 1);
			}
			else
			{
				tmpA = (tmpA << 1) ^ kR64;
			}

			output_u64[0].wrap(tmpA);
		}
		else if (kBlockSize == 16)
		{
			uint64_t tmpA = input_u64[0].unwrap();
			uint64_t tmpB = input_u64[1].unwrap();

			// is MSB not set
			if ((tmpA >> 63) == 0)
			{
				tmpA = (tmpA << 1) | (tmpB >> 63);
				tmpB = (tmpB << 1);
			}
			else
			{
				tmpA = (tmpA << 1) | (tmpB >> 63);
				tmpB = (tmpB << 1) ^ kR128;
			}

			output_u64[0].wrap(tmpA);
			output_u64[1].wrap(tmpB);
		}
	}
	
	inline void update_cbc_mac(const byte_t* block)
	{
		xor_block<kBlockSize>(mMac.data(), mMac.data(), block);
		mCipher.encrypt(mMac.data(), mMac.data());
	}
};

}}} // namespace tc::crypto::detail