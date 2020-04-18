#include <tc/crypto/Aes128GcmEncryptor.h>

#ifndef TC_CRYPTO_AES128GCMENCRYPTOR_NO_IMPL
void tc::crypto::EncryptAes128Gcm(byte_t* dst, const byte_t* src, size_t size, byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* key)
{
	Aes128GcmEncryptor encryptor;
	encryptor.initialize(key);
	encryptor.encrypt(dst, src, size, mac, mac_size, nonce, nonce_size, aad, aad_size);
}

bool tc::crypto::DecryptAes128Gcm(byte_t* dst, const byte_t* src, size_t size, const byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size, const byte_t* key)
{
	Aes128GcmEncryptor encryptor;
	encryptor.initialize(key);
	return encryptor.decrypt(dst, src, size, mac, mac_size, nonce, nonce_size, aad, aad_size);
}
#endif