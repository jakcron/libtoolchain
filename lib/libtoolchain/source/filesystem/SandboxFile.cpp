#include <tc/filesystem/SandboxFile.h>

tc::filesystem::SandboxFile::SandboxFile(const tc::SharedPtr<tc::filesystem::IFile>& file_ptr, uint64_t file_base_offset, uint64_t virtual_size) :
	mFile(file_ptr),
	mFileBaseOffset(file_base_offset),
	mVirtualSize(virtual_size),
	mVirtualOffset(0)
{
}

uint64_t tc::filesystem::SandboxFile::size()
{
	return mVirtualSize;
}

void tc::filesystem::SandboxFile::seek(uint64_t offset)
{
#define _MIN(x,y) (x < y? x : y)
	mVirtualOffset = _MIN(offset, mVirtualSize);
#undef _MIN
}

uint64_t tc::filesystem::SandboxFile::pos()
{
	return mVirtualOffset;
}

void tc::filesystem::SandboxFile::read(byte_t* out, size_t len)
{
	// assert proper position in file
	(*mFile)->seek(mVirtualOffset + mFileBaseOffset);

	// read data
	(*mFile)->read(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}

void tc::filesystem::SandboxFile::write(const byte_t* out, size_t len)
{
	// assert proper position in file
	(*mFile)->seek(mVirtualOffset + mFileBaseOffset);

	// write data
	(*mFile)->write(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}