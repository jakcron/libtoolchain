#include <tc/crypto/detail/EccKeyGeneratorImpl.h>
#include <mbedtls/ecp.h>
#include <mbedtls/rsa.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>

const std::string tc::crypto::detail::EccKeyGeneratorImpl::kClassName = "tc::crypto::detail::EccKeyGeneratorImpl";

struct tc::crypto::detail::EccKeyGeneratorImpl::ImplCtx
{
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_entropy_context entropy;
};

tc::crypto::detail::EccKeyGeneratorImpl::EccKeyGeneratorImpl() :
	mImplCtx(new ImplCtx())
{
	mbedtls_entropy_init( &(mImplCtx->entropy) );
	mbedtls_ctr_drbg_init( &(mImplCtx->ctr_drbg) );

	int ret = mbedtls_ctr_drbg_seed(&(mImplCtx->ctr_drbg), mbedtls_entropy_func, &(mImplCtx->entropy), (const unsigned char *)kClassName.c_str(), kClassName.size());
	switch (ret)
	{
		case (0):
			break;
		case (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED):
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ctr_drbg_seed() Entropy source failed");
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ctr_drbg_seed() An unexpected error occurred");
	}
}

tc::crypto::detail::EccKeyGeneratorImpl::~EccKeyGeneratorImpl()
{
	mbedtls_ctr_drbg_free( &(mImplCtx->ctr_drbg) );
	mbedtls_entropy_free( &(mImplCtx->entropy) );
}

static mbedtls_ecp_group_id convertToMbedtlsEcpGroupId(tc::crypto::EccCurveType ec_type)
{
	mbedtls_ecp_group_id group_id = MBEDTLS_ECP_DP_NONE;
	switch (ec_type)
	{
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192R1:
			group_id = MBEDTLS_ECP_DP_SECP192R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP224R1:
			group_id = MBEDTLS_ECP_DP_SECP224R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP256R1:
			group_id = MBEDTLS_ECP_DP_SECP256R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP384R1:
			group_id = MBEDTLS_ECP_DP_SECP384R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP521R1:
			group_id = MBEDTLS_ECP_DP_SECP521R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP256R1:
			group_id = MBEDTLS_ECP_DP_BP256R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP384R1:
			group_id = MBEDTLS_ECP_DP_BP384R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP512R1:
			group_id = MBEDTLS_ECP_DP_BP512R1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_CURVE25519:
			group_id = MBEDTLS_ECP_DP_CURVE25519;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192K1:
			group_id = MBEDTLS_ECP_DP_SECP192K1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP224K1:
			group_id = MBEDTLS_ECP_DP_SECP224K1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP256K1:
			group_id = MBEDTLS_ECP_DP_SECP256K1;
			break;
		case tc::crypto::EccCurveType::ECC_CURVE_TYPE_CURVE448:
			group_id = MBEDTLS_ECP_DP_CURVE448;
			break;
	}

	return group_id;
}

void tc::crypto::detail::EccKeyGeneratorImpl::generateKey(EccCurveType ec_type, byte_t* d, size_t d_size, byte_t* q, size_t q_size)
{
	mbedtls_ecp_group_id group_id = convertToMbedtlsEcpGroupId(ec_type);
	if (group_id == MBEDTLS_ECP_DP_NONE)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "ec_type was not valid.");
	}

	mbedtls_ecp_keypair key;
	mbedtls_ecp_keypair_init( &key );

	int ret = 1;
	
	// generate key
	ret = mbedtls_ecp_gen_key(group_id, &key, mbedtls_ctr_drbg_random, &(mImplCtx->ctr_drbg));
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ecp_gen_key() An unexpected error occurred.");
	}
	
	// export private component
	if (d != nullptr)
	{
		size_t d_len = mbedtls_mpi_size( &key.d );
		if (d_size < d_len)
		{
			throw tc::ArgumentNullException(kClassName, "d was not null, but d_size was insufficent to store private exponent");
		}

		ret = mbedtls_mpi_write_binary( &key.d, d, std::min<size_t>(d_size, d_len) );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_write_binary() An unexpected error occurred.");
		}
	}
	
	// export public component
	if (q != nullptr)
	{
		size_t p_len = mbedtls_mpi_size( &key.grp.P );

		// if key is < min size
		if (q_size < (p_len * 2))
		{
			throw tc::ArgumentNullException(kClassName, "q was not null, q_size was insufficent to store public exponent");
		}

		ret = mbedtls_mpi_write_binary( &key.Q.X, q, p_len );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_write_binary() An unexpected error occurred.");
		}

		ret = mbedtls_mpi_write_binary( &key.Q.Y, q + p_len, p_len );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_write_binary() An unexpected error occurred.");
		}
	}
	
	// clear key from mbedtls context
	mbedtls_ecp_keypair_free( &key );
}

void tc::crypto::detail::EccKeyGeneratorImpl::generatePublicKey(EccCurveType ec_type, byte_t* d, size_t d_size, byte_t* q, size_t q_size)
{
	mbedtls_ecp_group_id group_id = convertToMbedtlsEcpGroupId(ec_type);
	if (group_id == MBEDTLS_ECP_DP_NONE) { throw tc::ArgumentOutOfRangeException(kClassName, "ec_type was not valid."); }
	if (d == nullptr) { throw tc::ArgumentNullException(kClassName, "d was null"); }

	mbedtls_ecp_keypair key;
	mbedtls_ecp_keypair_init( &key );

	int ret = 1;
	// load group
	ret = mbedtls_ecp_group_load( &key.grp, group_id );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ecp_group_load() An unexpected error occurred.");
	}

	// import private component (d)
	ret = mbedtls_mpi_read_binary( &key.d, d, d_size );
	switch (ret)
	{
		case (0):
			break;
		//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_read_binary() An unexpected error occurred.");
	}

	// generate public component (Q) from private exponent (d) and base point (G)
	ret = mbedtls_ecp_mul( &key.grp, &key.Q, &key.d, &key.grp.G, mbedtls_ctr_drbg_random, &(mImplCtx->ctr_drbg) );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ecp_mul() An unexpected error occurred.");
	}
	
	// export public component
	if (q != nullptr)
	{
		size_t p_len = mbedtls_mpi_size( &key.grp.P );

		// if key is < min size
		if (q_size < (p_len * 2))
		{
			throw tc::ArgumentNullException(kClassName, "q was not null, q_size was insufficent to store public exponent");
		}

		ret = mbedtls_mpi_write_binary( &key.Q.X, q, p_len );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_write_binary() An unexpected error occurred.");
		}

		ret = mbedtls_mpi_write_binary( &key.Q.Y, q + p_len, p_len );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, "mbedtls_mpi_write_binary() An unexpected error occurred.");
		}
	}
	
	// clear key from mbedtls context
	mbedtls_ecp_keypair_free( &key );
}