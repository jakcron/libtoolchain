#include <tc/fs/PartitionedFileObject.h>

const std::string tc::fs::PartitionedFileObject::kClassName = "tc::fs::PartitionedFileObject";

tc::fs::PartitionedFileObject::PartitionedFileObject() :
	mFile(),
	mFileBaseOffset(0),
	mVirtualSize(0),
	mVirtualOffset(0)
{}
	

tc::fs::PartitionedFileObject::PartitionedFileObject(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size) :
	PartitionedFileObject()
{
	initialise(file, file_base_offset, virtual_size);
}

tc::fs::PartitionedFileObject::PartitionedFileObject(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size) :
	PartitionedFileObject()
{
	initialise(std::move(file), file_base_offset, virtual_size);
}

tc::fs::IFileObject* tc::fs::PartitionedFileObject::copyInstance() const
{
	return new PartitionedFileObject(*this);	
}

tc::fs::IFileObject* tc::fs::PartitionedFileObject::moveInstance()
{
	return new PartitionedFileObject(std::move(*this));
}

tc::ResourceState tc::fs::PartitionedFileObject::state()
{
	return mFile.state();
}

void tc::fs::PartitionedFileObject::initialise(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size)
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

void tc::fs::PartitionedFileObject::initialise(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size)
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

void tc::fs::PartitionedFileObject::close()
{
	mFile.close();
	mFileBaseOffset = 0;
	mVirtualSize = 0;
	mVirtualOffset = 0;
}

uint64_t tc::fs::PartitionedFileObject::size()
{
	return mVirtualSize;
}

void tc::fs::PartitionedFileObject::seek(uint64_t offset)
{
#define _MIN(x,y) (x < y? x : y)
	mVirtualOffset = _MIN(offset, mVirtualSize);
#undef _MIN
}

uint64_t tc::fs::PartitionedFileObject::pos()
{
	return mVirtualOffset;
}

void tc::fs::PartitionedFileObject::read(byte_t* out, size_t len)
{
	// assert proper position in file
	mFile.seek(mVirtualOffset + mFileBaseOffset);

	// read data
	mFile.read(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}

void tc::fs::PartitionedFileObject::write(const byte_t* out, size_t len)
{
	// assert proper position in file
	mFile.seek(mVirtualOffset + mFileBaseOffset);

	// write data
	mFile.write(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}