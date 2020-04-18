	/**
	 * @file Aes128XtsEncryptor.h
	 * @brief Declaration of tc::crypto::Aes128XtsEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/crypto/Aes128Encryptor.h>
#include <tc/crypto/XtsModeEncryptor.h>

namespace tc { namespace crypto {

#ifndef TC_CRYPTO_AES128ENCRYPTOR_NO_IMPL
	using Aes128XtsEncryptor = XtsModeEncryptor<Aes128Encryptor>;
#else
	#define TC_CRYPTO_AES128XTSENCRYPTOR_NO_IMPL
#endif

#ifndef TC_CRYPTO_AES128XTSENCRYPTOR_NO_IMPL
static_assert(std::is_base_of<IIvBasedEncryptor, Aes128XtsEncryptor>::value, "Aes128XtsEncryptor must be of type IIvBasedEncryptor.");

void EncryptAes128Xts(byte_t* dst, const byte_t* src, size_t size, size_t sector_size, const byte_t* iv, const byte_t* key1, const byte_t* key2);
void DecryptAes128Xts(byte_t* dst, const byte_t* src, size_t size, size_t sector_size, const byte_t* iv, const byte_t* key1, const byte_t* key2);
#endif

}} // namespace tc::crypto