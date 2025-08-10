#include <tc/crypto/EcdhSharedSecretGenerator.h>

void tc::crypto::GenerateEcdhSharedSecret(byte_t* data, size_t data_size, const EccKey& private_key, const EccKey& public_key)
{
    tc::crypto::EcdhSharedSecretGenerator gen;
    gen.initialize(private_key, public_key);
    gen.generateSharedSecretBytes(data, data_size);
}