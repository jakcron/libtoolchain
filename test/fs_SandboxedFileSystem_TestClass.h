#pragma once
#include "ITestClass.h"

#include <tc/fs.h>
#include <tc/SharedPtr.h>

class fs_SandboxedFileSystem_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileSystemBase : public tc::fs::IFileSystem
	{
	public:
		DummyFileSystemBase() :
			mCurDir(new tc::fs::Path())
		{
		}

		virtual void createFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createFile() not implemented");
		}

		virtual void removeFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "removeFile() not implemented");
		}

		virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file)
		{
			throw tc::Exception(kClassName, "openFile() not implemented");
		}

		virtual void createDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createDirectory() not implemented");
		}

		virtual void removeDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "removeDirectory() not implemented");
		}

		virtual void getWorkingDirectory(tc::fs::Path& path)
		{
			path = *mCurDir;
		}

		virtual void setWorkingDirectory(const tc::fs::Path& path)
		{
			*mCurDir = path;
		}

		virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
		{
			throw tc::Exception(kClassName, "getDirectoryListing() not implemented");
		}

		virtual tc::fs::IFileSystem* copyInstance() const
		{
			return new DummyFileSystemBase(*this);
		}

		virtual tc::fs::IFileSystem* moveInstance()
		{
			return new DummyFileSystemBase(std::move(*this));
		}
	private:
		static const std::string kClassName;
		tc::SharedPtr<tc::fs::Path> mCurDir;
	};

	void testSandboxRootPath();
	void testCreateFile();
	void testOpenFile();
	void testRemoveFile();
	void testCreateDirectory();
	void testRemoveDirectory();
	void testGetDirectoryListing();
	void testNavigateUpSandboxEscape();
	void testOpenFileOutsideSandbox();
};