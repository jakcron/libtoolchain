	/**
	 * @file Tdes168CbcEncryptor.h
	 * @brief Declarations for API resources for related to TDES168-CBC mode encryption/decryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2023/08/27
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/TdesEncryptor.h>
#include <tc/crypto/CbcEncryptor.h>

namespace tc { namespace crypto {

	/**
	 * @typedef Tdes168CbcEncryptor
	 * @brief Class for TDES-CBC encryption/decryption with a keysize of 168 bits (+ 24 parity bits = 192 bits).
	 * 
	 * @details This class encrypts/decrypts data using using TDES168-CBC.
	 * For more information refer to @ref CbcEncryptor.
	 */
using Tdes168CbcEncryptor = CbcEncryptor<Tdes168Encryptor>;

	/**
	 * @brief Utility function for TDES168-CBC encryption.
	 * 
	 * @param[out] dst Buffer where encrypted data will be written.
	 * @param[in]  src Pointer to data to encrypt.
	 * @param[in]  size Size in bytes of data to encrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * @param[in]  iv Pointer to initialization vector.
	 * @param[in]  iv_size Size in bytes of initialization vector.
	 * 
	 * @pre
	 * - @p size is a multiple of @ref Tdes168CbcEncryptor::kBlockSize.
	 * - @p key_size == @ref Tdes168CbcEncryptor::kKeySize.
	 * - @p iv_size == @ref Tdes168CbcEncryptor::kBlockSize.
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
	 * @throw tc::ArgumentOutOfRangeException @p size was not a multiple of @ref Tdes168CbcEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Tdes168CbcEncryptor::kKeySize.
	 * @throw tc::ArgumentNullException @p iv was null.
	 * @throw tc::ArgumentOutOfRangeException @p iv_size did not equal @ref Tdes168CbcEncryptor::kBlockSize.
	 */
void EncryptTdes168Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size);

	/**
	 * @brief Utility function for TDES168-CBC decryption.
	 * 
	 * @param[out] dst Buffer where decrypted data will be written.
	 * @param[in]  src Pointer to data to decrypt.
	 * @param[in]  size Size in bytes of data to decrypt.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * @param[in]  iv Pointer to initialization vector.
	 * @param[in]  iv_size Size in bytes of initialization vector.
	 * 
	 * @pre
	 * - @p size is a multiple of @ref Tdes168CbcEncryptor::kBlockSize.
	 * - @p key_size == @ref Tdes168CbcEncryptor::kKeySize.
	 * - @p iv_size == @ref Tdes168CbcEncryptor::kBlockSize.
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
	 * @throw tc::ArgumentOutOfRangeException @p size was not a multiple of @ref Tdes168CbcEncryptor::kBlockSize.
	 * @throw tc::ArgumentNullException @p key was null.
	 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref Tdes168CbcEncryptor::kKeySize.
	 * @throw tc::ArgumentNullException @p iv was null.
	 * @throw tc::ArgumentOutOfRangeException @p iv_size did not equal @ref Tdes168CbcEncryptor::kBlockSize.
	 */
void DecryptTdes168Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size);

}} // namespace tc::crypto
