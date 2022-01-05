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
#include <map>
#include <cstdint>
#include <cstring>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <tc/bn.h>

#ifdef _WIN32
#define NOMINMAX
#endif

	/// Alias uint8_t to byte_t to more explicity indicate its role in memory related contexts
using byte_t = uint8_t;

namespace tc {
	bool is_size_t_not_64bit();
	bool is_size_t_too_large_for_int64_t(size_t val);
	bool is_uint64_t_too_large_for_int64_t(uint64_t val);
	bool is_int64_t_too_large_for_size_t(int64_t val);
	bool is_uint64_t_too_large_for_size_t(uint64_t val);
}