	/**
	 * @file SinkUtil.h
	 * @brief Declaration of tc::io::SinkUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/02/08
	 **/
#pragma once
#include <tc/io/ISource.h>

namespace tc { namespace io {

	/**
	 * @class SinkUtil
	 * @brief Utility class for ISource objects.
	 **/
class SinkUtil
{
public:
	static int64_t getWritableSize(int64_t sink_length, int64_t sink_offset);
};

}} // namespace tc::io