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

	virtual size_t GetKeySize() const = 0;
	virtual size_t GetBlockSize() const = 0;

	virtual void EncryptBlock(byte_t* dst, size_t dst_size, const byte_t* src, size_t src_size) = 0;
	virtual void DecryptBlock(byte_t* dst, size_t dst_size, const byte_t* src, size_t src_size) = 0;
};

}}