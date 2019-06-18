#pragma once
#include "ITestClass.h"

#include <tc/fs.h>

class fs_GenericFileObject_TestClass : public ITestClass
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

		virtual tc::fs::IFileObject* copyInstance() const
		{
			throw tc::Exception("DummyFileBase", "copyInstance() not implemented");
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			throw tc::Exception("DummyFileBase", "copyInstance() not implemented");
		}

		virtual tc::ResourceState state()
		{
			throw tc::Exception("DummyFileBase", "state() not implemented");
		}

		virtual void close()
		{
			throw tc::Exception("DummyFileBase", "close() not implemented");
		}

		virtual uint64_t size()
		{
			throw tc::Exception("DummyFileBase", "size() not implemented");
		}
		
		virtual void seek(uint64_t offset)
		{
			throw tc::Exception("DummyFileBase", "seek() not implemented");
		}

		virtual uint64_t pos()
		{
			throw tc::Exception("DummyFileBase", "pos() not implemented");
		}

		virtual void read(byte_t* data, size_t len)
		{
			throw tc::Exception("DummyFileBase", "read() not implemented");
		}

		virtual void write(const byte_t* data, size_t len)
		{
			throw tc::Exception("DummyFileBase", "write() not implemented");
		}
	};

	void test_DefaultConstructor_IsNull();
	void test_GenericCopyConstructor();
	void test_GenericMoveConstructor();
	void test_CopyConstructor();
	void test_MoveConstructor();
	void test_CopyOperator();
	void test_MoveOperator();
	void test_Generic_Passthrough();
	void test_Close();
};