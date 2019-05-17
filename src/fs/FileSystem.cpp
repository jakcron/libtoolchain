#include <tc/fs/FileSystem.h>

tc::fs::FileSystem::FileSystem():
	mFileSystem()
{
}

tc::fs::FileSystem::FileSystem(const tc::fs::FileSystem& other):
	FileSystem()
{
	*this = other;
}

tc::fs::FileSystem::FileSystem(tc::fs::IFileSystem* fs_ptr):
	mFileSystem(fs_ptr)
{
}

tc::fs::FileSystem& tc::fs::FileSystem::operator=(const tc::fs::FileSystem& other)
{
	mFileSystem = other.mFileSystem;
	return *this;
}

void tc::fs::FileSystem::createFile(const tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->createFile(path);
}

void tc::fs::FileSystem::removeFile(const tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->removeFile(path);
}

void tc::fs::FileSystem::openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::FileObject& file)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->openFile(path, mode, file);
}

void tc::fs::FileSystem::createDirectory(const tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->createDirectory(path);
}

void tc::fs::FileSystem::removeDirectory(const tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->removeDirectory(path);
}

void tc::fs::FileSystem::getWorkingDirectory(tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->getWorkingDirectory(path);
}

void tc::fs::FileSystem::setWorkingDirectory(const tc::fs::Path& path)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->setWorkingDirectory(path);
}

void tc::fs::FileSystem::getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
{
	if (mFileSystem.isNull() == false)
		mFileSystem->getDirectoryListing(path, info);
}
