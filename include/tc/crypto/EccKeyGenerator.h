	/**
	 * @file EccKeyGenerator.h
	 * @brief Declarations for API resources for generating ECC keys.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/06/01
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/EccKey.h>
#include <tc/crypto/EccUtil.h>
#include <tc/crypto/detail/EccKeyGeneratorImpl.h>

namespace tc { namespace crypto {

	/**
	 * @class EccKeyGenerator
	 * @brief Class for generating ECC keys.
	 * 
	 * @details
	 * The underlying PRNG algorithm is CTR_DBRG.
	 */
class EccKeyGenerator
{
public:
		/**
		 * @brief Default constructor.
		 */
	EccKeyGenerator() :
		mImpl()
	{}

		/**
		 * @brief Generate an ECC key.
		 * 
		 * @param[out] key Reference to generated ECC key.
		 * @param[in]  curve_type ECC Curve Type.
		 * 
		 * @pre
		 * - @p ec_type must be of type @ref EccCurveType
		 * 
		 * @post
		 * - The generated key is written to <tt><var>key</var></tt>.
		 * 
		 * @throw tc::crypto::ArgumentException @p curve_type was not supported/valid.
		 */
	void generateKey(EccKey& key, EccCurveType curve_type)
	{
		size_t ecc_int_byte_length = EccUtil::eccIntegerByteLength(curve_type);

		if (ecc_int_byte_length == 0) throw tc::ArgumentException("tc::crypto::EccKeyGenerator::generateKey()", "curve_type was not supported/valid");

		key.curve_type = curve_type;
		key.d = tc::ByteData(ecc_int_byte_length);
		key.Q = tc::ByteData(ecc_int_byte_length * 2);

		mImpl.generateKey(curve_type, key.d.data(), key.d.size(), key.Q.data(), key.Q.size());
	}

		/**
		 * @brief Generate an ECC public key from an ECC private key key.
		 * 
		 * @param[out] public_key Object to store generated public key.
		 * @param[in]  private_key Private key to generate public key from.
		 * 
		 * @post
		 * - The generated public key is written to <tt><var>public_key</var></tt>.
		 * 
		 * @throw tc::crypto::ArgumentException @p private_key curve_type was not supported/valid.
		 */
	void generatePublicKey(EccKey& public_key, const EccKey& private_key)
	{
		size_t ecc_int_byte_length = EccUtil::eccIntegerByteLength(private_key.curve_type);

		if (ecc_int_byte_length == 0) throw tc::ArgumentException("tc::crypto::EccKeyGenerator::generatePublicKey()", "curve_type was not supported/valid");

		public_key.curve_type = private_key.curve_type;
		public_key.d = tc::ByteData(0);
		public_key.Q = tc::ByteData(ecc_int_byte_length * 2);

		mImpl.generatePublicKey(public_key.curve_type, private_key.d.data(), private_key.d.size(), public_key.Q.data(), public_key.Q.size());
	}

private:
	detail::EccKeyGeneratorImpl mImpl;
};

	/**
	 * @brief Utility function for generating an ECC key.
	 * 
	 * @param[out] key Object to store generated ECC key.
	 * @param[in]  curve_type Type of ECC curve to generate
	 * 
	 * @post
	 * - The generated key is written to <tt><var>key</var></tt>.
	 * 
	 * @throw tc::crypto::ArgumentException @p curve_type was not supported/valid.
	 */
void GenerateEccKey(EccKey& key, EccCurveType curve_type);

	/**
	 * @brief Utility function for generating an ECC public key from an ECC private key.
	 * 
	 * @param[out] public_key Object to store generated public key.
	 * @param[in]  private_key Private key to generate public key from.
	 * 
	 * @post
	 * - The generated public key is written to <tt><var>public_key</var></tt>.
	 * 
	 * @throw tc::crypto::ArgumentException @p curve_type was not supported/valid.
	 */
void GenerateEccPublicKey(EccKey& public_key, const EccKey& private_key);

}} // namespace tc::crypto