#include <tc/crypto/detail/AesImpl.h>

#ifdef __APPLE__
#define _USE_COMMON_CRYPO
#endif

#ifdef _USE_COMMON_CRYPO
#include <CommonCrypto/CommonCryptor.h>
#else
#include <mbedtls/aes.h>
#endif

struct tc::crypto::detail::AesImpl::ImplCtx
{
#ifdef _USE_COMMON_CRYPO
	CCCryptorRef mEncContext;
	CCCryptorRef mDecContext;
#else
	mbedtls_aes_context mEncContext;
	mbedtls_aes_context mDecContext;
#endif
};

tc::crypto::detail::AesImpl::AesImpl() :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
#ifdef _USE_COMMON_CRYPO
	
#else
	mbedtls_aes_init(&(mImplCtx->mEncContext));
	mbedtls_aes_init(&(mImplCtx->mDecContext));
#endif
}

tc::crypto::detail::AesImpl::~AesImpl()
{
#ifdef _USE_COMMON_CRYPO
	if (mImplCtx->mEncContext != nullptr) CCCryptorRelease(mImplCtx->mEncContext);
	if (mImplCtx->mDecContext != nullptr) CCCryptorRelease(mImplCtx->mDecContext);
#else
	mbedtls_aes_free(&(mImplCtx->mEncContext));
	mbedtls_aes_free(&(mImplCtx->mDecContext));
#endif
}

void tc::crypto::detail::AesImpl::initialize(const byte_t* key, size_t key_size)
{
	if (key == nullptr) { throw tc::ArgumentNullException("AesImpl::initialize()", "key was null."); }
	if (key_size != 16 && key_size != 24 && key_size != 32) { throw tc::ArgumentOutOfRangeException("AesImpl::initialize()", "key_size did not equal 16, 24 or 32."); }

#ifdef _USE_COMMON_CRYPO
	CCCryptorStatus enc_cryptor_status = CCCryptorCreate(kCCEncrypt, kCCAlgorithmAES, kCCOptionECBMode, key, key_size, nullptr, &(mImplCtx->mEncContext));
	CCCryptorStatus dec_cryptor_status = CCCryptorCreate(kCCDecrypt, kCCAlgorithmAES, kCCOptionECBMode, key, key_size, nullptr, &(mImplCtx->mDecContext));

	switch (enc_cryptor_status) {
		case (kCCSuccess) :
			break;
		case (kCCParamError) :
			throw tc::Exception("ParamError");
			break;
		case (kCCMemoryFailure) :
			throw tc::Exception("MemoryFailure");
			break;
		default:
			throw tc::Exception("");
			break;
	}
	switch (dec_cryptor_status) {
		case (kCCSuccess) :
			break;
		case (kCCParamError) :
			throw tc::Exception("ParamError");
			break;
		case (kCCMemoryFailure) :
			throw tc::Exception("MemoryFailure");
			break;
		default:
			throw tc::Exception("");
			break;
	}
#else
	mbedtls_aes_setkey_enc(&(mImplCtx->mEncContext), key, uint32_t(key_size) * 8);
	mbedtls_aes_setkey_dec(&(mImplCtx->mDecContext), key, uint32_t(key_size) * 8);
#endif

	mState = State::Initialized;
}

void tc::crypto::detail::AesImpl::encrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("AesImpl::encrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("AesImpl::encrypt()", "src was null."); }

#ifdef _USE_COMMON_CRYPO
	size_t data_moved = 0;
	CCCryptorStatus cryptor_status = CCCryptorUpdate(mImplCtx->mEncContext, src, 16, dst, 16, &data_moved);
	switch (cryptor_status) {
		case (kCCSuccess) :
			break;
		default:
			throw tc::Exception("");
			break;
	}
	if (data_moved != 16)
	{
		throw tc::Exception("");
	}
#else
	mbedtls_aes_crypt_ecb(&(mImplCtx->mEncContext), MBEDTLS_AES_ENCRYPT, src, dst);
#endif
}

void tc::crypto::detail::AesImpl::decrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("AesImpl::decrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("AesImpl::decrypt()", "src was null."); }

#ifdef _USE_COMMON_CRYPO
	size_t data_moved = 0;
	CCCryptorStatus cryptor_status = CCCryptorUpdate(mImplCtx->mDecContext, src, 16, dst, 16, &data_moved);
	switch (cryptor_status) {
		case (kCCSuccess) :
			break;
		default:
			throw tc::Exception("");
			break;
	}
	if (data_moved != 16)
	{
		throw tc::Exception("");
	}
#else
	mbedtls_aes_crypt_ecb(&(mImplCtx->mDecContext), MBEDTLS_AES_DECRYPT, src, dst);
#endif
}