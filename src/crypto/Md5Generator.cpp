#include <tc/crypto/Md5Generator.h>

#ifndef TC_CRYPTO_MD5GENERATOR_NO_IMPL
void tc::crypto::GenerateMd5Hash(byte_t* hash, const byte_t* data, size_t data_size)
{
	Md5Generator hashGenerator;

	hashGenerator.initialize();
	hashGenerator.update(data, data_size);
	hashGenerator.getHash(hash);
}
#endif