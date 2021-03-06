#include <tc/crypto/detail/Sha512Impl.h>
#include <mbedtls/md.h>

struct tc::crypto::detail::Sha512Impl::ImplCtx
{
	mbedtls_md_context_t mMdContext;
};

tc::crypto::detail::Sha512Impl::Sha512Impl() :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
	mbedtls_md_init(&(mImplCtx->mMdContext));
	mbedtls_md_setup(&(mImplCtx->mMdContext), mbedtls_md_info_from_type(MBEDTLS_MD_SHA512), 0);
}

tc::crypto::detail::Sha512Impl::~Sha512Impl()
{
	mbedtls_md_free(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Sha512Impl::initialize()
{
	mbedtls_md_starts(&(mImplCtx->mMdContext));
	mState = State::Initialized;
}

void tc::crypto::detail::Sha512Impl::update(const byte_t* src, size_t src_size)
{
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
}

void tc::crypto::detail::Sha512Impl::getHash(byte_t* hash)
{
	if (mState == State::Initialized)
	{
		mbedtls_md_finish(&(mImplCtx->mMdContext), mHash.data());
		mState = State::Done;
	}
	if (mState == State::Done)
	{
		memcpy(hash, mHash.data(), mHash.size());
	}
}