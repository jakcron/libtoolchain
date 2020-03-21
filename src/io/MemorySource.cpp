#include <tc/io/MemorySource.h>
#include <tc/io/SourceUtil.h>

const std::string tc::io::MemorySource::kClassName = "tc::io::MemorySource";

tc::io::MemorySource::MemorySource() :
	mData()
{

}

tc::io::MemorySource::MemorySource(const tc::ByteData& byte_data) :
	mData(byte_data)
{

}

tc::io::MemorySource::MemorySource(const byte_t* data, size_t len) :
	mData(data, len)
{
}

int64_t tc::io::MemorySource::length()
{
	return int64_t(mData.size());
}

tc::ByteData tc::io::MemorySource::pullData(int64_t offset, size_t count)
{
	size_t read_len = SourceUtil::getReadableSize(this->length(), offset, count);

	// if the read length is zero then return now.
	if (read_len == 0)
		return tc::ByteData();


	tc::ByteData out(read_len);

	memcpy(out.buffer(), mData.buffer() + offset, read_len);

	return out;
}
