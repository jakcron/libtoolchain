#include <tc/io/SubStream.h>

#include <tc/Exception.h>
#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotSupportedException.h>
#include <tc/ObjectDisposedException.h>

const std::string tc::io::SubStream::kClassName = "tc::io::SubStream";

tc::io::SubStream::SubStream() :
	mBaseStream(),
	mBaseStreamOffset(0),
	mSubStreamLength(0),
	mSubStreamPosition(0)
{}
	

tc::io::SubStream::SubStream(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length) :
	SubStream()
{
	initialise(stream, offset, length);
}

tc::io::SubStream::SubStream(std::shared_ptr<tc::io::IStream>&& stream, int64_t offset, int64_t length) :
	SubStream()
{
	initialise(std::move(stream), offset, length);
}

void tc::io::SubStream::initialise(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length)
{
	// dispose object before re-initialising
	dispose();

	// copy stream
	mBaseStream = stream;

	// validate arguments
	validateInitArgsAgainstBaseStream(offset, length);
	
	// set class state
	mBaseStreamOffset = offset;
	mSubStreamLength = length;
	mSubStreamPosition = 0;
}

void tc::io::SubStream::initialise(std::shared_ptr<tc::io::IStream>&& stream, int64_t offset, int64_t length)
{
	// dispose object before re-initialising
	dispose();

	// move stream
	mBaseStream = std::move(stream);
	
	// validate arguments
	validateInitArgsAgainstBaseStream(offset, length);
	
	// set class state
	mBaseStreamOffset = offset;
	mSubStreamLength = length;
	mSubStreamPosition = 0;
}

bool tc::io::SubStream::canRead() const
{
	return mBaseStream.get()? mBaseStream->canRead() : false;
}

bool tc::io::SubStream::canWrite() const
{
	return mBaseStream.get()? mBaseStream->canWrite() : false;
}
bool tc::io::SubStream::canSeek() const
{
	return mBaseStream.get()? mBaseStream->canSeek() : false;
}

int64_t tc::io::SubStream::length()
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::length()", "Failed to get stream length (stream is disposed)");
	}

	return mSubStreamLength;
}

int64_t tc::io::SubStream::position()
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::position()", "Failed to get file position (stream is disposed)");
	}

	return mSubStreamPosition;
}

size_t tc::io::SubStream::read(byte_t* buffer, size_t count)
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::read()", "Failed to read from stream (stream is disposed)");
	}

	// ensure data read won't exceed the boundary of the sub-stream
	if ((mSubStreamLength - mSubStreamPosition) < count)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"read()", "count too large, exceeded limit of sub stream");
	}

	// assert proper position in file
	mBaseStream->seek(mBaseStreamOffset + mSubStreamPosition, SeekOrigin::Begin);

	// read data
	size_t read_len = mBaseStream->read(buffer, count);

	// update sub stream position
	seek(mSubStreamPosition + count, SeekOrigin::Begin);

	return read_len;
}

void tc::io::SubStream::write(const byte_t* buffer, size_t count)
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::write()", "Failed to write to stream (stream is disposed)");
	}

	// ensure data read won't exceed the boundary of the sub-stream
	if ((mSubStreamLength - mSubStreamPosition) < count)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"write()", "count too large, exceeded limit of sub stream");
	}

	// assert proper position in file
	mBaseStream->seek(mBaseStreamOffset + mSubStreamPosition, SeekOrigin::Begin);

	// write data
	mBaseStream->write(buffer, count);

	// update sub stream position
	seek(mSubStreamPosition + count, SeekOrigin::Begin);
}

int64_t tc::io::SubStream::seek(int64_t offset, SeekOrigin origin)
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::seek()", "Failed to set stream position (stream is disposed)");
	}

#define _MIN(x,y) (x < y? x : y)
	mSubStreamPosition = _MIN(offset, mSubStreamLength);
#undef _MIN
}

void tc::io::SubStream::setLength(int64_t length)
{
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(kClassName+"::setLength()", "setLength is not supported for SubStream");
}

void tc::io::SubStream::flush()
{
	if (mBaseStream.get() == nullptr)
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

void tc::io::SubStream::validateInitArgsAgainstBaseStream(int64_t offset, int64_t length)
{
	// validate the stream exists
	if (mBaseStream.get() == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"initialise()", "stream is null");
	}

	// check if the stream supports seeking
	if (mBaseStream->canSeek() == false)
	{
		tc::NotSupportedException(kClassName+"initialise()", "Streams that do not support seeking are not supported");
	}

	
	// validate arguments
	if (offset < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"initialise()", "offset is negative");
	}
	if (length < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"initialise()", "length is negative");
	}

	int64_t base_length = mBaseStream->length();

	// validate arguments against stream length
	if (base_length > length)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"initialise()", "");
	}
	if ((base_length - length) < offset)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"initialise()", "");
	}
}