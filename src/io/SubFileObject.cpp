#include <tc/io/SubFileObject.h>
#include <tc/Exception.h>

const std::string tc::io::SubFileObject::kClassName = "tc::io::SubFileObject";

tc::io::SubFileObject::SubFileObject() :
	mFile(),
	mFileBaseOffset(0),
	mVirtualSize(0),
	mVirtualOffset(0)
{}
	

tc::io::SubFileObject::SubFileObject(const std::shared_ptr<tc::io::IFileObject>& file, uint64_t file_base_offset, uint64_t virtual_size) :
	SubFileObject()
{
	initialise(file, file_base_offset, virtual_size);
}

tc::io::SubFileObject::SubFileObject(std::shared_ptr<tc::io::IFileObject>&& file, uint64_t file_base_offset, uint64_t virtual_size) :
	SubFileObject()
{
	initialise(std::move(file), file_base_offset, virtual_size);
}

tc::ResourceState tc::io::SubFileObject::state()
{
	return mFile.get() ? mFile->state() : tc::ResourceState(RESFLAG_NOINIT);
}

void tc::io::SubFileObject::initialise(const std::shared_ptr<tc::io::IFileObject>& file, uint64_t file_base_offset, uint64_t virtual_size)
{
	close();

	mFile = file;
	if (mFile.get() != nullptr && mFile->state().test(RESFLAG_READY))
	{
		mFileBaseOffset = file_base_offset;
		mVirtualSize = virtual_size;
		mVirtualOffset = 0;
	}
	else
	{
		close();
	}
}

void tc::io::SubFileObject::initialise(std::shared_ptr<tc::io::IFileObject>&& file, uint64_t file_base_offset, uint64_t virtual_size)
{
	close();

	mFile = std::move(file);
	if (mFile.get() != nullptr && mFile->state().test(RESFLAG_READY))
	{
		mFileBaseOffset = file_base_offset;
		mVirtualSize = virtual_size;
		mVirtualOffset = 0;
	}
	else
	{
		close();
	}
}

void tc::io::SubFileObject::close()
{
	if (mFile.get() != nullptr)
		mFile->close();

	mFileBaseOffset = 0;
	mVirtualSize = 0;
	mVirtualOffset = 0;
}

uint64_t tc::io::SubFileObject::size()
{
	if (mFile.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get file size (no base file object)");
	}

	return mVirtualSize;
}

void tc::io::SubFileObject::seek(uint64_t offset)
{
	if (mFile.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to set file position (no base file object)");
	}

#define _MIN(x,y) (x < y? x : y)
	mVirtualOffset = _MIN(offset, mVirtualSize);
#undef _MIN
}

uint64_t tc::io::SubFileObject::pos()
{
	if (mFile.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get file position (no base file object)");
	}

	return mVirtualOffset;
}

void tc::io::SubFileObject::read(byte_t* out, size_t len)
{
	if (mFile.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to read file (no base file object)");
	}

	// assert proper position in file
	mFile->seek(mVirtualOffset + mFileBaseOffset);

	// read data
	mFile->read(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}

void tc::io::SubFileObject::write(const byte_t* out, size_t len)
{
	if (mFile.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to write file (no base file object)");
	}

	// assert proper position in file
	mFile->seek(mVirtualOffset + mFileBaseOffset);

	// write data
	mFile->write(out, len);

	// update virtual offset
	seek(mVirtualOffset + len);
}