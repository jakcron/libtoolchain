#include <tc/fs/LocalFileObject.h>
#include <tc/Exception.h>
#include <tc/fs/PathUtils.h>

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#endif

const std::string tc::fs::LocalFileObject::kClassName = "tc::fs::LocalFileObject";

tc::fs::LocalFileObject::FileHandle::~FileHandle()
{
#ifdef _WIN32
	CloseHandle(handle);
#else
	::close(handle);
#endif
}

tc::fs::LocalFileObject::LocalFileObject() :
	mState(0),
	mMode(FILEACCESS_READ),
	mFileHandle()
{}

tc::fs::LocalFileObject::LocalFileObject(const tc::fs::Path& path, tc::fs::FileAccessMode mode) :
	LocalFileObject()
{
	open(path, mode);
}

tc::ResourceState tc::fs::LocalFileObject::state()
{
	return mState;
}

void tc::fs::LocalFileObject::open(const tc::fs::Path& path, tc::fs::FileAccessMode mode)
{
	// close file before opening file
	close();

#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	// open file
	HANDLE file_handle = CreateFileW((LPCWSTR)unicode_path.c_str(),
							  getOpenModeFlag(mode),
							  getShareModeFlag(mode),
							  0,
							  getCreationModeFlag(mode),
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
		
	// check file handle
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		throw tc::Exception(kClassName, "Failed to open file (" + std::to_string(GetLastError()) + ")");
	}

	// store file handle
	mFileHandle = std::shared_ptr<tc::fs::LocalFileObject::FileHandle>(new tc::fs::LocalFileObject::FileHandle(file_handle));
	
	// set state as initialised
	mState.set(RESFLAG_READY);
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	// open file
	int file_handle = ::open(unicode_path.c_str(), getOpenModeFlag(mode), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	// check file handle
	if (file_handle == -1)
	{
		throw tc::Exception(kClassName, "Failed to open file (" + std::string(strerror(errno)) + ")");
	}

	// store file handle
	mFileHandle = std::shared_ptr<tc::fs::LocalFileObject::FileHandle>(new tc::fs::LocalFileObject::FileHandle(file_handle));
	
	// set state as initialised
	mState.set(RESFLAG_READY);
#endif
}

void tc::fs::LocalFileObject::close()
{
	if (mState.test(RESFLAG_READY))
	{
		mFileHandle.reset();
	}
	mState.reset() = 0;
}

uint64_t tc::fs::LocalFileObject::size()
{
	if (mState.test(RESFLAG_READY) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file size (no file open)");
	}

	uint64_t fsize = 0;
#ifdef _WIN32
	LARGE_INTEGER win_fsize;
	if (GetFileSizeEx(mFileHandle->handle, &win_fsize) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::to_string(GetLastError()) + ")");
	}

	fsize = win_fsize.QuadPart;

#else
	int64_t cur_pos = lseek(mFileHandle->handle, 0, SEEK_CUR);
	if (cur_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}

	int64_t end_pos = lseek(mFileHandle->handle, 0, SEEK_END);
	if (end_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	fsize = (uint64_t)end_pos;

	int64_t ret = lseek(mFileHandle->handle, cur_pos, SEEK_SET);
	if (ret == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	
#endif
	return fsize;
}

void tc::fs::LocalFileObject::seek(uint64_t offset)
{
	if (mState.test(RESFLAG_READY) == false)
	{
		throw tc::Exception(kClassName, "Failed to set file position (no file open)");
	}

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
		mFileHandle->handle,
		win_pos,
		&out,
		FILE_BEGIN
	) == false || out.QuadPart != win_pos.QuadPart)
	{
		throw tc::Exception(kClassName, "Failed to set file position (" + std::to_string(GetLastError()) + ")");
	}
#else
	int64_t fpos = lseek(mFileHandle->handle, offset, SEEK_SET);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to set file position (" + std::string(strerror(errno)) + ")");
	}
#endif
}

uint64_t tc::fs::LocalFileObject::pos()
{
	if (mState.test(RESFLAG_READY) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file position (no file open)");
	}

#ifdef _WIN32
	LARGE_INTEGER win_pos, out;
	win_pos.QuadPart = 0;
	if (SetFilePointerEx(
		mFileHandle->handle,
		win_pos,
		&out,
		FILE_CURRENT
	) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file position (" + std::to_string(GetLastError()) + ")");
	}

	return out.QuadPart;
#else
	int64_t fpos = lseek(mFileHandle->handle, 0, SEEK_CUR);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file position (" + std::string(strerror(errno)) + ")");
	}

	return fpos;
#endif
}

void tc::fs::LocalFileObject::read(byte_t* data, size_t len)
{
	if (mState.test(RESFLAG_READY) == false)
	{
		throw tc::Exception(kClassName, "Failed to read file (no file open)");
	}

	// prevent excessive read()
	if ((pos() + len) > size())
	{
		throw tc::Exception(kClassName, "Failed to read file (Illegal read length)");
	}

#ifdef _WIN32
	DWORD bytes_read;

	if (ReadFile(mFileHandle->handle, data, (DWORD)len, &bytes_read, NULL) == false)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::to_string(GetLastError()) + ")");
	}

	if (bytes_read != len)
	{
		throw tc::Exception(kClassName, "Failed to read file (bytes read was not correct length)");
	}
#else
	if (::read(mFileHandle->handle, data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::fs::LocalFileObject::write(const byte_t* data, size_t len)
{
	if (mState.test(RESFLAG_READY) == false)
	{
		throw tc::Exception(kClassName, "Failed to write file (no file open)");
	}

#ifdef _WIN32
	DWORD bytes_written;

	if (WriteFile(mFileHandle->handle, data, (DWORD)len, &bytes_written, NULL) == false)
	{
		throw tc::Exception(kClassName, "Failed to write file (" + std::to_string(GetLastError()) + ")");
	}

	if (bytes_written != len)
	{
		throw tc::Exception(kClassName, "Failed to write file (bytes written was not correct length)");
	}
#else
	if (::write(mFileHandle->handle, data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to write file (" + std::string(strerror(errno)) + ")");
	}
#endif
}

#ifdef _WIN32
DWORD tc::fs::LocalFileObject::getOpenModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FILEACCESS_READ):
			flag = GENERIC_READ;
			break;
		case (FILEACCESS_EDIT):
			flag = GENERIC_READ | GENERIC_WRITE;
			break;
		case (FILEACCESS_CREATE):
			flag = GENERIC_WRITE;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
DWORD tc::fs::LocalFileObject::getShareModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FILEACCESS_READ):
			flag = FILE_SHARE_READ;
			break;
		case (FILEACCESS_EDIT):
			flag = FILE_SHARE_READ;
			break;
		case (FILEACCESS_CREATE):
			flag = 0;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
DWORD tc::fs::LocalFileObject::getCreationModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FILEACCESS_READ):
			flag = OPEN_EXISTING;
			break;
		case (FILEACCESS_EDIT):
			flag = OPEN_EXISTING;
			break;
		case (FILEACCESS_CREATE):
			flag = CREATE_ALWAYS;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
#else
int tc::fs::LocalFileObject::getOpenModeFlag(FileAccessMode mode) const
{
	int flag = 0;
	switch (mode)
	{
		case (FILEACCESS_READ):
			flag = O_RDONLY;
			break;
		case (FILEACCESS_EDIT):
			flag = O_RDWR;
			break;
		case (FILEACCESS_CREATE):
			flag = O_CREAT | O_TRUNC | O_WRONLY;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
#endif