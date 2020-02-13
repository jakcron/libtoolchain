#include <tc/io/StreamSink.h>

const std::string tc::io::StreamSink::kClassName = "tc::io::StreamSink";

tc::io::StreamSink::StreamSink() :
	mBaseStream(nullptr)
{
}

tc::io::StreamSink::StreamSink(const std::shared_ptr<tc::io::IStream>& stream) :
	mBaseStream(stream)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "base stream is null");
	}

	if (mBaseStream->canWrite() == false)
	{
		throw tc::NotSupportedException(kClassName, "base stream does not support writing");
	}
}

int64_t tc::io::StreamSink::length()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::length()", "The base stream was not initialised.");
	}

	return mBaseStream->length();
}

void tc::io::StreamSink::setLength(int64_t length)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setLength()", "The base stream was not initialised.");
	}

	mBaseStream->setLength(length);
}

void tc::io::StreamSink::pushData(const tc::ByteData& data, int64_t offset)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::pushData()", "The base stream was not initialised.");
	}

	// no canSeek is checked here, it can be thrown by the base stream
	// but also only seek if necessary
	if (offset != 0 || (mBaseStream->canSeek() && mBaseStream->position() != 0))
	{
		mBaseStream->seek(offset, tc::io::SeekOrigin::Begin);
	}

	// canWrite is validated at class creation	
	mBaseStream->write(data.buffer(), data.size());
}