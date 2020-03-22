#include <tc/io/LocalStorage.h>
#include <tc/io/FileStream.h>
#include <tc/io/PathUtil.h>
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

const std::string tc::io::LocalStorage::kClassName = "tc::io::LocalStorage";

tc::io::LocalStorage::LocalStorage() :
	mState()
{
	mState = (1 << tc::RESFLAG_READY);
}

tc::ResourceStatus tc::io::LocalStorage::state()
{
	return mState;
}

void tc::io::LocalStorage::dispose()
{
	mState = 0;
}

void tc::io::LocalStorage::createFile(const tc::io::Path& path)
{
	tc::io::FileStream file(path, FileMode::Create, FileAccess::Write);
}

void tc::io::LocalStorage::removeFile(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	PathUtil::pathToWindowsUTF16(path, unicode_path);

	// delete file
	if (DeleteFileW((LPCWSTR)unicode_path.c_str()) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::removeFile()", "Failed to remove file (" + std::to_string(error) + ")");
		}
	}	
#else
	// convert Path to unicode string
	std::string unicode_path;
	PathUtil::pathToUnixUTF8(path, unicode_path);

	if (unlink(unicode_path.c_str()) == -1)
	{
		switch (errno) 
		{
			case (EACCES): // Search permission is denied for a component of the path prefix. -OR- Write permission is denied on the directory containing the link to be removed.
			case (EROFS): // The named file resides on a read-only file system.
			case (EPERM): // The named file is a directory and the effective user ID of the process is not the super-user. -OR- The directory containing the file is marked sticky, and neither the containing directory nor the file to be removed are owned by the effective user ID.
			case (EBUSY): // The entry to be unlinked is the mount point for a mounted file system. -OR- The file named by the path argument cannot be unlinked because it is being used by the system or by another process.
				throw tc::UnauthorisedAccessException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENAMETOOLONG): // A component of a pathname exceeds {NAME_MAX} characters, or an entire path name exceeds {PATH_MAX} characters (possibly as a result of expanding a symlink).
				throw tc::io::PathTooLongException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENOENT): // The named file does not exist.
				throw tc::io::FileNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENOTDIR): // A component of the path prefix is not a directory.
				throw tc::io::DirectoryNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (EFAULT): // Path points outside the process's allocated address space.
			case (EIO): // An I/O error occurs while deleting the directory entry or deallocating the inode.
			case (ELOOP): // Too many symbolic links are encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.
			default:
				throw tc::io::IOException(kClassName+"::removeFile()", "Failed to remove file (" + std::string(strerror(errno)) + ")");
		}
	}	
#endif
}

void tc::io::LocalStorage::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	stream = std::shared_ptr<tc::io::FileStream>(new tc::io::FileStream(path, mode, access));
}

void tc::io::LocalStorage::createDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	PathUtil::pathToWindowsUTF16(path, unicode_path);

	// create directory
	if (CreateDirectoryW((LPCWSTR)unicode_path.c_str(), nullptr) == false && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::createDirectory()", "Failed to create directory (" + std::to_string(error) + ")");
		}
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	PathUtil::pathToUnixUTF8(path, unicode_path);

	if (mkdir(unicode_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST)
	{
		switch (errno) 
		{
			case (EACCES): // Search permission is denied for a component of the path prefix. -OR- Write permission is denied for the parent directory.
			case (EROFS): // The parent directory resides on a read-only file system.
				throw tc::UnauthorisedAccessException(kClassName+"::createDirectory()", std::string(strerror(errno)));
			case (ENOTDIR): // A component of the path prefix is not a directory.
			case (ENOENT): // A component of the path prefix does not exist or path is an empty string.
				throw tc::io::DirectoryNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENAMETOOLONG): // A component of a pathname exceeded {NAME_MAX} characters, or an entire path name exceeded {PATH_MAX} characters.
				throw tc::io::PathTooLongException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (EISDIR): // The named file is the root directory.
			case (EDQUOT): // The new directory cannot be created because the user's quota of disk blocks on the file system that will contain the directory has been exhausted. -OR- The user's quota of inodes on the file system on which the directory is being created has been exhausted.
			//case (EEXIST): // The named file exists
			case (EFAULT): // Path points outside the process's allocated address space.
			case (EIO): // An I/O error occurred while reading from or writing to the file system. -OR- An I/O error occurred while making the directory entry or allocating the inode.
			case (ELOOP): // Too many symbolic links were encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.
			case (EMLINK): // The parent directory already has {LINK_MAX} links.
			case (ENOSPC): // The new directory cannot be created because there is no space left on the file system that would contain it. -OR- There are no free inodes on the file system on which the directory is being created.
			default:
				throw tc::io::IOException(kClassName+"::createDirectory()", "Failed to create directory (" + std::string(strerror(errno)) + ")");
		}
	}
#endif
}

void tc::io::LocalStorage::removeDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	PathUtil::pathToWindowsUTF16(path, unicode_path);

	if (RemoveDirectoryW((wchar_t*)unicode_path.c_str()) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::removeDirectory()", "Failed to remove directory (" + std::to_string(error) + ")");
		}
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	PathUtil::pathToUnixUTF8(path, unicode_path);

	if (rmdir(unicode_path.c_str()) == -1)
	{
		switch (errno) 
		{
			case (EACCES): // Search permission is denied for a component of the path prefix. -OR- Write permission is denied on the directory containing the link to be removed.
			case (EROFS): // The directory entry to be removed resides on a read-only file system.
			case (EPERM): // The directory containing the directory to be removed is marked sticky, and neither the containing directory nor the directory to be removed are owned by the effective user ID.
			case (EBUSY): // The directory to be removed is the mount point for a mounted file system.
				throw tc::UnauthorisedAccessException(kClassName+"::removeDirectory()", std::string(strerror(errno)));
			case (ENAMETOOLONG):
				throw tc::io::PathTooLongException(kClassName+"::removeDirectory()", std::string(strerror(errno)));
			case (ENOENT): // The named directory does not exist.
			case (ENOTDIR): // A component of the path prefix is not a directory.
				throw tc::io::DirectoryNotFoundException(kClassName+"::removeDirectory()", std::string(strerror(errno)));
			case (ENOTEMPTY): // The named directory contains files other than `.' and `..' in it.
				throw tc::io::DirectoryNotEmptyException(kClassName+"::removeDirectory()", std::string(strerror(errno)));
			case (EFAULT): // Path points outside the process's allocated address space.
			case (EIO): // An I/O error occurred while reading from or writing to the file system.
			case (ELOOP): // Too many symbolic links are encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.
			default:
				throw tc::io::IOException(kClassName+"::removeDirectory()", "Failed to remove directory (" + std::string(strerror(errno)) + ")");
		}
	}	
#endif
}

void tc::io::LocalStorage::getWorkingDirectory(tc::io::Path& path)
{
#ifdef _WIN32
	std::shared_ptr<char16_t> raw_char16_path(new char16_t[MAX_PATH]);

	// get current directory
	if (GetCurrentDirectoryW(MAX_PATH, (LPWSTR)(raw_char16_path.get())) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::getWorkingDirectory()", "Failed to get current working directory (" + std::to_string(error) + ")");
		}
	}

	path = Path(raw_char16_path.get());
#else
	setWorkingDirectory(Path("."));

	std::shared_ptr<char> raw_current_working_directory(new char[PATH_MAX]);

	if (getcwd(raw_current_working_directory.get(), PATH_MAX) == nullptr)
	{
		switch (errno) 
		{
			case (EACCES): // Read or search permission was denied for a component of the pathname.  This is only checked in limited cases, depending on implementation details.
				throw tc::UnauthorisedAccessException(kClassName+"::getWorkingDirectory()", std::string(strerror(errno)));
			case (EINVAL): // The size argument is zero.
			case (ENOENT): // A component of the pathname no longer exists.
			case (ENOMEM): // Insufficient memory is available.
			case (ERANGE): // The size argument is greater than zero but smaller than the length of the pathname plus 1.
			default:
				throw tc::io::IOException(kClassName+"::getWorkingDirectory()", "Failed to get current working directory (getcwd) (" + std::string(strerror(errno)) + ")");
		}
	}

	path = Path(raw_current_working_directory.get());
#endif
}

void tc::io::LocalStorage::setWorkingDirectory(const tc::io::Path& path)
{
#ifdef _WIN32
	// convert Path to unicode string
	std::u16string unicode_path;
	PathUtil::pathToWindowsUTF16(path, unicode_path);

	// delete file
	if (SetCurrentDirectoryW((LPCWSTR)unicode_path.c_str()) == false)
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::setWorkingDirectory()", "Failed to set current working directory (" + std::to_string(error) + ")");
		}
	}
#else
	// convert Path to unicode string
	std::string unicode_path;
	PathUtil::pathToUnixUTF8(path, unicode_path);

	// get full path to directory
	if (chdir(unicode_path.c_str()) != 0)
	{
		switch (errno) 
		{
			case (EACCES): // Search permission is denied for any component of the path name.
				throw tc::UnauthorisedAccessException(kClassName+"::setWorkingDirectory()", std::string(strerror(errno)));
			case (ENAMETOOLONG): // A component of a pathname exceeded {NAME_MAX} characters, or an entire path name exceeded {PATH_MAX} characters.
				throw tc::io::PathTooLongException(kClassName+"::setWorkingDirectory()", std::string(strerror(errno)));
			case (ENOENT): // The named directory does not exist.
			case (ENOTDIR): // A component of the path prefix is not a directory.
				throw tc::io::DirectoryNotFoundException(kClassName+"::setWorkingDirectory()", std::string(strerror(errno)));
			case (EFAULT): // Path points outside the process's allocated address space.
			case (EIO): // An I/O error occurred while reading from or writing to the file system.
			case (ELOOP): //  Too many symbolic links were encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.
			default:
				throw tc::io::IOException(kClassName+"::setWorkingDirectory()", "Failed to get directory info (chdir)(" + std::string(strerror(errno)) + ")");
		}
	}
#endif
}

void tc::io::LocalStorage::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	std::vector<std::string> child_dir_name_list;
	std::vector<std::string> child_file_name_list;
	Path current_directory_path;
#ifdef _WIN32
	Path wildcard_path = path + tc::io::Path("*");

	// convert Path to unicode string
	std::u16string unicode_path;
	PathUtil::pathToWindowsUTF16(wildcard_path, unicode_path);

	HANDLE dir_handle = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAW dir_entry;

	dir_handle = FindFirstFileW((LPCWSTR)unicode_path.c_str(), &dir_entry);
	if (dir_handle == INVALID_HANDLE_VALUE) 
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::getDirectoryListing()", "Failed to open directory (" + std::to_string(error) + ")");
		}
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

	// throw error where GetLastError() isn't just that there were no more files
	if (GetLastError() != ERROR_NO_MORE_FILES) 
	{
		FindClose(dir_handle);

		DWORD error = GetLastError();
		switch (error)
		{
			default:
				throw tc::io::IOException(kClassName+"::getDirectoryListing()", "Failed to open directory (" + std::to_string(error) + ")");
		}
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
	PathUtil::pathToUnixUTF8(path, unicode_path);
	
	// open directory
	dp = opendir(unicode_path.c_str());
	if (dp == nullptr)
	{
		switch (errno) 
		{
			case (EACCES): // Permission denied.
				throw tc::UnauthorisedAccessException(kClassName+"::getDirectoryListing()", std::string(strerror(errno)));
			case (ENOTDIR): // A component of the path prefix is not a directory. // name is not a directory.
			case (ENOENT): // Directory does not exist, or name is an empty string.
				throw tc::io::DirectoryNotFoundException(kClassName+"::getDirectoryListing()", std::string(strerror(errno)));
			case (EBADF): // fd is not a valid file descriptor open for reading.
			case (EMFILE):
			case (ENFILE):
			case (ENOMEM):
			default:
				throw tc::io::IOException(kClassName+"::getDirectoryListing()", "Failed to get directory info (opendir)(" + std::string(strerror(errno)) + ")");
		}
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
		switch (errno) 
		{
			case (EBADF): // fd is not a valid file descriptor open for reading.
			case (EIO): // An I/O error occurred while reading from or writing to the file system.
			default:
				throw tc::io::IOException(kClassName+"::getDirectoryListing()", "Failed to get directory info (readdir)(" + std::string(strerror(errno)) + ")");
		}
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

