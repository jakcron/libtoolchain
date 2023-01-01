#include <tc/crypto/detail/Sha2Impl.h>
#include <mbedtls/md.h>

struct tc::crypto::detail::Sha2Impl::ImplCtx
{
	mbedtls_md_context_t mMdContext;
};

tc::crypto::detail::Sha2Impl::Sha2Impl(size_t bitsize) :
	mState(State::None),
	mHashSize(0),
	mImplCtx(new ImplCtx())
{
	mbedtls_md_init(&(mImplCtx->mMdContext));

	const mbedtls_md_info_t* md_info = nullptr;
	switch(bitsize)
	{
		case (224):
			md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA224);
			break;
		case (256):
			md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
			break;
		case (384):
			md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA384);
			break;
		case (512):
			md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
			break;
		default:
			throw tc::crypto::CryptoException("tc::crypto::detail::Sha2Impl", "Invalid value for SHA2BitSize");
	}

	mHashSize = mbedtls_md_get_size(md_info);	
	mbedtls_md_setup(&(mImplCtx->mMdContext), md_info, 0);
}

tc::crypto::detail::Sha2Impl::~Sha2Impl()
{
	mbedtls_md_free(&(mImplCtx->mMdContext));
}

void tc::crypto::detail::Sha2Impl::initialize()
{
	mbedtls_md_starts(&(mImplCtx->mMdContext));
	mState = State::Initialized;
}

void tc::crypto::detail::Sha2Impl::update(const byte_t* src, size_t src_size)
{
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
}

void tc::crypto::detail::Sha2Impl::getHash(byte_t* hash)
{
	if (mState == State::Initialized)
	{
		mbedtls_md_finish(&(mImplCtx->mMdContext), mHash.data());
		mState = State::Done;
	}
	if (mState == State::Done)
	{
		memcpy(hash, mHash.data(), mHashSize);
	}	
}