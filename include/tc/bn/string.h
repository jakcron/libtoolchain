	/**
	 * @file string.h
	 * @brief Declaration of tc::bn::string
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2022/02/01
	 */
#pragma once
#include <tc/types.h>

namespace tc { namespace bn {

	/**
	 * @class string
	 * @brief This class represents a literal char array.
	 * 
	 * @tparam ENCODED_SIZE Literal size of the string. sizeof() will return this size.
	 * @tparam LOGICAL_SIZE Logical maximum size of the string, LOGICAL_SIZE <= ENCODED_SIZE. 
	 */
template <size_t ENCODED_SIZE, size_t LOGICAL_SIZE = ENCODED_SIZE>
class string
{
public:
	static_assert(ENCODED_SIZE >= LOGICAL_SIZE, "literal string had a logical size greater than the encoded size.");

	const char& operator[](size_t index) const { return mRawString[index]; }
	char& operator[](size_t index) { return mRawString[index]; }

	const char* data() const { return mRawString.data(); }
	char* data() { return mRawString.data(); }

	size_t max_size() const { return LOGICAL_SIZE; }
	size_t size() const
	{
		size_t chr_count = 0;

		for (; chr_count < LOGICAL_SIZE; chr_count++)
		{
			if (mRawString[chr_count] == 0) break;
		}

		return chr_count;
	}
	
	std::string str() const { return std::string(this->data(), this->size()); }

private:
	std::array<char, ENCODED_SIZE> mRawString;
};

}} // namespace tc::bn