	/**
	 * @file Sha2Impl.h
	 * @brief Declaration of tc::crypto::detail::Sha2Impl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/02/27
	 **/
#pragma once
#include <tc/types.h>

#include <tc/crypto/CryptoException.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class Sha2Impl
	 * @brief This class implements the SHA2 family of hash algorithms.
	 * 
	 * @details 
	 * SHA2 unlike SHA1 is a family of hash algoritms:
	 * * SHA2-224 : HashSize 28 bytes (224 bit), BlockSize 64 bytes
	 * * SHA2-256 : HashSize 32 bytes (256 bit), BlockSize 64 bytes
	 * * SHA2-384 : HashSize 48 bytes (384 bit), BlockSize 128 bytes
	 * * SHA2-512 : HashSize 64 bytes (512 bit), BlockSize 128 bytes
	 */
class Sha2Impl
{
public:
		/**
		 * @brief Construct a new Sha2Impl object
		 * 
		 * @param bitsize Size in bits of the SHA2 hash
		 * 
		 * @pre
		 * - @p bitsize is 224, 256, 384, or 512.
		 * 
		 * @throws tc::crypto::CryptoException @p bitsize was invalid.
		 */
	Sha2Impl(size_t bitsize);
	~Sha2Impl();

	void initialize();
	void update(const byte_t* data, size_t data_size);
	void getHash(byte_t* hash);
private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	State mState;

	size_t mHashSize;
	static const size_t kMaxHashSize = 64;
	std::array<byte_t, kMaxHashSize> mHash;

	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail