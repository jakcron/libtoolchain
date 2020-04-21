#include <tc/crypto/HmacSha512Generator.h>

#ifndef TC_CRYPTO_HMACSHA512GENERATOR_NO_IMPL
void tc::crypto::GenerateHmacSha512Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size)
{
	HmacSha512Generator hashGenerator;

	hashGenerator.initialize(key, key_size);
	hashGenerator.update(data, data_size);
	hashGenerator.getMac(mac);
}
#endif