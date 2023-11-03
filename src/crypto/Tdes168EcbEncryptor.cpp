#include <tc/crypto/Tdes168EcbEncryptor.h>

void tc::crypto::EncryptTdes168Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size)
{
	tc::crypto::Tdes168EcbEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.encrypt(dst, src, size);
}

void tc::crypto::DecryptTdes168Ecb(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size)
{
	tc::crypto::Tdes168EcbEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.decrypt(dst, src, size);
}