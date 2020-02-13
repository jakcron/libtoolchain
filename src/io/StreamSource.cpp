#include <tc/io/StreamSource.h>
#include <tc/io/SourceUtil.h>

const std::string tc::io::StreamSource::kClassName = "tc::io::StreamSource";

tc::io::StreamSource::StreamSource() :
	mBaseStream(nullptr)
{
}

tc::io::StreamSource::StreamSource(const std::shared_ptr<tc::io::IStream>& stream) :
	mBaseStream(stream)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "base stream is null");
	}

	if (mBaseStream->canRead() == false)
	{
		throw tc::NotSupportedException(kClassName, "base stream does not support reading.");
	}
}

int64_t tc::io::StreamSource::length()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::length()", "The base stream was not initialised.");
	}

	return mBaseStream->length();
}

tc::ByteData tc::io::StreamSource::pullData(int64_t offset, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::pullData()", "The base stream was not initialised.");
	}

	// no canSeek is checked here, it can be thrown by the base stream
	// but also only seek if necessary
	if (offset != 0 || (mBaseStream->canSeek() && mBaseStream->position() != 0))
	{
		mBaseStream->seek(offset, tc::io::SeekOrigin::Begin);
	}

	// get readable count
	size_t read_count = SourceUtil::getReadableSize(mBaseStream->length(), offset, count);
	
	// allocate ByteData
	ByteData data(read_count);

	// read from stream
	mBaseStream->read(data.buffer(), data.size());

	// return populated ByteData
	return data;
}