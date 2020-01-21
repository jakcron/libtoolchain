#include <tc/io/LocalFileSystem.h>
#include <tc/io/LocalFileObject.h>
#include <tc/io/PathUtils.h>
#include <tc/Exception.h>
#include <tc/string.h>

#ifdef _WIN32
#include <direct.h>
#include <cstdlib>
#else
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#include <iostream>

const std::string tc::io::LocalFileSystem::kClassName = "tc::io::LocalFileSystem";

tc::io::LocalFileSystem::LocalFileSystem() :
	mState()
{
	openFs();
}

tc::ResourceState tc::io::LocalFileSystem::getFsState()
{
	return mState;
}

void tc::io::LocalFileSystem::openFs()
{
	mState = (1 << tc::RESFLAG_READY);
}

void tc::io::LocalFileSystem::closeFs()
{
	mState = 0;
}

void tc::io::LocalFileSystem::createFile(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	// open file
	HANDLE file_handle = CreateFileW((LPCWSTR)unicode_path.c_str(),
							  GENERIC_WRITE,
							  0,
							  0,
							  CREATE_ALWAYS,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
		
	// check file handle
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		throw tc::Exception(kClassName, "Failed to create file (" + std::to_string(GetLastError()) + ")");
	}

	CloseHandle(file_handle);
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	int file_handle = open(unicode_path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (file_handle == -1)
	{
		throw tc::Exception(kClassName, "Failed to create file (" + std::string(strerror(errno)) + ")");
	}

	close(file_handle);
#endif
}

void tc::io::LocalFileSystem::removeFile(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	// delete file
	if (DeleteFileW((LPCWSTR)unicode_path.c_str()) == false)
	{
		throw tc::Exception(kClassName, "Failed to remove file (" + std::to_string(GetLastError()) + ")");
	}	
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	if (unlink(unicode_path.c_str()) == -1)
	{
		throw tc::Exception(kClassName, "Failed to remove file (" + std::string(strerror(errno)) + ")");
	}	
#endif
}

void tc::io::LocalFileSystem::openFile(const tc::io::Path& path, FileAccessMode mode, std::shared_ptr<tc::io::IFileObject>& file)
{
	file = std::shared_ptr<tc::io::LocalFileObject>(new tc::io::LocalFileObject(path, mode));
}

void tc::io::LocalFileSystem::createDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	// create directory
	if (CreateDirectoryW((LPCWSTR)unicode_path.c_str(), nullptr) == false && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		throw tc::Exception(kClassName, "Failed to create directory (" + std::to_string(GetLastError()) + ")");
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	if (mkdir(unicode_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST)
	{
		throw tc::Exception(kClassName, "Failed to create directory (" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::io::LocalFileSystem::removeDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	if (RemoveDirectoryW((wchar_t*)unicode_path.c_str()) == false)
	{
		throw tc::Exception(kClassName, "Failed to remove directory (" + std::to_string(GetLastError()) + ")");
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	if (rmdir(unicode_path.c_str()) == -1)
	{
		throw tc::Exception(kClassName, "Failed to remove directory (" + std::string(strerror(errno)) + ")");
	}	
#endif
}

void tc::io::LocalFileSystem::getWorkingDirectory(tc::io::Path& path)
{
#ifdef _WIN32
	std::shared_ptr<char16_t> raw_char16_path(new char16_t[MAX_PATH]);

	// get current directory
	if (GetCurrentDirectoryW(MAX_PATH, (LPWSTR)(raw_char16_path.get())) == false)
	{
		throw tc::Exception(kClassName, "Failed to get current working directory (" + std::to_string(GetLastError()) + ")");
	}

	path = Path(raw_char16_path.get());
#else
	setWorkingDirectory(Path("."));

	std::shared_ptr<char> raw_current_working_directory(new char[PATH_MAX]);

	if (getcwd(raw_current_working_directory.get(), PATH_MAX) == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get current working directory (getcwd)" + std::string(strerror(errno)) + ")");
	}

	path = Path(raw_current_working_directory.get());
#endif
}

void tc::io::LocalFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(path, unicode_path);

	// delete file
	if (SetCurrentDirectoryW((LPCWSTR)unicode_path.c_str()) == false)
	{
		throw tc::Exception(kClassName, "Failed to set current working directory (" + std::to_string(GetLastError()) + ")");
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	pathToUnixUTF8(path, unicode_path);

	// get full path to directory
	if (chdir(unicode_path.c_str()) != 0)
	{
		throw tc::Exception(kClassName, "Failed to get directory info (chdir)(" + std::string(strerror(errno)) + ")");
	}
#endif
}

void tc::io::LocalFileSystem::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	std::vector<std::string> child_dir_name_list;
	std::vector<std::string> child_file_name_list;
	Path current_directory_path;
#ifdef _WIN32
	Path wildcard_path = path + tc::io::Path("*");

	// convert Path to unicode string
	std::u16string unicode_path;
	pathToWindowsUTF16(wildcard_path, unicode_path);

	HANDLE dir_handle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAW dir_entry;

	dir_handle = FindFirstFileW((LPCWSTR)unicode_path.c_str(), &dir_entry);
	if (dir_handle == INVALID_HANDLE_VALUE) 
	{
		throw tc::Exception(kClassName, "Failed to open directory (" + std::to_string(GetLastError()) + ")");
	}

	do {
		std::string utf8_name;
		tc::string::transcodeUTF16ToUTF8((char16_t*)dir_entry.cFileName, utf8_name);

		if (dir_entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
			child_dir_name_list.push_back(utf8_name);
		}
		else 
		{
			child_file_name_list.push_back(utf8_name);
		}
	} while (FindNextFileW(dir_handle, &dir_entry) != 0);

	if (GetLastError() != ERROR_NO_MORE_FILES) 
	{
		FindClose(dir_handle);
		throw tc::Exception(kClassName, "Failed to open directory (" + std::to_string(GetLastError()) + ")");
	}

	FindClose(dir_handle);
	

	// save current dir for later
	Path prev_current_dir;
	getWorkingDirectory(prev_current_dir);

	// change the directory
	setWorkingDirectory(path);

	// save the path
	getWorkingDirectory(current_directory_path);

	// restore current directory
	setWorkingDirectory(prev_current_dir);
#else
	std::string unicode_path;
	DIR *dp;

	// convert Path to unicode string
	pathToUnixUTF8(path, unicode_path);
	
	// open directory
	dp = opendir(unicode_path.c_str());
	if (dp == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get directory info (opendir)(" + std::string(strerror(errno)) + ")");
	}

	// get file and directory names
	child_dir_name_list.clear();
	child_file_name_list.clear();
	
	// since errno can be set by external sources it will be cleared, since the conditions for checking errno being set aren't specific to failure
	errno = 0;
	for (struct dirent *ep = readdir(dp); ep != nullptr && errno == 0; ep = readdir(dp))
	{
		if (ep->d_type == DT_DIR)
		{
			child_dir_name_list.push_back(std::string(ep->d_name));
		}
		else if (ep->d_type == DT_REG)
		{
			child_file_name_list.push_back(std::string(ep->d_name));
		}
	}

	// throw an error if necessary 
	if (errno != 0)
	{
		throw tc::Exception(kClassName, "Failed to get directory info (readdir)(" + std::string(strerror(errno)) + ")");
	}
	

	// close dp
	closedir(dp);

	// save current dir for later
	Path prev_current_dir;
	getWorkingDirectory(prev_current_dir);

	// change the directory
	setWorkingDirectory(path);

	// save the path
	getWorkingDirectory(current_directory_path);

	// restore current directory
	setWorkingDirectory(prev_current_dir);
#endif
	info.abs_path = current_directory_path;
	info.dir_list = child_dir_name_list;
	info.file_list = child_file_name_list;
}

