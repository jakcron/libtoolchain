#include <tc/crypto/detail/HashImpl.h>
#include <tc/ByteData.h>
#include <mbedtls/md.h>
#include <mbedtls/md_internal.h>

struct tc::crypto::detail::HashImpl::ImplCtx
{
	mbedtls_md_context_t mMdContext;
	tc::ByteData mHash;
};

tc::crypto::detail::HashImpl::HashImpl(MdTypeId type_id) :
	mState(State::None),
	mImplCtx(new ImplCtx())
{
	// translate 
	mbedtls_md_type_t md_type = MBEDTLS_MD_NONE;
	switch (type_id)
	{
		case MD_MD5:
			md_type = MBEDTLS_MD_MD5;
			break;
		case MD_SHA1:
			md_type = MBEDTLS_MD_SHA1;
			break;
		case MD_SHA2_224:
			md_type = MBEDTLS_MD_SHA224;
			break;
		case MD_SHA2_256:
			md_type = MBEDTLS_MD_SHA256;
			break;
		case MD_SHA2_384:
			md_type = MBEDTLS_MD_SHA384;
			break;
		case MD_SHA2_512:
			md_type = MBEDTLS_MD_SHA512;
			break;
		default:
			throw tc::ArgumentOutOfRangeException("HashImpl::ctor()", "Unsupported md type.");
	}

	mbedtls_md_init(&(mImplCtx->mMdContext));
	mbedtls_md_setup(&(mImplCtx->mMdContext), mbedtls_md_info_from_type(md_type), 0);

	mImplCtx->mHash = tc::ByteData(this->hash_size());
}

tc::crypto::detail::HashImpl::~HashImpl()
{
	mbedtls_md_free(&(mImplCtx->mMdContext));
}

size_t tc::crypto::detail::HashImpl::hash_size() const
{
	return size_t(mImplCtx->mMdContext.md_info->size);
}

size_t  tc::crypto::detail::HashImpl::block_size() const
{
	return size_t(mImplCtx->mMdContext.md_info->block_size);
}

void tc::crypto::detail::HashImpl::start()
{
	mbedtls_md_starts(&(mImplCtx->mMdContext));
	mState = State::Initialized;
}

void tc::crypto::detail::HashImpl::update(const byte_t* src, size_t src_size)
{
	// state behaviour enforcement
	if (mState != State::Initialized) return;

	// input validatation
	if (src == nullptr && src_size != 0) { throw tc::ArgumentNullException("HashImpl::finish()", "src was null."); }

	// update md state
	mbedtls_md_update(&(mImplCtx->mMdContext), src, src_size);
}

void tc::crypto::detail::HashImpl::finish(byte_t* hash, size_t hash_size)
{
	// state behaviour enforcement
	if (mState != State::Initialized || mState != State::Done) return;

	// input validation
	if (hash == nullptr) { throw tc::ArgumentNullException("HashImpl::finish()", "hash was null."); }
	if (hash_size != this->hash_size()) { throw tc::ArgumentOutOfRangeException("HashImpl::finish()", "Incorrect hash_size."); }

	// finialize state if initialized
	if (mState == State::Initialized)
	{
		mbedtls_md_finish(&(mImplCtx->mMdContext), mImplCtx->mHash.data());
		mState = State::Done;
	}
	
	// export hash if complete
	if (mState == State::Done)
	{
		memcpy(hash, mImplCtx->mHash.data(), mImplCtx->mHash.size());
	}
}