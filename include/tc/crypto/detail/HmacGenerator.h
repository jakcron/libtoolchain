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
	static const size_t kMacSize = HashFunction::kHashSize;
	static const size_t kBlockSize = HashFunction::kBlockSize;

	HmacGenerator() :
		mState(State::None)
	{
	}
	~HmacGenerator()
	{
		memset(mKeyDigest, 0, kBlockSize);
		memset(mMac, 0, kMacSize);
		mState = State::None;	
	}

	size_t GetMacSize() const { return kMacSize; }
	size_t GetBlockSize() const { return kBlockSize; }

	void Initialize(const byte_t* key, size_t key_size);
	void Update(const byte_t* data, size_t data_size);
	void GetMac(byte_t* mac);
private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	HashFunction mHashFunction;
	byte_t mKeyDigest[kBlockSize];
	byte_t mMac[kMacSize];
	State mState;
};

template <typename HashFunction>
inline void HmacGenerator<HashFunction>::Initialize(const byte_t* key, size_t key_size)
{
	memset(mKeyDigest, 0x00, kBlockSize);

	if (key_size > kBlockSize)
	{
		mHashFunction.Initialize();
		mHashFunction.Update(key, key_size);
		mHashFunction.GetHash(mKeyDigest);
	}
	else
	{
		memcpy(mKeyDigest, key, key_size);
	}

	for (uint32_t i = 0 ; i < kBlockSize / sizeof(uint32_t); i++)
	{
		((uint32_t*)mKeyDigest)[i] ^= 0x36363636;
	}

	mHashFunction.Initialize();
	mHashFunction.Update(mKeyDigest, kBlockSize);

	mState = State::Initialized;
}

template <typename HashFunction>
inline void HmacGenerator<HashFunction>::Update(const byte_t* data, size_t data_size)
{
	mHashFunction.Update(data, data_size);
}

template <typename HashFunction>
inline void HmacGenerator<HashFunction>::GetMac(byte_t* mac)
{
	if (mState == State::Initialized)
	{
		mHashFunction.GetHash(mMac);

		for (uint32_t i = 0 ; i < kBlockSize / sizeof(uint32_t); i++)
		{
			((uint32_t*)mKeyDigest)[i] ^= 0x6A6A6A6A;
		}

		mHashFunction.Initialize();
		mHashFunction.Update(mKeyDigest, kBlockSize);
		mHashFunction.Update(mMac, kMacSize);
		mHashFunction.GetHash(mMac);

		mState = State::Done;
	}

	memcpy(mac, mMac, kMacSize);
}

}}} // namespace tc::crypto::detail