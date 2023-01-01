#include <tc/io/SubFileSystem.h>

const std::string tc::io::SubFileSystem::kClassName = "tc::io::SubFileSystem";

tc::io::SubFileSystem::SubFileSystem() :
	mBaseFileSystem(),
	mBasePathResolver(),
	mSubPathResolver()
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

	// get full path of root
	tc::io::Path canonical_base_path;
	mBaseFileSystem->getCanonicalPath(base_path, canonical_base_path);

	// set state for path resolvers
	mBasePathResolver.setCurrentDirectory(canonical_base_path);
	mSubPathResolver.setCurrentDirectory(tc::io::Path("/"));
}

tc::ResourceStatus tc::io::SubFileSystem::state()
{
	return mBaseFileSystem.get() ? mBaseFileSystem->state() : tc::ResourceStatus(1 << tc::RESFLAG_NOINIT);
}

void tc::io::SubFileSystem::dispose()
{
	if (mBaseFileSystem.get() != nullptr)
		mBaseFileSystem->dispose();

	mBasePathResolver = tc::io::BasicPathResolver();
	mSubPathResolver = tc::io::BasicPathResolver();
}

void tc::io::SubFileSystem::createFile(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::createFile()", "Failed to create file (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// create file
	mBaseFileSystem->createFile(real_path);
}

void tc::io::SubFileSystem::removeFile(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeFile()", "Failed to remove file (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// delete file
	mBaseFileSystem->removeFile(real_path);
}

void tc::io::SubFileSystem::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::openFile()", "Failed to open file (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// open file
	return mBaseFileSystem->openFile(real_path, mode, access, stream);
}

void tc::io::SubFileSystem::createDirectory(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectory()", "Failed to create directory (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// create directory
	mBaseFileSystem->createDirectory(real_path);
}

void tc::io::SubFileSystem::createDirectoryPath(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectoryPath()", "Failed to create directory path (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// create directory path
	mBaseFileSystem->createDirectoryPath(real_path);
}

void tc::io::SubFileSystem::removeDirectory(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeDirectory()", "Failed to remove directory (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// remove directory
	mBaseFileSystem->removeDirectory(real_path);
}

void tc::io::SubFileSystem::getCanonicalPath(const tc::io::Path& path, tc::io::Path& canon_path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::getCanonicalPath()", "Failed to get absolute path (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path real_path;
	subPathToRealPath(path, real_path);

	// get canononical real path
	tc::io::Path real_canon_path;
	mBaseFileSystem->getCanonicalPath(real_path, real_canon_path);

	// save canonical sub path
	realPathToSubPath(real_canon_path, canon_path);
}

void tc::io::SubFileSystem::getWorkingDirectory(tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::getWorkingDirectory()", "Failed to get current working directory (file system was not ready)");
	}

	path = mSubPathResolver.getCurrentDirectory();
}

void tc::io::SubFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::setWorkingDirectory()", "Failed to set current working directory (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path base_path;
	subPathToRealPath(path, base_path);

	// get absolute base path
	tc::io::Path canonical_base_path;
	mBaseFileSystem->getCanonicalPath(base_path, canonical_base_path);

	// save current directory
	tc::io::Path canonical_sub_path;
	realPathToSubPath(canonical_base_path, canonical_sub_path);
	mSubPathResolver.setCurrentDirectory(canonical_sub_path);
}

void tc::io::SubFileSystem::getDirectoryListing(const tc::io::Path& path, sDirectoryListing& info)
{
	if (this->state().test(RESFLAG_READY) == false)
	{
		throw tc::ObjectDisposedException(kClassName+"::getDirectoryListing()", "Failed to get directory listing (file system was not ready)");
	}

	// convert sub filesystem path to real path
	tc::io::Path canonical_base_path;
	subPathToRealPath(path, canonical_base_path);

	// get real directory info
	tc::io::sDirectoryListing dir_info;
	mBaseFileSystem->getDirectoryListing(canonical_base_path, dir_info);

	// convert directory absolute path
	tc::io::Path canonical_sub_path;
	realPathToSubPath(dir_info.abs_path, canonical_sub_path);
	
	// update info with sub filesystem path
	dir_info.abs_path = canonical_sub_path;

	// write object to output
	info = dir_info;
}

void tc::io::SubFileSystem::subPathToRealPath(const tc::io::Path& sub_path, tc::io::Path& real_path)
{
	// get canonical sub path
	tc::io::Path canonical_sub_path = mSubPathResolver.resolveCanonicalPath(sub_path);

	// get canonical base path
	real_path = mBasePathResolver.resolveCanonicalPath(canonical_sub_path.subpath(1, tc::io::Path::npos));
}

void tc::io::SubFileSystem::realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& sub_path)
{
	tc::io::Path canonical_base_path = mBasePathResolver.getCurrentDirectory();

	if (real_path.subpath(0, canonical_base_path.size()) != canonical_base_path)
	{
		throw tc::UnauthorisedAccessException(kClassName, "Sub filesystem escape detected");
	}

	sub_path = tc::io::Path("/") + real_path.subpath(canonical_base_path.size(), tc::io::Path::npos);
}