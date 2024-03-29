#include <tc/crypto/RsaPkcs1Sha2512Signer.h>

bool tc::crypto::SignRsa1024Pkcs1Sha2512(byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa1024Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.sign(signature, message_digest);
}

bool tc::crypto::VerifyRsa1024Pkcs1Sha2512(const byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa1024Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.verify(signature, message_digest);
}

bool tc::crypto::SignRsa2048Pkcs1Sha2512(byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa2048Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.sign(signature, message_digest);
}

bool tc::crypto::VerifyRsa2048Pkcs1Sha2512(const byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa2048Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.verify(signature, message_digest);
}

bool tc::crypto::SignRsa4096Pkcs1Sha2512(byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa4096Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.sign(signature, message_digest);
}

bool tc::crypto::VerifyRsa4096Pkcs1Sha2512(const byte_t* signature, const byte_t* message_digest, const RsaKey& key)
{
	tc::crypto::Rsa4096Pkcs1Sha2512Signer impl;
	impl.initialize(key);
	return impl.verify(signature, message_digest);
}