	/**
	 * @file RsaSignerImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::RsaSignerImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/19
	 **/
#pragma once

#include <tc/ByteData.h>
#include <tc/crypto/ISigner.h>
#include <tc/crypto/IHashSigner.h>
#include <tc/crypto/CryptoUtil.h>
#include <tc/crypto/CryptoException.h>
#include <tc/crypto/mbedtls_detail/MbedtlsErrorUtil.h>
#include <tc/crypto/RsaKey.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/md.h>
#include <mbedtls/rsa.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

	/**
	 * @class RsaSignerImpl
	 * @brief This class implements RSA signing with mbedtls
	 * 
	 * @note Use MBEDTLS_PKCS1_V21 for RSASSA (RsaPss)
	 * @note Use MBEDTLS_PKCS1_V15 for regular RSA signatures
	 **/
template <size_t KeyBitLen, int PaddingId, mbedtls_md_type_t HashType>
class RsaSignerImpl : public ISigner, public IHashSigner
{
public:
	RsaSignerImpl()
	{
		std::string pers = "tc::crypto::mbedtls_detail::RsaSignerImpl";

		mbedtls_entropy_init( &mEntropy );
		mbedtls_ctr_drbg_init( &mCtrDrbg );
		mbedtls_rsa_init( &mRsa, PaddingId, HashType );

		int ret = 1;

		if ( (ret = mbedtls_ctr_drbg_seed(&mCtrDrbg, mbedtls_entropy_func, &mEntropy, (const unsigned char *)pers.c_str(), pers.length())) != 0)
		{
			throw tc::crypto::CryptoException("mbedtls_ctr_drbg_seed", MbedtlsErrorUtil::GetRsaErrorAsString(ret));
		}
	}

	~RsaSignerImpl()
	{
		mbedtls_rsa_free( &mRsa );
		mbedtls_ctr_drbg_free( &mCtrDrbg );
		mbedtls_entropy_free( &mEntropy );
	}

	size_t block_size() const { return kKeySize; }
	size_t key_size() const { return kKeySize; }
	size_t signature_size() const { return kKeySize; }
	size_t hash_size() const { return mbedtls_md_get_size(mbedtls_md_info_from_type(HashType)); }

	void initialize(const byte_t* n, const byte_t* p, const byte_t* q, const byte_t* d)
	{
		int ret = 1;

		ret = mbedtls_rsa_import_raw(&mRsa, \
		                       n, n == nullptr ? 0 : kKeySize, \
							   p, p == nullptr ? 0 : kKeySize / 2, \
							   q, q == nullptr ? 0 : kKeySize / 2, \
							   d, d == nullptr ? 0 : kKeySize, \
							   (byte_t[]){0x01, 0x00, 0x01}, 3);
		
		if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_import_raw", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }

		ret = mbedtls_rsa_complete(&mRsa);

		if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_complete", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }
	}

	void initialize(const RsaKey<KeyBitLen>& key)
	{
		initialize(CryptoUtil::IsBufferZeros(key.n.data(), key.n.size()) ? key.n.data() : nullptr, nullptr, nullptr, CryptoUtil::IsBufferZeros(key.private_exponent.data(), key.private_exponent.size()) ? key.private_exponent.data() : nullptr);
	}

	void signData(byte_t* signature, const byte_t* src, size_t src_size)
	{
		auto hash = tc::ByteData(this->hash_size());

		mbedtls_md(mbedtls_md_info_from_type(HashType), src, src_size, hash.get());

		signHash(signature, hash.get());
	}

	bool verifyData(const byte_t* signature, const byte_t* src, size_t src_size)
	{
		auto hash = tc::ByteData(this->hash_size());
		
		mbedtls_md(mbedtls_md_info_from_type(HashType), src, src_size, hash.get());

		return verifyHash(signature, hash.get());
	}

	void signHash(byte_t* signature, const byte_t* hash)
	{
		int ret = mbedtls_rsa_pkcs1_sign(&mRsa, mbedtls_ctr_drbg_random, &mCtrDrbg, MBEDTLS_RSA_PRIVATE, HashType, this->hash_size(), hash, signature);

		if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_pkcs1_sign", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }
	}

	bool verifyHash(const byte_t* signature, const byte_t* hash)
	{
		int ret = mbedtls_rsa_pkcs1_verify(&mRsa, mbedtls_ctr_drbg_random, &mCtrDrbg, MBEDTLS_RSA_PUBLIC, HashType, this->hash_size(), hash, signature);

		if (ret == MBEDTLS_ERR_RSA_VERIFY_FAILED)
		{
			return false;
		}
		else if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_pkcs1_verify", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }

		return true;
	}
private:
	static const size_t kKeySize = KeyBitLen / 8;

	mbedtls_rsa_context mRsa;
    mbedtls_entropy_context mEntropy;
    mbedtls_ctr_drbg_context mCtrDrbg;
};

}}} // namespace tc::crypto::mbedtls_detail