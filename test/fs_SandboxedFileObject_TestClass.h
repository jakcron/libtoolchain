#pragma once
#include "ITestClass.h"

#include <tc/fs.h>
#include <tc/SharedPtr.h>

class fs_SandboxedFileObject_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileBase : public tc::fs::IFileObject
	{
	public:
		DummyFileBase()
		{
		}

		virtual void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}
		
		virtual void seek(uint64_t offset)
		{
			mOffset = offset;
		}

		virtual uint64_t pos()
		{
			return mOffset;
		}

		virtual void read(byte_t* data, size_t len)
		{
			throw tc::Exception(kClassName, "read() not implemented");
		}

		virtual void write(const byte_t* data, size_t len)
		{
			throw tc::Exception(kClassName, "write() not implemented");
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFileBase(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			return new DummyFileBase(*this);
		}
	private:
		static const std::string kClassName;
		uint64_t mOffset;
		uint64_t mSize;
	};

	void testSize();
	void testSeekPos();
	void testRead();
	void testWrite();
};