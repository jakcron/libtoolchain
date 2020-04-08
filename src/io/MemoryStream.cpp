#include <tc/io/MemoryStream.h>

#include <limits>
#include <tc/io/StreamUtil.h>

const std::string tc::io::MemoryStream::kClassName = "tc::io::MemoryStream";

tc::io::MemoryStream::MemoryStream() :
	MemoryStream(0)
{}

tc::io::MemoryStream::MemoryStream(size_t length) :
	mData(),
	mPosition(std::make_shared<int64_t>(0))
{
	setLength(length);
}

tc::io::MemoryStream::MemoryStream(const tc::ByteData& byte_data) :
	mData(byte_data),
	mPosition(std::make_shared<int64_t>(0))
{

}

tc::io::MemoryStream::MemoryStream(const byte_t* data, size_t len) :
	mData(data, len),
	mPosition(std::make_shared<int64_t>(0))
{
}

bool tc::io::MemoryStream::canRead() const 
{
	return true;
}

bool tc::io::MemoryStream::canWrite() const 
{
	return true;
}
	
bool tc::io::MemoryStream::canSeek() const 
{
	return true;
}

int64_t tc::io::MemoryStream::length() 
{
	return mData.size();
}

int64_t tc::io::MemoryStream::position() 
{
	return *mPosition;
}

size_t tc::io::MemoryStream::read(byte_t* ptr, size_t count) 
{
	if (ptr == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"::read()", "ptr is null.");
	}

	size_t readable_size = StreamUtil::getReadableSize(mData.size(), *mPosition, count);
	if (readable_size < count)
	{
		count = readable_size;
	}

	memcpy(ptr, mData.get() + *mPosition, count);

	*mPosition += int64_t(count);

	return count;
}

void tc::io::MemoryStream::write(const byte_t* ptr, size_t count) 
{
	if (ptr == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"::write()", "ptr is null.");
	}

	if (count > StreamUtil::getWritableSize(mData.size(), *mPosition))
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::write()", "count is too large.");
	}

	memcpy(mData.get() + *mPosition, ptr, count);

	*mPosition += int64_t(count);
}

int64_t tc::io::MemoryStream::seek(int64_t offset, SeekOrigin origin) 
{
	int64_t new_pos = StreamUtil::getSeekResult(offset, origin, *mPosition, (int64_t)mData.size());

	if (new_pos < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::seek()", "New position is negative.");
	}

	*mPosition = new_pos;

	return *mPosition;
}

void tc::io::MemoryStream::setLength(int64_t length) 
{
	// check length isn't too large (int64_t could be larger than size_t)
	if (length > std::numeric_limits<size_t>::max())
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::setLength()", "Length greater than maxium possible length for MemoryStream");
	}

	// check length isn't negative
	if (length < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::setLength()", "Length is negative.");
	}

	// create new ByteData
	ByteData data(length);

	// determine copy length (between old and new ByteData)
	size_t copy_len = std::min<size_t>(data.size(), mData.size());

	// copy from old to new ByteData
	memcpy(data.get(), mData.get(), copy_len);

	// re-assign mData (this frees the old mData)
	mData = data;

	// reduce position if shrunk
	*mPosition = std::min<int64_t>(*mPosition, int64_t(mData.size()));
}

void tc::io::MemoryStream::flush() 
{
	// do nothing
}

void tc::io::MemoryStream::dispose() 
{
	mData = ByteData();
}