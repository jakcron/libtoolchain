	/**
	 * @file pad.h
	 * @brief Declaration of tc::bn::pad
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/12/20
	 */
#pragma once
#include <tc/types.h>

namespace tc { namespace bn {

	/**
	 * @class pad
	 * @brief This class creates padding.
	 * 
	 * @tparam T size in bytes of the padding.
	 */ 
template <size_t T>
using pad = std::array<uint8_t, T>;

}} // namespace tc::bn