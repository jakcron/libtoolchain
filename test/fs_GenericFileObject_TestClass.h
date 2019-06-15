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

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFileBase(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			return new DummyFileBase(*this);
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
};