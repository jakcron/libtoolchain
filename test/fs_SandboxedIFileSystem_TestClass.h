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

		tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode)
		{
			throw tc::Exception(kClassName, "openFile() not implemented");
			return nullptr;
		}

		void deleteFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "deleteFile() not implemented");
		}

		void getCurrentDirectory(tc::fs::Path& path)
		{
			path = mCurDir;
		}

		void setCurrentDirectory(const tc::fs::Path& path)
		{
			mCurDir = path;
		}

		void createDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createDirectory() not implemented");
		}

		void deleteDirectory(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "deleteDirectory() not implemented");
		}

		void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& info)
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
	void testdeleteDirectory();
	void testGetDirectoryListing();
	void testNavigateUpSandboxEscape();
	void testOpenFileOutsideSandbox();
};