	/**
	 * @file HmacGeneratorImpl.h
	 * @brief Declaration of tc::crypto::HmacGeneratorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/14
	 **/
#pragma once

#include <tc/crypto/IMacGenerator.h>
#include <mbedtls/md.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <mbedtls_md_type_t HashType, size_t MacSize, size_t BlockSize>
class HmacGeneratorImpl : IMacGenerator
{
public:
	static const size_t kMacSize = MacSize;
	static const size_t kBlockSize = BlockSize;

	HmacGeneratorImpl()
	{
		mbedtls_md_init(&mMdContext);
		mbedtls_md_setup(&mMdContext, mbedtls_md_info_from_type(HashType), 1);
	}
	~HmacGeneratorImpl()
	{
		mbedtls_md_free(&mMdContext);
	}
	
	size_t GetMacSize() const { return kMacSize; }
	size_t GetBlockSize() const { return kBlockSize; }

	void Initialize(const byte_t* key, size_t key_size) { mbedtls_md_hmac_starts(&mMdContext, key, key_size); }
	void Update(const byte_t* data, size_t data_size) { mbedtls_md_hmac_update(&mMdContext, data, data_size); }
	void GetMac(byte_t* mac) { mbedtls_md_hmac_finish(&mMdContext, mac); }
private:
	mbedtls_md_context_t mMdContext;
};


}}} // namespace tc::crypto::mbedtls_detail