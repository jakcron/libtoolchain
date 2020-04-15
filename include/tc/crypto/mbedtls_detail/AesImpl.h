	/**
	 * @file AesImpl.h
	 * @brief Declaration of tc::crypto::AesImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/14
	 **/
#pragma once

#include <tc/types.h>
#include <mbedtls/aes.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <size_t KeySize>
class AesImpl
{
public:
	static const size_t kBlockSize = 16;

	~AesImpl();
	void Initialize(const void* pKey, size_t keySize, bool isEncryptionKey);
	void EncryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize);
	void DecryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize);
private:
	mbedtls_aes_context mAesContext;
};

}}} // namespace tc::crypto::mbedtls_detail