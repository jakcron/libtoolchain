	/**
	 * @file Aes128CtrEncryptor.h
	 * @brief Declaration of tc::crypto::Aes128CtrEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IEncryptor.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
#include <tc/crypto/mbedtls_detail/IvBasedEncryptorImpl.h>
#endif

namespace tc { namespace crypto {

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
	using Aes128CtrEncryptor = mbedtls_detail::IvBasedEncryptorImpl<MBEDTLS_CIPHER_ID_AES, 128, MBEDTLS_MODE_CTR>;
#else
	#define TC_CRYPTO_AES128CTRENCRYPTOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_AES128CTRENCRYPTOR_NO_IMPL
void EncryptAes128Ctr(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key);
void DecryptAes128Ctr(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key);
#endif

}} // namespace tc::crypto