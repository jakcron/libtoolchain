	/**
	 * @file Sha256Impl.h
	 * @brief Declaration of tc::crypto::detail::Sha256Impl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/05/28
	 **/
#pragma once

// include here
#include <tc/types.h>

namespace tc { namespace crypto { namespace detail {

class Sha256Impl
{
public:
	static const size_t kHashSize = 32;
	static const size_t kBlockSize = 64;

	Sha256Impl();
	~Sha256Impl();

	void initialize();
	void update(const byte_t* data, size_t data_size);
	void getHash(byte_t* hash);
private:
	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail