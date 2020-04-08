#include <tc/io/SubStream.h>
#include <tc/io/StreamUtil.h>
#include <algorithm>


const std::string tc::io::SubStream::kClassName = "tc::io::SubStream";

tc::io::SubStream::SubStream() :
	mBaseStream(),
	mBaseStreamOffset(0),
	mSubStreamLength(0),
	mSubStreamPosition(std::make_shared<int64_t>(0))
{}
	

tc::io::SubStream::SubStream(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length) :
	SubStream()
{
	// copy stream
	mBaseStream = stream;

	// validate the stream exists
	if (mBaseStream == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "stream is null");
	}

	// check if the stream supports seeking
	if (mBaseStream->canSeek() == false)
	{
		tc::NotSupportedException(kClassName, "Streams that do not support seeking are not supported");
	}

	
	// validate arguments
	if (offset < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "offset is negative");
	}
	if (length < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "length is negative");
	}

	int64_t base_length = mBaseStream->length();

	// validate arguments against stream length
	// substream length should not be greater than the base stream length
	if (length > base_length)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "SubStream length is greater than base stream length");
	}
	// Base length - length is the maximum possible offset for the substream
	if (offset > (base_length - length))
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "SubStream offset is greater than the maximum possible offset given the base stream size and SubStream size");
	}
	
	// set class state
	mBaseStreamOffset = offset;
	mSubStreamLength = length;
	*mSubStreamPosition = 0;
}

bool tc::io::SubStream::canRead() const
{
	return mBaseStream == nullptr ? mBaseStream->canRead() : false;
}

bool tc::io::SubStream::canWrite() const
{
	return mBaseStream == nullptr ? mBaseStream->canWrite() : false;
}
bool tc::io::SubStream::canSeek() const
{
	return mBaseStream == nullptr ? mBaseStream->canSeek() : false;
}

int64_t tc::io::SubStream::length()
{
	return mBaseStream == nullptr ? 0 : mSubStreamLength;
}

int64_t tc::io::SubStream::position()
{
	return mBaseStream == nullptr ? 0 : *mSubStreamPosition;
}

size_t tc::io::SubStream::read(byte_t* buffer, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::read()", "Failed to read from stream (stream is disposed)");
	}

	size_t readable_size = StreamUtil::getReadableSize(mSubStreamLength, *mSubStreamPosition, count);

	// ensure data read won't exceed the boundary of the sub-stream
	if (readable_size < count)
	{
		count = readable_size;
	}

	// assert proper position in file
	mBaseStream->seek(mBaseStreamOffset + *mSubStreamPosition, SeekOrigin::Begin);

	// read data
	size_t read_len = mBaseStream->read(buffer, count);

	// update sub stream position
	seek(count, SeekOrigin::Current);

	return read_len;
}

void tc::io::SubStream::write(const byte_t* buffer, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::write()", "Failed to write to stream (stream is disposed)");
	}

	size_t writable_size = StreamUtil::getWritableSize(mSubStreamLength, *mSubStreamPosition);

	// ensure data read won't exceed the boundary of the sub-stream
	if (writable_size < count)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"write()", "count too large, exceeded limit of sub stream");
	}

	// assert proper position in file
	mBaseStream->seek(mBaseStreamOffset + *mSubStreamPosition, SeekOrigin::Begin);

	// write data
	mBaseStream->write(buffer, count);

	// update sub stream position
	seek(count, SeekOrigin::Current);
}

int64_t tc::io::SubStream::seek(int64_t offset, SeekOrigin origin)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	*mSubStreamPosition = StreamUtil::getSeekResult(offset, origin, *mSubStreamPosition, mSubStreamLength);

	if (*mSubStreamPosition < 0)
	{
		throw tc::InvalidOperationException(kClassName+"::seek()", "Negative seek result determined");
	}

	return *mSubStreamPosition;
}

void tc::io::SubStream::setLength(int64_t length)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(kClassName+"::setLength()", "setLength is not supported for SubStream");
}

void tc::io::SubStream::flush()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mBaseStream->flush();
}

void tc::io::SubStream::dispose()
{
	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}
	
	// clear state
	mBaseStreamOffset = 0;
	mSubStreamLength = 0;
	mSubStreamPosition = 0;
}