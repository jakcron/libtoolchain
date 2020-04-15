#include <tc/crypto/Sha1Generator.h>

#ifndef TC_CRYPTO_SHA1GENERATOR_NO_IMPL
void tc::crypto::GenerateSha1Hash(byte_t* hash, const byte_t* data, size_t data_size)
{
	Sha1Generator hashGenerator;

	hashGenerator.Initialize();
	hashGenerator.Update(data, data_size);
	hashGenerator.GetHash(hash);
}
#endif