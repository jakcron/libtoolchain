	/**
	 * @file EccKey.h
	 * @brief Declarations for structures to store ECC keys.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/06/01
	 **/
#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>
#include <tc/crypto/EccCurveType.h>

#include <tc/ArgumentException.h>

namespace tc { namespace crypto {


	/**
	 * @struct EccKey
	 * @brief Struct for storing a ECC key. For use with ECC operations.
	 * 
	 * @note The public/private components are not compressed.
	 */
struct EccKey
{
    EccCurveType curve_type;
	tc::ByteData d; /**< Private component - big endian d integer */
	tc::ByteData Q; /**< Public component - big endian Q point */
};

	/**
	 * @struct EccPublicKey
	 * @brief This extends EccKey, exposing a constructor to create an ECC public key.
	 */
struct EccPublicKey : public EccKey
{
		/**
		 * @brief This constructs a @ref EccKey from the public component.
		 * 
		 * @param[in] curve_type ECC Curve Type.
         * @param[in] Q Buffer containing big-endian Q point.
		 * @param[in] Q_size Size in bytes of Q.
		 * 
		 * @pre @p ec_type must be of type @ref EccCurveType
         * @pre @p Q != nullptr
		 * @pre @p Q_size != 0
		 */
	EccPublicKey(EccCurveType curve_type, const byte_t* Q, size_t Q_size);
};

	/**
	 * @struct EccPrivateKey
	 * @brief This extends EccKey, exposing a constructor to create an ECC private key from a modulus and private exponent.
	 */
struct EccPrivateKey : public EccKey
{
		/**
		 * @brief This constructs a @ref EccKey from the private and public components.
		 * 
		 * @param[in] curve_type ECC Curve Type
         * @param[in] d Buffer containing big-endian d integer.
		 * @param[in] d_size Size in bytes of d.
         * @param[in] Q Buffer containing big-endian Q point.
		 * @param[in] Q_size Size in bytes of Q.
		 * 
		 * @pre @p ec_type must be of type @ref EccCurveType
         * @pre @p d != nullptr
		 * @pre @p d_size != 0
         * @pre @p Q != nullptr
		 * @pre @p Q_size != 0
		 */
	EccPrivateKey(EccCurveType curve_type, const byte_t* d, size_t d_size, const byte_t* Q, size_t Q_size);

		/**
		 * @brief This constructs a @ref EccKey from the private component (and generate the public component).
		 * 
		 * @param[in] curve_type ECC Curve Type
         * @param[in] d Buffer containing big-endian d integer.
		 * @param[in] d_size Size in bytes of d.
		 * 
         * @pre @p ec_type must be of type @ref EccCurveType
         * @pre @p d != nullptr
		 * @pre @p d_size != 0
		 */
	EccPrivateKey(EccCurveType curve_type, const byte_t* d, size_t d_size);
    
        /**
		 * @brief Generate public key from this private key.
		 * 
		 * @return EccKey containing the public key.
		 */
	EccKey getPublicKey();
};

}} // namespace tc::crypto