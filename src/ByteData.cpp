#include <tc/ByteData.h>

const std::string tc::ByteData::kClassName = "tc::ByteData";

tc::ByteData::ByteData() :
	ByteData(0)
{}

tc::ByteData::ByteData(size_t size)
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
		
		if (mPtr.get() == nullptr)
		{
			throw tc::OutOfMemoryException(kClassName, "Failed to allocate memory");
		}
	}
	
	mSize = size;
}

byte_t* tc::ByteData::buffer() const
{
	return mPtr.get();
}

size_t tc::ByteData::size() const
{
	return mPtr.get() == nullptr ? 0 : mSize;
}