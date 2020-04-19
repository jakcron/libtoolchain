	/**
	 * @file ISigner.h
	 * @brief Declaration of tc::crypto::ISigner
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/19
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class ISigner
{
public:
	virtual ~ISigner() = default;

	virtual size_t block_size() const = 0;
	virtual size_t key_size() const = 0;
	virtual size_t signature_size() const = 0;

	virtual void sign(byte_t* signature, const byte_t* src, size_t src_size) = 0;
	virtual bool verify(const byte_t* signature, const byte_t* src, size_t src_size) = 0;
};

}}