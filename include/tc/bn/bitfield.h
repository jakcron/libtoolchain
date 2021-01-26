	/**
	 * @file bitfield.h
	 * @brief Declaration of tc::bn::bitfield
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/12/20
	 */
#pragma once
#include <tc/types.h>

namespace tc { namespace bn {

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

}} // namespace tc::bn