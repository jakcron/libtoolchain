	/**
	 * @file TdesEncryptor.h
	 * @brief Declarations for API resources related to TDES block encryption.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2023/08/27
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/detail/TdesImpl.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace crypto {

	/**
	 * @class TdesEncryptor
	 * @brief Class for TDES encryption/decryption.
	 * 
	 * @tparam KeySize Size in bytes of the TDES encryption key. This must be 16 or 24.
	 * 
	 * @details
	 * This class has three states:
	 * - None : Not ready
	 * - Initialized : Ready to process data
	 * 
	 * General usage of this class is as follows:
	 * - Initialize TDES state with @ref initialize().
	 * - Encrypt or decrypt block(s) using @ref encrypt() or @ref decrypt().
	 */
template <size_t KeySize> 
class TdesEncryptor
{
public:
	static_assert(KeySize == 16 || KeySize == 24, "Unsupported TDES KeySize");

	static const size_t kKeySize   = KeySize; /**< TDES key size. */
	static const size_t kBlockSize = 8; /**< TDES processing block size. */

		/**
		 * @brief Default constructor.
		 * 
		 * @post
		 * - State is None. @ref initialize() must be called before use.
		 */
	TdesEncryptor() :
		mImpl()
	{}

		/**
		 * @brief Initialize TDES state with key.
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
		if (key_size != kKeySize) { throw tc::ArgumentOutOfRangeException("TdesEncryptor::initialize()", "key_size did not equal kKeySize."); }

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
	detail::TdesImpl mImpl;
};

	/**
	 * @typedef Tdes112Encryptor
	 * @brief Class for TDES-112 encryption/decryption.
	 */
using Tdes112Encryptor = TdesEncryptor<16>;

	/**
	 * @typedef Tdes168Encryptor
	 * @brief Class for TDES-168 encryption/decryption.
	 */
using Tdes168Encryptor = TdesEncryptor<24>;

}} // namespace tc::crypto