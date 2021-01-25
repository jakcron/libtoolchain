	/**
	 * @file coded_string.h
	 * @brief Declaration of tc::coded_string
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2021/01/24
	 */
#pragma once
#include <tc/types.h>

namespace tc {

template <size_t CODED_SIZE, size_t LOGICAL_SIZE = CODED_SIZE>
class coded_string
{
public:
	static_assert(CODED_SIZE >= LOGICAL_SIZE, "coded_string had a logical size greater than the coded size.");

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
	std::array<char, CODED_SIZE> mRawString;
};

}