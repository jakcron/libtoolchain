	/**
	 * @file IMacGenerator.h
	 * @brief Declaration of tc::crypto::IMacGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IMacGenerator
{
public:
	virtual ~IMacGenerator() = default;

	virtual size_t mac_size() const = 0;
	virtual size_t block_size() const = 0;

	virtual void initialize(const byte_t* key, size_t key_size) = 0;
	virtual void update(const byte_t* data, size_t data_size) = 0;
	virtual void getMac(byte_t* mac) = 0;
};

}} // namespace tc::crypto