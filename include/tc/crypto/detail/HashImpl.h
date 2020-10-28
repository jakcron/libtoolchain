	/**
	 * @file HashImpl.h
	 * @brief Declaration of tc::crypto::detail::HashImpl
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2020/06/01
	 **/
#pragma once
#include <tc/crypto/types.h>
#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class HashImpl
	 * @brief This class implements the many hash algorithms.
	 */
class HashImpl
{
public:
	HashImpl(MdTypeId md_type_id);
	~HashImpl();

	size_t hash_size() const;
	size_t block_size() const;

	void start();
	void update(const byte_t* src, size_t src_size);
	void finish(byte_t* hash, size_t hash_size);
private:
	enum class State
	{
		None,
		Initialized,
		Done
	};

	State mState;

	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail