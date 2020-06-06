	/**
	 * @file Pbkdf1Impl.h
	 * @brief Declaration of tc::crypto::detail::Pbkdf1Impl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/06/06
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/HmacGenerator.h>

#include <tc/crypto/CryptoException.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class Pbkdf1Impl
	 * @brief This class implements Password-Based Key Derivation Function 1 (PBKDF1)
	 * 
	 * @tparam HashFunction The class that implements the hash function used for key derivation.
	 * 
	 * @details
	 * PBKDF1 is a hash based key derivation function, as defined in RFC 8018.
	 * Applicable hash functions to use with PBKDF1 include.
	 * -# MD4
	 * -# MD5
	 * -# SHA-1
	 */
template <typename HashFunction>
class Pbkdf1Impl
{
public:
	static const size_t kMaxDerivableSize = HashFunction::kHashSize; /**< Maximum total data that can be derived */

	Pbkdf1Impl() :
		mState(State::None),
		mPassword(),
		mSalt(),
		mRoundCount(0),
		mHash(),
		mAvailableData(0),
		mTotalDataDerived(0)
	{
		std::memset(mDerivedData.data(), 0, mDerivedData.size());
	}

	~Pbkdf1Impl()
	{
		mState = State::None;
		std::memset(mPassword.data(), 0, mPassword.size());
		std::memset(mSalt.data(), 0, mSalt.size());
		std::memset(mDerivedData.data(), 0, mDerivedData.size());
		mRoundCount = 0;
		mAvailableData = 0;
		mTotalDataDerived = 0;
	}

	void initialize(const byte_t* password, size_t password_size, const byte_t* salt, size_t salt_size, size_t n_rounds)
	{
		if (n_rounds < 1) { throw tc::crypto::CryptoException("tc::crypto::detail::Pbkdf1Impl", "Round count must be >= 1."); }

		mPassword = tc::ByteData(password, password_size);
		mSalt = tc::ByteData(salt, salt_size);
		mRoundCount = n_rounds;
		mState = State::Initialized;
	}

	void getBytes(byte_t* out, size_t out_size)
	{
		if (mState != State::Initialized) return;

		// determine data remaining
		size_t derivable_data = kMaxDerivableSize - mTotalDataDerived + mAvailableData;

		if (out_size > derivable_data) { throw tc::crypto::CryptoException("tc::crypto::detail::Pbkdf1Impl", "Request too large."); }

		while (out_size != 0)
		{
			// if there is no availble data then we generate more
			if (mAvailableData == 0)
			{
				deriveBytes();

				// update the available digest to maximum
				mAvailableData = mDerivedData.size();

				mTotalDataDerived += mDerivedData.size();
			}

			// determine how much to copy in this loop
			size_t copy_size = std::min<size_t>(out_size, mAvailableData);

			// copy available data into out
			memcpy(out, mDerivedData.data() + mDerivedData.size() - mAvailableData, copy_size);

			// increment out pointer so next loop will copy to the right position
			out += copy_size;

			// decrement out_size so the next loop can track how much data is needed
			out_size -= copy_size;

			// decrement available digest so the next loop can determine where to copy from and generate more digest if needed
			mAvailableData -= copy_size;
		}
	}
private:
	enum State
	{
		None,
		Initialized
	};

	State mState;

	tc::ByteData mPassword;
	tc::ByteData mSalt;
	size_t mRoundCount;

	HashFunction mHash;
	std::array<byte_t, HashFunction::kHashSize> mDerivedData;
	size_t mAvailableData;
	size_t mTotalDataDerived;

	void deriveBytes()
	{
		// generate round 0 hash (password | salt)

		// init hash
		mHash.initialize();

		// Update Hash with password
		mHash.update(mPassword.data(), mPassword.size());

		// Update Hash with salt
		mHash.update(mSalt.data(), mSalt.size());

		// Save Hash
		mHash.getHash(mDerivedData.data());

		// do rounds 1 thru mRoundCount (prev round hash)
		for (size_t round = 1; round < mRoundCount; round++)
		{
			// initialise hash
			mHash.initialize();

			// update with previous round hash
			mHash.update(mDerivedData.data(), mDerivedData.size());

			// overwrite old hash digest with new hash digest
			mHash.getHash(mDerivedData.data());
		}
	}
};

}}} // namespace tc::crypto::detail