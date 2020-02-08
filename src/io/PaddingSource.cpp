#include <tc/io/PaddingSource.h>
#include <tc/io/SourceUtil.h>

tc::io::PaddingSource::PaddingSource() :
	mSourceLength(0),
	mPaddingByte(0)
{
}

tc::io::PaddingSource::PaddingSource(byte_t padding_byte, int64_t size) :
	mSourceLength(size),
	mPaddingByte(padding_byte)
{
}

int64_t tc::io::PaddingSource::length()
{
	return mSourceLength;
}

tc::ByteData tc::io::PaddingSource::pullData(int64_t offset, size_t count)
{
	tc::ByteData data(SourceUtil::getReadableSize(mSourceLength, offset, count));

	memset(data.buffer(), mPaddingByte, data.size());
	
	return data;
}