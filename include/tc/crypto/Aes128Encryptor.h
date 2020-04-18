	/**
	 * @file Aes128Encryptor.h
	 * @brief Declaration of tc::crypto::Aes128Encryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/crypto/IEncryptor.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
#include <tc/crypto/mbedtls_detail/AesEcbEncryptorImpl.h>
#endif

namespace tc { namespace crypto {

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
	using Aes128Encryptor = mbedtls_detail::AesEcbEncryptorImpl<128>;
#else
	#define TC_CRYPTO_AES128ENCRYPTOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_AES128ENCRYPTOR_NO_IMPL
static_assert(std::is_base_of<IEncryptor, Aes128Encryptor>::value, "Aes128Encryptor must be of type IEncryptor.");

void EncryptAes128(byte_t* dst, const byte_t* src, size_t size, const byte_t* key);
void DecryptAes128(byte_t* dst, const byte_t* src, size_t size, const byte_t* key);
#endif

}} // namespace tc::crypto