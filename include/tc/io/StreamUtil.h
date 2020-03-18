	/**
	 * @file StreamUtil.h
	 * @brief Declaration of tc::io::StreamUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/02/08
	 **/
#pragma once
#include <tc/io/IStream.h>

namespace tc { namespace io {

	/**
	 * @class StreamUtil
	 * @brief Utility class for IStream objects.
	 **/
class StreamUtil
{
public:
	static size_t getReadableSize(int64_t length, int64_t offset, size_t read_len);
	static size_t getWritableSize(int64_t length, int64_t offset);
};

}} // namespace tc::io