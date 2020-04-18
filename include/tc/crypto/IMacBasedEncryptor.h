	/**
	 * @file IMacBasedEncryptor.h
	 * @brief Declaration of tc::crypto::IMacBasedEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IMacBasedEncryptor
{
public:
	virtual ~IMacBasedEncryptor() = default;

	virtual size_t block_size() const = 0;
	virtual size_t key_size() const = 0;
	virtual size_t nonce_size() const = 0;

	virtual void encrypt(byte_t* dst, const byte_t* src, size_t size, byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size) = 0;
	virtual bool decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size) = 0;
};

}}