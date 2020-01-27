#include <tc/ByteData.h>

const std::string tc::ByteData::kClassName = "tc::ByteData";

tc::ByteData::ByteData(size_t size)
{
	mPtr = std::shared_ptr<byte_t>(new byte_t[size]);
	if (mPtr.get() == nullptr)
	{
		throw tc::OutOfMemoryException(kClassName);
	}
	mSize = size;
}