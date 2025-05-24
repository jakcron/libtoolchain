	/**
	 * @file CmacAes128Generator.h
	 * @brief Declarations for API resources for CMAC-AES-128 calculations.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2024/12/10
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/AesEncryptor.h>
#include <tc/crypto/CmacGenerator.h>

namespace tc { namespace crypto {

	/**
	 * @typedef CmacAes128Generator
	 * @brief Class for calculating CMAC-AES-128.
	 * 
	 * @details This class calcualtes CMAC using AES-128.
	 * For more information refer to @ref CmacGenerator.
	 */
using CmacAes128Generator = CmacGenerator<Aes128Encryptor>;

	/**
	 * @brief Utility function for calculating CMAC-AES-128.
	 * 
	 * @param[out] mac Pointer to the buffer storing the MAC.
	 * @param[in]  data Pointer to input data.
	 * @param[in]  data_size Size in bytes of input data.
	 * @param[in]  key Pointer to key data.
	 * @param[in]  key_size Size in bytes of key data.
	 * 
	 * @pre
	 * - Size of the MAC buffer must >= <tt>CmacAes128Generator::kMacSize</tt>.
	 * - @p key_size == <tt>CmacAes128Generator::kMacSize</tt>.
	 * 
	 * @post
	 * - The MAC is written to <tt><var>mac</var></tt>.
	 * 
	 * @details
	 * This function calculates a MAC for the passed in data array.
	 * To calculate a MAC for data split into multiple arrays, use the @ref CmacAes128Generator class.
	 */
void GenerateCmacAes128Mac(byte_t* mac, const byte_t* data, size_t data_size, const byte_t* key, size_t key_size);

}} // namespace tc::crypto
