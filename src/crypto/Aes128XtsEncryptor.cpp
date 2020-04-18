#include <tc/crypto/Aes128XtsEncryptor.h>

#ifndef TC_CRYPTO_AES128XTSENCRYPTOR_NO_IMPL
void tc::crypto::EncryptAes128Xts(byte_t* dst, const byte_t* src, size_t size, size_t sector_size, const byte_t* iv, const byte_t* key1, const byte_t* key2)
{
	Aes128XtsEncryptor encryptor;
	encryptor.initialize(key1, key2, sector_size);
	encryptor.encrypt(dst, src, size, iv); 
}

void tc::crypto::DecryptAes128Xts(byte_t* dst, const byte_t* src, size_t size, size_t sector_size, const byte_t* iv, const byte_t* key1, const byte_t* key2)
{
	Aes128XtsEncryptor encryptor;
	encryptor.initialize(key1, key2, sector_size);
	encryptor.decrypt(dst, src, size, iv); 
}
#endif