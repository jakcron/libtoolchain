#include <tc/crypto/Aes128CbcEncryptor.h>

#ifndef TC_CRYPTO_AES128CBCENCRYPTOR_NO_IMPL
void tc::crypto::EncryptAes128Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key)
{
	Aes128CbcEncryptor encryptor;
	encryptor.initialize(key);
	encryptor.encrypt(dst, src, size, iv);
}

void tc::crypto::DecryptAes128Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv, const byte_t* key)
{
	Aes128CbcEncryptor encryptor;
	encryptor.initialize(key);
	encryptor.decrypt(dst, src, size, iv);
}
#endif