#include <tc/fs/FileStream.h>

tc::fs::FileStream::FileStream() :
	mFile()
{
}

tc::fs::FileStream::FileStream(const tc::fs::FileStream& other) :
	FileStream()
{
	*this = other;
}

tc::fs::FileStream::FileStream(tc::fs::IFile* file_ptr) :
	mFile(file_ptr)
{
}

tc::fs::FileStream& tc::fs::FileStream::operator=(const tc::fs::FileStream& other)
{
	mFile = other.mFile;
	return *this;
}

uint64_t tc::fs::FileStream::size()
{
	if (mFile.isNull() == false)
		return mFile->size();
	else
		return 0;
}

void tc::fs::FileStream::seek(uint64_t offset)
{
	if (mFile.isNull() == false)
		mFile->seek(offset);
}

uint64_t tc::fs::FileStream::pos()
{
	if (mFile.isNull() == false)
		return mFile->pos();
	else
		return 0;
}

void tc::fs::FileStream::read(byte_t* data, size_t len)
{
	if (mFile.isNull() == false)
		mFile->read(data, len);
}

void tc::fs::FileStream::write(const byte_t* data, size_t len)
{
	if (mFile.isNull() == false)
		mFile->write(data, len);
}
