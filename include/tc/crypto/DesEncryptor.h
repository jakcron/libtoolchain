	/**
	 * @file DesEncryptor.h
	 * @brief Declarations for API resources related to DES block encryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2023/08/27
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/detail/DesImpl.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace crypto {

	/**
	 * @class DesEncryptor
	 * @brief Class for DES encryption/decryption.
	 * 
	 * @tparam KeySize Size in bytes of the DES encryption key. This must be 8.
	 * 
	 * @details
	 * This class has three states:
	 * - None : Not ready
	 * - Initialized : Ready to process data
	 * 
	 * General usage of this class is as follows:
	 * - Initialize DES state with @ref initialize().
	 * - Encrypt or decrypt block(s) using @ref encrypt() or @ref decrypt().
	 */
template <size_t KeySize> 
class DesEncryptor
{
public:
	static_assert(KeySize == 8, "Unsupported DES KeySize");

	static const size_t kKeySize   = KeySize; /**< DES key size. */
	static const size_t kBlockSize = 8; /**< DES processing block size. */

		/**
		 * @brief Default constructor.
		 * 
		 * @post
		 * - State is None. @ref initialize() must be called before use.
		 */
	DesEncryptor() :
		mImpl()
	{}

		/**
		 * @brief Initialize DES state with key.
		 * 
		 * @param[in] key Pointer to key data.
		 * @param[in] key_size Size in bytes of key data.
		 * 
		 * @pre 
		 * - @p key_size == @ref kKeySize.
		 * @post
		 * - Instance is now in initialized state.
		 * 
		 * @throw tc::ArgumentNullException @p key was null.
		 * @throw tc::ArgumentOutOfRangeException @p key_size did not equal @ref kKeySize.
		 */
	void initialize(const byte_t* key, size_t key_size)
	{
		if (key_size != kKeySize) { throw tc::ArgumentOutOfRangeException("DesEncryptor::initialize()", "key_size did not equal kKeySize."); }

		mImpl.initialize(key, key_size);
	}

		/**
		 * @brief Encrypt data block.
		 * 
		 * @param[out] dst Buffer to store encrypted block.
		 * @param[in]  src Pointer to block to encrypt.
		 * 
		 * @pre 
		 * - Instance is in initialized state.
		 * 
		 * @details
		 * This encrypts @ref kBlockSize number of bytes of data from @p src, writing it to @p dst.
		 * 
		 * @note 
		 *  - @p dst and @p src can be the same pointer.
		 * 
		 * @throw tc::ArgumentNullException @p dst was null.
		 * @throw tc::ArgumentNullException @p src was null.
		 */
	void encrypt(byte_t* dst, const byte_t* src)
	{
		mImpl.encrypt(dst, src);
	}

		/**
		 * @brief Decrypt data block.
		 * 
		 * @param[out] dst Buffer to store decrypted block.
		 * @param[in]  src Pointer to block to decrypt.
		 * 
		 * @pre 
		 * - Instance is in initialized state.
		 * 
		 * @details
		 * This decrypts @ref kBlockSize number of bytes of data from @p src, writing it to @p dst.
		 * 
		 * @note 
		 *  - @p dst and @p src can be the same pointer.
		 * 
		 * @throw tc::ArgumentNullException @p dst was null.
		 * @throw tc::ArgumentNullException @p src was null.
		 */
	void decrypt(byte_t* dst, const byte_t* src)
	{
		mImpl.decrypt(dst, src);
	}

private:
	detail::DesImpl mImpl;
};

	/**
	 * @typedef Des56Encryptor
	 * @brief Class for DES-56 encryption/decryption.
	 */
using Des56Encryptor = DesEncryptor<8>;

}} // namespace tc::crypto