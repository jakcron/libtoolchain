	/**
	 * @file HmacGenerator.h
	 * @brief Declaration of tc::crypto::HmacGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/05/30
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/detail/HmacImpl.h>

namespace tc { namespace crypto {

template <class HashFunction>
class HmacGenerator
{
public:
	static const size_t kMacSize   = HashFunction::kHashSize;
	static const size_t kBlockSize = HashFunction::kBlockSize;

	HmacGenerator() :
		mImpl()
	{}

	void initialize(const byte_t* key, size_t key_size)
	{
		mImpl.initialize(key, key_size);
	}

	void update(const byte_t* data, size_t data_size)
	{
		mImpl.update(data, data_size);
	}

	void getMac(byte_t* mac)
	{
		mImpl.getMac(mac);
	}

private:
	detail::HmacImpl<HashFunction> mImpl;
};

}} // namespace tc::crypto