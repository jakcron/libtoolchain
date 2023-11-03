#include <tc/crypto/detail/DesImpl.h>
#include <mbedtls/des.h>

struct tc::crypto::detail::DesImpl::ImplCtx
{
	mbedtls_des_context mEncContext;
	mbedtls_des_context mDecContext;
};

tc::crypto::detail::DesImpl::DesImpl() :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
	mbedtls_des_init(&(mImplCtx->mEncContext));
	mbedtls_des_init(&(mImplCtx->mDecContext));
}

tc::crypto::detail::DesImpl::~DesImpl()
{
	mbedtls_des_free(&(mImplCtx->mEncContext));
	mbedtls_des_free(&(mImplCtx->mDecContext));
}

void tc::crypto::detail::DesImpl::initialize(const byte_t* key, size_t key_size)
{
	if (key == nullptr) { throw tc::ArgumentNullException("DesImpl::initialize()", "key was null."); }
	if (key_size != 8) { throw tc::ArgumentOutOfRangeException("DesImpl::initialize()", "key_size did not equal 8."); }

	mbedtls_des_setkey_enc(&(mImplCtx->mEncContext), key);
	mbedtls_des_setkey_dec(&(mImplCtx->mDecContext), key);

	mState = State::Initialized;
}

void tc::crypto::detail::DesImpl::encrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("DesImpl::encrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("DesImpl::encrypt()", "src was null."); }

	mbedtls_des_crypt_ecb(&(mImplCtx->mEncContext), src, dst);
}

void tc::crypto::detail::DesImpl::decrypt(byte_t* dst, const byte_t* src)
{
	if (mState != State::Initialized) { return; }
	if (dst == nullptr) { throw tc::ArgumentNullException("DesImpl::decrypt()", "dst was null."); }
	if (src == nullptr) { throw tc::ArgumentNullException("DesImpl::decrypt()", "src was null."); }

	mbedtls_des_crypt_ecb(&(mImplCtx->mDecContext), src, dst);
}