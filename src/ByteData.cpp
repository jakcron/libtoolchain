#include <tc/ByteData.h>

const std::string tc::ByteData::kClassName = "tc::ByteData";

tc::ByteData::ByteData() :
	ByteData(0)
{}

tc::ByteData::ByteData(size_t size, bool clear_memory)
{
	if (size == 0)
	{
		mPtr.reset();
	}
	else 
	{
		try
		{
			mPtr = std::shared_ptr<byte_t>(new byte_t[size]);
		} 
		catch (std::bad_alloc) 
		{
			throw tc::OutOfMemoryException(kClassName, "std::bad_alloc thrown");
		}
		
		if (mPtr == nullptr)
		{
			throw tc::OutOfMemoryException(kClassName, "Failed to allocate memory");
		}
	}
	
	mSize = size;

	if (clear_memory == true)
	{
		memset(mPtr.get(), 0, mSize);
	}
}

tc::ByteData::ByteData(const byte_t* data, size_t size) :
	ByteData(size, false)
{
	memcpy(mPtr.get(), data, mSize);
}

byte_t* tc::ByteData::get() const
{
	return mPtr.get();
}

size_t tc::ByteData::size() const
{
	return mPtr == nullptr ? 0 : mSize;
}