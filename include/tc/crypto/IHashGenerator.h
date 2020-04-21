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

	virtual size_t hash_size() const = 0;
	virtual size_t block_size() const = 0;

	virtual void initialize() = 0;
	virtual void update(const byte_t* data, size_t data_size) = 0;
	virtual void getHash(byte_t* hash) = 0;
};

}}