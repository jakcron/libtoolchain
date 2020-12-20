	/**
	 * @file binary_utils.h
	 * @brief Declaration of inlines and classes for literal bit manipulation and other low-level operations.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/12/20
	 */
#pragma once
#include <tc/types.h>

	/**
	 * @brief Round a value up to an alignment value.
	 */
template <typename T>
inline T roundup(T value, T alignment)
{
	return value + alignment - value % alignment;
}

	/**
	 * @brief Align a value to an alignment value.
	 */
template <typename T>
inline T align(T value, T alignment)
{
	if(value % alignment != 0)
		return roundup(value,alignment);
	else
		return value;
}

namespace tc {

	/**
	 * @brief Generate struct magic 32bit number.
	 * @details This generates a little endian 32bit integer from char[4].
	 * 
	 * @param[in] magic Pointer to array of magic bytes.
	 * 
	 * @return Little endian magic uint32_t.
	 */ 
constexpr uint32_t make_struct_magic_uint32(const char magic[4])
{
	return uint32_t((uint32_t)(magic[3]) << 24 | (uint32_t)(magic[2]) << 16 | (uint32_t)(magic[1]) << 8 | (uint32_t)(magic[0]));
}

	/**
	 * @brief Generate struct magic 64bit number.
	 * @details This generates a little endian 64bit integer from char[8].
	 * 
	 * @param[in] magic Pointer to array of magic bytes.
	 * 
	 * @return Little endian magic uint64_t.
	 */ 
constexpr uint64_t make_struct_magic_uint64(const char magic[8])
{
	return uint64_t((uint64_t)(magic[7]) << 56 | (uint64_t)(magic[6]) << 48 | (uint64_t)(magic[5]) << 40 | (uint64_t)(magic[4]) << 32 | (uint64_t)(magic[3]) << 24 | (uint64_t)(magic[2]) << 16 | (uint64_t)(magic[1]) << 8 | (uint64_t)(magic[0]));
}

	/**
	 * @struct bitfield
	 * @brief This struct is a literal bitfield, with configurable byte and bit endianness.
	 * 
	 * @tparam T size in bytes of the bitfield.
	 * @tparam byte_order_le Boolean, true: byte order is little endian, false: byte order is big endian.
	 * @tparam bit_order_le Boolean, true: bit order is little endian, false: bit order is big endian.
	 * 
	 * @details
	 * This struct is meant to be used when defining written-to-disk structures, like file headers.
	 */ 
template <size_t T, bool byte_order_le = true, bool bit_order_le = true>
struct bitfield
{
public:
#define __BITFIELD_BYTE_INDEX_MATH(x) (byte_order_le? (x / 8) : (T - 1 - (x / 8)))
#define __BITFIELD_BIT_INDEX_MATH(x) (bit_order_le? (1 << (x % 8)) : (1 << (7 - (x % 8))))

	size_t bit_size() const { return T * 8; }

	void set(size_t bit)
	{
		bit %= (T*8);
		mArray[__BITFIELD_BYTE_INDEX_MATH(bit)] |= __BITFIELD_BIT_INDEX_MATH(bit);
	}

	void reset(size_t bit)
	{
		bit %= (T*8);
		mArray[__BITFIELD_BYTE_INDEX_MATH(bit)] &= ~(uint8_t(__BITFIELD_BIT_INDEX_MATH(bit)));
	}

	void flip(size_t bit)
	{
		bit %= (T*8);
		test(bit) ? reset(bit) : set(bit);
	}

	bool test(size_t bit) const
	{
		bit %= (T*8);
		return (mArray[__BITFIELD_BYTE_INDEX_MATH(bit)] & (__BITFIELD_BIT_INDEX_MATH(bit))) != 0;
	}

#undef __BITFIELD_BYTE_INDEX_MATH
#undef __BITFIELD_BIT_INDEX_MATH

private:
	std::array<uint8_t, T> mArray;
};

} // namespace tc