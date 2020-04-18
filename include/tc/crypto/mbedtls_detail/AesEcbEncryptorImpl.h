	/**
	 * @file AesEcbEncryptorImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::AesEcbEncryptorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/types.h>
#include <tc/crypto/IEncryptor.h>
#include <mbedtls/aes.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <size_t KeyBitLen>
class AesEcbEncryptorImpl : IEncryptor
{
public:
	// fix key sizes
	static_assert(KeyBitLen == 128 || KeyBitLen == 192 || KeyBitLen == 256, "Unsupported AES KeyBitLen");

	AesEcbEncryptorImpl()
	{
		memset(mKey.data(), 0, mKey.size());
		mbedtls_aes_init(&mAesContext);
	}
	~AesEcbEncryptorImpl()
	{
		memset(mKey.data(), 0, mKey.size());
		mbedtls_aes_free(&mAesContext);
	}

	size_t block_size() const { return 16; }
	size_t key_size() const { return mKey.size(); }

	void initialize(const byte_t* key)
	{
		if (key == nullptr) { /* throw exception */ }

		memcpy(mKey.data(), key, mKey.size());
	}

	void encrypt(byte_t* dst, const byte_t* src, size_t size)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (size == 0 || size % this->block_size()) { /* throw exception */ }

		mbedtls_aes_setkey_enc(&mAesContext, mKey.data(), this->key_size() * 8);

		for (size_t block_idx = 0, block_num = (size / block_size()); block_idx < block_num; block_idx++)
		{
			mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_ENCRYPT, src + (block_idx * this->block_size()), dst + (block_idx * this->block_size()));
		}
	}

	void decrypt(byte_t* dst, const byte_t* src, size_t size)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (size % this->block_size()) { /* throw exception */ }

		mbedtls_aes_setkey_dec(&mAesContext, mKey.data(), this->key_size() * 8);

		for (size_t block_idx = 0, block_num = (size / block_size()); block_idx < block_num; block_idx++)
		{
			mbedtls_aes_crypt_ecb(&mAesContext, MBEDTLS_AES_DECRYPT, src + (block_idx * this->block_size()), dst + (block_idx * this->block_size()));
		}
	}
private:
	std::array<byte_t, (KeyBitLen / 8)> mKey;
	mbedtls_aes_context mAesContext;
};

}}} // namespace tc::crypto::mbedtls_detail