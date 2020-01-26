#include <tc/io/LocalStorage.h>
#include <tc/io/FileStream.h>
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

const std::string tc::io::LocalStorage::kClassName = "tc::io::LocalStorage";

tc::io::LocalStorage::LocalStorage() :
	mState()
{
	openStorage();
}

void tc::io::LocalStorage::openStorage()
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
	pathToWindowsUTF16(path, unicode_path);

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
	pathToUnixUTF8(path, unicode_path);

	if (unlink(unicode_path.c_str()) == -1)
	{
		switch (errno) 
		{
			case (EACCES):
			case (EROFS):
			case (EISDIR):
			case (EPERM):
				throw tc::UnauthorisedAccessException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENAMETOOLONG):
				throw tc::io::PathTooLongException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENOENT):
				throw tc::io::FileNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENOTDIR):
				throw tc::io::DirectoryNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (EFAULT):
			case (EIO):
			case (ELOOP):
			case (ENOMEM):
			case (EBUSY):
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
	pathToWindowsUTF16(path, unicode_path);

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
	pathToUnixUTF8(path, unicode_path);

	if (mkdir(unicode_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST)
	{
		switch (errno) 
		{
			case (EACCES):
			case (EROFS):
				throw tc::UnauthorisedAccessException(kClassName+"::createDirectory()", std::string(strerror(errno)));
			case (ENOTDIR):
			case (ENOENT):
				throw tc::io::DirectoryNotFoundException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (ENAMETOOLONG):
				throw tc::io::PathTooLongException(kClassName+"::removeFile()", std::string(strerror(errno)));
			case (EISDIR):
			case (EDQUOT):
			//case (EEXIST):
			case (EFAULT):
			case (EIO):
			case (ELOOP):
			case (EMLINK):
			case (ENOSPC):
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
	pathToWindowsUTF16(path, unicode_path);

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
	pathToUnixUTF8(path, unicode_path);

	if (rmdir(unicode_path.c_str()) == -1)
	{
		/*
	 [EACCES]           Search permission is denied for a component of the path prefix.

     [EACCES]           Write permission is denied on the directory containing the link to be removed.

	 [EBUSY]            The directory to be removed is the mount point for a mounted file system.

     [EFAULT]           Path points outside the process's allocated address space.

     [EIO]              An I/O error occurs while deleting the directory entry or deallocating the inode.

     [ELOOP]            Too many symbolic links are encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.

     [ENAMETOOLONG]     A component of a pathname (possibly expanded by a symbolic link) exceeds {NAME_MAX} characters, or an entire path name exceeded {PATH_MAX} characters.

     [ENOENT]           The named directory does not exist.

     [ENOTDIR]          A component of the path is not a directory.

     [ENOTEMPTY]        The named directory contains files other than `.' and `..' in it.

     [EPERM]            The directory containing the directory to be removed is marked sticky, and neither the containing directory nor the directory to be removed are owned by the effective user ID.

     [EROFS]            The directory entry to be removed resides on a read-only file system.
		*/
		switch (errno) 
		{
			case (EACCES):
			case (EBUSY):
			case (EFAULT):
			case (EIO):
			case (ELOOP):
			case (ENAMETOOLONG):
			case (ENOENT):
			case (ENOTDIR):
			case (ENOTEMPTY):
			case (EPERM):
			case (EROFS):
			default:
				throw tc::io::IOException(kClassName+"::createDirectory()", "Failed to remove directory (" + std::string(strerror(errno)) + ")");
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
		/*
		The getcwd() function will fail if:

     [EINVAL]           The size argument is zero.

     [ENOENT]           A component of the pathname no longer exists.

     [ENOMEM]           Insufficient memory is available.

     [ERANGE]           The size argument is greater than zero but smaller than the length of the pathname plus 1.

     The getcwd() function may fail if:

     [EACCES]           Read or search permission was denied for a component of the pathname.  This is only checked in limited cases, depending on implementation details.
		*/
		switch (errno) 
		{
			case (EINVAL):
			case (ENOENT):
			case (ENOMEM):
			case (ERANGE):
			case (EACCES):
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
	pathToWindowsUTF16(path, unicode_path);

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
	pathToUnixUTF8(path, unicode_path);

	// get full path to directory
	if (chdir(unicode_path.c_str()) != 0)
	{
		/*
	 The chdir() system call will fail and the current working directory will be unchanged if one or more of the following are true:

     [EACCES]           Search permission is denied for any component of the path name.

     [EFAULT]           Path points outside the process's allocated address space.

     [EIO]              An I/O error occurred while reading from or writing to the file system.

     [ELOOP]            Too many symbolic links were encountered in translating the pathname.  This is taken to be indicative of a looping symbolic link.

     [ENAMETOOLONG]     A component of a pathname exceeded {NAME_MAX} characters, or an entire path name exceeded {PATH_MAX} characters.

     [ENOENT]           The named directory does not exist.

     [ENOTDIR]          A component of the path prefix is not a directory.
		*/
		switch (errno) 
		{
			case (EACCES):
			case (EFAULT):
			case (EIO):
			case (ELOOP):
			case (ENAMETOOLONG):
			case (ENOENT):
			case (ENOTDIR):
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
	pathToWindowsUTF16(wildcard_path, unicode_path);

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
	pathToUnixUTF8(path, unicode_path);
	
	// open directory
	dp = opendir(unicode_path.c_str());
	if (dp == nullptr)
	{
		/*
		EACCES
Permission denied.

EBADF

fd is not a valid file descriptor opened for reading.

EMFILE

Too many file descriptors in use by process.

ENFILE

Too many files are currently open in the system.

ENOENT

Directory does not exist, or name is an empty string.

ENOMEM

Insufficient memory to complete the operation.

ENOTDIR
name is not a directory.
		*/
		switch (errno) 
		{
			case (EACCES):
			case (EBADF):
			case (EMFILE):
			case (ENFILE):
			case (ENOENT):
			case (ENOMEM):
			case (ENOTDIR):
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
		/*
	 [EBADF]            fd is not a valid file descriptor open for reading.

     [EIO]              An I/O error occurred while reading from or writing to the file system.
	 */
		switch (errno) 
		{
			case (EBADF):
			case (EIO):
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

