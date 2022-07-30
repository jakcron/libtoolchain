	/**
	 * @file CcmEncryptor.h
	 * @brief Declaration of tc::crypto::CcmEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/07/17
	 **/
#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>
#include <tc/crypto/detail/CcmModeImpl.h>

namespace tc { namespace crypto {

	/**
	 * @class CcmEncryptor
	 * @brief Class for CCM mode encryption/decryption.
	 * 
	 * @tparam BlockCipher The class that implements the block cipher used for CCM mode authenticated encryption/decryption.
	 * 
	 * @details
	 * Counter with CBC-MAC (CCM) mode is an authenticated block cipher. It is designed to be used with small discrete payloads, 
	 * encrypted/decrypted in one go.
	 * 
	 * This class is a template class that takes a block cipher implementation class as template parameter.
	 * See @ref Aes128CcmEncryptor or similar for supplied realizations of this template class.
	 * 
	 * The implementation of @a BlockCipher must satisfies the following conditions.
	 * See @ref AesEncryptor or similar class, for more information including parameters to each function.
	 * 
	 * -# Has a @p kBlockSize constant that defines the size of the block to process.
	 * -# Has a @p kKeySize constant that defines the required key size to initialize the block cipher.
	 * -# Has an @p initialize method that initializes the state of the block cipher.
	 * -# Has an @p encrypt method that encrypts a block of input data.
	 * -# Has a @p decrypt method that decrypts a block of input data.
	 * 
	 * This class has two states:
	 * - None : Not ready
	 * - Initialized : Ready to process data
	 * 
	 * General usage of this class is as follows:
	 * - Initialize CCM state with @ref initialize().
	 * - Encrypt or decrypt data using @ref encrypt() or @ref decrypt().
	 *   - When using @ref decrypt() you must compare the generated MAC with the expected one, alternatively you can use @ref decrypt_and_verify()
	 */
template <class BlockCipher>
class CcmEncryptor
{
public:
	static const size_t kKeySize   = BlockCipher::kKeySize; /**< CCM mode key size. */
	static const size_t kBlockSize = BlockCipher::kBlockSize; /**< CCM mode block processing size. */

		/**
		 * @brief Default constructor.
		 * 
		 * @post
		 * - State is None. @ref initialize() must be called before use.
		 */
	CcmEncryptor() :
		mImpl()
	{}

		/**
		 * @brief Initializes the CCM encryption state.
		 * 
		 * @param[in] key Pointer to key data.
		 * @param[in] key_size Size in bytes of key data.
		 * 
		 * @pre
		 * - @p key_size == @ref kKeySize.
		 * 
		 * @post
		 * - Instance is now in a Initialized state.
		 * 
		 * @details
		 * This resets the CCM state, initializing the key schedule and initialization vector.
		 * 
		 * @note
		 * - This must be called before performing encryption/decryption.
		 * 
		 * @throw tc::ArgumentNullException @p key was null.
		 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal kKeySize.
		 */
	void initialize(const byte_t* key, size_t key_size)
	{
		mImpl.initialize(key, key_size);
	}

		/**
		 * @brief Encrypt data.
		 * 
		 * @param[out] dst Buffer where encrypted data will be written.
		 * @param[in]  src Pointer to data to encrypt.
		 * @param[in]  size Size in bytes of data to encrypt.
		 * @param[in]  iv Pointer to initialization vector.
		 * @param[in]  iv_size Size in bytes of initialization vector.
		 * @param[in]  add Pointer to additional authentication data.
		 * @param[in]  add_size Size in bytes of additional authentication data.
		 * @param[out] tag Buffer where message authentication code will be written.
		 * @param[in]  tag_size Size in bytes of message authentication code.
		 * 
		 * @pre
		 * - @p size > 0. Maximum value for @p size depends on @p iv_size. 
		 *   -  Where @p iv_size == `7`  @p size <= `0xffffffffffffffff` (64bits).
		 *   -  Where @p iv_size == `8`  @p size <= `0xffffffffffffff` (56bits).
		 *   -  Where @p iv_size == `9`  @p size <= `0xffffffffffff` (48bits).
		 *   -  Where @p iv_size == `10` @p size <= `0xffffffffff` (40bits).
		 *   -  Where @p iv_size == `11` @p size <= `0xffffffff` (32bits).
		 *   -  Where @p iv_size == `12` @p size <= `0xffffff` (24bits).
		 *   -  Where @p iv_size == `13` @p size <= `0xffff` (16bits).
		 * - @p tag_size is 4, 6, 8, 10, 12, 14, or 16.
		 * - @p iv_size is between 7 and 13 inclusive.
		 * - @p add_size is between 0 and `0xff00`.
		 * 
		 * @post
		 * - Encrypted data is written to @p dst.
		 * - Message authentication code is written to @p tag.
		 * 
		 * @details
		 * This encrypts/signs the data in @p src, writing it to @p dst, and writing message authentication code to @p tag.
		 * 
		 * @note
		 * - @p dst and @p src can be the same pointer.
		 * 
		 * @throw tc::ArgumentNullException @p dst was null.
		 * @throw tc::ArgumentNullException @p src was null.
		 * @throw tc::ArgumentOutOfRangeException @p size was 0 or too large.
		 * @throw tc::ArgumentNullException @p iv was null when @p iv_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p iv_size was invalid.
		 * @throw tc::ArgumentNullException @p add was null when @p add_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p add_size was invalid.
		 * @throw tc::ArgumentNullException @p tag was null when @p tag_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p tag_size was invalid.
		 */
	void encrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
	{
		mImpl.encrypt(dst, src, size, iv, iv_size, add, add_size, tag, tag_size);
	}

		/**
		 * @brief Decrypt data.
		 * 
		 * @param[out] dst Buffer where decrypted data will be written.
		 * @param[in]  src Pointer to data to decrypt.
		 * @param[in]  size Size in bytes of data to encrypt.
		 * @param[in]  iv Pointer to initialization vector.
		 * @param[in]  iv_size Size in bytes of initialization vector.
		 * @param[in]  add Pointer to additional authentication data.
		 * @param[in]  add_size Size in bytes of additional authentication data.
		 * @param[out] tag Buffer where message authentication code will be written.
		 * @param[in]  tag_size Size in bytes of message authentication code.
		 * 
		 * @pre
		 * - @p size > 0. Maximum value for @p size depends on @p iv_size. 
		 *   -  Where @p iv_size == `7`  @p size <= `0xffffffffffffffff` (64bits).
		 *   -  Where @p iv_size == `8`  @p size <= `0xffffffffffffff` (56bits).
		 *   -  Where @p iv_size == `9`  @p size <= `0xffffffffffff` (48bits).
		 *   -  Where @p iv_size == `10` @p size <= `0xffffffffff` (40bits).
		 *   -  Where @p iv_size == `11` @p size <= `0xffffffff` (32bits).
		 *   -  Where @p iv_size == `12` @p size <= `0xffffff` (24bits).
		 *   -  Where @p iv_size == `13` @p size <= `0xffff` (16bits).
		 * - @p tag_size is 4, 6, 8, 10, 12, 14, or 16.
		 * - @p iv_size is between 7 and 13 inclusive.
		 * - @p add_size is between 0 and `0xff00`.
		 * 
		 * @post
		 * - Decrypted data is written to @p dst.
		 * - Message authentication code is written to @p tag.
		 * 
		 * @details
		 * This decrypts/signs the data in @p src, writing it to @p dst, and writing message authentication code to @p tag.
		 * 
		 * @note
		 * - @p dst and @p src can be the same pointer.
		 * 
		 * @throw tc::ArgumentNullException @p dst was null.
		 * @throw tc::ArgumentNullException @p src was null.
		 * @throw tc::ArgumentOutOfRangeException @p size was 0 or too large.
		 * @throw tc::ArgumentNullException @p iv was null when @p iv_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p iv_size was invalid.
		 * @throw tc::ArgumentNullException @p add was null when @p add_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p add_size was invalid.
		 * @throw tc::ArgumentNullException @p tag was null when @p tag_size was non-zero or vice versa.
		 * @throw tc::ArgumentOutOfRangeException @p tag_size was invalid.
		 */
	void decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
	{
		mImpl.decrypt(dst, src, size, iv, iv_size, add, add_size, tag, tag_size);
	}

		/**
		 * @brief Decrypt and authenticate data.
		 * 
		 * @param[out] dst Buffer where decrypted data will be written.
		 * @param[in]  src Pointer to data to decrypt.
		 * @param[in]  size Size in bytes of data to encrypt.
		 * @param[in]  iv Pointer to initialization vector.
		 * @param[in]  iv_size Size in bytes of initialization vector.
		 * @param[in]  add Pointer to additional authentication data.
		 * @param[in]  add_size Size in bytes of additional authentication data.
		 * @param[in]  tag Pointer to expected message authentication code.
		 * @param[in]  tag_size Size in bytes of message authentication code.
		 * 
		 * @pre
		 * - @p size > 0. Maximum value for @p size depends on @p iv_size. 
		 *   -  Where @p iv_size == `7`  @p size <= `0xffffffffffffffff` (64bits).
		 *   -  Where @p iv_size == `8`  @p size <= `0xffffffffffffff` (56bits).
		 *   -  Where @p iv_size == `9`  @p size <= `0xffffffffffff` (48bits).
		 *   -  Where @p iv_size == `10` @p size <= `0xffffffffff` (40bits).
		 *   -  Where @p iv_size == `11` @p size <= `0xffffffff` (32bits).
		 *   -  Where @p iv_size == `12` @p size <= `0xffffff` (24bits).
		 *   -  Where @p iv_size == `13` @p size <= `0xffff` (16bits).
		 * - @p tag_size is 4, 6, 8, 10, 12, 14, or 16.
		 * - @p iv_size is between 7 and 13 inclusive.
		 * - @p add_size is between 0 and `0xff00`.
		 * 
		 * @post
		 * - Decrypted data is written to @p dst.
		 * 
		 * @return `true` if decryption and authentication was successful, `false` if otherwise.
		 * 
		 * @details
		 * This decrypts/authenticates the data in @p src, writing it to @p dst.
		 * 
		 * @note
		 * - @p dst and @p src can be the same pointer.
		 */
	bool decrypt_and_verify(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, const byte_t* tag, size_t tag_size) noexcept
	{
		bool valid_data = false;

		try 
		{
			/* Check tag_size before allocating memory */
			if (tag_size <= 2 || tag_size > 16 || tag_size % 2 != 0)
			{
				throw tc::Exception();
			}

			tc::ByteData calc_tag = tc::ByteData(tag_size);
			
			mImpl.decrypt(dst, src, size, iv, iv_size, add, add_size, calc_tag.data(), calc_tag.size());

			if (memcmp(calc_tag.data(), tag, tag_size) != 0)
			{
				throw tc::Exception();
			}

			valid_data = true;
		}
		catch (...) 
		{
			valid_data = false;
		}

		return valid_data;
	}

private:
	detail::CcmModeImpl<BlockCipher> mImpl;
};

}} // namespace tc::crypto