#include <tc/io/VirtualFileSystem.h>

#include <fmt/format.h>

const std::string tc::io::VirtualFileSystem::kClassName = "tc::io::VirtualFileSystem";

tc::io::VirtualFileSystem::VirtualFileSystem() :
	mCurDir(nullptr),
	mFsSnapshot(),
	mPathResolver()
{
}

tc::io::VirtualFileSystem::VirtualFileSystem(const FileSystemSnapshot& fs_snapshot, const std::shared_ptr<tc::io::IPortablePathResolver>& path_resolver) :
	VirtualFileSystem()
{
	mFsSnapshot = fs_snapshot;
	mPathResolver = path_resolver;

	// Use default path resolver if none was provided
	if (mPathResolver == nullptr)
	{
		mPathResolver = std::shared_ptr<tc::io::BasicPathResolver>(new tc::io::BasicPathResolver());
	}
	
	// resolve root canonical path
	tc::io::Path canonical_root_path = mPathResolver->resolveCanonicalPath(tc::io::Path("/"));

	// get root directory from filesystem snapshot
	auto root_itr = mFsSnapshot.dir_entry_path_map.find(canonical_root_path);

	// if the path was not found in the map, throw exception
	if (root_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::InvalidOperationException(kClassName, "Failed to located root directory. (Root path was not found in Path to Index map)");
	}
	// if the dir_entry index isn't valid, throw exception
	if (root_itr->second >= mFsSnapshot.dir_entries.size())
	{
		throw tc::InvalidOperationException(kClassName, "Failed to located root directory. (Root directory index was invalid)");
	}

	mCurDir = &mFsSnapshot.dir_entries.at(root_itr->second);
}

tc::ResourceStatus tc::io::VirtualFileSystem::state()
{
	return mCurDir == nullptr? tc::ResourceStatus(1 << tc::RESFLAG_NOINIT) : tc::ResourceStatus(1 << tc::RESFLAG_READY);
}

void tc::io::VirtualFileSystem::dispose()
{
	mCurDir = nullptr;
	mFsSnapshot.dir_entries.clear();
	mFsSnapshot.file_entries.clear();
	mFsSnapshot.dir_entry_path_map.clear();
	mFsSnapshot.file_entry_path_map.clear();
	mPathResolver.reset();
}

void tc::io::VirtualFileSystem::createFile(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createFile()", "VirtualFileSystem not initialized");
	}

	throw tc::NotSupportedException(kClassName+"::createFile()", "createFile is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::removeFile(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeFile()", "VirtualFileSystem not initialized");
	}

	throw tc::NotSupportedException(kClassName+"::removeFile()", "removeFile is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::openFile()", "VirtualFileSystem not initialized");
	}

	// resolve file path
	tc::io::Path resolved_path = mPathResolver->resolveCanonicalPath(path);

	// check input file permissions
	if (mode != tc::io::FileMode::Open)
	{
		throw tc::NotSupportedException(kClassName+"::openFile()", "This file-system is read-only, only FileMode::Open is supported.");
	}
	if (access != tc::io::FileAccess::Read)
	{
		throw tc::NotSupportedException(kClassName+"::openFile()", "This file-system is read-only, only FileAccess::Read is supported.");
	}

	// get file from filesystem snapshot 
	auto file_entry = getFileFromFsSnapshot("::openFile()", resolved_path);

	// assign stream from file entry
	stream = file_entry->stream;
}

void tc::io::VirtualFileSystem::createDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectory()", "VirtualFileSystem not initialized");
	}

	throw tc::NotSupportedException(kClassName+"::createDirectory()", "createDirectory is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::createDirectoryPath(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::createDirectoryPath()", "VirtualFileSystem not initialized");
	}

	throw tc::NotSupportedException(kClassName+"::createDirectoryPath()", "createDirectoryPath is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::removeDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::removeDirectory()", "VirtualFileSystem not initialized");
	}

	throw tc::NotSupportedException(kClassName+"::removeDirectory()", "removeDirectory is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::getCanonicalPath(const tc::io::Path& path, tc::io::Path& canon_path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getCanonicalPath()", "VirtualFileSystem not initialized");
	}

	// get logical canon path
	tc::io::Path tmp_canon_path = tc::io::Path();
	mPathResolver->resolveCanonicalPath(path, tmp_canon_path);

	// check if path exists
	bool path_exists_as_dir = false;
	bool path_exists_as_file = false;

	try
	{
		getDirectoryFromFsSnapshot("::getCanonicalPath()", tmp_canon_path);
		path_exists_as_dir = true;
	}
	catch (const tc::io::DirectoryNotFoundException&) { /* do nothing */ }
	
	try
	{
		getFileFromFsSnapshot("::getCanonicalPath()", tmp_canon_path);
		path_exists_as_file = true;
	}
	catch (const tc::io::FileNotFoundException&) { /* do nothing */ }

	// if path doesn't exist as a directory or file, throw not found exception
	if (!path_exists_as_dir && !path_exists_as_file)
	{
		throw tc::io::DirectoryNotFoundException(kClassName+"::getCanonicalPath()", fmt::format("Directory \"{:s}\" was not found.", path.to_string()));
	}

	// save canon path
	canon_path = tmp_canon_path;
}

void tc::io::VirtualFileSystem::getWorkingDirectory(tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getWorkingDirectory()", "VirtualFileSystem not initialized");
	}

	path = mCurDir->dir_listing.abs_path;
}

void tc::io::VirtualFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::setWorkingDirectory()", "VirtualFileSystem not initialized");
	}

	// resolve directory path
	tc::io::Path resolved_path = mPathResolver->resolveCanonicalPath(path);

	// get directory from filesystem snapshot
	auto dir_entry = getDirectoryFromFsSnapshot("::setWorkingDirectory()", resolved_path);

	// set current directory
	mCurDir = dir_entry;
	mPathResolver->setCurrentDirectory(mCurDir->dir_listing.abs_path);
}

void tc::io::VirtualFileSystem::getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::getDirectoryListing()", "VirtualFileSystem not initialized");
	}

	// resolve directory path
	tc::io::Path resolved_path = mPathResolver->resolveCanonicalPath(path);

	// get directory from filesystem snapshot
	auto dir_entry = getDirectoryFromFsSnapshot("::getDirectoryListing()", resolved_path);

	// set directory info
	info = dir_entry->dir_listing;
}

tc::io::VirtualFileSystem::FileSystemSnapshot::FileEntry* tc::io::VirtualFileSystem::getFileFromFsSnapshot(const std::string& method_name, const tc::io::Path& resolved_path)
{
	auto file_itr = mFsSnapshot.file_entry_path_map.find(resolved_path);
	// if resolved_path does not exist in the map, throw exception
	if (file_itr == mFsSnapshot.file_entry_path_map.end())
	{
		throw tc::io::FileNotFoundException(kClassName + method_name, "File does not exist. (Path to File Index map had no match)");
	}
	// if the file_entry index isn't valid, throw exception
	if (file_itr->second >= mFsSnapshot.file_entries.size())
	{
		throw tc::io::FileNotFoundException(kClassName + method_name, "File does not exist. (Invalid File Index)");
	}
	// if the file_entry index leads to a null IStream pointer, throw exception
	if (mFsSnapshot.file_entries.at(file_itr->second).stream == nullptr)
	{
		throw tc::io::FileNotFoundException(kClassName + method_name, "File does not exist. (File stream was null)");
	}
	// if the stream has invalid properties, throw exception
	if ( !(mFsSnapshot.file_entries.at(file_itr->second).stream->canRead() == true && mFsSnapshot.file_entries.at(file_itr->second).stream->canWrite() == false) )
	{
		throw tc::io::FileNotFoundException(kClassName + method_name, "File does not exist. (File stream had invalid permissions)");
	}

	return &(mFsSnapshot.file_entries.at(file_itr->second));
}

tc::io::VirtualFileSystem::FileSystemSnapshot::DirEntry* tc::io::VirtualFileSystem::getDirectoryFromFsSnapshot(const std::string& method_name, const tc::io::Path& resolved_path)
{
	auto dir_itr = mFsSnapshot.dir_entry_path_map.find(resolved_path);
	// if the path was not found in the map, throw exception
	if (dir_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::io::DirectoryNotFoundException(kClassName + method_name, "Directory does not exist. (Path to Directory Index map had no match)");
	}
	// if the dir_entry index isn't valid, throw exception
	if (dir_itr->second >= mFsSnapshot.dir_entries.size())
	{
		throw tc::io::DirectoryNotFoundException(kClassName + method_name, "Directory does not exist. (Invalid Directory Index)");
	}

	return &(mFsSnapshot.dir_entries.at(dir_itr->second));
}