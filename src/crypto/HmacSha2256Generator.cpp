#include <tc/crypto/HmacSha2256Generator.h>

void tc::crypto::GenerateHmacSha2256Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size)
{
	tc::crypto::HmacSha2256Generator impl;
	impl.initialize(key, key_size);
	impl.update(data, data_size);
	impl.getMac(mac);
}