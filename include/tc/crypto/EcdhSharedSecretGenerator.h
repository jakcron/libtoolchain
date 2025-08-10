	/**
	 * @file EcdhSharedSecretGenerator.h
	 * @brief Declarations for API resources for using ECC keys to generate shared secrets using ECDH.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2025/08/06
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/EccKey.h>
#include <tc/crypto/EccUtil.h>
#include <tc/crypto/detail/EcdhSharedSecretGeneratorImpl.h>

#include <tc/ArgumentNullException.h>

namespace tc { namespace crypto {

	/**
	 * @class EcdhSharedSecretGenerator
	 * @brief Class for using ECC keys to generate shared secrets using ECDH.
	 */
class EcdhSharedSecretGenerator
{
public:
		/**
		 * @brief Default constructor.
		 */
	EcdhSharedSecretGenerator() :
        mState(State_NotInitialized),
		mImpl()
	{}

        /**
         * @brief Utility function for generating an ECDH shared secret.

         * @param[in]  private_key ECC private key of the current party.
         * @param[in]  public_key ECC public key of other party.
         * 
         * @throw tc::crypto::ArgumentException  @p private_key was not a valid private key.
         * @throw tc::crypto::ArgumentException  @p public_key was not a valid public key.
         * @throw tc::crypto::ArgumentException  @p private_key or @p public_key curve type is not supported/valid.
         * @throw tc::crypto::ArgumentException @p private_key and @p public_key did not have the same curve type.
         */
    void initialize(const EccKey& private_key, const EccKey& public_key)
    {
        if (private_key.curve_type != public_key.curve_type)
        {
            throw tc::ArgumentOutOfRangeException("private_key and public_key did not have the same curve type.");
        }

        size_t ecc_integer_len = EccUtil::eccIntegerByteLength(private_key.curve_type);
        
        if (ecc_integer_len == 0)
        {
            throw tc::ArgumentOutOfRangeException("private_key or public_key curve type is not supported/valid.");
        }

        if (private_key.d.size() != ecc_integer_len)
        {
            throw tc::ArgumentOutOfRangeException("private_key was not a valid private key.");
        }

        if (public_key.Q.size() != (ecc_integer_len * 2))
        {
            throw tc::ArgumentOutOfRangeException("public_key was not a valid public key.");
        }

        mPrivateKey = private_key;
        mPublicKey = public_key;

        mState = State_Initialized;
    }

        /**
         * @brief Utility function for generating an ECDH shared secret.
         * 
         * @param[out] data Buffer to hold shared secret data.
         * @param[in]  data_size Size of @p data buffer.
         * 
         * @post
         * - The generated shared secret is written to <tt><var>data</var></tt> up to <tt><var>data_size</var></tt> bytes.
         * - Shared secret length cannot exceed the bitsize of the curve.
         * 
         * @throw tc::crypto::ArgumentNullException @p data_size > 0 but @p data was not nullptr.
         */
	void generateSharedSecretBytes(byte_t* data, size_t data_size)
	{
        if (mState != State_Initialized)
            return;

        // todo input sani logic here
        if (data_size > 0 && data != nullptr)
        {
            throw tc::ArgumentNullException("data_size > 0 but data was not nullptr.");
        }

		mImpl.generateSharedSecret(mPrivateKey.curve_type, data, data_size, mPrivateKey.d.data(), mPrivateKey.d.size(), mPublicKey.Q.data(), mPublicKey.Q.size());
	}

private:
    enum State 
    {
        State_NotInitialized,
        State_Initialized
    };

    State mState;
    tc::crypto::EccKey mPrivateKey;
    tc::crypto::EccKey mPublicKey;
	detail::EcdhSharedSecretGeneratorImpl mImpl;
};

	/**
	 * @brief Utility function for generating an ECDH shared secret.
	 * 
     * @param[out] data Buffer to hold shared secret data.
	 * @param[in]  data_size Size of @p data buffer.
     * @param[in]  private_key ECC private key of the current party.
     * @param[in]  public_key ECC public key of other party.
	 * 
	 * @post
	 * - The generated shared secret is written to <tt><var>data</var></tt> up to <tt><var>data_size</var></tt> bytes.
     * - Shared secret length cannot exceed the bitsize of the curve.
	 * 
	 * @throw tc::crypto::ArgumentNullException @p data_size > 0 but @p data was not nullptr.
     * @throw tc::crypto::ArgumentException  @p private_key was not a valid private key.
     * @throw tc::crypto::ArgumentException  @p public_key was not a valid public key.
     * @throw tc::crypto::ArgumentException  @p private_key or @p public_key curve type is not supported/valid.
     * @throw tc::crypto::ArgumentException @p private_key and @p public_key did not have the same curve type.
	 */
void GenerateEcdhSharedSecret(byte_t* data, size_t data_size, const EccKey& private_key, const EccKey& public_key);

}} // namespace tc::crypto