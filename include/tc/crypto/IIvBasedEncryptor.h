	/**
	 * @file IIvBasedEncryptor.h
	 * @brief Declaration of tc::crypto::IIvBasedEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IIvBasedEncryptor
{
public:
	virtual ~IIvBasedEncryptor() = default;

	virtual size_t block_size() const = 0;
	virtual size_t key_size() const = 0;
	virtual size_t iv_size() const = 0;

	virtual void encrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv) = 0;
	virtual void decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv) = 0;
};

}}