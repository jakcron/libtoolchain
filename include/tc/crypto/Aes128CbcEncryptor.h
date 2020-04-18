	/**
	 * @file Aes128CbcEncryptor.h
	 * @brief Declaration of tc::crypto::Aes128CbcEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/crypto/IIvBasedEncryptor.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
#include <tc/crypto/mbedtls_detail/IvBasedEncryptorImpl.h>
#endif

namespace tc { namespace crypto {

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
	using Aes128CbcEncryptor = mbedtls_detail::IvBasedEncryptorImpl<MBEDTLS_CIPHER_ID_AES, 128, MBEDTLS_MODE_CBC>;
#else
	#define TC_CRYPTO_AES128CBCENCRYPTOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_AES128CBCENCRYPTOR_NO_IMPL
static_assert(std::is_base_of<IIvBasedEncryptor, Aes128CbcEncryptor>::value, "Aes128CbcEncryptor must be of type IIvBasedEncryptor.");

void EncryptAes128Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key);
void DecryptAes128Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key);
#endif

}} // namespace tc::crypto