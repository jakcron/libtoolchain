#include <tc/io/EmptyStream.h>
#include <tc/io/StreamUtil.h>

const std::string tc::io::EmptyStream::kClassName = "tc::io::EmptyStream";

tc::io::EmptyStream::EmptyStream()
{}

bool tc::io::EmptyStream::canRead() const 
{
	return true;
}

bool tc::io::EmptyStream::canWrite() const 
{
	return false;
}
	
bool tc::io::EmptyStream::canSeek() const 
{
	return true;
}

int64_t tc::io::EmptyStream::length() 
{
	return 0;
}

int64_t tc::io::EmptyStream::position() 
{
	return 0;
}

size_t tc::io::EmptyStream::read(byte_t* ptr, size_t count) 
{
	if (ptr == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"::read()", "ptr is null.");
	}

	return 0;
}

size_t tc::io::EmptyStream::write(const byte_t* ptr, size_t count) 
{
	throw tc::NotSupportedException(kClassName+"::write()", "Stream does not support writing");
}

int64_t tc::io::EmptyStream::seek(int64_t offset, SeekOrigin origin) 
{
	// here to throw exception on bad origin value
	StreamUtil::getSeekResult(offset, origin, 0, 0);

	return 0;
}

void tc::io::EmptyStream::setLength(int64_t length) 
{
	throw tc::NotSupportedException(kClassName+"setLength()", "setLength() is not supported for tc::io::EmptyStream.");
}

void tc::io::EmptyStream::flush() 
{
	// do nothing
}

void tc::io::EmptyStream::dispose() 
{
}