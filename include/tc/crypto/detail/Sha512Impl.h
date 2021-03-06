	/**
	 * @file Sha512Impl.h
	 * @brief Declaration of tc::crypto::detail::Sha512Impl
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2020/06/01
	 **/
#pragma once
#include <tc/types.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class Sha512Impl
	 * @brief This class implements the SHA-512 hash algorithm.
	 */
class Sha512Impl
{
public:
	static const size_t kHashSize = 64;
	static const size_t kBlockSize = 128;

	Sha512Impl();
	~Sha512Impl();

	void initialize();
	void update(const byte_t* data, size_t data_size);
	void getHash(byte_t* hash);
private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	State mState;
	std::array<byte_t, kHashSize> mHash;

	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail