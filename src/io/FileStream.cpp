#include <tc/io/FileStream.h>
#include <tc/io/PathUtils.h>

// exceptions
#include <tc/Exception.h>
#include <tc/AccessViolationException.h>
#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotSupportedException.h>
#include <tc/NotImplementedException.h>
#include <tc/ObjectDisposedException.h>
#include <tc/OverflowException.h>
#include <tc/UnauthorisedAccessException.h>
#include <tc/io/IOException.h>
#include <tc/io/FileNotFoundException.h>
#include <tc/io/PathTooLongException.h>



#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#endif

const std::string tc::io::FileStream::kClassName = "tc::io::FileStream";

tc::io::FileStream::FileHandle::~FileHandle()
{
#ifdef _WIN32
	CloseHandle(handle);
#else
	::close(handle);
#endif
}

tc::io::FileStream::FileStream() :
	mCanRead(false),
	mCanWrite(false),
	mCanSeek(false),
	mFileHandle()
{}

tc::io::FileStream::FileStream(const tc::io::Path& path, FileMode mode, FileAccess access) :
	FileStream()
{
	open(path, mode, access);
}

void tc::io::FileStream::open(const tc::io::Path& path, FileMode mode, FileAccess access)
{
	// dispose stream before opening new stream
	dispose();

	open_impl(path, mode, access);
}

bool tc::io::FileStream::canRead() const
{
	return mCanRead;
}

bool tc::io::FileStream::canWrite() const
{
	return mCanWrite;
}
bool tc::io::FileStream::canSeek() const
{
	return mCanSeek;
}

int64_t tc::io::FileStream::length()
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::length()", "Failed to get stream length (stream is disposed)");
	}

	return length_impl();
}

int64_t tc::io::FileStream::position()
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::position()", "Failed to get file position (stream is disposed)");
	}

	if (mCanSeek == false)
	{
		throw tc::NotSupportedException(kClassName+"::position()", "This method is not supported for streams that do not support seeking");
	}

	return seek(0, SeekOrigin::Current);
}

size_t tc::io::FileStream::read(byte_t* buffer, size_t count)
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::read()", "Failed to read from stream (stream is disposed)");
	}

	if (mCanRead == false)
	{
		throw tc::UnauthorisedAccessException(kClassName+"::read()", "Stream does not support reading");
	}

	if (buffer == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"::read()", "buffer was null");
	}

	if (count < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::read()", "count was negative");
	}

	return read_impl(buffer, count);
}

void tc::io::FileStream::write(const byte_t* buffer, size_t count)
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::write()", "Failed to write to stream (no file open)");
	}

	if (mCanWrite == false)
	{
		throw tc::NotSupportedException(kClassName+"::write()", "Stream does not support writing");
	}

	if (buffer == nullptr)
	{
		throw tc::ArgumentNullException(kClassName+"::write()", "buffer was null");
	}

	if (count < 0)
	{
		throw tc::ArgumentOutOfRangeException(kClassName+"::write()", "count was negative");
	}

	write_impl(buffer, count);
}

int64_t tc::io::FileStream::seek(int64_t offset, SeekOrigin origin)
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	if (mCanSeek == false)
	{
		throw tc::NotSupportedException(kClassName+"::seek()", "Stream does not support seeking");
	}

	return seek_impl(offset, origin);
}

void tc::io::FileStream::setLength(int64_t length)
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	if (mCanWrite == false || mCanSeek == false)
	{
		throw tc::NotSupportedException(kClassName+"::setLength()", "Stream does not support both writing and seeking");
	}

	setLength_impl(length);
}

void tc::io::FileStream::flush()
{
	if (mFileHandle.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::flush()", "Failed to flush stream (stream is disposed)");
	}

	flush_impl();
}

void tc::io::FileStream::dispose()
{
	flush();
	mFileHandle.reset();
	mCanRead = false;
	mCanWrite = false;
	mCanSeek = false;
}

#ifdef _WIN32
void tc::io::FileStream::open_impl(const tc::io::Path& path, FileMode mode, FileAccess access)
{
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	DWORD access_flag = 0;
	DWORD share_mode_flag = 0;
	DWORD creation_flag = 0;

	// process mode
	switch (mode) 
	{
		case (FileMode::CreateNew):
			// create file if does not exist | return error if file does not exist
			creation_flag = CREATE_NEW;
			break;
		case (FileMode::Create):
			// create file if does not exist | truncate file if it exists
			creation_flag = CREATE_ALWAYS;
			break;
		case (FileMode::Open):
			// no flags
			creation_flag = OPEN_EXISTING;
			break;
		case (FileMode::OpenOrCreate):
			// create file if does not exist 
			creation_flag = OPEN_ALWAYS;
			break;
		case (FileMode::Truncate):
			// truncate file if file exists
			creation_flag = TRUNCATE_EXISTING;
			break;
		case (FileMode::Append):
			// open in append mode
			creation_flag = OPEN_EXISTING;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"open()", "Illegal value for mode");
	}

	// process access
	switch (access)
	{
		case (FileAccess::Read):
			// read access
			access_flag = GENERIC_READ;
			// shared read lock
			share_mode_flag = FILE_SHARE_READ;
			break;
		case (FileAccess::Write):
			// write access
			access_flag = GENERIC_WRITE;
			// exclusive lock
			share_mode_flag = 0;
			break;
		case (FileAccess::ReadWrite):
			// read/write access
			access_flag = GENERIC_READ | GENERIC_WRITE;
			// exclusive lock
			share_mode_flag = 0;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"open()", "Illegal value for access");
	}


	// open file
	HANDLE file_handle = CreateFileW((LPCWSTR)unicode_path.c_str(),
							  access_flag,
							  share_mode_flag,
							  0,
							  creation_flag,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
		
	// check file handle
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			case (ERROR_FILE_NOT_FOUND):
				throw tc::io::FileNotFoundException(kClassName+"::open()", std::to_string(error));
			case (ERROR_FILE_EXISTS):
				throw tc::io::IOException(kClassName+"::open()", std::to_string(error));
			case (ERROR_ACCESS_DENIED):
				throw tc::UnauthorisedAccessException(kClassName+"::open()", std::to_string(error));
			default:
				throw tc::io::IOException(kClassName+"::open()", "Failed to open file stream (" + std::to_string(error) + ")");
		}
	}

	// store file handle
	mFileHandle = std::shared_ptr<tc::io::FileStream::FileHandle>(new tc::io::FileStream::FileHandle(file_handle));
	
	// seek to end of file if in append mode
	if (mMode == FileMode::Append)
		seek(0, SeekOrigin::End);

	// set state flags
	mCanRead = (access_flag & GENERIC_READ) ? true : false;
	mCanWrite = (access_flag & GENERIC_WRITE) ? true : false;
	mCanSeek = GetFileType(mFileHandle->handle) == FILE_TYPE_DISK ? true : false;
}

int64_t tc::io::FileStream::length_impl()
{
	LARGE_INTEGER stream_length;

	if (GetFileSizeEx(mFileHandle->handle, &stream_length) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::length()", "Failed to get stream length (" + std::to_string(error) + ")");
		}
	}
	
	return (int64_t) stream_length.QuadPart;
}

size_t tc::io::FileStream::read_impl(byte_t* buffer, size_t count)
{
	DWORD bytes_read;

	if (ReadFile(mFileHandle->handle, buffer, (DWORD)count, &bytes_read, NULL) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::read()", "Failed to read from stream (" + std::to_string(error) + ")");
		}
	}

	if (bytes_read != count)
	{
		throw tc::io::IOException(kClassName+"::read()", "Failed to read from stream (bytes read was not correct length)");
	}

	return bytes_read;
}

void tc::io::FileStream::write_impl(const byte_t* buffer, size_t count)
{
	DWORD bytes_written;

	if (WriteFile(mFileHandle->handle, buffer, (DWORD)count, &bytes_written, NULL) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::write()", "Failed to write to stream (" + std::to_string(error) + ")");
		}
	}

	if (bytes_written != count)
	{
		throw tc::io::IOException(kClassName+"::write()", "Failed to write to stream (bytes written was not correct length)");
	}
}

int64_t tc::io::FileStream::seek_impl(int64_t offset, SeekOrigin origin)
{
	DWORD seek_flag = 0;
	switch(origin)
	{
		case (SeekOrigin::Begin):
			seek_flag = FILE_BEGIN;
			break;
		case (SeekOrigin::Current):
			seek_flag = FILE_CURRENT;
			break;
		case (SeekOrigin::End):
			seek_flag = FILE_END;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"::seek()", "Unknown SeekOrigin value");
	}

	LARGE_INTEGER win_pos, out;
	win_pos.QuadPart = offset;
	if (SetFilePointerEx(
		mFileHandle->handle,
		win_pos,
		&out,
		seek_flag
	) == false || out.QuadPart != win_pos.QuadPart)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::seek()", "Failed to set stream position (" + std::to_string(error) + ")");
		}
	}

	return out.QuadPart;
}

void tc::io::FileStream::setLength_impl(int64_t length)
{
	throw tc::NotImplementedException(kClassName, "setLength() not implemented");
}

void tc::io::FileStream::flush_impl()
{
	if (mCanWrite)
	{
		// flush buffers only applies to written data
		FlushFileBuffers(mFileHandle->handle);
	}
}
#else
void tc::io::FileStream::open_impl(const tc::io::Path& path, FileMode mode, FileAccess access)
{
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	// open file
	int open_flag = 0;

	// process mode
	switch (mode) 
	{
		case (FileMode::CreateNew):
			// create file if does not exist | return error if file does not exist
			open_flag |= O_CREAT | O_EXCL;
			break;
		case (FileMode::Create):
			// create file if does not exist | truncate file if it exists
			open_flag |= O_CREAT | O_TRUNC;
			break;
		case (FileMode::Open):
			// no flags
			open_flag |= 0;
			break;
		case (FileMode::OpenOrCreate):
			// create file if does not exist 
			open_flag |= O_CREAT;
			break;
		case (FileMode::Truncate):
			// truncate file if file exists
			open_flag |= O_TRUNC;
			break;
		case (FileMode::Append):
			// open in append mode
			open_flag |= O_APPEND;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"open()", "Illegal value for mode");
	}

	// process access
	switch (access)
	{
		case (FileAccess::Read):
			// read access | shared lock
			open_flag |= O_RDONLY | O_SHLOCK;
			break;
		case (FileAccess::Write):
			// write access | exclusive lock
			open_flag |= O_WRONLY | O_EXLOCK;
			break;
		case (FileAccess::ReadWrite):
			// read/write access | exclusive lock
			open_flag |= O_RDWR | O_EXLOCK;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"open()", "Illegal value for access");
	}

	// validate use of write dependent flags
	if ((open_flag & (O_APPEND | O_TRUNC | O_CREAT)) && !(open_flag & (O_WRONLY|O_RDWR))) {
		throw tc::ArgumentException(kClassName+"open()", "Stream open mode requires write access, but write access was not allowed");
	}

	// open file handle with Read/Write for User, Read for Group, nothing for others
	int file_handle	= ::open(unicode_path.c_str(), open_flag, S_IRUSR | S_IWUSR | S_IRGRP);

	// handle error
	if (file_handle == -1)
	{
		switch (errno) 
		{
			case (EACCES):
			case (EROFS):
				throw tc::UnauthorisedAccessException(kClassName+"::open()", std::string(strerror(errno)));
			case (ENAMETOOLONG):
				throw tc::io::PathTooLongException(kClassName+"open()", std::string(strerror(errno)));
			case (ENOENT):
				throw tc::io::FileNotFoundException(kClassName+"open()", std::string(strerror(errno)));
			case (EEXIST):
				throw tc::io::IOException(kClassName+"open()", std::string(strerror(errno)));
			case (EINVAL):
				throw tc::ArgumentOutOfRangeException(kClassName+"::open()", std::string(strerror(errno)));			
			case (EFAULT):
				throw tc::AccessViolationException(kClassName+"::open()", std::string(strerror(errno)));
			case (EISDIR):
				throw tc::io::FileNotFoundException(kClassName+"::open()", std::string(strerror(errno)));
			case (EDQUOT):
			case (EFBIG):
			case (EINTR):
			case (ELOOP):
			case (EMFILE):
			case (ENFILE):
			case (ENOMEM):
			case (ENOSPC):
			case (ENXIO):
			case (EOVERFLOW):
			case (EPERM):
			case (ETXTBSY):
			case (EWOULDBLOCK):
			default:
				throw tc::io::IOException(kClassName+"::open()", "Failed to open file stream (" + std::string(strerror(errno)) + ")");
		}
	}

	// store file handle
	mFileHandle = std::shared_ptr<tc::io::FileStream::FileHandle>(new tc::io::FileStream::FileHandle(file_handle));

	// get stat info on file
	struct stat stat_buf;
	if (fstat(mFileHandle->handle, &stat_buf) == -1)
	{
		throw tc::io::IOException(kClassName+"::open()", "Failed to check stream properties using fstat() (" + std::string(strerror(errno)) + ")");
	}

	// if this is a directory throw an exception
	if (S_ISDIR(stat_buf.st_mode))
	{
		throw tc::io::IOException(kClassName+"::open()", "Path refers to a directory not a file");
	}

	// set state flags
	mCanRead = (open_flag & (O_RDONLY|O_RDWR)) ? true : false;
	mCanWrite = (open_flag & (O_WRONLY|O_RDWR)) ? true : false;
	mCanSeek = S_ISREG(stat_buf.st_mode) ? true : false;
}

int64_t tc::io::FileStream::length_impl()
{
	int64_t length;

	// use seek method (real disk files)
	if (mCanSeek == true)
	{
		// save current position
		int64_t cur_pos = seek(0, SeekOrigin::Current);

		// seek to end of file
		length = seek(0, SeekOrigin::End);

		// restore current position
		seek(cur_pos, SeekOrigin::Begin);
	}
	else
	{
		throw tc::NotSupportedException(kClassName, "length() cannot be used with device-files or pipes");
	}
	
	return length;
}

size_t tc::io::FileStream::read_impl(byte_t* buffer, size_t count)
{
	int64_t read_len = ::read(mFileHandle->handle, buffer, count);

	if (read_len == -1)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::string(strerror(errno)) + ")");
	}

	// handle error
	if (read_len == -1)
	{
		switch (errno) 
		{	
			case (EINVAL):
				throw tc::ArgumentOutOfRangeException(kClassName+"::read()", std::string(strerror(errno)));			
			case (EFAULT):
				throw tc::AccessViolationException(kClassName+"::read()", std::string(strerror(errno)));
			case (EISDIR):
				throw tc::io::FileNotFoundException(kClassName+"::read()", std::string(strerror(errno)));
			case (EBADF):
			case (EAGAIN):
			case (EINTR):
			case (EIO):
			default:
				throw tc::io::IOException(kClassName+"::read()", "Failed to read from stream (" + std::string(strerror(errno)) + ")");
		}
	}

	return read_len;
}

void tc::io::FileStream::write_impl(const byte_t* buffer, size_t count)
{
	int64_t write_len = ::write(mFileHandle->handle, buffer, count);

	// handle error
	if (write_len == -1)
	{
		switch (errno) 
		{	
			case (EINVAL):
				throw tc::ArgumentOutOfRangeException(kClassName+"::write()", std::string(strerror(errno)));			
			case (EFBIG):
				throw tc::OverflowException(kClassName+"::write()", std::string(strerror(errno)));
			case (EFAULT):
				throw tc::AccessViolationException(kClassName+"::write()", std::string(strerror(errno)));
			case (EAGAIN):
			case (EDESTADDRREQ):
			case (EDQUOT):
			case (EINTR):
			case (EIO):
			case (ENOSPC):
			case (EPERM):
			case (EPIPE):
			default:
				throw tc::io::IOException(kClassName+"::write()", "Failed to write to stream (" + std::string(strerror(errno)) + ")");
		}
	}
}

int64_t tc::io::FileStream::seek_impl(int64_t offset, SeekOrigin origin)
{
	int seek_flag = 0;
	switch(origin)
	{
		case (SeekOrigin::Begin):
			seek_flag = SEEK_SET;
			break;
		case (SeekOrigin::Current):
			seek_flag = SEEK_CUR;
			break;
		case (SeekOrigin::End):
			seek_flag = SEEK_END;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kClassName+"::seek()", "Unknown SeekOrigin value");
	}

#ifdef _LARGEFILE64_SOURCE
	int64_t fpos = lseek64(mFileHandle->handle, offset, seek_flag);
#else 
	int64_t fpos = lseek(mFileHandle->handle, offset, seek_flag);
#endif

	// handle error
	if (fpos == -1)
	{
		switch (errno) 
		{
			case (EINVAL):
				throw tc::ArgumentOutOfRangeException(kClassName+"::seek()",  std::string(strerror(errno)));			
			case (EOVERFLOW):
				throw tc::OverflowException(kClassName+"::seek()",  std::string(strerror(errno)));
			case (EBADF):
			case (ESPIPE):
			case (ENXIO):
			default:
				throw tc::io::IOException(kClassName+"::seek()", "Failed to set stream position (" + std::string(strerror(errno)) + ")");
		}
	}

	return fpos;
}

void tc::io::FileStream::setLength_impl(int64_t length)
{
	throw tc::NotImplementedException(kClassName, "setLength() not implemented");
}

void tc::io::FileStream::flush_impl()
{
	// open/read/write are non-buffered
}
#endif