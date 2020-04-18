	/**
	 * @file types.h
	 * @brief Declaration of generic types used by libtoolchain
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2020/04/05
	 **/
#pragma once
#include <string>
#include <array>
#include <vector>
#include <cstdint>
#include <cstring>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tc/endian.h>

#ifdef _WIN32
#define NOMINMAX
#endif

	/// Alias uint8_t to byte_t to more explicity indicate its role in memory related contexts
using byte_t = uint8_t;