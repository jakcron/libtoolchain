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

	if (mBaseStream->canSeek() == false)
	{
		throw tc::NotSupportedException(kClassName, "base stream does not support seeking");
	}
}

int64_t tc::io::StreamSink::length()
{
	return mBaseStream == nullptr ? 0 :mBaseStream->length();
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

	mBaseStream->seek(offset, tc::io::SeekOrigin::Begin);
	size_t data_writen_size = mBaseStream->write(data.get(), data.size());

	if (data_writen_size != data.size())
	{
		throw tc::io::IOException(kClassName+"::pushData()", "Not all data was written to base stream.");
	}
}