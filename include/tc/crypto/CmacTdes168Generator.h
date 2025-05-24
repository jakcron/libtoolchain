	/**
	 * @file CmacTdes168Generator.h
	 * @brief Declarations for API resources for CMAC-TDES-168 calculations.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2024/12/10
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/TdesEncryptor.h>
#include <tc/crypto/CmacGenerator.h>

namespace tc { namespace crypto {

	/**
	 * @typedef CmacTdes168Generator
	 * @brief Class for calculating CMAC-TDES-168.
	 * 
	 * @details This class calcualtes CMAC using TDES-168.
	 * For more information refer to @ref CmacGenerator.
	 */
using CmacTdes168Generator = CmacGenerator<Tdes168Encryptor>;

	/**
	 * @brief Utility function for calculating CMAC-TDES-168.
	 * 
	 * @param[out] mac Pointer to the buffer storing the MAC.
	 * @param[in]  data Pointer to input data.
	 * @param[in]  data_size Size in bytes of input data.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - Size of the MAC buffer must >= <tt>CmacTdes168Generator::kMacSize</tt>.
	 * - @p key_size == <tt>CmacTdes168Generator::kMacSize</tt>.
	 * 
	 * @post
	 * - The MAC is written to <tt><var>mac</var></tt>.
	 * 
	 * @details
	 * This function calculates a MAC for the passed in data array.
	 * To calculate a MAC for data split into multiple arrays, use the @ref CmacTdes168Generator class.
	 */
void GenerateCmacTdes168Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);

}} // namespace tc::crypto
