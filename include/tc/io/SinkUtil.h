	/**
	 * @file SinkUtil.h
	 * @brief Declaration of tc::io::SinkUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/02/08
	 **/
#pragma once
#include <tc/io/ISink.h>

namespace tc { namespace io {

	/**
	 * @class SinkUtil
	 * @brief Utility class for ISink objects.
	 **/
class SinkUtil
{
public:
		/**
		 * @brief Get size of writeable data for an ISink given the sink size and deisred write offset
		 * 
		 * @param[in] sink_length Total length of sink.
		 * @param[in] write_offset Byte offset in sink to begin writing from.
		 * 
		 * @return Largest possible writeable length.
		 **/
	static int64_t getWritableSize(int64_t sink_length, int64_t sink_offset);
};

}} // namespace tc::io