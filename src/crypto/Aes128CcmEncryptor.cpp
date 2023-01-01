#include <tc/crypto/Aes128CcmEncryptor.h>

void tc::crypto::EncryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
{
	tc::crypto::Aes128CcmEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.encrypt(dst, src, size, iv, iv_size, add, add_size, tag, tag_size);
}

void tc::crypto::DecryptAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, byte_t* tag, size_t tag_size)
{
	tc::crypto::Aes128CcmEncryptor crypt;
	crypt.initialize(key, key_size);
	crypt.decrypt(dst, src, size, iv, iv_size, add, add_size, tag, tag_size);
}

bool tc::crypto::DecryptVerifyAes128Ccm(byte_t* dst, const byte_t* src, size_t size, const byte_t* key, size_t key_size, const byte_t* iv, size_t iv_size, const byte_t* add, size_t add_size, const byte_t* tag, size_t tag_size)
{
	tc::crypto::Aes128CcmEncryptor crypt;
	
	try {
		crypt.initialize(key, key_size);
	}
	catch (...) {
		return false;
	}
	
	return crypt.decrypt_and_verify(dst, src, size, iv, iv_size, add, add_size, tag, tag_size);
}
