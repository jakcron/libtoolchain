	/**
	 * @file Aes128EcbEncryptor.h
	 * @brief Declarations for API resources for related to AES128-ECB mode encryption/decryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/07/04
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/AesEncryptor.h>
#include <tc/crypto/EcbEncryptor.h>

namespace tc { namespace crypto {

	/**
	 * @typedef Aes128EcbEncryptor
	 * @brief Class for AES-ECB encryption/decryption with a keysize of 128 bits.
	 * 
	 * @details This class encrypts/decrypts data using using AES128-ECB.
	 * For more information refer to @ref EcbEncryptor.
	 */
using Aes128EcbEncryptor = EcbEncryptor<Aes128Encryptor>;

	/**
	 * @brief Utility function for AES128-ECB encryption.
	 * 
	 * @param[out] dst Buffer where encrypted data will be written.
	 * @param[in]  src Pointer to data to encrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - @p size >= @ref Aes128EcbEncryptor::kBlockSize.
	 * - @p key_size == @ref Aes128EcbEncryptor::kKeySize.
	 * 
	 * @post
	 * - Encrypted data is written to @p dst.
	 * 
	 * @details
	 * This encrypts the data in @p src, writing it to @p dst.
	 * 
	 * @note
	 * - @p dst and @p src can be the same pointer.
	 * 
	 * @throw tc::ArgumentNullException @p dst was null.
	 * @throw tc::ArgumentNullException @p src was null.
	 * @throw tc::ArgumentOutOfRangeException @p size was less than @ref Aes128EcbEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Aes128EcbEncryptor::kKeySize.
	 */
void EncryptAes128Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size);

	/**
	 * @brief Utility function for AES128-ECB decryption.
	 * 
	 * @param[out] dst Buffer where decrypted data will be written.
	 * @param[in]  src Pointer to data to decrypt.
	 * @param[in]  size Size in bytes of data to decrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - @p size >= @ref Aes128EcbEncryptor::kBlockSize.
	 * - @p key_size == @ref Aes128EcbEncryptor::kKeySize.
	 * 
	 * @post
	 * - Decrypted data is written to @p dst.
	 * 
	 * @details
	 * This decrypts the data in @p src, writing it to @p dst.
	 * 
	 * @note
	 * - @p dst and @p src can be the same pointer.
	 * 
	 * @throw tc::ArgumentNullException @p dst was null.
	 * @throw tc::ArgumentNullException @p src was null.
	 * @throw tc::ArgumentOutOfRangeException @p size was less than @ref Aes128EcbEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Aes128EcbEncryptor::kKeySize.
	 */
void DecryptAes128Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size);

}} // namespace tc::crypto
