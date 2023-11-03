#include <tc/crypto/Tdes112CbcEncryptor.h>

void tc::crypto::EncryptTdes112Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size)
{
	tc::crypto::Tdes112CbcEncryptor crypt;
	crypt.initialize(key, key_size, iv, iv_size);
	crypt.encrypt(dst, src, size);
}

void tc::crypto::DecryptTdes112Cbc(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size)
{
	tc::crypto::Tdes112CbcEncryptor crypt;
	crypt.initialize(key, key_size, iv, iv_size);
	crypt.decrypt(dst, src, size);
}