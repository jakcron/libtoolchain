#include <tc/crypto/detail/TdesImpl.h>
#include <mbedtls/des.h>

struct tc::crypto::detail::TdesImpl::ImplCtx
{
	mbedtls_des3_context mEncContext;
	mbedtls_des3_context mDecContext;
};

tc::crypto::detail::TdesImpl::TdesImpl() :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
	mbedtls_des3_init(&(mImplCtx->mEncContext));
	mbedtls_des3_init(&(mImplCtx->mDecContext));
}

tc::crypto::detail::TdesImpl::~TdesImpl()
{
	mbedtls_des3_free(&(mImplCtx->mEncContext));
	mbedtls_des3_free(&(mImplCtx->mDecContext));
}

void tc::crypto::detail::TdesImpl::initialize(const byte_t* key, size_t key_size)
{
	if (key == nullptr) { throw tc::ArgumentNullException("TdesImpl::initialize()", "key was null."); }
	if (key_size != 16 && key_size != 24) { throw tc::ArgumentOutOfRangeException("TdesImpl::initialize()", "key_size did not equal 16 or 24."); }

	if (key_size == 16)
	{
		mbedtls_des3_set2key_enc(&(mImplCtx->mEncContext), key);
		mbedtls_des3_set2key_dec(&(mImplCtx->mDecContext), key);
	}
	else if (key_size == 24)
	{
		mbedtls_des3_set3key_enc(&(mImplCtx->mEncContext), key);
		mbedtls_des3_set3key_dec(&(mImplCtx->mDecContext), key);
	} 

	mState = State::Initialized;
}

void tc::crypto::detail::TdesImpl::encrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("TdesImpl::encrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("TdesImpl::encrypt()", "src was null."); }

	mbedtls_des3_crypt_ecb(&(mImplCtx->mEncContext), src, dst);
}

void tc::crypto::detail::TdesImpl::decrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("TdesImpl::decrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("TdesImpl::decrypt()", "src was null."); }

	mbedtls_des3_crypt_ecb(&(mImplCtx->mDecContext), src, dst);
}