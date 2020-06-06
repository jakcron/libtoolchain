	/**
	 * @file HmacSha512Generator.h
	 * @brief Declarations for API resources for HMAC-SHA-512 calculations.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/06/06
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/Sha512Generator.h>
#include <tc/crypto/HmacGenerator.h>

namespace tc { namespace crypto {

	/**
	 * @typedef HmacSha512Generator
	 * @brief Class for calculating HMAC-SHA-512.
	 * 
	 * @details This class calcualtes MAC using SHA-512.
	 * For more information refer to @ref HmacGenerator.
	 */
using HmacSha512Generator = HmacGenerator<Sha512Generator>;

	/**
	 * @brief Utility function for calculating HMAC-SHA-512.
	 * 
	 * @param[out] mac Pointer to the buffer storing the MAC.
	 * @param[in]  data Pointer to input data.
	 * @param[in]  data_size Size in bytes of input data.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - Size of the MAC buffer must >= <tt>HmacSha512Generator::kMacSize</tt>.
	 * 
	 * @post
	 * - The MAC is written to <tt><var>mac</var></tt>.
	 * 
	 * @details
	 * This function calculates a MAC for the passed in data array.
	 * To calculate a MAC for data split into multiple arrays, use the @ref HmacSha512Generator class.
	 */
void GenerateHmacSha512Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);

}} // namespace tc::crypto