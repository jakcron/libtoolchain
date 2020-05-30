	/**
	 * @file Sha1Impl.h
	 * @brief Declaration of tc::crypto::detail::Sha1Impl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/05/28
	 **/
#pragma once

// include here
#include <tc/types.h>

namespace tc { namespace crypto { namespace detail {

class Sha1Impl
{
public:
	static const size_t kHashSize = 20;
	static const size_t kBlockSize = 64;

	Sha1Impl();
	~Sha1Impl();

	void initialize();
	void update(const byte_t* data, size_t data_size);
	void getHash(byte_t* hash);
private:
	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail