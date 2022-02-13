#include <tc/crypto/detail/PrbgImpl.h>

#ifdef __APPLE__
#define _USE_COMMON_CRYPO
#endif

#ifdef _USE_COMMON_CRYPO
#include <CommonCrypto/CommonRandom.h>
#else
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#endif

const std::string tc::crypto::detail::PrbgImpl::kClassName = "tc::crypto::detail::PrbgImpl";

struct tc::crypto::detail::PrbgImpl::ImplCtx
{
#ifdef _USE_COMMON_CRYPO

#else
	mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
#endif
};

tc::crypto::detail::PrbgImpl::PrbgImpl() :
	mImplCtx(new ImplCtx())
{
#ifdef _USE_COMMON_CRYPO

#else
	mbedtls_ctr_drbg_init(&(mImplCtx->ctr_drbg));
	mbedtls_entropy_init(&(mImplCtx->entropy));
	int ret = mbedtls_ctr_drbg_seed(&(mImplCtx->ctr_drbg), mbedtls_entropy_func, &(mImplCtx->entropy), (const unsigned char *)kClassName.c_str(), kClassName.size());
	switch (ret)
	{
		case (0):
			break;
		case (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED):
			throw tc::crypto::CryptoException(kClassName, "Entropy source failed");
		default:
			throw tc::crypto::CryptoException(kClassName, "An unexpected error occurred");
	}
#endif
}

tc::crypto::detail::PrbgImpl::~PrbgImpl()
{
#ifdef _USE_COMMON_CRYPO

#else
	mbedtls_ctr_drbg_free(&(mImplCtx->ctr_drbg));
	mbedtls_entropy_free(&(mImplCtx->entropy));
#endif
}

void tc::crypto::detail::PrbgImpl::getBytes(byte_t* data, size_t data_size)
{
#ifdef _USE_COMMON_CRYPO
	CCRNGStatus status = CCRandomGenerateBytes(data, data_size);
	switch (status)
	{
	case (kCCSuccess):
		//throw tc::crypto::CryptoException(kClassName, "Success");
		break;
	case (kCCParamError):
		throw tc::crypto::CryptoException(kClassName, "Illegal parameter value.");
		break;
	case (kCCBufferTooSmall):
		throw tc::crypto::CryptoException(kClassName, "Insufficent buffer provided for specified operation.");
		break;
	case (kCCMemoryFailure):
		throw tc::crypto::CryptoException(kClassName, "Memory allocation failure.");
		break;
	case (kCCAlignmentError):
		throw tc::crypto::CryptoException(kClassName, "Input size was not aligned properly.");
		break;
	case (kCCDecodeError):
		throw tc::crypto::CryptoException(kClassName, "Input data did not decode or decrypt properly.");
		break;
	case (kCCUnimplemented):
		throw tc::crypto::CryptoException(kClassName, "Function not implemented for the current algorithm.");
		break;
	case (kCCOverflow):
		throw tc::crypto::CryptoException(kClassName, "Overflow");
		break;
	case (kCCRNGFailure):
		throw tc::crypto::CryptoException(kClassName, "RNGFailure");
		break;
	case (kCCUnspecifiedError):
		throw tc::crypto::CryptoException(kClassName, "UnspecifiedError");
		break;
	case (kCCCallSequenceError):
		throw tc::crypto::CryptoException(kClassName, "CallSequenceError");
		break;
	case (kCCKeySizeError):
		throw tc::crypto::CryptoException(kClassName, "KeySizeError");
		break;
	}
#else
	int ret = mbedtls_ctr_drbg_random(&(mImplCtx->ctr_drbg), data, data_size);
	switch (ret)
	{
		case (0):
			break;
		case (MBEDTLS_ERR_CTR_DRBG_REQUEST_TOO_BIG):
			throw tc::crypto::CryptoException(kClassName, "Request too big");
		case (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED):
			throw tc::crypto::CryptoException(kClassName, "Entropy source failed");
		default:
			throw tc::crypto::CryptoException(kClassName, "An unexpected error occurred");
	}
#endif
}