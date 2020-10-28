#pragma once
/**
 * @file IHashCalculator.h
 * @brief Defines interface for classes that implement a Hash Calculator
 * @author Jack (jakcron)
 * @version v1.0 Initial version
 * @date 2020/10/27
 */
#include <tc/types.h>

namespace tc { namespace crypto {

class IMacCalculator
{
public:
	virtual ~IMacCalculator() = default;

	virtual size_t hash_size() const = 0;
	virtual size_t block_size() const = 0;

	virtual void start() = 0;
	virtual void update(const byte_t* data, size_t data_size) = 0;
	virtual void finish(byte_t* hash, size_t data_size) = 0;
};

}} // namespace tc::crypto