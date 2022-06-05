	/**
	 * @file CcmModeImpl.h
	 * @brief Declaration of tc::crypto::detail::CcmModeImpl
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2020/10/04
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
		if (iv_size != 0 && iv == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "iv_size was non-zero, but iv was null."); }
		if (add_size != 0 && add == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "add_size was non-zero, but add was null."); }
		if (tag_size != 0 && tag == nullptr) { throw tc::ArgumentNullException("CcmModeImpl::encrypt()", "tag_size was non-zero, but iv was null."); }

		auto ctr = std::array<byte_t, kBlockSize>();
		auto block = std::array<byte_t, kBlockSize>();
		auto tag_tmp = std::array<byte_t, kBlockSize>();
    	byte_t q;


		/*
		 * Check length requirements: SP800-38C A.1
		 * Additional requirement: a < 2^16 - 2^8 to simplify the code.
		 * 'length' checked later (when writing it to the first block)
		 *
		 * Also, loosen the requirements to enable support for CCM* (IEEE 802.15.4).
		 */
		if (tag_size == 2 || tag_size > 16 || tag_size % 2 != 0)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "tag_size was not valid.");
		}

		/* Also implies q is within bounds */
		if (iv_size < 7 || iv_size > 13)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "iv_size was not valid.");
		}

		if (add_size > 0xFF00)
		{
			throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "add_size was not valid.");
		}
		
		// q is between 2 and 8
		q = 16 - 1 - (byte_t)iv_size;

		 /*
		 * First block B_0:
		 * 0        .. 0        flags
		 * 1        .. iv_len   nonce (aka iv)
		 * iv_len+1 .. 15       length
		 *
		 * With flags as (bits):
		 * 7        0
		 * 6        add present?
		 * 5 .. 3   (t - 2) / 2
		 * 2 .. 0   q - 1
		 */
		// encode flag into block
		block[0] = 0;
		block[0] |= ( add_size > 0 ) << 6;
		block[0] |= ( ( tag_len - 2 ) / 2 ) << 3;
		block[0] |= q - 1;

		// encode iv into block
		memcpy(block.data() + 1, iv, iv_size);

		// encoded payload size (big endian, in the free space as defined by q)
		{
			size_t size_encodable = size;
			for (size_t i = 0; i < q; i++, size_encodable >>= 8)
			{
				block[15-i] = (byte_t)(size_encodeable & 0xFF);
			}

			if (size_encodable != 0)
			{
				throw tc::ArgumentOutOfRangeException("CcmModeImpl::encrypt()", "size was too large.");
			}
		}

		 /* Start CBC-MAC with first block */
		memset(tag_tmp.data(), 0, tag_tmp.size());
		update_cbc_mac(block.data(), tag_tmp.data());

		/*
		 * If there is additional data, update CBC-MAC with
		 * add_size, add, 0 (padding to a block boundary)
		 */
		if (add_size > 0)
		{
			size_t use_size;
			size_t add_remaining_size = add_size;
			const byte_t* add_ptr = add;

			memset(block.data(), 0, 16);
			block[0] = (byte_t)( ( add_size >> 8 ) & 0xFF );
			block[1] = (byte_t)( ( add_size      ) & 0xFF );

			use_size = std::min<size_t>(add_remaining_size, 16 - 2);
			memcpy(block.data() + 2, add_ptr, use_size);
			add_remaining_size -= use_size;
			add_ptr += use_size;

			update_cbc_mac(block.data(), tag_tmp.data());

			while (add_remaining_size > 0)
			{
				use_size = std::min<size_t>(add_remaining_size, 16);

				memset(block.data(), 0, 16);
				memcpy(block.data(), add_ptr, use_size);
				
				update_cbc_mac(block.data(), tag_tmp.data());

				add_remaining_size -= use_size;
				add_ptr += use_size;
			}
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
		ctr[0] = q - 1;
		memcpy(ctr.data() + 1, iv, iv_len );
		memset(ctr.data() + 1 + iv_len, 0, q );
		ctr[15] = 1;


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

	//template <size_t BlockSize>
	inline void update_cbc_mac(const byte_t* block, byte_t* tag)
	{
		xor_block<kBlockSize>(tag, tag, block);
		mCipher.encrypt(tag, tag);
	}

	inline void ctr_crypt(byte_t* dst_block, const byte_t* src_block, size_t crypt_len)
	{
		// encrypt ctr to temp block
		mCipher.encrypt(mTempBlock.data(), mIv.data());

		// crypt block
		crypt_len = std::min<size_t>(crypt_len, kBlockSize);
		for (size_t i = 0; i < crypt_len; i++)
			dst_block[i] = src_block[i] ^ mTempBlock[i];
	}
};

}}} // namespace tc::crypto::detail