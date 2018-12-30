#include <tc/filesystem.h>
#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

class DummyFileSystemBase : public tc::filesystem::IFileSystem
{
public:
	DummyFileSystemBase()
	{
	}

	tc::filesystem::IFile* openFile(const tc::filesystem::Path& path, tc::filesystem::FileAccessMode mode)
	{
		throw tc::Exception(kClassName, "openFile() not implemented");
		return nullptr;
	}

	void deleteFile(const tc::filesystem::Path& path)
	{
		throw tc::Exception(kClassName, "deleteFile() not implemented");
	}

	void getCurrentDirectory(tc::filesystem::Path& path)
	{
		path = mCurDir;
	}

	void setCurrentDirectory(const tc::filesystem::Path& path)
	{
		mCurDir = path;
	}

	void createDirectory(const tc::filesystem::Path& path)
	{
		throw tc::Exception(kClassName, "createDirectory() not implemented");
	}

	void removeDirectory(const tc::filesystem::Path& path)
	{
		throw tc::Exception(kClassName, "removeDirectory() not implemented");
	}

	void getDirectoryInfo(const tc::filesystem::Path& path, tc::filesystem::DirectoryInfo& info)
	{
		throw tc::Exception(kClassName, "getDirectoryInfo() not implemented");
	}
private:
	const std::string kClassName = "DummyFileSystemBase";
	tc::filesystem::Path mCurDir;
};

void testSandboxRootPath()
{
	std::cout << "[SandboxFileSystem] testSandboxRootPath : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");
		tc::filesystem::Path sandbox_relative_root = testdir_path + tc::filesystem::Path("sandbox");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + sandbox_relative_root);

			// save sandbox real path
			tc::filesystem::Path sandbox_real_root;
			sb_fs->setCurrentDirectory(tc::filesystem::Path("/"));
			fs->getCurrentDirectory(sandbox_real_root);

			// check the sandbox is generating the correct path
			if (sandbox_real_root != dummyfs_curdir + sandbox_relative_root)
			{
				throw tc::Exception("Sandbox root directory did not have expected absolute real path");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

	
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testCreateFile()
{
	std::cout << "[SandboxFileSystem] testCreateFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::filesystem::IFile* openFile(const tc::filesystem::Path& path, tc::filesystem::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::filesystem::FAM_CREATE)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access permissions");
				}
				if (path != mCurDir + tc::filesystem::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
				return nullptr;
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to create file
			sb_fs->openFile(tc::filesystem::Path("/a_dir/testfile"), tc::filesystem::FAM_CREATE);
			
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testOpenFile()
{
	std::cout << "[SandboxFileSystem] testOpenFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::filesystem::IFile* openFile(const tc::filesystem::Path& path, tc::filesystem::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::filesystem::FAM_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access permissions");
				}
				if (path != mCurDir + tc::filesystem::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
				return nullptr;
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to open file
			sb_fs->openFile(tc::filesystem::Path("/a_dir/testfile"), tc::filesystem::FAM_READ);
			
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testRemoveFile()
{
	std::cout << "[SandboxFileSystem] testRemoveFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void deleteFile(const tc::filesystem::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::filesystem::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
			}
		private:
			tc::filesystem::Path mCurDir;
		};
	
		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to delete file
			sb_fs->deleteFile(tc::filesystem::Path("/a_dir/testfile"));

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}


void testCreateDirectory()
{
	std::cout << "[SandboxFileSystem] testCreateDirectory : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void createDirectory(const tc::filesystem::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::filesystem::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to create directory
			sb_fs->createDirectory(tc::filesystem::Path("/a_dir/testdir/hey"));

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testRemoveDirectory()
{
	std::cout << "[SandboxFileSystem] testRemoveDirectory : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void removeDirectory(const tc::filesystem::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::filesystem::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to remove directory
			sb_fs->removeDirectory(tc::filesystem::Path("/a_dir/testdir/hey"));

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testGetDirectoryListing()
{
	std::cout << "[SandboxFileSystem] testGetDirectoryListing : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void getDirectoryInfo(const tc::filesystem::Path& path, tc::filesystem::DirectoryInfo& dir_info)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::filesystem::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}

				dir_info.setDirectoryPath(path);
				dir_info.setChildDirectoryList(std::vector<std::string>({ "dir0", "dir1", "dir2" }));
				dir_info.setChildFileList(std::vector<std::string>({ "file0", "file1" }));
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + testdir_path);

			// save sandbox dir info
			tc::filesystem::DirectoryInfo sb_dir_info;
			sb_fs->getDirectoryInfo(tc::filesystem::Path("/a_dir/testdir/hey"), sb_dir_info);

			// save real dir info
			tc::filesystem::DirectoryInfo real_dir_info;
			fs->getDirectoryInfo(dummyfs_curdir + tc::filesystem::Path("testdir/a_dir/testdir/hey"), real_dir_info);

			if (sb_dir_info.getChildFileList() != real_dir_info.getChildFileList())
			{
				throw tc::Exception("DummyFileSystem", "File list was not as expected");
			}

			if (sb_dir_info.getChildDirectoryList() != real_dir_info.getChildDirectoryList())
			{
				throw tc::Exception("DummyFileSystem", "Directory list was not as expected");
			}

			std::vector<std::string> raw_sandbox_path;
			for (size_t i = 0; i < sb_dir_info.getDirectoryPath().getPathElementList().size(); i++)
			{
				if (sb_dir_info.getDirectoryPath().getPathElementList()[i] == "" && i == 0)
				{
					continue;
				}

				raw_sandbox_path.push_back(sb_dir_info.getDirectoryPath().getPathElementList()[i]);
			}

			tc::filesystem::Path fixed_sandbox_path;
			fixed_sandbox_path.setPathElementList(raw_sandbox_path);

			if ((dummyfs_curdir + testdir_path + fixed_sandbox_path) != real_dir_info.getDirectoryPath())
			{
				throw tc::Exception("DummyFileSystem", "Directory path was not as expected");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}


void testNavigateUpSandboxEscape()
{
	std::cout << "[SandboxFileSystem] testNavigateUpSandboxEscape : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void getDirectoryInfo(const tc::filesystem::Path& path, tc::filesystem::DirectoryInfo& dir_info)
			{			
				dir_info.setDirectoryPath(path);
				mLastUsedPath = path;
			}

			const tc::filesystem::Path& getLastUsedPath()
			{
				return mLastUsedPath;
			}

		private:
			tc::filesystem::Path mLastUsedPath;
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// save the current directory
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");
		tc::filesystem::Path sandbox_relative_root = testdir_path + tc::filesystem::Path("sandbox");

		// test navigating outside of sandbox with ".." navigation
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + sandbox_relative_root);

			// get info about current directory
			tc::filesystem::DirectoryInfo dir_info;
			sb_fs->getDirectoryInfo(tc::filesystem::Path("./../../../../../../../../../../../../../..///./././"), dir_info);
			
			if (dir_info.getDirectoryPath() != tc::filesystem::Path("/"))
			{
				throw tc::Exception("Sandbox directory path not as expected");
			}

			if (((DummyFileSystem*)fs.operator->())->getLastUsedPath() != dummyfs_curdir + sandbox_relative_root)
			{
				throw tc::Exception("Real directory path not as expected");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testOpenFileOutsideSandbox()
{
	std::cout << "[SandboxFileSystem] testOpenFileOutsideSandbox : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::filesystem::IFile* openFile(const tc::filesystem::Path& path, tc::filesystem::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::filesystem::FAM_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access mode");
				}
				if (path == tc::filesystem::Path("/home/jakcron/source/LibToolChain/testdir/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "escaped sandbox");
				}
				if (path != tc::filesystem::Path("/home/jakcron/source/LibToolChain/testdir/sandbox/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "sandbox path was not as expected");
				}
				return nullptr;
			}
		private:
			tc::filesystem::Path mCurDir;
		};

		tc::SharedPtr<tc::filesystem::IFileSystem> fs = new DummyFileSystem();

		// save the current directory
		tc::filesystem::Path dummyfs_curdir = tc::filesystem::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::filesystem::Path testdir_path = tc::filesystem::Path("testdir");
		tc::filesystem::Path sandbox_relative_root = testdir_path + tc::filesystem::Path("sandbox");

		// test accessing file outside of sandbox
		try {
			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFileSystem> sb_fs = new tc::filesystem::SandboxFileSystem(fs, dummyfs_curdir + sandbox_relative_root);
			  
			// try to open the file just outside the sandbox
			sb_fs->setCurrentDirectory(tc::filesystem::Path("/"));
			tc::SharedPtr<tc::filesystem::IFile> inacessible_file = sb_fs->openFile(tc::filesystem::Path("../inaccessible_file0"), tc::filesystem::FAM_READ);

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

int main(int argc, char** argv)
{
	testSandboxRootPath();
	testCreateFile();
	testOpenFile();
	testRemoveFile();
	testCreateDirectory();
	testRemoveDirectory();
	testGetDirectoryListing();
	testNavigateUpSandboxEscape();
	testOpenFileOutsideSandbox();
}