#include <tc/crypto/Sha512Generator.h>

#ifndef TC_CRYPTO_SHA512GENERATOR_NO_IMPL
void tc::crypto::GenerateSha512Hash(byte_t* hash, const byte_t* data, size_t data_size)
{
	Sha512Generator hashGenerator;

	hashGenerator.initialize();
	hashGenerator.update(data, data_size);
	hashGenerator.getHash(hash);
}
#endif