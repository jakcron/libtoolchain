#include <tc/crypto/mbedtls_detail/MbedtlsErrorUtil.h>

#include <mbedtls/rsa.h>

std::string tc::crypto::mbedtls_detail::MbedtlsErrorUtil::GetRsaErrorAsString(int error_code)
{
	std::string error_string = "";
	switch (error_code)
	{
		case (MBEDTLS_ERR_RSA_BAD_INPUT_DATA):
			error_string = "Bad input parameters to function.";
			break;
		case (MBEDTLS_ERR_RSA_INVALID_PADDING):
			error_string = "Input data contains invalid padding and is rejected.";
			break;
		case (MBEDTLS_ERR_RSA_KEY_GEN_FAILED):
			error_string = "Something failed during generation of a key.";
			break;
		case (MBEDTLS_ERR_RSA_KEY_CHECK_FAILED):
			error_string = "Key failed to pass the validity check of the library.";
			break;
		case (MBEDTLS_ERR_RSA_PUBLIC_FAILED):
			error_string = "The public key operation failed.";
			break;
		case (MBEDTLS_ERR_RSA_PRIVATE_FAILED):
			error_string = "The private key operation failed.";
			break;
		case (MBEDTLS_ERR_RSA_VERIFY_FAILED):
			error_string = "The PKCS#1 verification failed.";
			break;
		case (MBEDTLS_ERR_RSA_OUTPUT_TOO_LARGE):
			error_string = "The output buffer for decryption is not large enough.";
			break;
		case (MBEDTLS_ERR_RSA_RNG_FAILED):
			error_string = "The random generator failed to generate non-zeros.";
			break;
	}

	return error_string;
}