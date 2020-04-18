#include <tc/crypto/Aes128Encryptor.h>

#ifndef TC_CRYPTO_AES128ENCRYPTOR_NO_IMPL
void tc::crypto::EncryptAes128(byte_t* dst, const byte_t* src, size_t size, const byte_t* key)
{
	Aes128Encryptor encryptor;
	encryptor.initialize(key);
	encryptor.encrypt(dst, src, size);
}

void tc::crypto::DecryptAes128(byte_t* dst, const byte_t* src, size_t size, const byte_t* key)
{
	Aes128Encryptor encryptor;
	encryptor.initialize(key);
	encryptor.decrypt(dst, src, size);
}
#endif