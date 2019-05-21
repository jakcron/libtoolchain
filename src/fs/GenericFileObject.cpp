#include <tc/fs/GenericFileObject.h>

const std::string tc::fs::GenericFileObject::kClassName = "tc::fs::GenericFileObject";

tc::fs::GenericFileObject::GenericFileObject() :
	mPtr(nullptr)
{
}

tc::fs::GenericFileObject::GenericFileObject(const tc::fs::GenericFileObject& other) :
	GenericFileObject()
{
	*this = other;
}

tc::fs::GenericFileObject::GenericFileObject(tc::fs::GenericFileObject&& other) :
	GenericFileObject()
{
	*this = std::move(other);
}

tc::fs::GenericFileObject::GenericFileObject(const tc::fs::IFileObject& other) :
	mPtr(other.copyInstance())
{
}

tc::fs::GenericFileObject::GenericFileObject(tc::fs::IFileObject&& other) :
	mPtr(other.moveInstance())
{
}

tc::fs::GenericFileObject::~GenericFileObject()
{
	deletePtr();
}

tc::fs::GenericFileObject& tc::fs::GenericFileObject::operator=(const tc::fs::GenericFileObject& other)
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

tc::fs::GenericFileObject& tc::fs::GenericFileObject::operator=(tc::fs::GenericFileObject&& other)
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

uint64_t tc::fs::GenericFileObject::size()
{
	if (mPtr != nullptr)
		return mPtr->size();
	else
		return 0;
}

void tc::fs::GenericFileObject::seek(uint64_t offset)
{
	if (mPtr != nullptr)
		mPtr->seek(offset);
}

uint64_t tc::fs::GenericFileObject::pos()
{
	if (mPtr != nullptr)
		return mPtr->pos();
	else
		return 0;
}

void tc::fs::GenericFileObject::read(byte_t* data, size_t len)
{
	if (mPtr != nullptr)
		mPtr->read(data, len);
}

void tc::fs::GenericFileObject::write(const byte_t* data, size_t len)
{
	if (mPtr != nullptr)
		mPtr->write(data, len);
}

tc::fs::IFileObject* tc::fs::GenericFileObject::copyInstance() const
{
	return new GenericFileObject(*this);	
}

tc::fs::IFileObject* tc::fs::GenericFileObject::moveInstance()
{
	return new GenericFileObject(std::move(*this));
}

void tc::fs::GenericFileObject::deletePtr()
{
	if (mPtr != nullptr)
	{
		delete mPtr;
		mPtr = nullptr;
	}
}