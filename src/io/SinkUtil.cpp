#include <tc/io/SinkUtil.h>

int64_t tc::io::SinkUtil::getWritableSize(int64_t sink_length, int64_t write_offset)
{
	if (sink_length < 0 || write_offset < 0)
		return 0;

	if (write_offset > sink_length)
		return 0;

	return sink_length - write_offset;
}