#include <tc/io/SubFileSystem.h>

const std::string tc::io::SubFileSystem::kClassName = "tc::io::SubFileSystem";

tc::io::SubFileSystem::SubFileSystem() :
	mBaseFileSystem(),
	mBaseFileSystemPath(),
	mSubFileSystemPath()
{
}

tc::io::SubFileSystem::SubFileSystem(const std::shared_ptr<tc::io::IFileSystem>& file_system, const tc::io::Path& base_path) :
	SubFileSystem()
{
	// copy IFileSystem ptr
	mBaseFileSystem = file_system;
	
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "file_system is null");
	}
	else if (mBaseFileSystem->state().test(RESFLAG_READY) == false)
	{
		throw tc::InvalidOperationException(kClassName, "file_system is not ready");
	}

	// set class state
	mSubFileSystemPath = tc::io::Path("/");

	// save current path
	tc::io::Path current_path;
	mBaseFileSystem->getWorkingDirectory(current_path);

	// get full path of root
	mBaseFileSystem->setWorkingDirectory(base_path);
	mBaseFileSystem->getWorkingDirectory(mBaseFileSystemPath);

	// restore current path
	mBaseFileSystem->setWorkingDirectory(current_path);
}

tc::ResourceStatus tc::io::SubFileSystem::state()
{
	return mBaseFileSystem.get() ? mBaseFileSystem->state() : tc::ResourceStatus(1 << tc::RESFLAG_NOINIT);
}

void tc::io::SubFileSystem::dispose()
{
	if (mBaseFileSystem.get() != nullptr)
		mBaseFileSystem->dispose();
	
	mBaseFileSystemPath.clear();
	mSubFileSystemPath.clear();
}

void tc::io::SubFileSystem::createFile(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createFile()", "Failed to create file (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// delete file
	mBaseFileSystem->createFile(real_path);
}

void tc::io::SubFileSystem::removeFile(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeFile()", "Failed to remove file (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// delete file
	mBaseFileSystem->removeFile(real_path);
}

void tc::io::SubFileSystem::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::openFile()", "Failed to open file (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// open file
	return mBaseFileSystem->openFile(real_path, mode, access, stream);
}

void tc::io::SubFileSystem::createDirectory(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectory()", "Failed to create directory (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// create directory
	mBaseFileSystem->createDirectory(real_path);
}

void tc::io::SubFileSystem::removeDirectory(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeDirectory()", "Failed to remove directory (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// remove directory
	mBaseFileSystem->removeDirectory(real_path);
}

void tc::io::SubFileSystem::getWorkingDirectory(tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getWorkingDirectory()", "Failed to get current working directory (no base file system)");
	}

	path = mSubFileSystemPath;
}

void tc::io::SubFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setWorkingDirectory()", "Failed to set current working directory (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// save previous basefs working directory path
	tc::io::Path prev_working_directory;
	mBaseFileSystem->getWorkingDirectory(prev_working_directory);

	// set and get working directory path so that real_path is populated with the full real path
	mBaseFileSystem->setWorkingDirectory(real_path);
	mBaseFileSystem->getWorkingDirectory(real_path);

	// restore previous basefs working directory path
	mBaseFileSystem->setWorkingDirectory(prev_working_directory);

	// save current directory
	realPathToSubPath(real_path, mSubFileSystemPath);
}

void tc::io::SubFileSystem::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getDirectoryListing()", "Failed to get directory listing (no base file system)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// get real directory info
	tc::io::sDirectoryListing real_info;
	mBaseFileSystem->getDirectoryListing(real_path, real_info);

	// convert directory absolute path
	tc::io::Path subfilesystem_dir_path;
	realPathToSubPath(real_info.abs_path, subfilesystem_dir_path);
	
	// update info with sub filesystem path
	real_info.abs_path = subfilesystem_dir_path;

	// write object to output
	info = real_info;
}

void tc::io::SubFileSystem::subPathToRealPath(const tc::io::Path& sub_path, tc::io::Path& real_path)
{
	tc::io::Path subfilesystem_current_dir;
	tc::io::Path subfilesystem_path_;

	// test if the sub filesystem path is an absolute path (begins with the root element)
	if (sub_path.size() > 0 && *sub_path.begin() == "")
	{
		subfilesystem_current_dir = sub_path;
	}
	// otherwise this is a relative directory and the working directory (which includes the root element) must be obtained
	else
	{
		subfilesystem_path_ = sub_path;
		getWorkingDirectory(subfilesystem_current_dir);
	}

	// get santized path (removes elements that could be used to escape the sub filesystem)
	tc::io::Path safe_subfilesystem_path;
	sanitiseInputPath(subfilesystem_current_dir + subfilesystem_path_, safe_subfilesystem_path);
	
	// the real path is the sub filesystem root path + sub filesystem path
	real_path = mBaseFileSystemPath + safe_subfilesystem_path;
}

void tc::io::SubFileSystem::realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& sub_path)
{
	// get iterator for real path
	tc::io::Path::const_iterator real_path_itr = real_path.begin();

	// determine if the path is large enough to preclude the root path
	if (real_path.size() < mBaseFileSystemPath.size())
	{
		throw tc::UnauthorisedAccessException(kClassName, "Sub filesystem escape detected");
	}

	// confirm the real path includes the root path
	for (tc::io::Path::const_iterator root_path_itr = mBaseFileSystemPath.begin(); root_path_itr != mBaseFileSystemPath.end(); root_path_itr++, real_path_itr++)
	{
		if (*real_path_itr != *root_path_itr)
		{
			throw tc::UnauthorisedAccessException(kClassName, "Sub filesystem escape detected");
		}
	}

	// clear sub_path
	sub_path = tc::io::Path();

	// Put root char
	sub_path.push_back("");

	// save all path elements after the root sub filesystem path
	for (; real_path_itr != real_path.end(); real_path_itr++)
	{
		sub_path.push_back(*real_path_itr);
	}
}

void tc::io::SubFileSystem::sanitiseInputPath(const tc::io::Path& unsafe_path, tc::io::Path& safe_path) const
{
	//for (size_t i = 0; i < unsafe_path.getPathElementList().size(); i++)
	for (tc::io::Path::const_iterator itr = unsafe_path.begin(); itr != unsafe_path.end(); itr++)
	{
		// root directory
		if (*itr == "" && itr == unsafe_path.begin())
		{
			continue;
		}
		// skip the working directory "."
		else if (*itr == ".")
		{
			continue;
		}
		// skip empty directories
		else if (*itr == "")
		{
			continue;
		}
		// directory navigate up element
		else if (*itr == "..")
		{
			if (!safe_path.empty())
				safe_path.pop_back();
		}
		// normal elements
		else
		{
			safe_path.push_back(*itr);
		}
	}
}