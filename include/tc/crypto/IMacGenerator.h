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

	// static const size_t kMacSize = X;
	// static const size_t kBlockSize = X;
	virtual size_t GetMacSize() const = 0;
	virtual size_t GetBlockSize() const = 0;

	virtual void Initialize(const byte_t* key, size_t key_size) = 0;
	virtual void Update(const byte_t* data, size_t data_size) = 0;
	virtual void GetMac(byte_t* mac) = 0;
};

}} // namespace tc::crypto