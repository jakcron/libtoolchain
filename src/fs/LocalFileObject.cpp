#include "LocalFileObject.h"
#include <tc/Exception.h>

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#endif

const std::string tc::fs::LocalFileObject::kClassName = "tc::fs::LocalFileObject";

tc::fs::LocalFileObject::LocalFileObject(FileAccessMode mode, fs_handle_t file_handle) :
	mMode(mode),
	mFileHandle(new LocalFileHandle(file_handle))
{
	
}

uint64_t tc::fs::LocalFileObject::size()
{
	uint64_t fsize = 0;
#ifdef _WIN32
	LARGE_INTEGER win_fsize;
	if (GetFileSizeEx(mFileHandle->getHandle(), &win_fsize) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::to_string(GetLastError()) + ")");
	}

	fsize = win_fsize.QuadPart;

#else
	int64_t cur_pos = lseek(mFileHandle->getHandle(), 0, SEEK_CUR);
	if (cur_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}

	int64_t end_pos = lseek(mFileHandle->getHandle(), 0, SEEK_END);
	if (end_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	fsize = (uint64_t)end_pos;

	int64_t ret = lseek(mFileHandle->getHandle(), cur_pos, SEEK_SET);
	if (ret == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	
#endif
	return fsize;
}

void tc::fs::LocalFileObject::seek(uint64_t offset)
{
	// limit seek to the file size
	uint64_t fsize = size();
	if (offset > fsize)
	{
		offset = fsize;
	}
	

#ifdef _WIN32
	LARGE_INTEGER win_pos, out;
	win_pos.QuadPart = offset;
	if (SetFilePointerEx(
		mFileHandle->getHandle(),
		win_pos,
		&out,
		FILE_BEGIN
	) == false || out.QuadPart != win_pos.QuadPart)
	{
		throw tc::Exception(kClassName, "Failed to set file position (" + std::to_string(GetLastError()) + ")");
	}
#else
	int64_t fpos = lseek(mFileHandle->getHandle(), offset, SEEK_SET);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to set file position (" + std::string(strerror(errno)) + ")");
	}
#endif
}

uint64_t tc::fs::LocalFileObject::pos()
{
#ifdef _WIN32
	LARGE_INTEGER win_pos, out;
	win_pos.QuadPart = 0;
	if (SetFilePointerEx(
		mFileHandle->getHandle(),
		win_pos,
		&out,
		FILE_CURRENT
	) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file position (" + std::to_string(GetLastError()) + ")");
	}

	return out.QuadPart;
#else
	int64_t fpos = lseek(mFileHandle->getHandle(), 0, SEEK_CUR);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file position (" + std::string(strerror(errno)) + ")");
	}

	return fpos;
#endif
}

void tc::fs::LocalFileObject::read(byte_t* data, size_t len)
{
	// prevent excessive read()
	if ((pos() + len) > size())
	{
		throw tc::Exception(kClassName, "Failed to read file (Illegal read length)");
	}

#ifdef _WIN32
	DWORD bytes_read;

	if (ReadFile(mFileHandle->getHandle(), data, (DWORD)len, &bytes_read, NULL) == false)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::to_string(GetLastError()) + ")");
	}

	if (bytes_read != len)
	{
		throw tc::Exception(kClassName, "Failed to read file (bytes read was not correct length)");
	}
#else
	if (::read(mFileHandle->getHandle(), data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::fs::LocalFileObject::write(const byte_t* data, size_t len)
{
#ifdef _WIN32
	DWORD bytes_written;

	if (WriteFile(mFileHandle->getHandle(), data, (DWORD)len, &bytes_written, NULL) == false)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::to_string(GetLastError()) + ")");
	}

	if (bytes_written != len)
	{
		throw tc::Exception(kClassName, "Failed to read file (bytes written was not correct length)");
	}
#else
	if (::write(mFileHandle->getHandle(), data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to write file (" + std::string(strerror(errno)) + ")");
	}
#endif
}

tc::fs::IFileObject* tc::fs::LocalFileObject::copyInstance() const
{
	return new LocalFileObject(*this);
}
tc::fs::IFileObject* tc::fs::LocalFileObject::moveInstance()
{
	return new LocalFileObject(std::move(*this));
}