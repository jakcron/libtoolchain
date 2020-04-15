	/**
	 * @file IHashGenerator.h
	 * @brief Declaration of tc::crypto::IHashGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IHashGenerator
{
public:
	virtual ~IHashGenerator() = default;

	// static const size_t kHashSize = X;
	// static const size_t kBlockSize = X;
	virtual size_t GetHashSize() const = 0;
	virtual size_t GetBlockSize() const = 0;

	virtual void Initialize() = 0;
	virtual void Update(const byte_t* data, size_t data_size) = 0;
	virtual void GetHash(byte_t* hash) = 0;
};

}}