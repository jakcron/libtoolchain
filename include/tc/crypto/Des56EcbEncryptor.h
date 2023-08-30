	/**
	 * @file Des56EcbEncryptor.h
	 * @brief Declarations for API resources for related to DES56-ECB mode encryption/decryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2023/08/27
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/DesEncryptor.h>
#include <tc/crypto/EcbEncryptor.h>

namespace tc { namespace crypto {

	/**
	 * @typedef Des56EcbEncryptor
	 * @brief Class for DES-ECB encryption/decryption with a keysize of 56 bits (+ 8 parity bits = 64 bits).
	 * 
	 * @details This class encrypts/decrypts data using using DES56-ECB.
	 * For more information refer to @ref EcbEncryptor.
	 */
using Des56EcbEncryptor = EcbEncryptor<Des56Encryptor>;

	/**
	 * @brief Utility function for DES56-ECB encryption.
	 * 
	 * @param[out] dst Buffer where encrypted data will be written.
	 * @param[in]  src Pointer to data to encrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - @p size >= @ref Des56EcbEncryptor::kBlockSize.
	 * - @p key_size == @ref Des56EcbEncryptor::kKeySize.
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
	 * @throw tc::ArgumentOutOfRangeException @p size was less than @ref Des56EcbEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Des56EcbEncryptor::kKeySize.
	 */
void EncryptDes56Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size);

	/**
	 * @brief Utility function for DES56-ECB decryption.
	 * 
	 * @param[out] dst Buffer where decrypted data will be written.
	 * @param[in]  src Pointer to data to decrypt.
	 * @param[in]  size Size in bytes of data to decrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - @p size >= @ref Des56EcbEncryptor::kBlockSize.
	 * - @p key_size == @ref Des56EcbEncryptor::kKeySize.
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
	 * @throw tc::ArgumentOutOfRangeException @p size was less than @ref Des56EcbEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Des56EcbEncryptor::kKeySize.
	 */
void DecryptDes56Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size);

}} // namespace tc::crypto
