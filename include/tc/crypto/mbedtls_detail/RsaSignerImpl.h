	/**
	 * @file RsaSignerImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::RsaSignerImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/19
	 **/
#pragma once

#include <tc/crypto/ISigner.h>
#include <tc/crypto/IHashSigner.h>

#include <tc/ByteData.h>
#include <tc/crypto/RsaKey.h>
#include <tc/crypto/CryptoUtil.h>
#include <tc/crypto/CryptoException.h>
#include <tc/crypto/mbedtls_detail/MbedtlsErrorUtil.h>

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
	static_assert(KeyBitLen == 1024 || KeyBitLen == 2048 || KeyBitLen == 4096, "RsaSignerImpl only supports 1024, 2048 and 4096 key bit lengths.");

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

	void initialize(const byte_t* n, const byte_t* p, const byte_t* q, const byte_t* d, const byte_t* e)
	{
		int ret = 1;

		ret = mbedtls_rsa_import_raw(&mRsa, \
		                       n, n == nullptr ? 0 : kKeySize, \
							   p, p == nullptr ? 0 : kKeySize / 2, \
							   q, q == nullptr ? 0 : kKeySize / 2, \
							   d, d == nullptr ? 0 : kKeySize, \
							   e == nullptr ? (byte_t[]){0x01, 0x00, 0x01} : e, e == nullptr ? 3 : kKeySize);
		
		if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_import_raw", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }

		ret = mbedtls_rsa_complete(&mRsa);

		if (ret != 0) { throw tc::crypto::CryptoException("mbedtls_rsa_complete", MbedtlsErrorUtil::GetRsaErrorAsString(ret)); }
	}

	void initialize(const RsaKey<KeyBitLen>& key)
	{
		initialize(\
			CryptoUtil::IsBufferZeros(key.n.data(), key.n.size()) ? key.n.data() : nullptr, \
			CryptoUtil::IsBufferZeros(key.p.data(), key.p.size()) ? key.p.data() : nullptr, \
			CryptoUtil::IsBufferZeros(key.q.data(), key.q.size()) ? key.q.data() : nullptr, \
			CryptoUtil::IsBufferZeros(key.d.data(), key.d.size()) ? key.d.data() : nullptr, \
			CryptoUtil::IsBufferZeros(key.e.data(), key.e.size()) ? key.e.data() : nullptr
		);
	}

	void signData(byte_t* signature, const byte_t* src, size_t src_size)
	{
		auto hash = tc::ByteData(this->hash_size());

		mbedtls_md(mbedtls_md_info_from_type(HashType), src, src_size, hash.data());

		signHash(signature, hash.data());
	}

	bool verifyData(const byte_t* signature, const byte_t* src, size_t src_size)
	{
		auto hash = tc::ByteData(this->hash_size());
		
		mbedtls_md(mbedtls_md_info_from_type(HashType), src, src_size, hash.data());

		return verifyHash(signature, hash.data());
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