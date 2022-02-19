#include <tc/io/VirtualFileSystem.h>

tc::io::VirtualFileSystem::VirtualFileSystem() :
	mModuleLabel("tc::io::VirtualFileSystem"),
	mCurDir(nullptr),
	mFsSnapshot(),
	mPathResolver()
{
}

tc::io::VirtualFileSystem::VirtualFileSystem(const FileSystemSnapshot& fs_snapshot, const std::shared_ptr<IPathResolver>& path_resolver) :
	VirtualFileSystem()
{
	mFsSnapshot = fs_snapshot;
	mPathResolver = path_resolver;

	// Use default path resolver if none was provided
	if (mPathResolver == nullptr)
	{
		mPathResolver = std::shared_ptr<DefaultPathResolver>(new DefaultPathResolver());
	}
	
	// get root directory
	tc::io::Path root_path;
	mPathResolver->resolvePath(tc::io::Path("/"), tc::io::Path("/"), root_path);

	auto root_itr = mFsSnapshot.dir_entry_path_map.find(root_path);
	if (root_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::InvalidOperationException(mModuleLabel, "Failed to located root directory");
	}
	// if the path was not found in the map, throw exception
	if (root_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::InvalidOperationException(mModuleLabel, "Failed to located root directory");
	}
	// if the dir_entry index isn't valid, throw exception
	if (root_itr->second >= mFsSnapshot.dir_entries.size())
	{
		throw tc::InvalidOperationException(mModuleLabel, "Failed to located root directory");
	}

	mCurDir = &mFsSnapshot.dir_entries.at(root_itr->second);
}

tc::ResourceStatus tc::io::VirtualFileSystem::state()
{
	return mCurDir == nullptr? tc::ResourceStatus(tc::RESFLAG_NOINIT) : tc::ResourceStatus(tc::RESFLAG_READY);
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
		throw tc::ObjectDisposedException(mModuleLabel+"::createFile()", "VirtualFileSystem not initialised");
	}

	throw tc::NotImplementedException(mModuleLabel+"::createFile()", "createFile is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::removeFile(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::removeFile()", "VirtualFileSystem not initialised");
	}

	throw tc::NotImplementedException(mModuleLabel+"::removeFile()", "removeFile is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::openFile()", "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;
	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	if (mode != tc::io::FileMode::Open)
	{
		throw tc::NotImplementedException(mModuleLabel+"::openFile()", "This file-system is read-only, only FileMode::Open is supported.");
	}
	if (access != tc::io::FileAccess::Read)
	{
		throw tc::NotImplementedException(mModuleLabel+"::openFile()", "This file-system is read-only, only FileAccess::Read is supported.");
	}

	auto file_itr = mFsSnapshot.file_entry_path_map.find(resolved_path);
	// if resolved_path does not exist in the map, throw exception
	if (file_itr == mFsSnapshot.file_entry_path_map.end())
	{
		throw tc::io::FileNotFoundException(mModuleLabel+"::openFile()", "File does not exist.");
	}
	// if the file_entry index isn't valid or leads to a null IStream pointer, throw exception
	if (file_itr->second >= mFsSnapshot.file_entries.size() || mFsSnapshot.file_entries.at(file_itr->second).stream == nullptr)
	{
		throw tc::io::FileNotFoundException(mModuleLabel+"::openFile()", "File does not exist.");
	}
	// if the stream has invalid properties, throw exception
	if ( !(mFsSnapshot.file_entries.at(file_itr->second).stream->canRead() == true && mFsSnapshot.file_entries.at(file_itr->second).stream->canWrite() == false) )
	{
		throw tc::io::FileNotFoundException(mModuleLabel+"::openFile()", "File does not exist.");
	}

	stream = mFsSnapshot.file_entries.at(file_itr->second).stream;
}

void tc::io::VirtualFileSystem::createDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::createDirectory()", "VirtualFileSystem not initialised");
	}

	throw tc::NotImplementedException(mModuleLabel+"::createDirectory()", "createDirectory is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::removeDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::removeDirectory()", "VirtualFileSystem not initialised");
	}

	throw tc::NotImplementedException(mModuleLabel+"::removeDirectory()", "removeDirectory is not supported for VirtualFileSystem");
}

void tc::io::VirtualFileSystem::getWorkingDirectory(tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::getWorkingDirectory()", "VirtualFileSystem not initialised");
	}

	path = mCurDir->dir_listing.abs_path;
}

void tc::io::VirtualFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setWorkingDirectory()", "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;
	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	auto dir_itr = mFsSnapshot.dir_entry_path_map.find(resolved_path);
	// if the path was not found in the map, throw exception
	if (dir_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel+"::setWorkingDirectory()", "Directory does not exist.");
	}
	// if the dir_entry index isn't valid, throw exception
	if (dir_itr->second >= mFsSnapshot.dir_entries.size())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel+"::setWorkingDirectory()", "Directory does not exist.");
	}

	mCurDir = &mFsSnapshot.dir_entries.at(dir_itr->second);
}

void tc::io::VirtualFileSystem::getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::getDirectoryListing()", "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;

	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	auto dir_itr = mFsSnapshot.dir_entry_path_map.find(resolved_path);
	// if the path was not found in the map, throw exception
	if (dir_itr == mFsSnapshot.dir_entry_path_map.end())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel+"::getDirectoryListing()", "Directory does not exist.");
	}
	// if the dir_entry index isn't valid, throw exception
	if (dir_itr->second >= mFsSnapshot.dir_entries.size())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel+"::getDirectoryListing()", "Directory does not exist.");
	}

	info = mFsSnapshot.dir_entries.at(dir_itr->second).dir_listing;
}

tc::io::VirtualFileSystem::DefaultPathResolver::DefaultPathResolver()
{

}

void tc::io::VirtualFileSystem::DefaultPathResolver::resolvePath(const tc::io::Path& in_path, const tc::io::Path& current_working_directory, tc::io::Path& resolved_path)
{
	tc::io::Path in_tmp = in_path;
	tc::io::Path tmp = current_working_directory;
	
	 // clear the empty root path name (this should always be true, check done for readablility)
	if (tmp.front().empty())
		tmp.pop_front();
	
	// if input has empty root path at front, then this is an absolute path
	if (in_tmp.front().empty())
	{
		in_tmp.pop_front();

		// also clear tmp
		tmp.clear();
	}

	// combine in_tmp with tmp
	for (auto itr = in_tmp.begin(); itr != in_tmp.end(); itr++)
	{
		if (*itr == ".")
			continue;
		else if (*itr == "..")
		{
			// ".." is the parent directory, so if there are path elements then we remove from the back to "go to the parent directory"
			if (!tmp.empty())
				tmp.pop_back();
			else
				continue;
		}
		else
			tmp.push_back(*itr);
	}

	// re-add empty root path name
	tmp.push_front("");

	resolved_path = tmp;
}