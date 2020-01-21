#pragma once
#include "ITestClass.h"

#include <tc/fs.h>

class fs_PartitionedFileObject_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileBase : public tc::fs::IFileObject
	{
	public:
		DummyFileBase()
		{
			init();
		}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		void init()
		{
			mState.set(tc::RESFLAG_READY);
			mOffset = 0;
			mSize = 0;
		}

		virtual void close()
		{
			mState = 0;
			mOffset = 0;
			mSize = 0;
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
	private:
		static const std::string kClassName;
		tc::ResourceState mState;
		uint64_t mOffset;
		uint64_t mSize;
	};

	void testSize();
	void testSeekPos();
	void testRead();
	void testWrite();
};