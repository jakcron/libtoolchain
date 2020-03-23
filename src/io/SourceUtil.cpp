#include <tc/io/SourceUtil.h>

size_t tc::io::SourceUtil::getReadableSize(int64_t source_length, int64_t read_offset, size_t read_length)
{
	if (source_length < 0 || read_offset < 0)
		return 0;

	int64_t readable_length = (read_offset < source_length) ? (source_length - read_offset) : 0;

	// if size_t has less digits than int64_t we must limit readable_length to the maximum value for a size_t
	if (std::numeric_limits<size_t>::digits < std::numeric_limits<int64_t>::digits)
		readable_length = int64_t(std::min<int64_t>(readable_length, int64_t(std::numeric_limits<size_t>::max())));

	return std::min<size_t>(size_t(readable_length), read_length);
}