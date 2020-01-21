#pragma once
#include "ITestClass.h"

#include <tc/fs.h>

class fs_SandboxedFileSystem_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyFileSystemBase : public tc::fs::IFileSystem
	{
	public:
		DummyFileSystemBase()
		{
			initFs();
		}

		virtual tc::ResourceState getFsState()
		{
			return mState;
		}

		void initFs()
		{
			closeFs();
			mCurDir = std::make_shared<tc::fs::Path>();
			mState.set(tc::RESFLAG_READY);
		}

		virtual void closeFs()
		{
			mState.reset();
			mCurDir.reset();
		}

		virtual void createFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "createFile() not implemented");
		}

		virtual void removeFile(const tc::fs::Path& path)
		{
			throw tc::Exception(kClassName, "removeFile() not implemented");
		}

		virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, std::shared_ptr<tc::fs::IFileObject>& file)
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
	private:
		static const std::string kClassName;
		tc::ResourceState mState;
		std::shared_ptr<tc::fs::Path> mCurDir;
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