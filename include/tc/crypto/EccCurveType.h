	/**
	 * @file EccCurveType.h
	 * @brief Declaration of tc::crypto::EccCurveType
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/06/01
	 **/
#pragma once

namespace tc { namespace crypto {

    /**
	 * @struct EccCurveType
	 * @brief Defines supported ECC curves 
	 */
enum EccCurveType
{
    ECC_CURVE_TYPE_SECP192R1,      /**< The 192-bit curve defined by FIPS 186-4 and SEC1. */
    ECC_CURVE_TYPE_SECP224R1,      /**< The 224-bit curve defined by FIPS 186-4 and SEC1. */
    ECC_CURVE_TYPE_SECP256R1,      /**< The 256-bit curve defined by FIPS 186-4 and SEC1. */
    ECC_CURVE_TYPE_SECP384R1,      /**< The 384-bit curve defined by FIPS 186-4 and SEC1. */
    ECC_CURVE_TYPE_SECP521R1,      /**< The 521-bit curve defined by FIPS 186-4 and SEC1. */
    ECC_CURVE_TYPE_BP256R1,        /**< 256-bit Brainpool curve. */
    ECC_CURVE_TYPE_BP384R1,        /**< 384-bit Brainpool curve. */
    ECC_CURVE_TYPE_BP512R1,        /**< 512-bit Brainpool curve. */
    ECC_CURVE_TYPE_CURVE25519,     /**< Curve25519. */
    ECC_CURVE_TYPE_SECP192K1,      /**< 192-bit "Koblitz" curve. */
    ECC_CURVE_TYPE_SECP224K1,      /**< 224-bit "Koblitz" curve. */
    ECC_CURVE_TYPE_SECP256K1,      /**< 256-bit "Koblitz" curve. */
    ECC_CURVE_TYPE_CURVE448,       /**< Curve448. */
};

}} // namespace tc::io