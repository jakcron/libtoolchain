#include <tc/io/SubFileSystem.h>

tc::io::SubFileSystem::SubFileSystem() :
	mModuleLabel("tc::io::SubFileSystem"),
	mBaseFileSystem(),
	mBaseFileSystemPath(),
	mSubFileSystemPath(),
	mPathResolver()
{
}

tc::io::SubFileSystem::SubFileSystem(const std::shared_ptr<tc::io::IFileSystem>& file_system, const tc::io::Path& base_path) :
	SubFileSystem()
{
	// copy IFileSystem ptr
	mBaseFileSystem = file_system;
	
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ArgumentNullException(mModuleLabel, "file_system is null");
	}
	else if (mBaseFileSystem->state().test(RESFLAG_READY) == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "file_system is not ready");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::createFile()", "Failed to create file (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::removeFile()", "Failed to remove file (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::openFile()", "Failed to open file (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::createDirectory()", "Failed to create directory (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::removeDirectory()", "Failed to remove directory (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::getWorkingDirectory()", "Failed to get current working directory (no base file system)");
	}

	path = mSubFileSystemPath;
}

void tc::io::SubFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (mBaseFileSystem == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setWorkingDirectory()", "Failed to set current working directory (no base file system)");
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
		throw tc::ObjectDisposedException(mModuleLabel+"::getDirectoryListing()", "Failed to get directory listing (no base file system)");
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
	// get absolute sub path
	tc::io::Path absolute_sub_path;
	mPathResolver.resolvePath(sub_path, mSubFileSystemPath, absolute_sub_path);

	// remove root path element from absolute sub path to make it relative
	if (absolute_sub_path.empty() == false && absolute_sub_path.front() == "")
		absolute_sub_path.pop_front();

	// get absolute base path
	tc::io::Path absolute_base_path;
	mPathResolver.resolvePath(absolute_sub_path, mBaseFileSystemPath, absolute_base_path);
	
	// the real path the absolute base path
	real_path = absolute_base_path;
}

void tc::io::SubFileSystem::realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& sub_path)
{
	// get iterator for real path
	tc::io::Path::const_iterator real_path_itr = real_path.begin();

	// determine if the path is large enough to preclude the root path
	if (real_path.size() < mBaseFileSystemPath.size())
	{
		throw tc::UnauthorisedAccessException(mModuleLabel, "Sub filesystem escape detected");
	}

	// confirm the real path includes the root path
	for (tc::io::Path::const_iterator root_path_itr = mBaseFileSystemPath.begin(); root_path_itr != mBaseFileSystemPath.end(); root_path_itr++, real_path_itr++)
	{
		if (*real_path_itr != *root_path_itr)
		{
			throw tc::UnauthorisedAccessException(mModuleLabel, "Sub filesystem escape detected");
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