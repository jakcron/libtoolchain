	/**
	 * @file EccUtil.h
	 * @brief Declaration of tc::crypto::EccUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/06/08
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/EccCurveType.h>

namespace tc { namespace crypto {

	/**
	 * @class EccUtil
	 * @brief Utility functions for ECC operations based classes.
	 **/
class EccUtil
{
public:
		/**
		 * @brief Get length of ECC integer in bits.
		 **/
	static size_t eccIntegerBitLength(EccCurveType curve_type);

    	/**
		 * @brief Get length of ECC integer in bytes (rounding up).
		 **/
	static size_t eccIntegerByteLength(EccCurveType curve_type);
};

}} // namespace tc::crypto