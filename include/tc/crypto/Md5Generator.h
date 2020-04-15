	/**
	 * @file Md5Generator.h
	 * @brief Declaration of tc::crypto::Md5Generator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IHashGenerator.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_HASH_IMPL
#include <tc/crypto/mbedtls_detail/HashGeneratorImpl.h>
#endif

namespace tc { namespace crypto {

#ifdef TC_CRYPTO_USE_MBEDTLS_HASH_IMPL
	using Md5Generator = mbedtls_detail::HashGeneratorImpl<MBEDTLS_MD_MD5, 16, 64>;
#else
	#define TC_CRYPTO_MD5GENERATOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_MD5GENERATOR_NO_IMPL
void GenerateMd5Hash(byte_t* hash, const byte_t* data, size_t data_size);
#endif

}} // namespace tc::crypto