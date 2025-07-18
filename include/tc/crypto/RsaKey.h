	/**
	 * @file RsaKey.h
	 * @brief Declarations for structures to store RSA keys.
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2025/06/01
	 **/
#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

namespace tc { namespace crypto {

	/**
	 * @struct RsaKey
	 * @brief Struct for storing a RSA key. For use with RSA calculations.
	 */
struct RsaKey
{
	tc::ByteData n; /**< Modulus */
	tc::ByteData e; /**< Public exponent */
	tc::ByteData d; /**< Private exponent */
};

	/**
	 * @struct RsaPublicKey
	 * @brief This extends RsaKey, exposing a constructor to create a RSA public key from a modulus (and optionally a public exponent).
	 */
struct RsaPublicKey : public RsaKey
{
		/**
		 * @brief This constructs a @ref RsaKey from a modulus and the default public exponent (0x10001).
		 * 
		 * @param[in] modulus Buffer containing big-endian modulus.
		 * @param[in] modulus_size Size in bytes of modulus.
		 * 
		 * @pre @p modulus != nullptr
		 * @pre @p modulus_size != 0
		 */
	RsaPublicKey(const byte_t* modulus, size_t modulus_size);

		/**
		 * @brief This constructs a @ref RsaKey from a modulus, and a public exponent.
		 * 
		 * @param[in] modulus Buffer containing big-endian modulus.
		 * @param[in] modulus_size Size in bytes of modulus.
		 * @param[in] public_exponent Buffer containing big-endian public exponent.
		 * @param[in] public_exponent_size Size in bytes of public exponent.
		 * 
		 * @pre @p modulus != nullptr
		 * @pre @p modulus_size != 0
		 * @pre @p public_exponent != nullptr
		 * @pre @p public_exponent_size != 0
		 */
	RsaPublicKey(const byte_t* modulus, size_t modulus_size, const byte_t* public_exponent, size_t public_exponent_size);
};

	/**
	 * @struct RsaPrivateKey
	 * @brief This extends RsaKey, exposing a constructor to create a RSA private key from a modulus and private exponent.
	 */
struct RsaPrivateKey : public RsaKey
{
		/**
		 * @brief This constructs a @ref RsaKey from a modulus, private exponent, and the default public exponent (0x10001).
		 * 
		 * @param[in] modulus Buffer containing big-endian modulus.
		 * @param[in] modulus_size Size in bytes of modulus.
		 * @param[in] private_exponent Buffer containing big-endian private exponent.
		 * @param[in] private_exponent_size Size in bytes of private exponent.
		 * 
		 * @pre @p modulus != nullptr
		 * @pre @p modulus_size != 0
		 * @pre @p private_exponent != nullptr
		 * @pre @p private_exponent_size != 0
		 */
	RsaPrivateKey(const byte_t* modulus, size_t modulus_size, const byte_t* private_exponent, size_t private_exponent_size);

		/**
		 * @brief This constructs a @ref RsaKey from a modulus, private exponent, and the default public exponent (0x10001).
		 * 
		 * @param[in] modulus Buffer containing big-endian modulus.
		 * @param[in] modulus_size Size in bytes of modulus.
		 * @param[in] public_exponent Buffer containing big-endian public exponent.
		 * @param[in] public_exponent_size Size in bytes of public exponent.
		 * @param[in] private_exponent Buffer containing big-endian private exponent.
		 * @param[in] private_exponent_size Size in bytes of private exponent.
		 * 
		 * @pre @p modulus != nullptr
		 * @pre @p modulus_size != 0
		 * @pre @p private_exponent != nullptr
		 * @pre @p private_exponent_size != 0
		 * @pre @p public_exponent != nullptr
		 * @pre @p public_exponent_size != 0
		 */
	RsaPrivateKey(const byte_t* modulus, size_t modulus_size, const byte_t* public_exponent, size_t public_exponent_size, const byte_t* private_exponent, size_t private_exponent_size);


		/**
		 * @brief Generate public key from this private key.
		 * 
		 * @return RsaKey containing the public key.
		 */
	RsaKey getPublicKey();
};

}} // namespace tc::crypto