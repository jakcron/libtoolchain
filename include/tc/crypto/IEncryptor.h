	/**
	 * @file IEncryptor.h
	 * @brief Declaration of tc::crypto::IEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IEncryptor
{
public:
	virtual ~IEncryptor() = default;

	virtual size_t block_size() const = 0;
	virtual size_t key_size() const = 0;

	virtual void encrypt(byte_t* dst, const byte_t* src, size_t size) = 0;
	virtual void decrypt(byte_t* dst, const byte_t* src, size_t size) = 0;
};

}}