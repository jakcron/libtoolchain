#include <tc/crypto/HmacSha1Generator.h>

#ifndef TC_CRYPTO_HMACSHA1GENERATOR_NO_IMPL
void tc::crypto::GenerateHmacSha1Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size)
{
	HmacSha1Generator hashGenerator;

	hashGenerator.initialize(key, key_size);
	hashGenerator.update(data, data_size);
	hashGenerator.getMac(mac);
}
#endif