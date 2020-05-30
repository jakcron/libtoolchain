#include <tc/crypto/detail/Md5Impl.h>
#include <mbedtls/md.h>
#include <mbedtls/oid.h>

struct tc::crypto::detail::Md5Impl::ImplCtx
{
	mbedtls_md_context_t mMdContext;
};

tc::crypto::detail::Md5Impl::Md5Impl() :
	mImplCtx(new ImplCtx())
{
	mbedtls_md_init(&(mImplCtx->mMdContext));
	mbedtls_md_setup(&(mImplCtx->mMdContext), mbedtls_md_info_from_type(MBEDTLS_MD_MD5), 0);
}

tc::crypto::detail::Md5Impl::~Md5Impl()
{
	mbedtls_md_free(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Md5Impl::initialize()
{
	mbedtls_md_starts(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Md5Impl::update(const byte_t* src, size_t src_size)
{
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
}

void tc::crypto::detail::Md5Impl::getHash(byte_t* hash)
{
	mbedtls_md_finish(&(mImplCtx->mMdContext), hash);
}