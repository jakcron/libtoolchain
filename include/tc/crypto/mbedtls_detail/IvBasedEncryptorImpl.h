	/**
	 * @file IvBasedEncryptorImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::IvBasedEncryptorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/16
	 **/
#pragma once

#include <tc/ByteData.h>
#include <tc/crypto/IIvBasedEncryptor.h>
#include <mbedtls/cipher.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <mbedtls_cipher_id_t CipherId, int KeyBitLen, mbedtls_cipher_mode_t CipherMode>
class IvBasedEncryptorImpl : public IIvBasedEncryptor
{
public:
	IvBasedEncryptorImpl()
	{
		memset(mKey.data(), 0, KeyBitLen / 8);
		mbedtls_cipher_init(&mCtx);
		int ret = mbedtls_cipher_setup(&mCtx, mbedtls_cipher_info_from_values(CipherId, KeyBitLen, CipherMode));
		if (ret != 0) { /* throw exception*/ }
	}

	~IvBasedEncryptorImpl()
	{
		memset(mKey.data(), 0, KeyBitLen / 8);
		mbedtls_cipher_free(&mCtx);
	}
	
	size_t block_size() const { return size_t(mbedtls_cipher_get_block_size(&mCtx)); }
	size_t key_size() const { return KeyBitLen / 8; }
	size_t iv_size() const { return block_size(); }
	

	void initialize(const byte_t* key) 
	{
		if (key == nullptr) { /* throw exception */ }

		memcpy(mKey.data(), key, mKey.size());
	}

	void encrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (iv == nullptr) { /* throw exception */ }

		// mbedtls_cipher_setkey will succeed because the input was already validated
		mbedtls_cipher_setkey(&mCtx, mKey.data(), KeyBitLen, MBEDTLS_ENCRYPT);

		size_t out_size = size;
		int ret = mbedtls_cipher_crypt(&mCtx, iv, this->iv_size(), src, size, dst, &out_size);
		if (ret != 0) { /* throw exception */ }
		if (out_size != size) { /* throw exception */ }
	}

	void decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (iv == nullptr) { /* throw exception */ }

		// mbedtls_cipher_setkey will succeed because the input was already validated
		mbedtls_cipher_setkey(&mCtx, mKey.data(), KeyBitLen, MBEDTLS_DECRYPT);

		size_t out_size = size;
		int ret = mbedtls_cipher_crypt(&mCtx, iv, this->iv_size(), src, size, dst, &out_size);
		if (ret != 0) { /* throw exception */ }
		if (out_size != size) { /* throw exception */ }
	}
private:
	std::array<byte_t, (KeyBitLen / 8)> mKey;
	mbedtls_cipher_context_t mCtx;
};

}}} // namespace tc::crypto::mbedtls_detail