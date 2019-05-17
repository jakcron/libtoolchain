#include <tc/fs/FileObject.h>

tc::fs::FileObject::FileObject() :
	mFile()
{
}

tc::fs::FileObject::FileObject(const tc::fs::FileObject& other) :
	FileObject()
{
	*this = other;
}

tc::fs::FileObject::FileObject(tc::fs::IFileObject* file_ptr) :
	mFile(file_ptr)
{
}

tc::fs::FileObject& tc::fs::FileObject::operator=(const tc::fs::FileObject& other)
{
	mFile = other.mFile;
	return *this;
}

uint64_t tc::fs::FileObject::size()
{
	if (mFile.isNull() == false)
		return mFile->size();
	else
		return 0;
}

void tc::fs::FileObject::seek(uint64_t offset)
{
	if (mFile.isNull() == false)
		mFile->seek(offset);
}

uint64_t tc::fs::FileObject::pos()
{
	if (mFile.isNull() == false)
		return mFile->pos();
	else
		return 0;
}

void tc::fs::FileObject::read(byte_t* data, size_t len)
{
	if (mFile.isNull() == false)
		mFile->read(data, len);
}

void tc::fs::FileObject::write(const byte_t* data, size_t len)
{
	if (mFile.isNull() == false)
		mFile->write(data, len);
}
