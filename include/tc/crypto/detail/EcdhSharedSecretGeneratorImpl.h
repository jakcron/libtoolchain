	/**
	 * @file EcdhSharedSecretGeneratorImpl.h
	 * @brief Declaration of tc::crypto::detail::EcdhSharedSecretGeneratorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/08/04
	 **/
#pragma once
#include <tc/types.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/crypto/CryptoException.h>
#include <tc/crypto/EccCurveType.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class EcdhSharedSecretGeneratorImpl
	 * @brief This class implements the ECDH shared secret generation.
	 */
class EcdhSharedSecretGeneratorImpl
{
public:
		/**
		 * @brief Default constructor
		 * @details
		 * This initializes ECDH shared secret generator state.
		 */
	EcdhSharedSecretGeneratorImpl();

		/**
		 * @brief Destructor
		 * @details
		 * Cleans up ECDH shared secret generator state.
		 */
	~EcdhSharedSecretGeneratorImpl();

		/**
		 * @brief Generate an ECDH shared secret based on own prvate key, external public key.
		 * 
		 * @param[in]  ec_type Type of Elliptic Curve @ref EccCurveType
		 * @param[out] z      Buffer to store shared secret.
		 * @param[in]  z_size Size of shared secret buffer.
		 * @param[in]  d      Buffer to store private component.
		 * @param[in]  d_size Size of private component buffer.
		 * @param[in]  Q      Buffer to store public component.
		 * @param[in]  Q_size Size of public component buffer.
		 * 
		 * @pre 
		 * - @p ec_type must be of type @ref EccCurveType
         * - @p d & @p Q must be from the same curve.
		 * @post
		 * - @p z will be populated with generated shared secret.
		 * 
		 * @note
		 * - Secret can be optionally not generated if the corresponding input variables are null and zero.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p ec_type was not of type @ref EccCurveType
		 * @throw tc::crypto::CryptoException An unexpected error has occurred.
		 * @throw tc::crypto::CryptoException Something failed during generation of the shared secret.
		 * @throw tc::ArgumentException @p z was not null, but @p z_size was not large enough.
		 * @throw tc::ArgumentException @p d was not null, but @p d_size was not large enough.
		 * @throw tc::ArgumentException @p Q was not null, but @p Q_size was not large enough.
		 */
	void generateSharedSecret(EccCurveType ec_type, byte_t* z, size_t z_size, const byte_t* d, size_t d_size, const byte_t* Q, size_t Q_size);
private:
	static const std::string kClassName;	

	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail