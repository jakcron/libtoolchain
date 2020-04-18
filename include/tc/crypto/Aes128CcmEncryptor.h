	/**
	 * @file Aes128CcmEncryptor.h
	 * @brief Declaration of tc::crypto::Aes128CcmEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/crypto/IMacBasedEncryptor.h>

#ifdef TC_CRYPTO_USE_MBEDTLS_AES_IMPL
#include <tc/crypto/mbedtls_detail/MacBasedEncryptorImpl.h>
#endif

namespace tc { namespace crypto {

#ifndef TC_CRYPTO_AES128ENCRYPTOR_NO_IMPL
	using Aes128CcmEncryptor = mbedtls_detail::MacBasedEncryptorImpl<MBEDTLS_CIPHER_ID_AES, 128, MBEDTLS_MODE_CCM>;
#else
	#define TC_CRYPTO_AES128CCMENCRYPTOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_AES128CCMENCRYPTOR_NO_IMPL
static_assert(std::is_base_of<IMacBasedEncryptor, Aes128CcmEncryptor>::value, "Aes128CcmEncryptor must be of type IMacBasedEncryptor.");

void EncryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* key);
bool DecryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* key);
#endif

}} // namespace tc::crypto