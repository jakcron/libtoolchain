#include <tc/fs/LocalFile.h>
#include <tc/Exception.h>

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#endif


tc::filesystem::LocalFile::LocalFile(FileAccessMode mode, LocalFileSystem::fs_handle_t file_handle) :
	mMode(mode),
	mFileHandle(file_handle)
{
	
}

tc::filesystem::LocalFile::~LocalFile()
{
#ifdef _WIN32
	CloseHandle(mFileHandle);
#else
	close(mFileHandle);
#endif
}

uint64_t tc::filesystem::LocalFile::size()
{
	uint64_t fsize = 0;
#ifdef _WIN32
	if (mMode != FAM_CREATE)
	{
		LARGE_INTEGER win_fsize;
		if (GetFileSizeEx(mFileHandle, &win_fsize) == false)
		{
			throw tc::Exception(kClassName, "Failed to get file sizee");
		}

		fsize = win_fsize.QuadPart;
	}
	else
	{
		fsize = 0;
	}
#else
	int64_t cur_pos = lseek(mFileHandle, 0, SEEK_CUR);
	if (cur_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}

	int64_t end_pos = lseek(mFileHandle, 0, SEEK_END);
	if (end_pos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	fsize = (uint64_t)end_pos;

	int64_t ret = lseek(mFileHandle, cur_pos, SEEK_SET);
	if (ret == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file size (" + std::string(strerror(errno)) + ")");
	}
	
#endif
	return fsize;
}

void tc::filesystem::LocalFile::seek(uint64_t offset)
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
		mFileHandle,
		win_pos,
		&out,
		FILE_BEGIN
	) == false || out.QuadPart != win_pos.QuadPart)
	{
		throw tc::Exception(kClassName, "Failed to set file position");
	}
#else
	int64_t fpos = lseek(mFileHandle, offset, SEEK_SET);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to set file position (" + std::string(strerror(errno)) + ")");
	}
#endif
}

uint64_t tc::filesystem::LocalFile::pos()
{
#ifdef _WIN32
	LARGE_INTEGER win_pos, out;
	win_pos.QuadPart = 0;
	if (SetFilePointerEx(
		mFileHandle,
		win_pos,
		&out,
		FILE_CURRENT
	) == false)
	{
		throw tc::Exception(kClassName, "Failed to get file position");
	}

	return out.QuadPart;
#else
	int64_t fpos = lseek(mFileHandle, 0, SEEK_CUR);

	if (fpos == -1)
	{
		throw tc::Exception(kClassName, "Failed to get file position (" + std::string(strerror(errno)) + ")");
	}

	return fpos;
#endif
}

void tc::filesystem::LocalFile::read(byte_t* data, size_t len)
{
	// prevent excessive read()
	if ((pos() + len) > size())
	{
		throw tc::Exception(kClassName, "Failed to read file (Illegal read length)");
	}

#ifdef _WIN32
	LARGE_INTEGER win_len;
	win_len.QuadPart = len;

	static const DWORD kDwordHalf = (MAXDWORD / (DWORD)2) + 1; // 0x80000000
	static const LONG kDwordFull = (LONG)kDwordHalf * (LONG)2; // 0x100000000

	// if the size is greater than a DWORD, read it in parts, 
	for (LONG i = 0; i < win_len.HighPart; i++)
	{
		// since kDwordFull isn't a valid DWORD value, read in two parts
		ReadFile(
			mFileHandle,
			data + i * kDwordFull,
			kDwordHalf,
			NULL,
			NULL
		);
		ReadFile(
			mFileHandle,
			data + i * kDwordFull + kDwordHalf,
			kDwordHalf,
			NULL,
			NULL
		);
	}

	// read remainding low part
	if (win_len.LowPart > 0)
	{
		ReadFile(
			mFileHandle,
			data + win_len.HighPart * kDwordFull,
			win_len.LowPart,
			NULL,
			NULL
		);
	}
#else
	if (::read(mFileHandle, data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to read file (" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::filesystem::LocalFile::write(const byte_t* data, size_t len)
{
	if (mMode == FAM_READ)
		throw tc::Exception(kClassName, "Failed to write file (File is READ_ONLY)");

#ifdef _WIN32
	LARGE_INTEGER win_len;
	win_len.QuadPart = len;

	static const DWORD kDwordHalf = ((DWORD)MAXDWORD / (DWORD)2) + 1; // 0x80000000
	static const size_t kDwordFull = (size_t)kDwordHalf * (size_t)2; // 0x100000000

															   // if the size is greater than a DWORD, read it in parts, 
	for (LONG i = 0; i < win_len.HighPart; i++)
	{
		// since kDwordFull isn't a valid DWORD value, read in two parts
		WriteFile(
			mFileHandle,
			data + i * kDwordFull,
			kDwordHalf,
			NULL,
			NULL
		);
		WriteFile(
			mFileHandle,
			data + i * kDwordFull + kDwordHalf,
			kDwordHalf,
			NULL,
			NULL
		);
	}

	// read remainding low part
	if (win_len.LowPart > 0)
	{
		WriteFile(
			mFileHandle,
			data + win_len.HighPart * kDwordFull,
			win_len.LowPart,
			NULL,
			NULL
		);
	}
#else
	if (::write(mFileHandle, data, len) == -1)
	{
		throw tc::Exception(kClassName, "Failed to write file (" + std::string(strerror(errno)) + ")");
	}
#endif
}