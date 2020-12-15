	/**
	 * @file bitwise_types.h
	 * @brief Declaration of macros and classes to handle literal bit-fields and bit-masks/bit-shifting.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/12/05
	 **/
#pragma once
#include <array>
#include <cinttypes>

namespace tc {

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

}