	/**
	 * @file IHashSigner.h
	 * @brief Declaration of tc::crypto::IHashSigner
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/21
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class IHashSigner
{
public:
	virtual ~IHashSigner() = default;

	virtual size_t block_size() const = 0;
	virtual size_t key_size() const = 0;
	virtual size_t signature_size() const = 0;
	virtual size_t hash_size() const = 0;

	virtual void signHash(byte_t* signature, const byte_t* hash) = 0;
	virtual bool verifyHash(const byte_t* signature, const byte_t* hash) = 0;
};

}}