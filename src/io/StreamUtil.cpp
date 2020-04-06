#include <tc/io/StreamUtil.h>

size_t tc::io::StreamUtil::getReadableSize(int64_t stream_length, int64_t read_offset, size_t read_length)
{
	if (stream_length < 0 || read_offset < 0)
		return 0;

	int64_t readable_length = (read_offset < stream_length) ? (stream_length - read_offset) : 0;

	// if size_t has less digits than int64_t we must limit readable_length to the maximum value for a size_t
	if (std::numeric_limits<size_t>::digits < std::numeric_limits<int64_t>::digits)
		readable_length = int64_t(std::min<int64_t>(readable_length, int64_t(std::numeric_limits<size_t>::max())));

	return std::min<size_t>(size_t(readable_length), read_length);
}

size_t tc::io::StreamUtil::getWritableSize(int64_t stream_length, int64_t write_offset)
{
	if (stream_length < 0 || write_offset < 0)
		return 0;

	int64_t writable_length = stream_length > write_offset ? stream_length - write_offset : 0;

	// if size_t has less digits than int64_t we must limit writable_length to the maximum value for a size_t
	if (std::numeric_limits<size_t>::digits < std::numeric_limits<int64_t>::digits)
		writable_length = int64_t(std::min<int64_t>(writable_length, int64_t(std::numeric_limits<size_t>::max())));

	return size_t(writable_length);
}

int64_t tc::io::StreamUtil::getSeekResult(int64_t offset, tc::io::SeekOrigin origin, int64_t current_position, int64_t stream_length)
{
	int64_t new_pos = 0;
	switch (origin)
	{
		case (SeekOrigin::Begin):
			new_pos = offset;
			break;
		case (SeekOrigin::Current):
			new_pos = current_position + offset;
			break;
		case (SeekOrigin::End):
			new_pos = stream_length + offset;
			break;
		default:
			throw tc::ArgumentOutOfRangeException("Illegal value for origin.");
	}

	return new_pos;
}