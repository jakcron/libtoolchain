#include <tc/crypto/HmacMd5Generator.h>

#ifndef TC_CRYPTO_HMACMD5GENERATOR_NO_IMPL
void tc::crypto::GenerateHmacMd5Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size)
{
	HmacMd5Generator hashGenerator;

	hashGenerator.initialize(key, key_size);
	hashGenerator.update(data, data_size);
	hashGenerator.getMac(mac);
}
#endif