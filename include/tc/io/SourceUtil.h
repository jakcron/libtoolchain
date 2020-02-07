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
	static size_t getPullableCount(int64_t source_length, int64_t source_offset, size_t data_to_pull);
};

}} // namespace tc::io