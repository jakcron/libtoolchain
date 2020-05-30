	/**
	 * @file HmacGenerator.h
	 * @brief Declaration of tc::crypto::HmacGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/05/30
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/Sha1Generator.h>
#include <tc/crypto/HmacGenerator.h>

namespace tc { namespace crypto {

using HmacSha1Generator = HmacGenerator<Sha1Generator>;

void GenerateHmacSha1Mac(byte_t* mac, 
                         const byte_t* data, size_t data_size,
						 const byte_t* key, size_t key_size);

}} // namespace tc::crypto
