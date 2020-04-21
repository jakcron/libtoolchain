	/**
	 * @file HmacGenerator.h
	 * @brief Declaration of tc::crypto::detail::HmacGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/14
	 **/
#pragma once

#include <tc/crypto/IMacGenerator.h>

namespace tc { namespace crypto { namespace detail {

template <typename HashFunction>
class HmacGenerator : IMacGenerator
{
public:
	HmacGenerator() :
		mHashFunction(),
		mKeyDigest(kBlockSize),
		mMac(kMacSize),
		mState(State::None)
	{
	}
	~HmacGenerator()
	{
		memset(mKeyDigest.get(), 0, mKeyDigest.size());
		memset(mMac.get(), 0, mMac.size());
		mState = State::None;
	}

	size_t mac_size() const { return mMac.size(); }
	size_t block_size() const { return kBlockSize; }

	void initialize(const byte_t* key, size_t key_size)
	{
		memset(mKeyDigest.get(), 0x00, mKeyDigest.size());

		if (key_size > kBlockSize)
		{
			mHashFunction.initialize();
			mHashFunction.update(key, key_size);
			mHashFunction.getHash(mKeyDigest.get());
		}
		else
		{
			memcpy(mKeyDigest.get(), key, key_size);
		}

		for (uint32_t i = 0 ; i < kBlockSize / sizeof(uint32_t); i++)
		{
			((uint32_t*)mKeyDigest.get())[i] ^= 0x36363636;
		}

		mHashFunction.initialize();
		mHashFunction.update(mKeyDigest.get(), mKeyDigest.size());

		mState = State::Initialized;
	}

	void update(const byte_t* data, size_t data_size)
	{
		mHashFunction.update(data, data_size);
	}

	void getMac(byte_t* mac)
	{
		if (mState == State::Initialized)
		{
			mHashFunction.getHash(mMac.get());

			for (uint32_t i = 0 ; i < kBlockSize / sizeof(uint32_t); i++)
			{
				((uint32_t*)mKeyDigest.get())[i] ^= 0x6A6A6A6A;
			}

			mHashFunction.initialize();
			mHashFunction.update(mKeyDigest.get(), mKeyDigest.size());
			mHashFunction.update(mMac.get(), mMac.size());
			mHashFunction.getHash(mMac.get());

			mState = State::Done;
		}

		memcpy(mac, mMac.get(), mMac.size());
	}
private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	static const size_t kMacSize = HashFunction::kHashSize;
	static const size_t kBlockSize = HashFunction::kBlockSize;

	HashFunction mHashFunction;
	tc::ByteData mKeyDigest;
	tc::ByteData mMac;
	State mState;
};

}}} // namespace tc::crypto::detail