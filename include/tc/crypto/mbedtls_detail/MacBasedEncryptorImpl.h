	/**
	 * @file MacBasedEncryptorImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::MacBasedEncryptorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/ByteData.h>
#include <tc/crypto/IMacBasedEncryptor.h>
#include <mbedtls/cipher.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <mbedtls_cipher_id_t CipherId, int KeyBitLen, mbedtls_cipher_mode_t CipherMode>
class MacBasedEncryptorImpl : public IMacBasedEncryptor
{
public:

	MacBasedEncryptorImpl()
	{
		memset(mKey.data(), 0, mKey.size());
		mbedtls_cipher_init(&mCtx);

		int ret = mbedtls_cipher_setup(&mCtx, mbedtls_cipher_info_from_values(CipherId, KeyBitLen, CipherMode));
		if (ret != 0) { /* throw exception*/ }
	}

	~MacBasedEncryptorImpl()
	{
		memset(mKey.data(), 0, mKey.size());
		mbedtls_cipher_free(&mCtx);
	}
	
	size_t block_size() const { return size_t(mbedtls_cipher_get_block_size(&mCtx)); }
	size_t key_size() const { return mKey.size(); }
	size_t nonce_size() const { return size_t(mbedtls_cipher_get_iv_size(&mCtx)); } 
	

	void initialize(const byte_t* key) 
	{
		if (key == nullptr) { /* throw exception */ }

		memcpy(mKey.data(), key, mKey.size());
	}

	void encrypt(byte_t* dst, const byte_t* src, size_t size, byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size)
	{
		// mbedtls_cipher_setkey will succeed because the input was already validated
		mbedtls_cipher_setkey(&mCtx, mKey.data(), KeyBitLen, MBEDTLS_ENCRYPT);

		size_t out_size = size;
		int ret = mbedtls_cipher_auth_encrypt(&mCtx, nonce, nonce_size, aad, aad_size, src, size, dst, &out_size, mac, mac_size);

		if (ret != 0) { /* throw exception */ }
		if (out_size != size) { /* throw exception */ }
	}

	bool decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* aad, size_t aad_size)
	{
		// mbedtls_cipher_setkey will succeed because the input was already validated
		mbedtls_cipher_setkey(&mCtx, mKey.data(), KeyBitLen, MBEDTLS_DECRYPT);

		size_t out_size = size;
		int ret = mbedtls_cipher_auth_decrypt(&mCtx, nonce, nonce_size, aad, aad_size, src, size, dst, &out_size, mac, mac_size);

		// MAC was invalid
		if (ret == MBEDTLS_ERR_CIPHER_AUTH_FAILED)
		{
			return false;
		}
		if (ret != 0) { /* throw exception */ }
		if (out_size != size) { /* throw exception */ }

		return true;
	}
private:
	std::array<byte_t, (KeyBitLen / 8)> mKey;
	mbedtls_cipher_context_t mCtx;
};

}}} // namespace tc::crypto::mbedtls_detail