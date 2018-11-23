#include <tc/fs/LocalFileSystem.h>
#include <tc/fs/LocalFile.h>
#include <tc/Exception.h>
#include <tc/unicode.h>

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#endif

#include <iostream>

tc::filesystem::LocalFileSystem::LocalFileSystem()
{
}

tc::filesystem::LocalFileSystem::~LocalFileSystem()
{
}

tc::filesystem::IFile* tc::filesystem::LocalFileSystem::openFile(const tc::filesystem::Path& path, FileAccessMode mode)
{
	tc::filesystem::IFile* ifile_ptr = nullptr;

#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUtf16(path, unicode_path);

	// open file
	fs_handle_t file_handle = CreateFileW((LPCWSTR)unicode_path.c_str(),
							  getOpenModeFlag(mode),
							  getShareModeFlag(mode),
							  0,
							  getCreationModeFlag(mode),
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	// check file handle
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		throw tc::Exception(kClassName, "Failed to open file.");
	}

	ifile_ptr = new LocalFile(mode, file_handle);
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUtf8(path, unicode_path);

	fs_handle_t file_handle = open(unicode_path.c_str(), getOpenModeFlag(mode), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (file_handle == -1)
	{
		throw tc::Exception(kClassName, "Failed to delete file (" + std::string(strerror(errno)) + ")");
	}

	ifile_ptr = new LocalFile(mode, file_handle);
#endif

	return ifile_ptr;
}

void tc::filesystem::LocalFileSystem::deleteFile(const tc::filesystem::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUtf16(path, unicode_path);

	// delete file
	if (DeleteFileW((LPCWSTR)unicode_path.c_str()) == false)
	{
		throw tc::Exception(kClassName, "Failed to delete file");
	}	
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUtf8(path, unicode_path);

	if (unlink(unicode_path.c_str()) == -1)
	{
		throw tc::Exception(kClassName, "Failed to delete file (" + std::string(strerror(errno)) + ")");
	}	
#endif
}

const tc::filesystem::Path& tc::filesystem::LocalFileSystem::getCurrentDirectory()
{
	return mCurrentDirectory;
}

void tc::filesystem::LocalFileSystem::setCurrentDirectory(const tc::filesystem::Path& path)
{

}

void tc::filesystem::LocalFileSystem::createDirectory(const tc::filesystem::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUtf16(path, unicode_path);

	// create directory
	if (CreateDirectoryW((LPCWSTR)unicode_path.c_str(), nullptr) != 0)
	{
		throw tc::Exception(kClassName, "Failed to create directory.");
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUtf8(path, unicode_path);

	if (mkdir(unicode_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
	{
		throw tc::Exception(kClassName, "Failed to create directory (" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::filesystem::LocalFileSystem::removeDirectory(const tc::filesystem::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUtf16(path, unicode_path);

	if (RemoveDirectoryW((wchar_t*)unicode_path.c_str()) != true)
	{
		throw tc::Exception(kClassName, "Failed to remove directory");
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUtf8(path, unicode_path);

	if (rmdir(unicode_path.c_str()) == -1)
	{
		throw tc::Exception(kClassName, "Failed to remove directory (" + std::string(strerror(errno)) + ")");
	}	
#endif
}

void tc::filesystem::LocalFileSystem::getDirectoryInfo(const tc::filesystem::Path& path, DirectoryInfo& info)
{
	
}

#ifdef _WIN32
DWORD tc::filesystem::LocalFileSystem::getOpenModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FAM_READ):
			flag = GENERIC_READ;
			break;
		case (FAM_EDIT):
			flag = GENERIC_READ | GENERIC_WRITE;
			break;
		case (FAM_CREATE):
			flag = GENERIC_WRITE;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
DWORD tc::filesystem::LocalFileSystem::getShareModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FAM_READ):
			flag = FILE_SHARE_READ;
			break;
		case (FAM_EDIT):
			flag = FILE_SHARE_READ;
			break;
		case (FAM_CREATE):
			flag = 0;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}
DWORD tc::filesystem::LocalFileSystem::getCreationModeFlag(FileAccessMode mode) const
{
	DWORD flag = 0;
	switch (mode)
	{
		case (FAM_READ):
			flag = OPEN_EXISTING;
			break;
		case (FAM_EDIT):
			flag = OPEN_EXISTING;
			break;
		case (FAM_CREATE):
			flag = CREATE_ALWAYS;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}

void tc::filesystem::LocalFileSystem::pathToWindowsUtf16(const tc::filesystem::Path& path, std::u16string& out)
{
	std::u16string utf16_element;

	out.clear();
	for (size_t i = 0; i < path.getPathElementList().size(); i++)
	{
		tc::unicode::transcodeUtf8toUtf16(path.getPathElementList()[i], utf16_element);
		out += utf16_element;
		if (i+1 < path.getPathElementList().size())
			out += "\\";
		else if (element == "" || i == 0)
			out += "\\";
	}
}
#else
int tc::filesystem::LocalFileSystem::getOpenModeFlag(FileAccessMode mode) const
{
	int flag = 0;
	switch (mode)
	{
		case (FAM_READ):
			flag = O_RDONLY;
			break;
		case (FAM_EDIT):
			flag = O_RDWR;
			break;
		case (FAM_CREATE):
			flag = O_CREAT | O_TRUNC | O_WRONLY;
			break;
		default:
			throw tc::Exception(kClassName, "Unknown open mode");
	}
	return flag;
}

void tc::filesystem::LocalFileSystem::pathToUnixUtf8(const tc::filesystem::Path& path, std::string& out)
{
	out.clear();
	for (size_t i = 0; i < path.getPathElementList().size(); i++)
	{
		const std::string& element = path.getPathElementList()[i];
		out += element;
		if (i+1 < path.getPathElementList().size())
			out += "/";
		else if (element == "" && i == 0)
			out += "/";
	}
}
#endif