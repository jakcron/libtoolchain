	/**
	 * @file SourceUtil.h
	 * @brief Declaration of tc::io::SourceUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/02/07
	 **/
#pragma once
#include <tc/io/ISource.h>

namespace tc { namespace io {

	/**
	 * @class SourceUtil
	 * @brief Utility class for ISource objects.
	 **/
class SourceUtil
{
public:
		/**
		 * @brief Get size of readable data for an ISource given the source size, desired read offset and length
		 * 
		 * @param[in] source_length Total length of source.
		 * @param[in] read_offset Byte offset in source to begin reading from.
		 * @param[in] read_length of data to read from source.
		 * 
		 * @return Largest possible readable length.
		 **/
	static size_t getReadableSize(int64_t length, int64_t offset, size_t read_len);
};

}} // namespace tc::io