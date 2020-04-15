	/**
	 * @file IEncryptorWithMac.h
	 * @brief Declaration of tc::crypto::IEncryptorWithMac
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IEncryptorWithMac
{
public:
	virtual ~IEncryptorWithMac() = default;

	virtual size_t GetKeySize() const = 0;
	virtual size_t GetNonceSize() const = 0;
	virtual size_t GetBlockSize() const = 0;

	virtual void EncryptBlock(byte_t* dst, size_t dst_size, /* here you receive the mac generated to keep */byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* src, size_t src_size) = 0;
	virtual void DecryptBlock(byte_t* dst, size_t dst_size, /* here you receive the mac generated to validate */byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* src, size_t src_size) = 0;
};

}}