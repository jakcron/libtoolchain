	/**
	 * @file Aes128CcmEncryptor.h
	 * @brief Declarations for API resources for related to AES128-CCM mode encryption/decryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/07/04
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/AesEncryptor.h>
#include <tc/crypto/CcmEncryptor.h>

namespace tc { namespace crypto {

	/**
	 * @typedef Aes128CcmEncryptor
	 * @brief Class for AES-CCM encryption/decryption with a keysize of 128 bits.
	 * 
	 * @details This class encrypts/decrypts data using using AES128-CCM.
	 * For more information refer to @ref CcmEncryptor.
	 */
using Aes128CcmEncryptor = CcmEncryptor<Aes128Encryptor>;

	/**
	 * @brief Utility function for AES128-CCM encryption.
	 * 
	 * @param[out] dst Buffer where encrypted data will be written.
	 * @param[in]  src Pointer to data to encrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
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
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Aes128CcmEncryptor::kKeySize.
	 * @throw tc::ArgumentNullException @p iv was null when @p iv_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p iv_size was invalid.
	 * @throw tc::ArgumentNullException @p add was null when @p add_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p add_size was invalid.
	 * @throw tc::ArgumentNullException @p tag was null when @p tag_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p tag_size was invalid.
	 */
void EncryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size);

	/**
	 * @brief Utility function for AES128-CCM decryption.
	 * 
	 * @param[out] dst Buffer where decrypted data will be written.
	 * @param[in]  src Pointer to data to decrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * @param[in]  iv Pointer to initialization vector.
	 * @param[in]  iv_size Size in bytes of initialization vector.
	 * @param[in]  add Pointer to additional authentication data.
	 * @param[in]  add_size Size in bytes of additional authentication data.
	 * @param[out] tag Buffer where message authentication code will be written.
	 * @param[in]  tag_size Size in bytes of message authentication code.
	 * 
	 * @pre
	 * - @p key_size == @ref Aes128CcmEncryptor::kKeySize.
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
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Aes128CcmEncryptor::kKeySize.
	 * @throw tc::ArgumentNullException @p iv was null when @p iv_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p iv_size was invalid.
	 * @throw tc::ArgumentNullException @p add was null when @p add_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p add_size was invalid.
	 * @throw tc::ArgumentNullException @p tag was null when @p tag_size was non-zero or vice versa.
	 * @throw tc::ArgumentOutOfRangeException @p tag_size was invalid.
	 */
void DecryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size);

	/**
	 * @brief Utility function for AES128-CCM decryption and verification.
	 * 
	 * @param[out] dst Buffer where decrypted data will be written.
	 * @param[in]  src Pointer to data to decrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * @param[in]  iv Pointer to initialization vector.
	 * @param[in]  iv_size Size in bytes of initialization vector.
	 * @param[in]  add Pointer to additional authentication data.
	 * @param[in]  add_size Size in bytes of additional authentication data.
	 * @param[in]  tag Pointer to expected message authentication code.
	 * @param[in]  tag_size Size in bytes of message authentication code.
	 * 
	 * @pre
	 * - @p key_size == @ref Aes128CcmEncryptor::kKeySize.
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
bool DecryptVerifyAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, const byte_t* tag, size_t tag_size);

}} // namespace tc::crypto
