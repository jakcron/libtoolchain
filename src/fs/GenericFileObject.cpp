#include <tc/fs/GenericFileObject.h>

#include <tc/Exception.h>

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
	if (mPtr == nullptr)
	{
		throw tc::Exception(kClassName, "size() called on NullObject");
	}

	return mPtr->size();
}

void tc::fs::GenericFileObject::seek(uint64_t offset)
{
	if (mPtr == nullptr)
	{
		throw tc::Exception(kClassName, "seek() called on NullObject");
	}

	mPtr->seek(offset);
}

uint64_t tc::fs::GenericFileObject::pos()
{
	if (mPtr == nullptr)
	{
		throw tc::Exception(kClassName, "pos() called on NullObject");
	}

	return mPtr->pos();
}

void tc::fs::GenericFileObject::read(byte_t* data, size_t len)
{
	if (mPtr == nullptr)
	{
		throw tc::Exception(kClassName, "read() called on NullObject");
	}

	mPtr->read(data, len);
}

void tc::fs::GenericFileObject::write(const byte_t* data, size_t len)
{
	if (mPtr == nullptr)
	{
		throw tc::Exception(kClassName, "write() called on NullObject");
	}

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

bool tc::fs::GenericFileObject::isNull() const
{
	return mPtr == nullptr;
}

void tc::fs::GenericFileObject::deletePtr()
{
	if (mPtr != nullptr)
	{
		delete mPtr;
		mPtr = nullptr;
	}
}