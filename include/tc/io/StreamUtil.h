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
		/**
		 * @brief Get size of readable data for an IStream given the stream size, desired read offset and length
		 * 
		 * @param[in] stream_length Total length of stream.
		 * @param[in] read_offset Byte offset in stream to begin reading from.
		 * @param[in] read_length of data to read from stream.
		 * 
		 * @return Largest possible readable length.
		 **/
	static size_t getReadableSize(int64_t stream_length, int64_t read_offset, size_t read_length);

		/**
		 * @brief Get size of writeable data for an IStream given the stream size and deisred write offset
		 * 
		 * @param[in] stream_length Total length of stream.
		 * @param[in] write_offset Byte offset in stream to begin writing from.
		 * 
		 * @return Largest possible writeable length.
		 **/
	static size_t getWritableSize(int64_t stream_length, int64_t write_offset);
};

}} // namespace tc::io