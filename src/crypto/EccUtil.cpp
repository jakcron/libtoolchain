#include <tc/crypto/EccUtil.h>

size_t tc::crypto::EccUtil::eccIntegerBitLength(EccCurveType curve_type)
{
    size_t ecc_int_bit_length = 0;
    switch (curve_type)
    {
        case (ECC_CURVE_TYPE_SECP192R1):
            ecc_int_bit_length = 192;
            break;
        case (ECC_CURVE_TYPE_SECP224R1):
            ecc_int_bit_length = 224;
            break;
        case (ECC_CURVE_TYPE_SECP256R1):
            ecc_int_bit_length = 256;
            break;
        case (ECC_CURVE_TYPE_SECP384R1):
            ecc_int_bit_length = 384;
            break;
        case (ECC_CURVE_TYPE_SECP521R1):
            ecc_int_bit_length = 521; 
            break;
        case (ECC_CURVE_TYPE_BP256R1):
            ecc_int_bit_length = 256;
            break;
        case (ECC_CURVE_TYPE_BP384R1):
            ecc_int_bit_length = 384;
            break;
        case (ECC_CURVE_TYPE_BP512R1):
            ecc_int_bit_length = 512;
            break;
        case (ECC_CURVE_TYPE_CURVE25519):
            ecc_int_bit_length = 255;
            break;
        case (ECC_CURVE_TYPE_SECP192K1):
            ecc_int_bit_length = 192;
            break;
        case (ECC_CURVE_TYPE_SECP224K1):
            ecc_int_bit_length = 224;
            break;
        case (ECC_CURVE_TYPE_SECP256K1):
            ecc_int_bit_length = 256;
            break;
        case (ECC_CURVE_TYPE_CURVE448):
            ecc_int_bit_length = 448;
            break;
        default:
            ecc_int_bit_length = 0;
            break;
    }

    return ecc_int_bit_length;
}

size_t tc::crypto::EccUtil::eccIntegerByteLength(EccCurveType curve_type)
{
    size_t ecc_int_bit_length = eccIntegerBitLength(curve_type);
    return ecc_int_bit_length / 8 + (ecc_int_bit_length % 8 != 0);
}
