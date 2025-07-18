#include <tc/crypto/EccKeyGenerator.h>

void tc::crypto::GenerateEccKey(EccKey& key, EccCurveType curve_type)
{
	tc::crypto::EccKeyGenerator impl;
	impl.generateKey(key, curve_type);
}

void tc::crypto::GenerateEccPublicKey(EccKey& public_key, const EccKey& private_key)
{
	tc::crypto::EccKeyGenerator impl;
	impl.generatePublicKey(public_key, private_key);
}