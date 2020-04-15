	/**
	 * @file HmacSha512Generator.h
	 * @brief Declaration of tc::crypto::HmacSha512Generator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IMacGenerator.h>
#include <tc/crypto/Sha512Generator.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
#include <tc/crypto/mbedtls_detail/HmacGeneratorImpl.h>
#else
#include <tc/crypto/HmacGenerator.h>
#endif

namespace tc { namespace crypto {

#ifndef TC_CRYPTO_SHA512GENERATOR_NO_IMPL

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
	using HmacSha512Generator = mbedtls_detail::HmacGeneratorImpl<MBEDTLS_MD_SHA512, 64, 128>;
#else
	using HmacSha512Generator = HmacGenerator<Sha512Generator>;
#endif // TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL

#else
	#define TC_CRYPTO_HMACSHA512GENERATOR_NO_IMPL
#endif // TC_CRYPTO_SHA512GENERATOR_NO_IMPL

#ifndef TC_CRYPTO_HMACSHA512GENERATOR_NO_IMPL
void GenerateHmacSha512Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);
#endif // TC_CRYPTO_HMACSHA512GENERATOR_NO_IMPL

}} // namespace tc::crypto