#include <tc/io/SubStorage.h>
#include <tc/Exception.h>

const std::string tc::io::SubStorage::kClassName = "tc::io::SubStorage";

tc::io::SubStorage::SubStorage() :
	mFileSystem(),
	mRootPath(),
	mWorkingDirectory()
{
}

tc::io::SubStorage::SubStorage(const std::shared_ptr<tc::io::IStorage>& fs, const tc::io::Path& root_path) :
	SubStorage()
{
	initialiseFs(fs, root_path);
}

tc::io::SubStorage::SubStorage(std::shared_ptr<tc::io::IStorage>&& fs, const tc::io::Path& root_path) :
	SubStorage()
{
	initialiseFs(std::move(fs), root_path);
}

tc::ResourceStatus tc::io::SubStorage::getFsState()
{
	return mFileSystem.get() ? mFileSystem->getFsState() : tc::ResourceStatus(RESFLAG_NOINIT);
}

void tc::io::SubStorage::initialiseFs(const std::shared_ptr<tc::io::IStorage>& fs, const tc::io::Path& root_path)
{
	closeFs();

	mFileSystem = fs;
	
	if (mFileSystem.get() != nullptr && mFileSystem->getFsState().test(RESFLAG_READY))
	{
		mRootPath = root_path; 
		mWorkingDirectory = tc::io::Path("/");

		// get full path of root
		mFileSystem->setWorkingDirectory(root_path);
		mFileSystem->getWorkingDirectory(mRootPath);
	}
	else
	{
		closeFs();
	}
}

void tc::io::SubStorage::initialiseFs(std::shared_ptr<tc::io::IStorage>&& fs, const tc::io::Path& root_path)
{
	closeFs();

	mFileSystem = std::move(fs);

	if (mFileSystem.get() != nullptr && mFileSystem->getFsState().test(RESFLAG_READY))
	{
		mRootPath = root_path; 
		mWorkingDirectory = tc::io::Path("/");

		// get full path of root
		mFileSystem->setWorkingDirectory(root_path);
		mFileSystem->getWorkingDirectory(mRootPath);
	}
	else
	{
		closeFs();
	}
}

void tc::io::SubStorage::closeFs()
{
	if (mFileSystem.get() != nullptr)
		mFileSystem->closeFs();
	
	mRootPath.clear();
	mWorkingDirectory.clear();
}

void tc::io::SubStorage::createFile(const tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to create file (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->createFile(real_path);
}

void tc::io::SubStorage::removeFile(const tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to remove file (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->removeFile(real_path);
}

void tc::io::SubStorage::openFile(const tc::io::Path& path, FileAccessMode mode, std::shared_ptr<tc::io::IStream>& file)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to open file (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// open file
	return mFileSystem->openFile(real_path, mode, file);
}

void tc::io::SubStorage::createDirectory(const tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to create directory (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// create directory
	mFileSystem->createDirectory(real_path);
}

void tc::io::SubStorage::removeDirectory(const tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to remove directory (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// remove directory
	mFileSystem->removeDirectory(real_path);
}

void tc::io::SubStorage::getWorkingDirectory(tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get current working directory (no base filesystem)");
	}

	path = mWorkingDirectory;
}

void tc::io::SubStorage::setWorkingDirectory(const tc::io::Path& path)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to set current working directory (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// set current directory
	mFileSystem->setWorkingDirectory(real_path);

	// save current directory
	realPathToSandboxPath(real_path, mWorkingDirectory);
}

void tc::io::SubStorage::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	if (mFileSystem.get() == nullptr)
	{
		throw tc::Exception(kClassName, "Failed to get directory listing (no base filesystem)");
	}

	// convert sandbox path to real path
	tc::io::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// get real directory info
	tc::io::sDirectoryListing real_info;
	mFileSystem->getDirectoryListing(real_path, real_info);

	// convert directory absolute path
	tc::io::Path sandbox_dir_path;
	realPathToSandboxPath(real_info.abs_path, sandbox_dir_path);
	
	// update info with sandbox path
	real_info.abs_path = sandbox_dir_path;

	// write object to output
	info = real_info;
}

void tc::io::SubStorage::sandboxPathToRealPath(const tc::io::Path& sandbox_path, tc::io::Path& real_path)
{
	tc::io::Path sandbox_current_dir;
	tc::io::Path sandbox_path_;

	// test if the sandbox path is an absolute path (begins with the root element)
	if (sandbox_path.size() > 0 && *sandbox_path.begin() == "")
	{
		sandbox_current_dir = sandbox_path;
	}
	// otherwise this is a relative directory and the working directory (which includes the root element) must be obtained
	else
	{
		sandbox_path_ = sandbox_path;
		getWorkingDirectory(sandbox_current_dir);
	}

	// get santized path (removes elements that could be used to escape the sandbox)
	tc::io::Path safe_sandbox_path;
	sanitiseInputPath(sandbox_current_dir + sandbox_path_, safe_sandbox_path);
	
	// the real path is the sandbox root path + sandbox path
	real_path = mRootPath + safe_sandbox_path;
}

void tc::io::SubStorage::realPathToSandboxPath(const tc::io::Path& real_path, tc::io::Path& sandbox_path)
{
	// get iterator for real path
	tc::io::Path::const_iterator real_path_itr = real_path.begin();

	// determine if the path is large enough to preclude the root path
	if (real_path.size() < mRootPath.size())
	{
		throw tc::Exception(kClassName, "Sandbox security exception (sandbox escape detected)");
	}

	// confirm the real path includes the root path
	for (tc::io::Path::const_iterator root_path_itr = mRootPath.begin(); root_path_itr != mRootPath.end(); root_path_itr++, real_path_itr++)
	{
		if (*real_path_itr != *root_path_itr)
		{
			throw tc::Exception(kClassName, "Sandbox security exception (sandbox escape detected)");
		}
	}

	// Put root char
	sandbox_path.push_back("");

	// save all path elements after the root sandbox path
	for (; real_path_itr != real_path.end(); real_path_itr++)
	{
		sandbox_path.push_back(*real_path_itr);
	}
}

void tc::io::SubStorage::sanitiseInputPath(const tc::io::Path& unsafe_path, tc::io::Path& safe_path) const
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
			if (safe_path.size() > 0)
				safe_path.pop_back();
		}
		// normal elements
		else
		{
			safe_path.push_back(*itr);
		}
	}
}