	/**
	 * @file HmacSha1Generator.h
	 * @brief Declaration of tc::crypto::HmacSha1Generator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IMacGenerator.h>
#include <tc/crypto/Sha1Generator.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
#include <tc/crypto/mbedtls_detail/HmacGeneratorImpl.h>
#else
#include <tc/crypto/detail/HmacGenerator.h>
#endif

namespace tc { namespace crypto {

#ifndef TC_CRYPTO_SHA1GENERATOR_NO_IMPL

#ifdef TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL
	using HmacSha1Generator = mbedtls_detail::HmacGeneratorImpl<MBEDTLS_MD_SHA1, 20, 64>;
#else
	using HmacSha1Generator = detail::HmacGenerator<Sha1Generator>;
#endif // TC_CRYPTO_USE_MBEDTLS_HMAC_IMPL

#else
	#define TC_CRYPTO_HMACSHA1GENERATOR_NO_IMPL
#endif // TC_CRYPTO_SHA1GENERATOR_NO_IMPL

#ifndef TC_CRYPTO_HMACSHA1GENERATOR_NO_IMPL
void GenerateHmacSha1Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);
#endif // TC_CRYPTO_HMACSHA1GENERATOR_NO_IMPL

}} // namespace tc::crypto