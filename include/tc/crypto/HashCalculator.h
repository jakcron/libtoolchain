#pragma once
/**
 * @file HashCalculator.h
 * @brief Defines interface for classes that implement a Hash Calculator
 * @author Jack (jakcron)
 * @version v1.0 Initial version
 * @date 2020/10/27
 */
#include <tc/crypto/types.h>
#include <tc/crypto/IHashCalculator.h>
#include <tc/crypto/detail/HashImpl.h>

namespace tc { namespace crypto {

template <MdTypeId TYPE_ID>
class HashCalculator : public IHashCalculator
{
public:
	HashCalculator() : mMdType(TYPE_ID), mImpl(TYPE_ID) {}

	MdTypeId hash_type() const { return mMdType; }

	size_t hash_size() const { return mImpl.hash_size(); }
	size_t block_size() const { return mImpl.block_size(); }

	void start() { mImpl.start(); }
	void update(const byte_t* data, size_t data_size) { mImpl.update(data, data_size); }
	void finish(byte_t* hash, size_t hash_size) { mImpl.finish(hash, hash_size); }
private:
	MdTypeId mMdType;
	detail::HashImpl mImpl;
};

}} // namespace tc::crypto