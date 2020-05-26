	/**
	 * @file RsaKeyGeneratorImpl.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::RsaKeyGeneratorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/21
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
	 * @class RsaKeyGeneratorImpl
	 * @brief This class implements RSA key generation with mbedtls
	 **/
template <size_t KeyBitLen>
class RsaKeyGeneratorImpl
{
public:
	static_assert(KeyBitLen == 1024 || KeyBitLen == 2048 || KeyBitLen == 4096, "RsaKeyGeneratorImpl only supports 1024, 2048 and 4096 key bit lengths.");

	RsaKeyGeneratorImpl()
	{
		std::string pers = "tc::crypto::mbedtls_detail::RsaKeyGeneratorImpl";

		mbedtls_entropy_init( &mEntropy );
		mbedtls_ctr_drbg_init( &mCtrDrbg );
		mbedtls_rsa_init( &mRsa, 0, 0 );

		int ret = 1;

		if ( (ret = mbedtls_ctr_drbg_seed(&mCtrDrbg, mbedtls_entropy_func, &mEntropy, (const unsigned char *)pers.c_str(), pers.length())) != 0)
		{
			throw tc::crypto::CryptoException("mbedtls_ctr_drbg_seed", MbedtlsErrorUtil::GetRsaErrorAsString(ret));
		}
	}

	~RsaKeyGeneratorImpl()
	{
		mbedtls_rsa_free( &mRsa );
		mbedtls_ctr_drbg_free( &mCtrDrbg );
		mbedtls_entropy_free( &mEntropy );
	}

	size_t key_size() const { return kKeySize; }

	RsaKey<KeyBitLen> generateKey()
	{
		int ret = 1;
		
		// generate key
		ret = mbedtls_rsa_gen_key(&mRsa, mbedtls_ctr_drbg_random, &mCtrDrbg, KeyBitLen, 0x10001);

		if (ret != 0)
		{
			throw tc::crypto::CryptoException("mbedtls_rsa_gen_key", MbedtlsErrorUtil::GetRsaErrorAsString(ret));
		}

		// export key from mbedtls context
		RsaKey<KeyBitLen> rsa_key;
		ret = mbedtls_rsa_export_raw(&mRsa, \
			rsa_key.n.data(), rsa_key.n.size(), \
			rsa_key.p.data(), rsa_key.p.size(), \
			rsa_key.q.data(), rsa_key.q.size(), \
			rsa_key.d.data(), rsa_key.d.size(), \
			rsa_key.e.data(), rsa_key.e.size(), \
		);

		if (ret != 0)
		{
			throw tc::crypto::CryptoException("mbedtls_rsa_export_raw", MbedtlsErrorUtil::GetRsaErrorAsString(ret));
		}

		// clear key from mbedtls context
		mbedtls_rsa_init( &mRsa, PaddingId, HashType );

		// return key
		return rsa_key;
	}

private:
	static const size_t kKeySize = KeyBitLen / 8;

	mbedtls_rsa_context mRsa;
    mbedtls_entropy_context mEntropy;
    mbedtls_ctr_drbg_context mCtrDrbg;
};

}}} // namespace tc::crypto::mbedtls_detail