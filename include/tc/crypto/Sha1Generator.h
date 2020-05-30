	/**
	 * @file Sha1Generator.h
	 * @brief Declaration of tc::crypto::Sha1Generator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/05/30
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/detail/Sha1Impl.h>

namespace tc { namespace crypto {

class Sha1Generator
{
public:
	static const size_t kAsn1OidDataSize = 5;
	static const std::array<byte_t, kAsn1OidDataSize> kAsn1OidData;

	static const size_t kHashSize  = 20;
	static const size_t kBlockSize = 64;

	Sha1Generator() :
		mImpl()
	{}

	void initialize()
	{
		mImpl.initialize();
	}

	void update(const byte_t* data, size_t data_size)
	{
		mImpl.update(data, data_size);
	}

	void getHash(byte_t* hash)
	{
		mImpl.getHash(hash);
	}

private:
	detail::Sha1Impl mImpl;
};

void GenerateSha1Hash(byte_t* hash, 
                      const byte_t* data, size_t data_size);

}} // namespace tc::crypto