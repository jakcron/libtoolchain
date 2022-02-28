#include <tc/io/ConcatenatedStream.h>

const std::string tc::io::ConcatenatedStream::kClassName = "tc::io::ConcatenatedStream";


tc::io::ConcatenatedStream::ConcatenatedStream() :
	mStreamList(),
	mCurrentStream(mStreamList.begin()),
	mCanRead(false),
	mCanWrite(false),
	mCanSeek(false),
	mStreamLength(0)
{}

tc::io::ConcatenatedStream::ConcatenatedStream(const std::vector<std::shared_ptr<tc::io::IStream>>& stream_list) :
	ConcatenatedStream()
{
	// process stream list
}

bool tc::io::ConcatenatedStream::canRead() const
{
	return mStreamList.empty() ? false : mCanRead;
}

bool tc::io::ConcatenatedStream::canWrite() const
{
	return mStreamList.empty() ? false : mCanWrite;
}

bool tc::io::ConcatenatedStream::canSeek() const
{
	return mStreamList.empty() ? false : mCanSeek;
}

int64_t tc::io::ConcatenatedStream::length()
{
	return mStreamList.empty() ? 0 : mStreamLength;
}

int64_t tc::io::ConcatenatedStream::position()
{
	return (mCurrentStream == mStreamList.end()) ? 0 : (mCurrentStream->offset + mCurrentStream->stream->position());
}

size_t tc::io::ConcatenatedStream::read(byte_t* ptr, size_t count)
{
	if (mCurrentStream == mStreamList.end())
	{
		throw tc::ObjectDisposedException(kClassName+"read()", "Stream was disposed.");
	}
	if (mCanRead == false)
	{
		throw tc::NotSupportedException(kClassName+"read()", "Stream does not support reading.");
	}

	// read

	return 0;
}

size_t tc::io::ConcatenatedStream::write(const byte_t* ptr, size_t count)
{
	if (mCurrentStream == mStreamList.end())
	{
		throw tc::ObjectDisposedException(kClassName+"write()", "Stream was disposed.");
	}
	if (mCanWrite == false)
	{
		throw tc::NotSupportedException(kClassName+"write()", "Stream does not support writing.");
	}

	// write

	return 0;
}

int64_t tc::io::ConcatenatedStream::seek(int64_t offset, SeekOrigin origin)
{
	if (mCurrentStream == mStreamList.end())
	{
		throw tc::ObjectDisposedException(kClassName+"seek()", "Stream was disposed.");
	}
	if (mCanSeek == false)
	{
		throw tc::NotSupportedException(kClassName+"seek()", "Stream does not support seeking.");
	}

	// seek

	return 0;
}

void tc::io::ConcatenatedStream::setLength(int64_t length)
{
	if (mCurrentStream == mStreamList.end())
	{
		throw tc::ObjectDisposedException(kClassName+"setLength()", "Stream was disposed.");
	}

	throw tc::NotImplementedException(kClassName+"setLength()", "setLength() is not implemented for tc::io::ConcatenatedStream.");
}

void tc::io::ConcatenatedStream::flush()
{
	if (mCurrentStream == mStreamList.end())
	{
		throw tc::ObjectDisposedException(kClassName+"flush()", "Stream was disposed.");
	}

	mCurrentStream->stream->flush();
}

void tc::io::ConcatenatedStream::dispose()
{
	mCurrentStream = mStreamList.end();
	mStreamList.clear();
	mCurrentStream = mStreamList.end();

	mCanRead = false;
	mCanWrite = false;
	mCanSeek = false;
	mStreamLength = 0;
}