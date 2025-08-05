#include <tc/crypto/detail/EcdhSharedSecretGeneratorImpl.h>
#include <mbedtls/ecp.h>
#include <mbedtls/rsa.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <fmt/core.h>

const std::string tc::crypto::detail::EcdhSharedSecretGeneratorImpl::kClassName = "tc::crypto::detail::EcdhSharedSecretGeneratorImpl";

struct tc::crypto::detail::EcdhSharedSecretGeneratorImpl::ImplCtx
{
	mbedtls_ctr_drbg_context ctr_drbg;
	mbedtls_entropy_context entropy;

	mbedtls_ecp_group grp; // ec group
	mbedtls_mpi d; // source private key
	mbedtls_ecp_point Q; // source public key
	mbedtls_ecp_point P; // target point
};

tc::crypto::detail::EcdhSharedSecretGeneratorImpl::EcdhSharedSecretGeneratorImpl() :
	mImplCtx(new ImplCtx())
{
	mbedtls_entropy_init( &(mImplCtx->entropy) );
	mbedtls_ctr_drbg_init( &(mImplCtx->ctr_drbg) );

	int ret = mbedtls_ctr_drbg_seed( &(mImplCtx->ctr_drbg), mbedtls_entropy_func, &(mImplCtx->entropy), (const unsigned char *)kClassName.c_str(), kClassName.size() );
	switch (ret)
	{
		case (0):
			break;
		case (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED):
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ctr_drbg_seed() Entropy source failed");
		default:
			throw tc::crypto::CryptoException(kClassName, "mbedtls_ctr_drbg_seed() An unexpected error occurred");
	}

	mbedtls_ecp_group_init( &(mImplCtx->grp) );
	mbedtls_mpi_init( &(mImplCtx->d) );
	mbedtls_ecp_point_init( &(mImplCtx->Q) );
	mbedtls_ecp_point_init( &(mImplCtx->P) );
}

tc::crypto::detail::EcdhSharedSecretGeneratorImpl::~EcdhSharedSecretGeneratorImpl()
{
	mbedtls_ecp_point_free( &(mImplCtx->P) );
	mbedtls_ecp_point_free( &(mImplCtx->Q) );
	mbedtls_mpi_free( &(mImplCtx->d) );
	mbedtls_ecp_group_free( &(mImplCtx->grp) );
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

void tc::crypto::detail::EcdhSharedSecretGeneratorImpl::generateSharedSecret(EccCurveType ec_type, byte_t* z, size_t z_size, const byte_t* d, size_t d_size, const byte_t* Q, size_t Q_size)
{
	mbedtls_ecp_group_id group_id = convertToMbedtlsEcpGroupId(ec_type);
	if (group_id == MBEDTLS_ECP_DP_NONE)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, fmt::format("ec_type ({}) was not valid.", (uint32_t)ec_type));
	}

	int ret;

	// clear source d mpi
	ret = mbedtls_mpi_lset( &(mImplCtx->d) , 0 );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_mpi_lset(d) An unexpected error occurred. {:x})", ret));	
	}

	// clear source Q point
	ret = mbedtls_ecp_set_zero( &(mImplCtx->Q) );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_ecp_set_zero(Q) An unexpected error occurred. {:x})", ret));	
	}

	// clear source P point
	ret = mbedtls_ecp_set_zero( &(mImplCtx->P) );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_ecp_set_zero(P) An unexpected error occurred. {:x})", ret));	
	}

	// load ecp group
	ret = mbedtls_ecp_group_load( &(mImplCtx->grp), group_id );
	switch (ret)
	{
		case (0):
			break;
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_ecp_group_load() An unexpected error occurred. {:x})", ret));	
	}

	// get p_len from ecp group
	size_t p_len = mbedtls_mpi_size( &(mImplCtx->grp.P) );

	// import private component (d)
    if (d_size < p_len)
    {
        throw tc::ArgumentOutOfRangeException(kClassName, fmt::format("d size was insufficent {} (expected {})", d_size, p_len));
    }
	ret = mbedtls_mpi_read_binary( &(mImplCtx->d), d, d_size );
	switch (ret)
	{
		case (0):
			break;
		//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_mpi_read_binary(d) An unexpected error occurred.", ret));
	}

	// import public component (Q)
    if (Q_size < (p_len * 2))
    {
        throw tc::ArgumentOutOfRangeException(kClassName, fmt::format("Q size was insufficent {} (expected {})", Q_size, (p_len * 2)));
    }
	ret = mbedtls_mpi_read_binary( &(mImplCtx->Q.X), Q, p_len );
	switch (ret)
	{
		case (0):
			break;
		//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_mpi_read_binary(Q.X) An unexpected error occurred.", ret));
	}
	ret = mbedtls_mpi_read_binary( &(mImplCtx->Q.Y), Q + p_len, p_len );
	switch (ret)
	{
		case (0):
			break;
		//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_mpi_read_binary(Q.Y) An unexpected error occurred.", ret));
	}

	// generate shared secret point (P) from private component (d) and public component (Q)
	ret = mbedtls_ecp_mul( &(mImplCtx->grp), &(mImplCtx->P), &(mImplCtx->d), &(mImplCtx->Q), mbedtls_ctr_drbg_random, &(mImplCtx->ctr_drbg) );
	switch (ret)
	{
		case (0):
			break;
		case (MBEDTLS_ERR_ECP_INVALID_KEY):
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_ecp_mul() Invalid public or private key. {:x})", ret));
		default:
			throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_ecp_mul() An unexpected error occurred. {:x})", ret));
	}
	
	// export shared secret
	if (z != nullptr)
	{
		// if key is < min size
		if (z_size < p_len)
		{
			throw tc::ArgumentNullException(kClassName, "z was not null, z_size was insufficent to store shared secret");
		}

		ret = mbedtls_mpi_write_binary( &(mImplCtx->P.X), z, p_len );
		switch (ret)
		{
			case (0):
				break;
			//case (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL):
			default:
				throw tc::crypto::CryptoException(kClassName, fmt::format("mbedtls_mpi_write_binary() An unexpected error occurred. {:x})", ret));
		}
	}
}