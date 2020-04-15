	/**
	 * @file CipherImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::CipherImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/15
	 **/
#pragma once

#include <tc/crypto/IHashGenerator.h>
#include <mbedtls/cipher.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

template <mbedtls_cipher_id_t CipherId, int KeyBitLen, mbedtls_cipher_mode_t CipherMode>
class CipherImpl
{
public:

	CipherImpl()
	{
		mbedtls_cipher_init(&mCtx);
		int ret = mbedtls_cipher_setup(&mCtx, mbedtls_cipher_info_from_values(CipherId, KeyBitLen, CipherMode));
		if (ret == MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA)
		{
		}
		if (ret == MBEDTLS_ERR_CIPHER_ALLOC_FAILED)
		{
		}
	}
	~CipherImpl()
	{
		mbedtls_cipher_free(&mCtx);
	}
	
	size_t GetBlockSize() const { return size_t(mbedtls_cipher_get_block_size(&mCtx)); }
	size_t GetIvSize() const { return size_t(mbedtls_cipher_get_iv_size(&mCtx)); }
	size_t GetKeyBitLen() const { return mbedtls_cipher_get_key_bitlen(&mCtx); }
	size_t GetKeySize() const { return GetKeyBitLen() / 8;}

	void SetKey(const byte_t* key, size_t key_size, bool is_encrypt_mode) 
	{
		mbedtls_cipher_setkey(&mCtx, key, key_size * 8, is_encrypt_mode ? MBEDTLS_ENCRYPT : MBEDTLS_DECRYPT);
	}

	int Encrypt(byte_t* dst, size_t dst_size, const byte_t* iv, size_t iv_size, const byte_t* src, size_t src_size)
	{
		return mbedtls_cipher_crypt(&mCtx, iv, iv_size, src, src_size, dst, dst_size);
	}

	int Decrypt(byte_t* dst, size_t dst_size, const byte_t* iv, size_t iv_size, const byte_t* src, size_t src_size)
	{
		return mbedtls_cipher_crypt(&mCtx, iv, iv_size, src, src_size, dst, dst_size);
	}

	int AuthEncrypt(byte_t* dst, size_t dst_size, byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* src, size_t src_size, const byte_t* aad, size_t aad_size)
	{
		return mbedtls_cipher_auth_encrypt(&mCtx, nonce, nonce_size, aad, aad_size, src, src_size, dst, dst_size, mac, mac_size);
	}

	int AuthDecrypt(byte_t* dst, size_t dst_size, const byte_t* mac, size_t mac_size, const byte_t* nonce, size_t nonce_size, const byte_t* src, size_t src_size, const byte_t* aad, size_t aad_size)
	{
		return mbedtls_cipher_auth_decrypt(&mCtx, nonce, nonce_size, aad, aad_size, src, src_size, dst, dst_size, mac, mac_size);
	}
private:
	mbedtls_cipher_context_t mCtx;
};

}}} // namespace tc::crypto::mbedtls_detail