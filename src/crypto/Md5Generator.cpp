#include <tc/crypto/Md5Generator.h>

const std::array<byte_t, tc::crypto::Md5Generator::kAsn1OidDataSize> tc::crypto::Md5Generator::kAsn1OidData = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05};

void tc::crypto::GenerateMd5Hash(byte_t* hash, const byte_t* data, size_t data_size)
{
	tc::crypto::Md5Generator impl;
	impl.initialize();
	impl.update(data, data_size);
	impl.getHash(hash);
}