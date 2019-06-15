#pragma once
#include "ITestClass.h"

#include <tc/fs.h>

class fs_GenericFileSystem_TestClass : public ITestClass
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

	class DummyFileSystemBase : public tc::fs::IFileSystem
	{
	public:
		DummyFileSystemBase()
		{
		}

		virtual void createFile(const tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "createFile() not implemented");
		}

		virtual void removeFile(const tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "removeFile() not implemented");
		}

		virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file)
		{
			throw tc::Exception("DummyFileSystemBase", "openFile() not implemented");
		}

		virtual void createDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "createDirectory() not implemented");
		}

		virtual void removeDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "removeDirectory() not implemented");
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "getWorkingDirectory() not implemented");
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception("DummyFileSystemBase", "setWorkingDirectory() not implemented");
		}

		virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
		{
			throw tc::Exception("DummyFileSystemBase", "getDirectoryListing() not implemented");
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystemBase(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystemBase(std::move(*this));
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