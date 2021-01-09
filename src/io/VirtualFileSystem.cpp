#include <tc/io/VirtualFileSystem.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <tc/cli.h>
#include <tc/io.h>
#include <tc/string.h>

tc::io::VirtualFileSystem::VirtualFileSystem() :
	mModuleLabel("tc::io::VirtualFileSystem"),
	mCurDir(nullptr),
	mFsMeta(),
	mPathResolver()
{
}

tc::io::VirtualFileSystem::VirtualFileSystem(const FileSystemMeta& fs_meta, const std::shared_ptr<IPathResolver>& path_resolver) :
	VirtualFileSystem()
{
	mFsMeta = fs_meta;
	mPathResolver = path_resolver;

	// Use default path resolver if none was provided
	if (mPathResolver == nullptr)
	{
		mPathResolver = std::shared_ptr<DefaultPathResolver>(new DefaultPathResolver());
	}
	
	// get root directory
	tc::io::Path root_path;
	mPathResolver->resolvePath(tc::io::Path("/"), tc::io::Path("/"), root_path);

	auto root_itr = mFsMeta.dir_hash_map.find(root_path);
	if (root_itr == mFsMeta.dir_hash_map.end())
	{
		throw tc::InvalidOperationException(mModuleLabel, "Failed to located root directory");
	}

	/*
	auto dir_listing = mFsMeta.dir_entries.at(root_itr->second).dir_listing;
	for (auto itr = dir_listing.file_list.begin(); itr != dir_listing.file_list.end(); itr++)
	{
		std::cout << "get fucked: " << *itr;
	}
	*/

	mCurDir = &mFsMeta.dir_entries.at(root_itr->second);
}

tc::ResourceStatus tc::io::VirtualFileSystem::state()
{
	return mCurDir == nullptr? tc::ResourceStatus(tc::RESFLAG_NOINIT) : tc::ResourceStatus(tc::RESFLAG_READY);
}

void tc::io::VirtualFileSystem::dispose()
{
	mCurDir = nullptr;
	mFsMeta.dir_entries.clear();
	mFsMeta.file_entries.clear();
	mFsMeta.dir_hash_map.clear();
	mFsMeta.file_hash_map.clear();
	mPathResolver.reset();
}

void tc::io::VirtualFileSystem::createFile(const tc::io::Path& path)
{
	throw tc::NotSupportedException(mModuleLabel, "createFile() is not supported.");
}

void tc::io::VirtualFileSystem::removeFile(const tc::io::Path& path)
{
	throw tc::NotSupportedException(mModuleLabel, "removeFile() is not supported.");
}

void tc::io::VirtualFileSystem::openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;
	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	if (mode != tc::io::FileMode::Open)
	{
		throw tc::io::FileNotFoundException(mModuleLabel, "This file-system is read-only, only FileMode::Open is supported.");
	}
	if (access != tc::io::FileAccess::Read)
	{
		throw tc::io::FileNotFoundException(mModuleLabel, "This file-system is read-only, only FileAccess::Read is supported.");
	}

	auto file_itr = mFsMeta.file_hash_map.find(resolved_path);
	if (file_itr == mFsMeta.file_hash_map.end())
	{
		throw tc::io::FileNotFoundException(mModuleLabel, "File does not exist.");
	}

	stream = mFsMeta.file_entries.at(file_itr->second).stream;
}

void tc::io::VirtualFileSystem::createDirectory(const tc::io::Path& path)
{
	throw tc::NotSupportedException(mModuleLabel, "createDirectory() is not supported.");
}

void tc::io::VirtualFileSystem::removeDirectory(const tc::io::Path& path)
{
	throw tc::NotSupportedException(mModuleLabel, "removeDirectory() is not supported.");
}

void tc::io::VirtualFileSystem::getWorkingDirectory(tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "VirtualFileSystem not initialised");
	}

	path = mCurDir->dir_listing.abs_path;
}

void tc::io::VirtualFileSystem::setWorkingDirectory(const tc::io::Path& path)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;
	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	auto dir_itr = mFsMeta.dir_hash_map.find(resolved_path);
	if (dir_itr == mFsMeta.dir_hash_map.end())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel, "Directory does not exist.");
	}

	mCurDir = &mFsMeta.dir_entries.at(dir_itr->second);
}

void tc::io::VirtualFileSystem::getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info)
{
	if (mCurDir == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "VirtualFileSystem not initialised");
	}

	tc::io::Path resolved_path;

	mPathResolver->resolvePath(path, mCurDir->dir_listing.abs_path, resolved_path);

	auto dir_itr = mFsMeta.dir_hash_map.find(resolved_path);
	if (dir_itr == mFsMeta.dir_hash_map.end())
	{
		throw tc::io::DirectoryNotFoundException(mModuleLabel, "Directory does not exist.");
	}

	info = mFsMeta.dir_entries.at(dir_itr->second).dir_listing;
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
			tmp.pop_back();
		else
			tmp.push_back(*itr);
	}

	// re-add empty root path name
	tmp.push_front("");

	resolved_path = tmp;
}