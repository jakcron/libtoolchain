#include <tc/crypto/Sha256Generator.h>

const std::array<byte_t, tc::crypto::Sha256Generator::kAsn1OidDataSize> tc::crypto::Sha256Generator::kAsn1OidData = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

void tc::crypto::GenerateSha256Hash(byte_t* hash, const byte_t* data, size_t data_size)
{
	tc::crypto::Sha256Generator impl;
	impl.initialize();
	impl.update(data, data_size);
	impl.getHash(hash);
}