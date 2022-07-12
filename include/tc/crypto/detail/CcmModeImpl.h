	/**
	 * @file CcmModeImpl.h
	 * @brief Declaration of tc::crypto::detail::CcmModeImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/07/12
	 **/
#pragma once
#include <tc/types.h>

#include <tc/crypto/detail/BlockUtilImpl.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class CcmModeImpl
	 * @brief This class implements the CCM (<b>C</b>ounter with <b>C</b>BC-<b>M</b>AC) mode cipher as a template class.
	 * 
	 * @tparam BlockCipher The class that implements the block cipher used for CCM mode encryption/decryption.
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
class CcmModeImpl
{
public:
	static_assert(BlockCipher::kBlockSize == 16, "CcmModeImpl only supports BlockCiphers with block size 16.");

	static const size_t kKeySize = BlockCipher::kKeySize;
	static const size_t kBlockSize = BlockCipher::kBlockSize;

	CcmModeImpl() :
		mState(None),
		mCipher()
	{

	}

	void initialize(const byte_t* key, size_t key_size) 
	{
		if (key == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::initialize()", "key was null."); }
		if (key_size != kKeySize) { throw tc::ArgumentOutOfRangeException("CcmModeImpl::initialize()", "key_size did not equal kKeySize."); }
		
		mCipher.initialize(key, key_size);
		mState = State::Initialized;
	}

	void encrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
	{
		if (mState != State::Initialized) { return ; }
		if (dst == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "dst was null."); }
		if (src == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "src was null."); }
		if (size == 0) { throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "size was 0."); }
		if (iv_size == 0 != iv == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "iv_size was non-zero, when iv was null. Or vice versa."); }
		if (add_size == 0 != add == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "add_size was non-zero, when add was null. Or vice versa."); }
		if (tag_size == 0 != tag == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "tag_size was non-zero, when iv was null. Or vice versa."); }

		/* Declare temp variables */
		auto ctr = std::array<byte_t, kBlockSize>();
		auto enc_ctr = std::array<byte_t, kBlockSize>();
		auto block = std::array<byte_t, kBlockSize>();
		auto tag_tmp = std::array<byte_t, kBlockSize>();

		/* Check tag_size */
		if (tag_size <= 2 || tag_size > 16 || tag_size % 2 != 0)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "tag_size was not valid.");
		}

		/* Check iv_size (Also implies q is within bounds) */
		if (iv_size < 7 || iv_size > 13)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "iv_size was not valid.");
		}

		/* Check add_size */
		if (add_size > 0xFF00)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "add_size was too large.");
		}
		
		/* Determine if payload size can be encoded given length of iv */
		if (size > calculate_max_encodable_payload(iv_size))
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "size was too large.");
		}

		/* Generate first block for CBC-MAC */
		create_tag_block0(block.data(), iv, iv_size, add_size, tag_size, size);

		/* Start CBC-MAC with first block */
		memset(tag_tmp.data(), 0, tag_tmp.size());
		update_cbc_mac(block.data(), tag_tmp.data());

		/* Update CBC-MAC with additional data if present */
		if (add_size > 0)
		{
			update_cbc_mac_with_add(tag_tmp.data(), add, add_size);
		}

		/*
		 * Prepare counter block for encryption:
		 * 0        .. 0        flags
		 * 1        .. iv_len   nonce (aka iv)
		 * iv_len+1 .. 15       counter (initially 1)
		 *
		 * With flags as (bits):
		 * 7 .. 3   0
		 * 2 .. 0   q - 1
		 */
		{
			ctr[0] = q - 1;
			memcpy(ctr.data() + 1, iv, iv_len );
			memset(ctr.data() + 1 + iv_len, 0, q );
			ctr[15] = 1;
		}

		/* Iterate through blocks */
		for (size_t block_idx = 0, block_num = (size / kBlockSize); block_idx < block_num; block_idx++)
		{
			/* Update CBC-MAC with data block */
			memcpy(block.data(), src + (block_idx * kBlockSize), kBlockSize);
			update_cbc_mac(block.data(), tag_tmp.data());

			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR src block with encrypted block counter (dst = src ^ enc_ctr) */
			xor_block<kBlockSize>(dst + (block_idx * kBlockSize), src + (block_idx * kBlockSize), enc_ctr.data());

			/* Increment block counter */
			incr_counter<kBlockSize>(ctr.data(), 1);
		}

		/* Process partial block */
		size_t block_remaining = (size % kBlockSize);
		if (block_remaining > 0)
		{
			/* Update CBC-MAC with partial data block */
			memset(block.data(), 0, kBlockSize);
			memcpy(block.data(), src + (block_idx * kBlockSize), kBlockSize);
			update_cbc_mac(block.data(), tag_tmp.data());

			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR src block with encrypted block counter (dst = src ^ enc_ctr) */
			for (size_t i = 0; i < block_remaining; i++)
			{
				dst[((size / kBlockSize) * kBlockSize) + i] = src[((size / kBlockSize) * kBlockSize) + i] ^ enc_ctr[i];
			}
		}

		/* Finialise CBC-MAC */
		{
			/* Clear Block Counter */
			memset(ctr.data(), 0, kBlockSize);

			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR CBC-MAC with encrypted block counter */
			xor_block<kBlockSize>(tmp_tag.data(), tmp_tag.data(), enc_ctr.data());
		}
		

		/* Write CBC-MAC to output */
		memcpy(tag, tmp_tag.data(), tag_size);
	}

	void decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
	{
		if (mState != State::Initialized) { return ; }
		if (dst == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::decrypt()", "dst was null."); }
		if (src == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::decrypt()", "src was null."); }
		if (size == 0) { throw tc::ArgumentOutOfRangeException("CcmModeImpl::decrypt()", "size was 0."); }
		if (iv_size == 0 != iv == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::decrypt()", "iv_size was non-zero, when iv was null. Or vice versa."); }
		if (add_size == 0 != add == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::decrypt()", "add_size was non-zero, when add was null. Or vice versa."); }
		if (tag_size == 0 != tag == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::decrypt()", "tag_size was non-zero, when iv was null. Or vice versa."); }

		/* Declare temp variables */
		auto ctr = std::array<byte_t, kBlockSize>();
		auto enc_ctr = std::array<byte_t, kBlockSize>();
		auto block = std::array<byte_t, kBlockSize>();
		auto tag_tmp = std::array<byte_t, kBlockSize>();

		/* Check tag_size */
		if (tag_size <= 2 || tag_size > 16 || tag_size % 2 != 0)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "tag_size was not valid.");
		}

		/* Check iv_size (Also implies q is within bounds) */
		if (iv_size < 7 || iv_size > 13)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "iv_size was not valid.");
		}

		/* Check add_size */
		if (add_size > 0xFF00)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "add_size was too large.");
		}
		
		/* Determine if payload size can be encoded given length of iv */
		if (size > calculate_max_encodable_payload(iv_size))
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "size was too large.");
		}

		/* Generate first block for CBC-MAC */
		create_tag_block0(block.data(), iv, iv_size, add_size, tag_size, size);

		/* Start CBC-MAC with first block */
		memset(tag_tmp.data(), 0, tag_tmp.size());
		update_cbc_mac(block.data(), tag_tmp.data());

		/* Update CBC-MAC with additional data if present */
		if (add_size > 0)
		{
			update_cbc_mac_with_add(tag_tmp.data(), add, add_size);
		}

		/*
		 * Prepare counter block for encryption:
		 * 0        .. 0        flags
		 * 1        .. iv_len   nonce (aka iv)
		 * iv_len+1 .. 15       counter (initially 1)
		 *
		 * With flags as (bits):
		 * 7 .. 3   0
		 * 2 .. 0   q - 1
		 */
		{
			ctr[0] = q - 1;
			memcpy(ctr.data() + 1, iv, iv_len );
			memset(ctr.data() + 1 + iv_len, 0, q );
			ctr[15] = 1;
		}

		/* Iterate through blocks */
		for (size_t block_idx = 0, block_num = (size / kBlockSize); block_idx < block_num; block_idx++)
		{
			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR src block with encrypted block counter (dst = src ^ enc_ctr) */
			xor_block<kBlockSize>(dst + (block_idx * kBlockSize), src + (block_idx * kBlockSize), enc_ctr.data());

			/* Update CBC-MAC with decrypted data block */
			memcpy(block.data(), dst + (block_idx * kBlockSize), kBlockSize);
			update_cbc_mac(block.data(), tag_tmp.data());

			/* Increment block counter */
			incr_counter<kBlockSize>(ctr.data(), 1);
		}

		/* Process partial block */
		size_t block_remaining = (size % kBlockSize);
		if (block_remaining > 0)
		{
			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR src block with encrypted block counter (dst = src ^ enc_ctr) */
			for (size_t i = 0; i < block_remaining; i++)
			{
				dst[((size / kBlockSize) * kBlockSize) + i] = src[((size / kBlockSize) * kBlockSize) + i] ^ enc_ctr[i];
			}

			/* Update CBC-MAC with partial decrypted data block */
			memset(block.data(), 0, kBlockSize);
			memcpy(block.data(), dst + (block_idx * kBlockSize), kBlockSize);
			update_cbc_mac(block.data(), tag_tmp.data());
		}

		/* Finialise CBC-MAC */
		{
			/* Clear Block Counter */
			memset(ctr.data(), 0, kBlockSize);

			/* Encrypt block counter */
			mCipher.encrypt(enc_ctr.data(), ctr.data());

			/* XOR CBC-MAC with encrypted block counter */
			xor_block<kBlockSize>(tmp_tag.data(), tmp_tag.data(), enc_ctr.data());
		}
		

		/* Write CBC-MAC to output */
		memcpy(tag, tmp_tag.data(), tag_size);
	}
private:
	enum State
	{
		None,
		Initialized
	};

	State mState;
	
	BlockCipher mCipher;
	std::array<byte_t, kBlockSize> mTag;
	std::array<byte_t, kBlockSize> mIv;

	inline size_t calculate_q(size_t iv_size)
	{
		return kBlockSize - sizeof(byte_t) - iv_size;
	}

	inline size_t calculate_max_encodable_payload(size_t iv_size)
	{
		return (((size_t)1) << (calculate_q(iv_size) * 8)) - 1;
	}

	inline void create_tag_block0(const byte_t* block, const byte_t* iv, size_t iv_size, size_t add_size, size_t tag_size, size_t payload_size)
	{
		/*
		 * First block B_0:
		 * 0         .. 0        flags
		 * 1         .. iv_size  nonce (aka iv)
		 * iv_size+1 .. 15       payload_size
		 *
		 * With flags as (bits):
		 * 7        0
		 * 6        add present?
		 * 5 .. 3   (t - 2) / 2
		 * 2 .. 0   q - 1
		 */

		size_t q = calculate_q(iv_size);
		
		// encode flag into block
		block[0] = 0;
		//block[0] |= (0 & 1)                    << 7;
		block[0] |= ((add_size != 0) & 1)      << 6;
		block[0] |= (((tag_size - 2) / 2) & 7) << 3;
		block[0] |= ((q - 1) & 7)              << 0;

		// encode iv into block
		memcpy(block + 1, iv, iv_size);

		// encoded payload size (big endian, in the free space as defined by q)
		{
			size_t size_encodable = payload_size;
			for (size_t i = 0; i < q; i++, size_encodable >>= 8)
			{
				block[kBlockSize - 1 - i] = (byte_t)(size_encodeable & 0xFF);
			}
		}
	}

	inline void update_cbc_mac_with_add(byte_t* tag, const byte_t* add, size_t add_size)
	{
		/*
		 * If there is additional data, update CBC-MAC with
		 * add_size, add, 0 (padding to a block boundary)
		 */
		auto block = std::array<byte_t, kBlockSize>();
		if (add_size > 0)
		{
			size_t use_size;
			size_t add_pos = 0;
			const byte_t* add_ptr = add;

			memset(block.data(), 0, block.size());
			block[0] = (byte_t)( ( add_size >> 8 ) & 0xFF );
			block[1] = (byte_t)( ( add_size      ) & 0xFF );

			use_size = std::min<size_t>(add_size - add_pos, block.size() - 2);
			memcpy(block.data() + 2, add + add_pos, use_size);
			add_pos += use_size;

			update_cbc_mac(block.data(), tag);

			while (add_pos < add_size)
			{
				use_size = std::min<size_t>(add_size - add_pos, block.size());

				memset(block.data(), 0, block.size());
				memcpy(block.data(), add + add_pos, use_size);
				
				update_cbc_mac(block.data(), tag);

				add_pos += use_size;
			}
		}
	}

	//template <size_t BlockSize>
	inline void update_cbc_mac(const byte_t* block, byte_t* tag)
	{
		xor_block<kBlockSize>(tag, tag, block);
		mCipher.encrypt(tag, tag);
	}
};

}}} // namespace tc::crypto::detail