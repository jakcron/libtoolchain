#include <tc/fs/SandboxedIFile.h>

tc::fs::SandboxedIFile::SandboxedIFile(const tc::SharedPtr<tc::fs::IFile>& file_ptr, uint64_t file_base_offset, uint64_t virtual_size) :
	mFile(file_ptr),
	mFileBaseOffset(file_base_offset),
	mVirtualSize(virtual_size),
	mVirtualOffset(0)
{
}

uint64_t tc::fs::SandboxedIFile::size()
{
	return mVirtualSize;
}

void tc::fs::SandboxedIFile::seek(uint64_t offset)
{
#define _MIN(x,y) (x < y? x : y)
	mVirtualOffset = _MIN(offset, mVirtualSize);
#undef _MIN
}

uint64_t tc::fs::SandboxedIFile::pos()
{
	return mVirtualOffset;
}

void tc::fs::SandboxedIFile::read(byte_t* out, size_t len)
{
	// assert proper position in file
	mFile->seek(mVirtualOffset + mFileBaseOffset);

	// read data
	mFile->read(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}

void tc::fs::SandboxedIFile::write(const byte_t* out, size_t len)
{
	// assert proper position in file
	mFile->seek(mVirtualOffset + mFileBaseOffset);

	// write data
	mFile->write(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}