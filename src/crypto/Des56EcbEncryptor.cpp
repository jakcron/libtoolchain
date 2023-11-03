#include <tc/crypto/Des56EcbEncryptor.h>

void tc::crypto::EncryptDes56Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size)
{
	tc::crypto::Des56EcbEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.encrypt(dst, src, size);
}

void tc::crypto::DecryptDes56Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size)
{
	tc::crypto::Des56EcbEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.decrypt(dst, src, size);
}