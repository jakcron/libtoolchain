#include <tc/crypto/mbedtls_detail/AesImpl.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>

template<>
tc::crypto::mbedtls_detail::AesImpl<16>::~AesImpl()
{
	mbedtls_aes_free(&mAesContext);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<16>::Initialize(const void* pKey, size_t keySize, bool isEncryptionKey)
{
	mbedtls_aes_init(&mAesContext);

	if (isEncryptionKey)
		mbedtls_aes_setkey_enc(&mAesContext, (const unsigned char*)pKey, 16 * 8);
	else
		mbedtls_aes_setkey_dec(&mAesContext, (const unsigned char*)pKey, 16 * 8);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<16>::EncryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_ENCRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<16>::DecryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_DECRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}

template<>
tc::crypto::mbedtls_detail::AesImpl<24>::~AesImpl()
{
	mbedtls_aes_free(&mAesContext);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<24>::Initialize(const void* pKey, size_t keySize, bool isEncryptionKey)
{
	mbedtls_aes_init(&mAesContext);

	if (isEncryptionKey)
		mbedtls_aes_setkey_enc(&mAesContext, (const unsigned char*)pKey, 24 * 8);
	else
		mbedtls_aes_setkey_dec(&mAesContext, (const unsigned char*)pKey, 24 * 8);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<24>::EncryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_ENCRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<24>::DecryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_DECRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}

template<>
tc::crypto::mbedtls_detail::AesImpl<32>::~AesImpl()
{
	mbedtls_aes_free(&mAesContext);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<32>::Initialize(const void* pKey, size_t keySize, bool isEncryptionKey)
{
	mbedtls_aes_init(&mAesContext);

	if (isEncryptionKey)
		mbedtls_aes_setkey_enc(&mAesContext, (const unsigned char*)pKey, 32 * 8);
	else
		mbedtls_aes_setkey_dec(&mAesContext, (const unsigned char*)pKey, 32 * 8);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<32>::EncryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_ENCRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}

template<>
void tc::crypto::mbedtls_detail::AesImpl<32>::DecryptBlock(void* pDst, size_t dstSize, const void* pSrc, size_t srcSize)
{
	mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_DECRYPT, (const unsigned char*)pSrc, (unsigned char*)pDst);
}