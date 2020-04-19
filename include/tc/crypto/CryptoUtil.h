	/**
	 * @file CryptoUtil.h
	 * @brief Declaration of tc::crypto::CryptoUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/18
	 **/
#pragma once

#include <tc/types.h>

namespace tc { namespace crypto {

class CryptoUtil
{
public:
	static void XorBlock128(byte_t* dst, const byte_t* src_1, const byte_t* src_2);
	static void GaloisFunc128(byte_t* tweak);
	static void IncrementCounter128(byte_t* ctr, size_t incr);
	static void CreateXtsTweak128(byte_t* tweak, const byte_t* base_tweak, size_t sector_index);
};

}} // namespace tc::crypto