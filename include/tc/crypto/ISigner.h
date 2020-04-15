	/**
	 * @file ISigner.h
	 * @brief Declaration of tc::crypto::ISigner
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/config.h>

namespace tc { namespace crypto {

class ISigner
{
public:
	virtual ~ISigner() = default;

	virtual size_t GetKeySize() const = 0;
	virtual size_t GetBlockSize() const = 0;
	virtual size_t GetSignatureSize() const = 0;

	virtual void SignBlock(byte_t* signature, size_t signature_size, const byte_t* src, size_t src_size) = 0;
	virtual bool VerifyBlock(const byte_t* signature, size_t signature_size, const byte_t* src, size_t src_size) = 0;
};

}}