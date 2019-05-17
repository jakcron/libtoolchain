#pragma once
#include "ITestClass.h"

#include <tc/fs.h>
#include <tc/SharedPtr.h>

class fs_SandboxedFileObject_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileBase : public tc::fs::IFile
	{
	public:
		DummyFileBase()
		{
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		uint64_t size()
		{
			return mSize;
		}
		
		void seek(uint64_t offset)
		{
			mOffset = offset;
		}

		uint64_t pos()
		{
			return mOffset;
		}

		void read(byte_t* data, size_t len)
		{
			throw tc::Exception(kClassName, "read() not implemented");
		}

		void write(const byte_t* data, size_t len)
		{
			throw tc::Exception(kClassName, "write() not implemented");
		}
	private:
		const std::string kClassName = "DummyFileBase";
		uint64_t mOffset;
		uint64_t mSize;
	};

	void testSize();
	void testSeekPos();
	void testRead();
	void testWrite();
};