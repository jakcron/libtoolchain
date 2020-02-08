#include <tc/io/SubStorage.h>

const std::string tc::io::SubStorage::kClassName = "tc::io::SubStorage";

tc::io::SubStorage::SubStorage() :
	mBaseStorage(),
	mBaseStoragePath(),
	mSubStoragePath()
{
}

tc::io::SubStorage::SubStorage(const std::shared_ptr<tc::io::IStorage>& storage, const tc::io::Path& base_path) :
	SubStorage()
{
	// copy IStorage ptr
	mBaseStorage = storage;
	
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ArgumentNullException(kClassName, "storage is null");
	}
	else if (mBaseStorage->state().test(RESFLAG_READY) == false)
	{
		throw tc::InvalidOperationException(kClassName, "storage is not ready");
	}

	// set class state
	mSubStoragePath = tc::io::Path("/");

	// get full path of root
	mBaseStorage->setWorkingDirectory(base_path);
	mBaseStorage->getWorkingDirectory(mBaseStoragePath);
}

tc::ResourceStatus tc::io::SubStorage::state()
{
	return mBaseStorage.get() ? mBaseStorage->state() : tc::ResourceStatus(RESFLAG_NOINIT);
}

void tc::io::SubStorage::dispose()
{
	if (mBaseStorage.get() != nullptr)
		mBaseStorage->dispose();
	
	mBaseStoragePath.clear();
	mSubStoragePath.clear();
}

void tc::io::SubStorage::createFile(const tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createFile()", "Failed to create file (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// delete file
	mBaseStorage->createFile(real_path);
}

void tc::io::SubStorage::removeFile(const tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeFile()", "Failed to remove file (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// delete file
	mBaseStorage->removeFile(real_path);
}

void tc::io::SubStorage::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::openFile()", "Failed to open file (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// open file
	return mBaseStorage->openFile(real_path, mode, access, stream);
}

void tc::io::SubStorage::createDirectory(const tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectory()", "Failed to create directory (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// create directory
	mBaseStorage->createDirectory(real_path);
}

void tc::io::SubStorage::removeDirectory(const tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeDirectory()", "Failed to remove directory (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// remove directory
	mBaseStorage->removeDirectory(real_path);
}

void tc::io::SubStorage::getWorkingDirectory(tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getWorkingDirectory()", "Failed to get current working directory (no base storage)");
	}

	path = mSubStoragePath;
}

void tc::io::SubStorage::setWorkingDirectory(const tc::io::Path& path)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setWorkingDirectory()", "Failed to set current working directory (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// set current directory
	mBaseStorage->setWorkingDirectory(real_path);

	// save current directory
	realPathToSubPath(real_path, mSubStoragePath);
}

void tc::io::SubStorage::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	if (mBaseStorage.get() == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setWorkingDirectory()", "Failed to get directory listing (no base storage)");
	}

	// convert substorage path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// get real directory info
	tc::io::sDirectoryListing real_info;
	mBaseStorage->getDirectoryListing(real_path, real_info);

	// convert directory absolute path
	tc::io::Path substorage_dir_path;
	realPathToSubPath(real_info.abs_path, substorage_dir_path);
	
	// update info with substorage path
	real_info.abs_path = substorage_dir_path;

	// write object to output
	info = real_info;
}

void tc::io::SubStorage::subPathToRealPath(const tc::io::Path& substorage_path, tc::io::Path& real_path)
{
	tc::io::Path substorage_current_dir;
	tc::io::Path substorage_path_;

	// test if the substorage path is an absolute path (begins with the root element)
	if (substorage_path.size() > 0 && *substorage_path.begin() == "")
	{
		substorage_current_dir = substorage_path;
	}
	// otherwise this is a relative directory and the working directory (which includes the root element) must be obtained
	else
	{
		substorage_path_ = substorage_path;
		getWorkingDirectory(substorage_current_dir);
	}

	// get santized path (removes elements that could be used to escape the substorage)
	tc::io::Path safe_substorage_path;
	sanitiseInputPath(substorage_current_dir + substorage_path_, safe_substorage_path);
	
	// the real path is the substorage root path + substorage path
	real_path = mBaseStoragePath + safe_substorage_path;
}

void tc::io::SubStorage::realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& substorage_path)
{
	// get iterator for real path
	tc::io::Path::const_iterator real_path_itr = real_path.begin();

	// determine if the path is large enough to preclude the root path
	if (real_path.size() < mBaseStoragePath.size())
	{
		throw tc::UnauthorisedAccessException(kClassName, "Substorage escape detected");
	}

	// confirm the real path includes the root path
	for (tc::io::Path::const_iterator root_path_itr = mBaseStoragePath.begin(); root_path_itr != mBaseStoragePath.end(); root_path_itr++, real_path_itr++)
	{
		if (*real_path_itr != *root_path_itr)
		{
			throw tc::UnauthorisedAccessException(kClassName, "Substorage escape detected");
		}
	}

	// Put root char
	substorage_path.push_back("");

	// save all path elements after the root substorage path
	for (; real_path_itr != real_path.end(); real_path_itr++)
	{
		substorage_path.push_back(*real_path_itr);
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