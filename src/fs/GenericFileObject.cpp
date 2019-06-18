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
	// don't allow GenericFileObject to adopt dead FileObjects
	if (mPtr.isNull() == false && mPtr->state().test(RESFLAG_READY) == false)
	{
		mPtr.release();
	}
}

tc::fs::GenericFileObject::GenericFileObject(tc::fs::IFileObject&& other) :
	mPtr(other.moveInstance())
{
	// don't allow GenericFileObject to adopt dead FileObjects
	if (mPtr.isNull() == false && mPtr->state().test(RESFLAG_READY) == false)
	{
		mPtr.release();
	}
}

tc::fs::GenericFileObject::~GenericFileObject()
{
	mPtr.release();
}

tc::fs::GenericFileObject& tc::fs::GenericFileObject::operator=(const tc::fs::GenericFileObject& other)
{
	if (this != &other)
	{
		mPtr = other.mPtr;
	}
	return *this;
}

tc::fs::GenericFileObject& tc::fs::GenericFileObject::operator=(tc::fs::GenericFileObject&& other)
{
	if (this != &other)
	{
		mPtr = std::move(other.mPtr);
	}
	return *this;
}

tc::fs::IFileObject* tc::fs::GenericFileObject::copyInstance() const
{
	return new GenericFileObject(*this);	
}

tc::fs::IFileObject* tc::fs::GenericFileObject::moveInstance()
{
	return new GenericFileObject(std::move(*this));
}

tc::ResourceState tc::fs::GenericFileObject::state()
{
	return mPtr.isNull() ? tc::ResourceState(0) :  mPtr->state();
}

void tc::fs::GenericFileObject::close()
{
	mPtr.release();
}

uint64_t tc::fs::GenericFileObject::size()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "size() called on NullObject");
	}

	return mPtr->size();
}

void tc::fs::GenericFileObject::seek(uint64_t offset)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "seek() called on NullObject");
	}

	mPtr->seek(offset);
}

uint64_t tc::fs::GenericFileObject::pos()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "pos() called on NullObject");
	}

	return mPtr->pos();
}

void tc::fs::GenericFileObject::read(byte_t* data, size_t len)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "read() called on NullObject");
	}

	mPtr->read(data, len);
}

void tc::fs::GenericFileObject::write(const byte_t* data, size_t len)
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "write() called on NullObject");
	}

	mPtr->write(data, len);
}