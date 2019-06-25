#include <tc/fs/GenericFileSystem.h>

#include <tc/Exception.h>

const std::string tc::fs::GenericFileSystem::kClassName = "tc::fs::GenericFileSystem";

tc::fs::GenericFileSystem::GenericFileSystem():
	mPtr(nullptr)
{
}

tc::fs::GenericFileSystem::GenericFileSystem(const tc::fs::IFileSystem& other) :
	mPtr(other.copyInstance())
{
	// don't allow GenericFileSystem to adopt dead FileSystems
	if (mPtr.isNull() == false && mPtr->getFsState().test(RESFLAG_READY) == false)
	{
		mPtr.release();
	}
}

tc::fs::GenericFileSystem::GenericFileSystem(tc::fs::IFileSystem&& other) :
	mPtr(other.moveInstance())
{
	// don't allow GenericFileSystem to adopt dead FileSystems
	if (mPtr.isNull() == false && mPtr->getFsState().test(RESFLAG_READY) == false)
	{
		mPtr.release();
	}
}

tc::fs::IFileSystem* tc::fs::GenericFileSystem::copyInstance() const
{
	return new GenericFileSystem(*this);	
}

tc::fs::IFileSystem* tc::fs::GenericFileSystem::moveInstance()
{
	return new GenericFileSystem(std::move(*this));
}

tc::ResourceState tc::fs::GenericFileSystem::getFsState()
{
	return mPtr.isNull() ? tc::ResourceState(0) : mPtr->getFsState();
}

void tc::fs::GenericFileSystem::closeFs()
{
	mPtr.release();
}

void tc::fs::GenericFileSystem::createFile(const tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "createFile() called on NullObject");
	}

	mPtr->createFile(path);
}

void tc::fs::GenericFileSystem::removeFile(const tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "removeFile() called on NullObject");
	}

	mPtr->removeFile(path);
}

void tc::fs::GenericFileSystem::openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "openFile() called on NullObject");
	}

	mPtr->openFile(path, mode, file);
}

void tc::fs::GenericFileSystem::createDirectory(const tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "createDirectory() called on NullObject");
	}

	mPtr->createDirectory(path);
}

void tc::fs::GenericFileSystem::removeDirectory(const tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "removeDirectory() called on NullObject");
	}

	mPtr->removeDirectory(path);
}

void tc::fs::GenericFileSystem::getWorkingDirectory(tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "getWorkingDirectory() called on NullObject");
	}

	mPtr->getWorkingDirectory(path);
}

void tc::fs::GenericFileSystem::setWorkingDirectory(const tc::fs::Path& path)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "setWorkingDirectory() called on NullObject");
	}

	mPtr->setWorkingDirectory(path);
}

void tc::fs::GenericFileSystem::getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "getDirectoryListing() called on NullObject");
	}

	mPtr->getDirectoryListing(path, info);
}