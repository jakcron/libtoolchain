	/**
	 * @file RsaPkcs1Signer.h
	 * @brief Declaration of tc::crypto::RsaPkcs1Signer
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/09/12
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/detail/RsaImpl.h>
#include <tc/crypto/detail/RsaPkcs1Padding.h>
#include <tc/crypto/RsaKey.h>


namespace tc { namespace crypto {

	/**
	 * @class RsaPkcs1Signer
	 * @brief Class for calculating an RSA-PKCS1 signature.
	 * 
	 * @tparam HashFunction The class that implements the hash function used with RSA-PKCS1.
	 * 
	 * @details
	 * This class is a template class that takes a hash function implementation class as template parameter.
	 * See @ref Rsa2048Pkcs1Sha256Signer or similar for supplied realizations of this template class.
	 * 
	 * The implementation of <var>HashFunction</var> must satisfies the following conditions.
	 * See @ref Sha256Generator or similar class, for more information including parameters to each function.
	 * 
	 * -# Has a <tt>kAsn1OidDataSize</tt> constant that defines the size of the ASN.1 encoded OID for the hash algorithm
	 * -# Has a <tt>kAsn1OidData</tt> constant that defines the ASN.1 encoded OID for the hash algorithm
	 * -# Has a <tt>kBlockSize</tt> constant that defines the size of the block to process.
	 * -# Has a <tt>kHashSize</tt> constant that defines the output size of the hash value.
	 * -# Has an <tt>initialize</tt> method that begins processing.
	 * -# Has an <tt>update</tt> method that updates the hash value on input.
	 * -# Has a <tt>getHash</tt> method that gets the final hash value.
	 * 
	 * This class has two states:
	 * - None : Not ready
	 * - Initialized : Ready to process input data
	 * 
	 * General usage of this class is as follows:
	 * - Initialize RSA Signer state with @ref initialize().
	 * - Sign/Verify message digest with @ref sign() / @ref verify().
	 */
template <size_t KeySize, class HashFunction>
class RsaPkcs1Signer
{
public:

	static const size_t kSignatureSize = KeySize; /**< RSA-PKCS1 signature size */

		/**
		 * @brief Default constructor.
		 * 
		 * @post
		 * - State is None. @ref initialize() must be called before use.
		 */
	RsaPkcs1Signer() :
		mState(State::None),
		mRsaImpl(),
		mPadImpl()
	{}

		/**
		 * @brief Initializes the MAC calculation.
		 * 
		 * @param[in] key Pointer to key data.
		 * @param[in] key_size Size in bytes of key data.
		 * 
		 * @post
		 * - Instance is now in a Initialized state
		 * 
		 * @details
		 * Resets the MAC calculation state to the begin state.
		 * 
		 * @note
		 * - This must be called before calculating a new MAC.
		 */
	void initialize(const RsaKey& key)
	{
		mRsaImpl.initialize(KeySize << 3, key.n.data(), key.n.size(), nullptr, 0, nullptr, 0, key.d.data(), key.d.size(), key.e.data(), key.e.size());
		
		mState = State::Initialized;
	}
	
	void sign(byte_t* signature, const byte_t* hash)
	{
		if (mState != State::Initialized) return;

		std::array<byte_t, kSignatureSize> block;
		memset(block.data(), 0, block.size());

		auto res = mPadImpl.BuildPad(block.data(), block.size(), hash, HashFunction::kHashSize);
		
		switch (res)
		{
			case (detail::RsaPkcs1Padding<HashFunction>::Result::kSuccess):
				break;
			case (detail::RsaPkcs1Padding<HashFunction>::Result::kBlockSizeTooSmall):
				throw tc::crypto::CryptoException("tc::crypto::RsaPkcs1Signer::sign()","KeySize too small.");
			default:
				throw tc::crypto::CryptoException("tc::crypto::RsaPkcs1Signer::sign()","Unexpected error has occured.");
		}

		mRsaImpl.privateTransform(signature, block.data());		
	}

	bool verify(const byte_t* signature, const byte_t* hash)
	{
		if (mState != State::Initialized) return false;

		std::array<byte_t, kSignatureSize> block;
		memcpy(block.data(), signature, block.size());

		mRsaImpl.publicTransform(block.data(), signature);		

		auto res = mPadImpl.CheckPad(hash, HashFunction::kHashSize, block.data(), block.size());
		
		return (res == detail::RsaPkcs1Padding<HashFunction>::Result::kSuccess);
	}

private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	State mState;
	detail::RsaImpl mRsaImpl;
	detail::RsaPkcs1Padding<HashFunction> mPadImpl;
};

}} // namespace tc::crypto