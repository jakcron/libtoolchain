#include <tc/crypto/detail/Sha256Impl.h>
#include <mbedtls/md.h>
#include <mbedtls/oid.h>

struct tc::crypto::detail::Sha256Impl::ImplCtx
{
	mbedtls_md_context_t mMdContext;
};

tc::crypto::detail::Sha256Impl::~Sha256Impl()
{
	mbedtls_md_free(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Sha256Impl::initialize()
{
	mbedtls_md_starts(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Sha256Impl::update(const byte_t* src, size_t src_size)
{
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
}

void tc::crypto::detail::Sha256Impl::getHash(byte_t* hash)
{
	mbedtls_md_finish(&(mImplCtx->mMdContext), hash);
}