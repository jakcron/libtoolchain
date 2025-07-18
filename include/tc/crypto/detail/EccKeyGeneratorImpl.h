	/**
	 * @file EccKeyGeneratorImpl.h
	 * @brief Declaration of tc::crypto::detail::EccKeyGeneratorImpl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/05/24
	 **/
#pragma once
#include <tc/types.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/crypto/CryptoException.h>
#include <tc/crypto/EccCurveType.h>

namespace tc { namespace crypto { namespace detail {

	/**
	 * @class EccKeyGeneratorImpl
	 * @brief This class implements the RSA key generation.
	 */
class EccKeyGeneratorImpl
{
public:
		/**
		 * @brief Default constructor
		 * @details
		 * This initializes RSA key generator state.
		 */
	EccKeyGeneratorImpl();

		/**
		 * @brief Destructor
		 * @details
		 * Cleans up ECC key generator state.
		 */
	~EccKeyGeneratorImpl();

		/**
		 * @brief Generate an ECC key.
		 * 
		 * @param[in]  ec_type Type of Elliptic Curve @ref EccCurveType
		 * @param[out] d      Buffer to store private component.
		 * @param[in]  d_size Size of private component buffer.
		 * @param[out] Q      Buffer to store public component.
		 * @param[in]  Q_size Size of public component buffer.
		 * 
		 * @pre 
		 * - @p ec_type must be of type @ref EccCurveType
		 * @post
		 * - Key components are exported if the related buffers were not null.
		 * 
		 * @note
		 * - Key components can be optionally not exported if the corresponding input variables are null and zero.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p ec_type was not of type @ref EccCurveType
		 * @throw tc::crypto::CryptoException An unexpected error has occurred.
		 * @throw tc::crypto::CryptoException Something failed during generation of a key.
		 * @throw tc::crypto::CryptoException The random generator failed to generate non-zeros.
		 * @throw tc::ArgumentException @p d was not null, but @p d_size was not large enough.
		 * @throw tc::ArgumentException @p q was not null, but @p q_size was not large enough.
		 */
	void generateKey(EccCurveType ec_type, byte_t* d, size_t d_size, byte_t* Q, size_t Q_size);

		/**
		 * @brief Generate an ECC Public key based on the private component.
		 * 
		 * @param[in]  ec_type Type of Elliptic Curve @ref EccCurveType
		 * @param[in]  d      Buffer to store private component.
		 * @param[in]  d_size Size of private component buffer.
		 * @param[out] Q      Buffer to store public component.
		 * @param[in]  Q_size Size of public component buffer.
		 * 
		 * @pre 
		 * - @p ec_type must be of type @ref EccCurveType
		 * @post
		 * - Key components are exported if the related buffers were not null.
		 * 
		 * @note
		 * - Key components can be optionally not exported if the corresponding input variables are null and zero.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p ec_type was not of type @ref EccCurveType
		 * @throw tc::crypto::CryptoException An unexpected error has occurred.
		 * @throw tc::crypto::CryptoException Something failed during generation of a key.
		 * @throw tc::crypto::CryptoException The random generator failed to generate non-zeros.
		 * @throw tc::ArgumentException @p d was null, or @p d_size was not large enough.
		 * @throw tc::ArgumentException @p q was not null, but @p q_size was not large enough.
		 */
	void generatePublicKey(EccCurveType ec_type, byte_t* d, size_t d_size, byte_t* Q, size_t Q_size);
private:
	static const std::string kClassName;	

	struct ImplCtx;
	std::unique_ptr<ImplCtx> mImplCtx;
};

}}} // namespace tc::crypto::detail