	/**
	 * @file HashGeneratorImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::HashGeneratorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IHashGenerator.h>
#include <mbedtls/md.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <mbedtls_md_type_t HashType, size_t HashSize, size_t BlockSize>
class HashGeneratorImpl : IHashGenerator
{
public:
	HashGeneratorImpl()
	{
		mbedtls_md_init(&mMdContext);
		mbedtls_md_setup(&mMdContext, mbedtls_md_info_from_type(HashType), 0);
	}
	~HashGeneratorImpl()
	{
		mbedtls_md_free(&mMdContext);
	}
	
	size_t hash_size() const { return kHashSize; }
	size_t block_size() const { return kBlockSize; }

	void initialize() { mbedtls_md_starts(&mMdContext); }
	void update(const byte_t* data, size_t data_size) { mbedtls_md_update(&mMdContext, data, data_size); }
	void getHash(byte_t* hash) { mbedtls_md_finish(&mMdContext, hash); }
private:
	static const size_t kHashSize = HashSize;
	static const size_t kBlockSize = BlockSize;
	mbedtls_md_context_t mMdContext;
};

}}} // namespace tc::crypto::mbedtls_detail