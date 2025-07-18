#include <tc/crypto/RsaKey.h>

static const byte_t kPublicExponent[3] = { 0x01, 0x00, 0x01 };

tc::crypto::RsaPublicKey::RsaPublicKey(const byte_t* modulus, size_t modulus_size) :
	RsaPublicKey(modulus, modulus_size, kPublicExponent, sizeof(kPublicExponent))
{
}

tc::crypto::RsaPublicKey::RsaPublicKey(const byte_t* modulus, size_t modulus_size, const byte_t* public_exponent, size_t public_exponent_size)
{
	if (modulus != nullptr && modulus_size != 0 && public_exponent != nullptr && public_exponent_size != 0)
	{
		this->n = tc::ByteData(modulus, modulus_size);
		this->e = tc::ByteData(public_exponent, public_exponent_size);
		this->d = tc::ByteData();
	}
}

tc::crypto::RsaPrivateKey::RsaPrivateKey(const byte_t* modulus, size_t modulus_size, const byte_t* private_exponent, size_t private_exponent_size) :
	RsaPrivateKey(modulus, modulus_size, kPublicExponent, sizeof(kPublicExponent), private_exponent, private_exponent_size)
{
}

tc::crypto::RsaPrivateKey::RsaPrivateKey(const byte_t* modulus, size_t modulus_size, const byte_t* public_exponent, size_t public_exponent_size, const byte_t* private_exponent, size_t private_exponent_size)
{
	if (modulus != nullptr && modulus_size != 0 && public_exponent != nullptr && public_exponent_size != 0 && private_exponent != nullptr && private_exponent_size != 0)
	{
		this->n = tc::ByteData(modulus, modulus_size);
		this->e = tc::ByteData(public_exponent, public_exponent_size);
		this->d = tc::ByteData(private_exponent, private_exponent_size);
	}
}

tc::crypto::RsaKey tc::crypto::RsaPrivateKey::getPublicKey()
{
	return RsaPublicKey(this->n.data(), this->n.size(), this->e.data(), this->e.size());
}