	/**
	 * @file types.h
	 * @brief Declaration of generic types used by libtoolchain
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/01/15
	 **/
	#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <memory>
#include <tc/endian.h>

	/// Alias uint8_t to byte_t to more explicity indicate its role in memory related contexts
using byte_t = uint8_t;