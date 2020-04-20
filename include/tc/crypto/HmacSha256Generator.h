	/**
	 * @file HmacSha256Generator.h
	 * @brief Declaration of tc::crypto::HmacSha256Generator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IMacGenerator.h>
#include <tc/crypto/Sha256Generator.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
#include <tc/crypto/mbedtls_detail/HmacGeneratorImpl.h>
#else
#include <tc/crypto/detail/HmacGenerator.h>
#endif

namespace tc { namespace crypto {

#ifndef TC_CRYPTO_SHA256GENERATOR_NO_IMPL

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
	using HmacSha256Generator = mbedtls_detail::HmacGeneratorImpl<MBEDTLS_MD_SHA256, 32, 64>;
#else
	using HmacSha256Generator = detail::HmacGenerator<Sha256Generator>;
#endif // TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL

#else
	#define TC_CRYPTO_HMACSHA256GENERATOR_NO_IMPL
#endif // TC_CRYPTO_SHA256GENERATOR_NO_IMPL

#ifndef TC_CRYPTO_HMACSHA256GENERATOR_NO_IMPL
void GenerateHmacSha256Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);
#endif // TC_CRYPTO_HMACSHA256GENERATOR_NO_IMPL

}} // namespace tc::crypto