#include <tc/fs/GenericFileSystem.h>

const std::string tc::fs::GenericFileSystem::kClassName = "tc::fs::GenericFileSystem";

tc::fs::GenericFileSystem::GenericFileSystem():
	mPtr(nullptr)
{
}

tc::fs::GenericFileSystem::GenericFileSystem(const tc::fs::GenericFileSystem& other) :
	GenericFileSystem()
{
	*this = other;
}

tc::fs::GenericFileSystem::GenericFileSystem(tc::fs::GenericFileSystem&& other) :
	GenericFileSystem()
{
	*this = std::move(other);
}

tc::fs::GenericFileSystem::GenericFileSystem(const tc::fs::IFileSystem& other) :
	mPtr(other.copyInstance())
{
}

tc::fs::GenericFileSystem::GenericFileSystem(tc::fs::IFileSystem&& other) :
	mPtr(other.moveInstance())
{
}

tc::fs::GenericFileSystem::~GenericFileSystem()
{
	deletePtr();
}

tc::fs::GenericFileSystem& tc::fs::GenericFileSystem::operator=(const tc::fs::GenericFileSystem& other)
{
	if (this != &other)
	{
		deletePtr();
		if (other.mPtr != nullptr)
		{
			mPtr = other.mPtr->copyInstance();
		}
	}
	return *this;
}

tc::fs::GenericFileSystem& tc::fs::GenericFileSystem::operator=(tc::fs::GenericFileSystem&& other)
{
	if (this != &other)
	{
		deletePtr();
		if (other.mPtr != nullptr)
		{
			mPtr = other.mPtr->moveInstance();
			other.deletePtr();
		}
	}
	return *this;
}

void tc::fs::GenericFileSystem::createFile(const tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->createFile(path);
}

void tc::fs::GenericFileSystem::removeFile(const tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->removeFile(path);
}

void tc::fs::GenericFileSystem::openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file)
{
	if (mPtr != nullptr)
		mPtr->openFile(path, mode, file);
}

void tc::fs::GenericFileSystem::createDirectory(const tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->createDirectory(path);
}

void tc::fs::GenericFileSystem::removeDirectory(const tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->removeDirectory(path);
}

void tc::fs::GenericFileSystem::getWorkingDirectory(tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->getWorkingDirectory(path);
}

void tc::fs::GenericFileSystem::setWorkingDirectory(const tc::fs::Path& path)
{
	if (mPtr != nullptr)
		mPtr->setWorkingDirectory(path);
}

void tc::fs::GenericFileSystem::getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
{
	if (mPtr != nullptr)
		mPtr->getDirectoryListing(path, info);
}

tc::fs::IFileSystem* tc::fs::GenericFileSystem::copyInstance() const
{
	return new GenericFileSystem(*this);	
}

tc::fs::IFileSystem* tc::fs::GenericFileSystem::moveInstance()
{
	return new GenericFileSystem(std::move(*this));
}

void tc::fs::GenericFileSystem::deletePtr()
{
	if (mPtr != nullptr)
	{
		delete mPtr;
		mPtr = nullptr;
	}
}