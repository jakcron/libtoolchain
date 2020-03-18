#include <tc/io/StreamUtil.h>

size_t tc::io::StreamUtil::getReadableSize(int64_t length, int64_t offset, size_t read_size)
{
	if (length < 0 || offset < 0)
		return 0;

	int64_t available_data = (offset < length) ? (length - offset) : 0;

	return size_t(std::min<int64_t>(available_data, int64_t(read_size)));
}

size_t tc::io::StreamUtil::getWritableSize(int64_t length, int64_t offset)
{
	if (length < 0 || offset < 0)
		return 0;

	if (offset > length)
		return 0;

	return length - offset;
}
