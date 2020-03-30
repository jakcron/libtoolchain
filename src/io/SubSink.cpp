#include <tc/io/SubSink.h>
#include <tc/io/SinkUtil.h>

const std::string tc::io::SubSink::kClassName = "tc::io::SubSink";

tc::io::SubSink::SubSink() :
	mBaseSink(nullptr),
	mBaseSinkOffset(0),
	mSubSinkLength(0)
{

}

tc::io::SubSink::SubSink(const std::shared_ptr<tc::io::ISink>& sink, int64_t offset, int64_t length) :
	SubSink()
{
	mBaseSink = sink;

	// validate arguments
	if (mBaseSink == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "sink is null");
	}

	if (offset < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "offset is negative");
	}
	if (length < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "length is negative");
	}

	int64_t base_length = mBaseSink->length();

	// validate arguments against sink length
	// sub sink length should not be greater than the base sink length
	if (length > base_length)
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "sub sink length is greater than base sink length");
	}
	// Base length - length is the maximum possible offset for the sub sink
	if (offset > (base_length - length))
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "sub sink offset is greater than the maximum possible offset given the base stream size and SubStream size");
	}
	
	// set class state
	mBaseSinkOffset = offset;
	mSubSinkLength = length;
}

int64_t tc::io::SubSink::length()
{
	return mBaseSink == nullptr ? 0 : mSubSinkLength;
}

void tc::io::SubSink::setLength(int64_t length)
{
	if (mBaseSink == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setLength()", "Failed to set sink length (no base sink)");
	}

	mBaseSink->setLength(length);
}

void tc::io::SubSink::pushData(const tc::ByteData& data, int64_t offset)
{
	if (mBaseSink == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::pushData()", "Failed to push data (no base sink)");
	}

	int64_t writable_size = SinkUtil::getWritableSize(mSubSinkLength, offset);

	if (writable_size < data.size())
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::pushData()", "data was too large to be written sink at the given offset.");
	}

	mBaseSink->pushData(data, mBaseSinkOffset + offset);
}