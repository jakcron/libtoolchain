	/**
	 * @file CmacGenerator.h
	 * @brief Declaration of tc::crypto::CmacGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2024/12/10
	 **/
#pragma once
#include <tc/types.h>
#include <tc/crypto/detail/CmacImpl.h>

namespace tc { namespace crypto {

	/**
	 * @class CmacGenerator
	 * @brief Class for calculating an CMAC.
	 * 
	 * @tparam BlockCipher The class that implements the CBC encryption operation for generating MAC.
	 * 
	 * @details
	 * This class is a template class that takes a hash function implementation class as template parameter.
	 * See @ref CmacAes128Generator or similar for supplied realizations of this template class.
	 * 
	 * The implementation of <var>BlockCipher</var> must satisfy the following conditions.
	 * See @ref Aes128Encryptor or similar class, for more information including parameters to each function.
	 * 
	 * -# Has a <tt>kBlockSize</tt> constant that defines the size of the block to process.
	 * -# Has a <tt>kHashSize</tt> constant that defines the output size of the hash value.
	 * -# Has an <tt>initialize</tt> method that begins processing.
	 * -# Has an <tt>update</tt> method that updates the hash value on input.
	 * -# Has a <tt>getHash</tt> method that gets the final hash value.
	 * 
	 * This class has three states:
	 * - None : Not ready
	 * - Initialized : Ready to process input data
	 * - Done : MAC is calculated
	 * 
	 * General usage of this class is as follows:
	 * - Initialize MAC Generator state with @ref initialize().
	 * - Update MAC with input data with @ref update().
	 * - Complete MAC calculation and export MAC with @ref getMac().
	 * 
	 * Below is code sample for calculating MAC with one call to @ref update():
	 * @code
	 * tc::ByteData key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	 * 
	 * // open file stream
	 * auto stream = tc::io::FileStream("a_file.bin", tc::io::FileMode::Open, tc::io::FileAccess::Read);
	 * 
	 * // create array to store MAC
	 * std::array<byte_t, tc::crypto::CmacGenerator<BlockCipher>::kMacSize> mac;
	 * 
	 * // initialize generator. CmacGenerator<BlockCipher> is now in a ready state. 
	 * tc::crypto::CmacGenerator<BlockCipher> impl;
	 * impl.initialize(key.data(), key.size());
	 * 
	 * // reset stream position to beginning (not strictly necessary for an unused tc::io::FileStream)
	 * stream.seek(0, tc::io::SeekOrigin::Begin);
	 * 
	 * // read whole file into memory. This is unsafe for large file sizes especially on 32-bit systems.
	 * tc::ByteData data = tc::ByteData((size_t)stream.length());
	 * stream.read(data.data(), data.size());
	 * 
	 * // update generator state with stream data
	 * impl.update(data.data(), data.size());
	 * 
	 * // complete generator state and write MAC to mac
	 * impl.getMac(mac.data());
	 * @endcode 
	 * 
	 * Below is code sample for calculating MAC with sequential calls to @ref update():
	 * @code
	 * tc::ByteData key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	 * 
	 * // open file stream
	 * auto stream = tc::io::FileStream("a_file.bin", tc::io::FileMode::Open, tc::io::FileAccess::Read);
	 * 
	 * // create read block (size 512)
	 * static const size_t kReadBlockSize = 0x200;
	 * std::array<byte_t, kReadBlockSize> block;
	 * 
	 * // create array to store MAC
	 * std::array<byte_t, tc::crypto::CmacGenerator<BlockCipher>::kMacSize> mac;
	 * 
	 * // initialize generator. CmacGenerator<BlockCipher> is now in a ready state. 
	 * tc::crypto::CmacGenerator<BlockCipher> impl;
	 * impl.initialize(key.data(), key.size());
	 * 
	 * // reset stream position to beginning (not strictly necessary for an unused tc::io::FileStream)
	 * stream.seek(0, tc::io::SeekOrigin::Begin);
	 * 
	 * // iterate over blocks in stream until no more data can be read
	 * size_t read_count = 0;
	 * while ( 0 != (read_count = tc::io::IOUtil::getReadableCount(stream.position(), stream.length(), block.size())) )
	 * {
	 *   // read block from stream
	 *   stream.read(block.data(), read_count);
	 * 
	 *   // update generator state with stream data
	 *   impl.update(block.data(), read_count);
	 * }
	 * 
	 * // complete generator state and write MAC to mac
	 * impl.getMac(mac.data());
	 * @endcode 
	 */
template <class BlockCipher>
class CmacGenerator
{
public:
	static const size_t kKeySize   = BlockCipher::kKeySize; /**< CMAC Key size */
	static const size_t kMacSize   = BlockCipher::kBlockSize; /**< CMAC MAC size */
	static const size_t kBlockSize = BlockCipher::kBlockSize; /**< CMAC block processing size */

		/**
		 * @brief Default constructor.
		 * 
		 * @post
		 * - State is None. @ref initialize() must be called before use.
		 */
	CmacGenerator() :
		mImpl()
	{}

		/**
		 * @brief Initializes the MAC calculation.
		 * 
		 * @param[in] key Pointer to key data.
		 * @param[in] key_size Size in bytes of key data.
		 * 
		 * @pre
		 * - @p key_size == @ref kKeySize.
		 * 
		 * @post
		 * - Instance is now in a Initialized state
		 * 
		 * @details
		 * Resets the MAC calculation state to the begin state.
		 * 
		 * @note
		 * - This must be called before calculating a new MAC.
		 */
	void initialize(const byte_t* key, size_t key_size)
	{
		mImpl.initialize(key, key_size);
	}

		/**
		 * @brief Update MAC with specified data.
		 * 
		 * @param[in] data Pointer to input data.
		 * @param[in] data_size Size of input data.
		 * 
		 * @details
		 * Data can be input to the generator in one @ref update() call or split across multiple sequential calls.
		 * 
		 * For example the following scenarios all generate the same MAC.
		 * @code
		 * std::string key = "i am an hmac key";
		 * 
		 * // generate data to be calculate MAC from
		 * tc::ByteData data = tc::ByteData(0x30);
		 * memset(data.data(), 0xff, data.size());
		 * 
		 * // create generator instance
		 * tc::crypto::CmacGenerator<BlockCipher> impl;
		 * 
		 * // scenario 1 (one call to update() 0x30 bytes, totaling 0x30 bytes inputted)
		 * std::array<byte_t, tc::crypto::CmacGenerator<BlockCipher>::kMacSize> mac1;
		 * impl.initialize((const byte_t*)key.c_str(), key.size());
		 * impl.update(data.data(), data.size());
		 * impl.getMac(mac1.data());
		 * 
		 * // scenario 2 (three calls to update() 0x10 bytes each, totaling 0x30 bytes inputted)
		 * std::array<byte_t, tc::crypto::CmacGenerator<BlockCipher>::kMacSize> mac2;
		 * impl.initialize((const byte_t*)key.c_str(), key.size());
		 * impl.update(data.data() + 0x00, 0x10);
		 * impl.update(data.data() + 0x10, 0x10);
		 * impl.update(data.data() + 0x20, 0x10);
		 * impl.getMac(mac2.data());
		 * 
		 * // scenario 3 (two calls to update() one 0x10 bytes, the second 0x20 bytes, totaling 0x30 bytes inputted)
		 * std::array<byte_t, tc::crypto::CmacGenerator<BlockCipher>::kMacSize> mac3;
		 * impl.initialize((const byte_t*)key.c_str(), key.size());
		 * impl.update(data.data() + 0x00, 0x10);
		 * impl.update(data.data() + 0x10, 0x20);
		 * impl.getMac(mac3.data());
		 * @endcode
		 * 
		 * @note 
		 * - If input data is broken up into blocks and supplied via multiple @ref update() calls, the order must be consistent with the original input data.
		 */
	void update(const byte_t* data, size_t data_size)
	{
		mImpl.update(data, data_size);
	}

		/**
		 * @brief Completes MAC calculation and output MAC.
		 * 
		 * @param[out] mac Pointer to buffer storing MAC.
		 * 
		 * @pre
		 * - Instance is in either Initialized or Done state.
		 * - The size of the <tt><var>mac</var></tt> buffer must be >= @ref kMacSize.
		 * 
		 * @post
		 * - Instance is now in a Done state.
		 * - The calculated MAC is written to <tt><var>mac</var></tt>.
		 * 
		 * @note 
		 * - If the instance is in a None state, then this call does nothing.
		 */ 
	void getMac(byte_t* mac)
	{
		mImpl.getMac(mac);
	}

private:
	detail::CmacImpl<BlockCipher> mImpl;
};

}} // namespace tc::crypto