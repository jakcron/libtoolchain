#include <tc/crypto/detail/Sha1Impl.h>

#ifdef __APPLE__
#define _USE_COMMON_CRYPO
#endif

#ifdef _USE_COMMON_CRYPO
#include <CommonCrypto/CommonDigest.h>
#else
#include <mbedtls/md.h>
#endif

struct tc::crypto::detail::Sha1Impl::ImplCtx
{
#ifdef _USE_COMMON_CRYPO
	CC_SHA1_CTX mMdContext;
#else
	mbedtls_md_context_t mMdContext;
#endif
};

tc::crypto::detail::Sha1Impl::Sha1Impl() :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
#ifdef _USE_COMMON_CRYPO
	CC_SHA1_Init(&(mImplCtx->mMdContext));
#else
	mbedtls_md_init(&(mImplCtx->mMdContext));
	mbedtls_md_setup(&(mImplCtx->mMdContext), mbedtls_md_info_from_type(MBEDTLS_MD_SHA1), 0);
#endif
}

tc::crypto::detail::Sha1Impl::~Sha1Impl()
{
#ifdef _USE_COMMON_CRYPO
	CC_SHA1_Init(&(mImplCtx->mMdContext));
#else
	mbedtls_md_free(&(mImplCtx->mMdContext));
#endif
}

void tc::crypto::detail::Sha1Impl::initialize()
{
#ifdef _USE_COMMON_CRYPO
	CC_SHA1_Init(&(mImplCtx->mMdContext));
#else
	mbedtls_md_starts(&(mImplCtx->mMdContext));
#endif
	mState = State::Initialized;
}

void tc::crypto::detail::Sha1Impl::update(const byte_t* src, size_t src_size)
{
#ifdef _USE_COMMON_CRYPO
	CC_SHA1_Update(&(mImplCtx->mMdContext), src, src_size);
#else
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
#endif
}

void tc::crypto::detail::Sha1Impl::getHash(byte_t* hash)
{
	if (mState == State::Initialized)
	{
#ifdef _USE_COMMON_CRYPO
		CC_SHA1_Final(mHash.data(), &(mImplCtx->mMdContext));
#else
		mbedtls_md_finish(&(mImplCtx->mMdContext), mHash.data());
#endif
		mState = State::Done;
	}
	if (mState == State::Done)
	{
		memcpy(hash, mHash.data(), mHash.size());
	}
}