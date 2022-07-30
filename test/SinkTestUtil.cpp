#include "SinkTestUtil.h"
#include <fmt/format.h>

const std::string SinkTestUtil::DummySinkBase::kClassName = "DummySinkBase";

void SinkTestUtil::testSinkLength(tc::io::ISink& sink, int64_t expected_len)
{
	int64_t actual_len = sink.length();
	if (actual_len != expected_len)
	{
		throw tc::Exception(fmt::format("length() returned: {:d}, when it should have been {:d}.", actual_len, expected_len));
	}
}

SinkTestUtil::DummySinkBase::DummySinkBase() :
	DummySinkBase(0x10000000)
{
}

SinkTestUtil::DummySinkBase::DummySinkBase(int64_t length) :
	DummySinkBase(length, true)
{
}

SinkTestUtil::DummySinkBase::DummySinkBase(int64_t length, bool canSetLength)
{
	init(length, canSetLength);
}

void SinkTestUtil::DummySinkBase::init(int64_t length, bool canSetLength)
{
	mCanSetLength = canSetLength;
	mLength = length;
}

int64_t SinkTestUtil::DummySinkBase::length()
{
	return mLength;
}

void SinkTestUtil::DummySinkBase::setLength(int64_t length)
{
	if (mCanSetLength == false)
		throw tc::NotImplementedException(kClassName, "setLength() is not implemented");
		
	mLength = length;
}

size_t SinkTestUtil::DummySinkBase::pushData(const tc::ByteData& data, int64_t offset)
{
	throw tc::NotImplementedException(kClassName, "pushData not implemented");
}

SinkTestUtil::DummySinkTestablePushData::DummySinkTestablePushData() :
	DummySinkBase(),
	expected_data(std::make_shared<tc::ByteData>(0)),
	expected_offset(std::make_shared<int64_t>(0))
{}

void SinkTestUtil::DummySinkTestablePushData::setExpectedPushDataCfg(const tc::ByteData& data, int64_t offset)
{
	*expected_data = data;
	*expected_offset = offset;
}

size_t SinkTestUtil::DummySinkTestablePushData::pushData(const tc::ByteData& data, int64_t offset)
{
	if (offset != *expected_offset)
	{
		throw tc::Exception(fmt::format("pushData() was called on base_sink with offset {:d}, when it should have been {:d}.", offset, *expected_offset));
	}

	if (data.size() != expected_data->size())
	{
		throw tc::Exception(fmt::format("pushData() passed a ByteData to base_sink with size {:d}, when it should have been {:d}.", data.size(), expected_data->size()));
	}

	if (memcmp(data.data(), expected_data->data(), data.size()) != 0)
	{
		throw tc::Exception("ByteData pushed to base sink did not have expected data.");
	}

	return data.size();
}