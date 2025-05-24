#include <tc/crypto/CmacTdes168Generator.h>

void tc::crypto::GenerateCmacTdes168Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size)
{
	tc::crypto::CmacTdes168Generator impl;
	impl.initialize(key, key_size);
	impl.update(data, data_size);
	impl.getMac(mac);
}