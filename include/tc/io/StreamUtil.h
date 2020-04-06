	/**
	 * @file StreamUtil.h
	 * @brief Declaration of tc::io::StreamUtil
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2020/04/06
	 **/
#pragma once
#include <tc/io/IStream.h>

#include <tc/ArgumentOutOfRangeException.h>

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

		/**
		 * @brief Get the logical result for seek(), given the current position and stream length
		 * 
		 * @param[in] offset A byte offset relative to the origin parameter.
		 * @param[in] origin A value of type @ref tc::io::SeekOrigin indicating the reference point used to obtain the new position.
		 * @param[in] current_position The current byte offset relative to the beginning of the stream.
		 * @param[in] stream_length The length of the stream.
		 * 
		 * @return The new position within the stream.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p origin has an illegal value.
		 **/
	static int64_t getSeekResult(int64_t offset, tc::io::SeekOrigin origin, int64_t current_position, int64_t stream_length);
};

}} // namespace tc::io