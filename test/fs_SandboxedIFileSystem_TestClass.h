#pragma once
#include "ITestClass.h"

#include <tc/fs.h>
#include <tc/SharedPtr.h>

class fs_SandboxedIFileSystem_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileSystemBase : public tc::fs::IFileSystem
	{
	public:
		DummyFileSystemBase()
		{
		}

		void createFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createFile() not implemented");
		}

		void removeFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "removeFile() not implemented");
		}

		void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::SharedPtr<tc::fs::IFile>& file)
		{
			throw tc::Exception(kClassName, "openFile() not implemented");
		}

		void createDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createDirectory() not implemented");
		}

		void removeDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "removeDirectory() not implemented");
		}

		void getWorkingDirectory(tc::fs::Path& path)
		{
			path = mCurDir;
		}

		void setWorkingDirectory(const tc::fs::Path& path)
		{
			mCurDir = path;
		}

		void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info)
		{
			throw tc::Exception(kClassName, "getDirectoryListing() not implemented");
		}
	private:
		const std::string kClassName = "DummyFileSystemBase";
		tc::fs::Path mCurDir;
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