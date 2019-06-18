#include <tc/fs/SandboxedFileObject.h>

const std::string tc::fs::SandboxedFileObject::kClassName = "tc::fs::SandboxedFileObject";

tc::fs::SandboxedFileObject::SandboxedFileObject() :
	mFile(),
	mFileBaseOffset(0),
	mVirtualSize(0),
	mVirtualOffset(0)
{}
	

tc::fs::SandboxedFileObject::SandboxedFileObject(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size) :
	SandboxedFileObject()
{
	initialise(file, file_base_offset, virtual_size);
}

tc::fs::SandboxedFileObject::SandboxedFileObject(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size) :
	SandboxedFileObject()
{
	initialise(std::move(file), file_base_offset, virtual_size);
}

tc::fs::IFileObject* tc::fs::SandboxedFileObject::copyInstance() const
{
	return new SandboxedFileObject(*this);	
}

tc::fs::IFileObject* tc::fs::SandboxedFileObject::moveInstance()
{
	return new SandboxedFileObject(std::move(*this));
}

tc::ResourceState tc::fs::SandboxedFileObject::state()
{
	return mFile.state();
}

void tc::fs::SandboxedFileObject::initialise(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size)
{
	close();

	mFile = file;
	if (mFile.state().test(RESFLAG_READY))
	{
		mFileBaseOffset = file_base_offset;
		mVirtualSize = virtual_size;
		mVirtualOffset = 0;
	}
	else
	{
		mFile.close();
	}
}

void tc::fs::SandboxedFileObject::initialise(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size)
{
	close();

	mFile = std::move(file);
	if (mFile.state().test(RESFLAG_READY))
	{
		mFileBaseOffset = file_base_offset;
		mVirtualSize = virtual_size;
		mVirtualOffset = 0;
	}
	else
	{
		mFile.close();
	}
}

void tc::fs::SandboxedFileObject::close()
{
	mFile.close();
	mFileBaseOffset = 0;
	mVirtualSize = 0;
	mVirtualOffset = 0;
}

uint64_t tc::fs::SandboxedFileObject::size()
{
	return mVirtualSize;
}

void tc::fs::SandboxedFileObject::seek(uint64_t offset)
{
#define _MIN(x,y) (x < y? x : y)
	mVirtualOffset = _MIN(offset, mVirtualSize);
#undef _MIN
}

uint64_t tc::fs::SandboxedFileObject::pos()
{
	return mVirtualOffset;
}

void tc::fs::SandboxedFileObject::read(byte_t* out, size_t len)
{
	// assert proper position in file
	mFile.seek(mVirtualOffset + mFileBaseOffset);

	// read data
	mFile.read(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}

void tc::fs::SandboxedFileObject::write(const byte_t* out, size_t len)
{
	// assert proper position in file
	mFile.seek(mVirtualOffset + mFileBaseOffset);

	// write data
	mFile.write(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}