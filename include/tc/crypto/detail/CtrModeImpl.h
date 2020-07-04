	/**
	 * @file CtrModeImpl.h
	 * @brief Declaration of tc::crypto::detail::CtrModeImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/07/04
	 **/
#pragma once
#include <tc/types.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class CtrModeImpl
	 * @brief This class implements the CTR (<b>c</b>oun<b>t</b>e<b>r</b>) mode cipher as a template class.
	 * 
	 * @tparam BlockCipher The class that implements the block cipher used for CTR mode encryption/decryption.
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
class CtrModeImpl
{
public:
	static const size_t kKeySize = BlockCipher::kKeySize;
	static const size_t kBlockSize = BlockCipher::kBlockSize;

	CtrModeImpl() :
		mState(None),
		mCipher()
	{

	}

	void initialize(const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size) 
	{
		if (key == nullptr) { throw tc::ArgumentNullException("CtrModeImpl::initialize()", "key was null."); }
		if (key_size != kKeySize) { throw tc::ArgumentOutOfRangeException("CtrModeImpl::initialize()", "key_size did not equal kKeySize."); }
		if (iv == nullptr) { throw tc::ArgumentNullException("CtrModeImpl::initialize()", "iv was null."); }
		if (iv_size != kBlockSize) { throw tc::ArgumentOutOfRangeException("CtrModeImpl::initialize()", "iv_size did not equal kBlockSize."); }

		mCipher.initialize(key, key_size);
		memcpy(mIv.data(), iv, mIv.size());
		mState = State::Initialized;
	}

	void crypt(byte_t* dst, const byte_t* src, size_t size, uint64_t block_number)
	{
		if (mState != State::Initialized) { return ; }
		if (dst == nullptr) { throw tc::ArgumentNullException("CtrModeImpl::crypt()", "dst was null."); }
		if (src == nullptr) { throw tc::ArgumentNullException("CtrModeImpl::crypt()", "src was null."); }
		if (size == 0) { throw tc::ArgumentOutOfRangeException("CtrModeImpl::crypt()", "size was 0."); }

		auto iv = std::array<byte_t, kBlockSize>();
		auto enc_iv = std::array<byte_t, kBlockSize>();

		// import and increment iv
		memcpy(iv.data(), mIv.data(), mIv.size());
		incr_counter<kBlockSize>(iv.data(), block_number);

		// iterate through blocks
		for (size_t block_idx = 0, block_num = (size / kBlockSize); block_idx < block_num; block_idx++)
		{
			// encrypt IV
			mCipher.encrypt(enc_iv.data(), iv.data());

			// dst = src ^ enc_iv
			xor_block<kBlockSize>(dst + (block_idx * kBlockSize), src + (block_idx * kBlockSize), enc_iv.data());

			// increment counter
			incr_counter<kBlockSize>(iv.data(), 1);
		}

		// process partial block
		size_t block_remaining = (size % kBlockSize);
		if (block_remaining > 0)
		{
			// encrypt IV
			mCipher.encrypt(enc_iv.data(), iv.data());

			// dst = src ^ enc_iv
			for (size_t i = 0; i < block_remaining; i++)
			{
				dst[((size / kBlockSize) * kBlockSize) + i] = src[((size / kBlockSize) * kBlockSize) + i] ^ enc_iv[i];
			}
		}
	}
private:
	enum State
	{
		None,
		Initialized
	};

	State mState;
	
	BlockCipher mCipher;
	std::array<byte_t, kBlockSize> mIv;

	template <size_t BlockSize>
	inline void incr_counter(byte_t* counter, uint64_t incr)
	{
		for(uint64_t i = 0; i < incr; i++) {
			for (uint32_t j = kBlockSize; j > 0; j--) {
				// increment u8 by 1
				counter[j-1]++;

				// if it didn't overflow to 0, then we can exit now
				if (counter[j-1])
					break;

				// if we reach here, the next u8 needs to be incremented
				if (j == 1)
					j = kBlockSize;
			}
		}
	}

	template <>
	inline void incr_counter<16>(byte_t* counter, uint64_t incr)
	{
		be_uint64_t* counter_words = (be_uint64_t*)counter;

		uint64_t carry = incr;
		for (size_t i = 0; carry != 0 ; i = ((i + 1) % 2))
		{
			uint64_t word = counter_words[1 - i].unwrap();
			uint64_t remaining = std::numeric_limits<uint64_t>::max() - word;

			if (remaining > carry)
			{
				counter_words[1 - i].wrap(word + carry);
				carry = 0;
			}
			else
			{
				counter_words[1 - i].wrap(carry - remaining - 1);
				carry = 1;
			}
		}
	}

	template <size_t BlockSize>
	inline void xor_block(byte_t* dst, const byte_t* src_a, const byte_t* src_b)
	{
		for (size_t i = 0; i < BlockSize; i++) { dst[i] = src_a[i] ^ src_b[i];}
	}

	template <>
	inline void xor_block<16>(byte_t* dst, const byte_t* src_a, const byte_t* src_b)
	{
		((uint64_t*)dst)[0] = ((uint64_t*)src_a)[0] ^ ((uint64_t*)src_b)[0];
		((uint64_t*)dst)[1] = ((uint64_t*)src_a)[1] ^ ((uint64_t*)src_b)[1];
	}
};

}}} // namespace tc::crypto::detail