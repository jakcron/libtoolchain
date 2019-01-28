#include <tc/Exception.h>
#include <iostream>

#include "fs_SandboxedIFileSystem_TestClass.h"


void fs_SandboxedIFileSystem_TestClass::testSandboxRootPath()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testSandboxRootPath : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");
		tc::fs::Path sandbox_relative_root = testdir_path + tc::fs::Path("sandbox");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + sandbox_relative_root);

			// save sandbox real path
			tc::fs::Path sandbox_real_root;
			sb_fs->setCurrentDirectory(tc::fs::Path("/"));
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

void fs_SandboxedIFileSystem_TestClass::testCreateFile()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testCreateFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::fs::FAM_CREATE)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access permissions");
				}
				if (path != mCurDir + tc::fs::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
				return nullptr;
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to create file
			sb_fs->openFile(tc::fs::Path("/a_dir/testfile"), tc::fs::FAM_CREATE);
			
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

void fs_SandboxedIFileSystem_TestClass::testOpenFile()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testOpenFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::fs::FAM_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access permissions");
				}
				if (path != mCurDir + tc::fs::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
				return nullptr;
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to open file
			sb_fs->openFile(tc::fs::Path("/a_dir/testfile"), tc::fs::FAM_READ);
			
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

void fs_SandboxedIFileSystem_TestClass::testRemoveFile()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testRemoveFile : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void deleteFile(const tc::fs::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::fs::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
			}
		private:
			tc::fs::Path mCurDir;
		};
	
		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to delete file
			sb_fs->deleteFile(tc::fs::Path("/a_dir/testfile"));

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


void fs_SandboxedIFileSystem_TestClass::testCreateDirectory()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testCreateDirectory : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void createDirectory(const tc::fs::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::fs::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to create directory
			sb_fs->createDirectory(tc::fs::Path("/a_dir/testdir/hey"));

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

void fs_SandboxedIFileSystem_TestClass::testdeleteDirectory()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testdeleteDirectory : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void deleteDirectory(const tc::fs::Path& path)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::fs::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// attempt to remove directory
			sb_fs->deleteDirectory(tc::fs::Path("/a_dir/testdir/hey"));

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

void fs_SandboxedIFileSystem_TestClass::testGetDirectoryListing()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testGetDirectoryListing : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& dir_info)
			{
				getCurrentDirectory(mCurDir);
				if (path != mCurDir + tc::fs::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}

				dir_info.setPath(path);
				dir_info.setDirectoryList(std::vector<std::string>({ "dir0", "dir1", "dir2" }));
				dir_info.setFileList(std::vector<std::string>({ "file0", "file1" }));
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// define directory names
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");
		tc::fs::Path testdir_path = tc::fs::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + testdir_path);

			// save sandbox dir info
			tc::fs::DirectoryInfo sb_dir_info;
			sb_fs->getDirectoryListing(tc::fs::Path("/a_dir/testdir/hey"), sb_dir_info);

			// save real dir info
			tc::fs::DirectoryInfo real_dir_info;
			fs->getDirectoryListing(dummyfs_curdir + tc::fs::Path("testdir/a_dir/testdir/hey"), real_dir_info);

			if (sb_dir_info.getFileList() != real_dir_info.getFileList())
			{
				throw tc::Exception("DummyFileSystem", "File list was not as expected");
			}

			if (sb_dir_info.getDirectoryList() != real_dir_info.getDirectoryList())
			{
				throw tc::Exception("DummyFileSystem", "Directory list was not as expected");
			}

			std::vector<std::string> raw_sandbox_path;
			for (size_t i = 0; i < sb_dir_info.getPath().getPathElementList().size(); i++)
			{
				if (sb_dir_info.getPath().getPathElementList()[i] == "" && i == 0)
				{
					continue;
				}

				raw_sandbox_path.push_back(sb_dir_info.getPath().getPathElementList()[i]);
			}

			tc::fs::Path fixed_sandbox_path;
			fixed_sandbox_path.setPathElementList(raw_sandbox_path);

			if ((dummyfs_curdir + testdir_path + fixed_sandbox_path) != real_dir_info.getPath())
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


void fs_SandboxedIFileSystem_TestClass::testNavigateUpSandboxEscape()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testNavigateUpSandboxEscape : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& dir_info)
			{			
				dir_info.setPath(path);
				mLastUsedPath = path;
			}

			const tc::fs::Path& getLastUsedPath()
			{
				return mLastUsedPath;
			}

		private:
			tc::fs::Path mLastUsedPath;
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// save the current directory
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::fs::Path testdir_path = tc::fs::Path("testdir");
		tc::fs::Path sandbox_relative_root = testdir_path + tc::fs::Path("sandbox");

		// test navigating outside of sandbox with ".." navigation
		try
		{
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + sandbox_relative_root);

			// get info about current directory
			tc::fs::DirectoryInfo dir_info;
			sb_fs->getDirectoryListing(tc::fs::Path("./../../../../../../../../../../../../../..///./././"), dir_info);
			
			if (dir_info.getPath() != tc::fs::Path("/"))
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

void fs_SandboxedIFileSystem_TestClass::testOpenFileOutsideSandbox()
{
	std::cout << "[tc::fs::SandboxedIFileSystem] testOpenFileOutsideSandbox : ";
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode)
			{
				getCurrentDirectory(mCurDir);
				if (mode != tc::fs::FAM_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access mode");
				}
				if (path == tc::fs::Path("/home/jakcron/source/LibToolChain/testdir/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "escaped sandbox");
				}
				if (path != tc::fs::Path("/home/jakcron/source/LibToolChain/testdir/sandbox/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "sandbox path was not as expected");
				}
				return nullptr;
			}
		private:
			tc::fs::Path mCurDir;
		};

		tc::SharedPtr<tc::fs::IFileSystem> fs = new DummyFileSystem();

		// save the current directory
		tc::fs::Path dummyfs_curdir = tc::fs::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::fs::Path testdir_path = tc::fs::Path("testdir");
		tc::fs::Path sandbox_relative_root = testdir_path + tc::fs::Path("sandbox");

		// test accessing file outside of sandbox
		try {
			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFileSystem> sb_fs = new tc::fs::SandboxedIFileSystem(fs, dummyfs_curdir + sandbox_relative_root);
			  
			// try to open the file just outside the sandbox
			sb_fs->setCurrentDirectory(tc::fs::Path("/"));
			tc::SharedPtr<tc::fs::IFile> inacessible_file = sb_fs->openFile(tc::fs::Path("../inaccessible_file0"), tc::fs::FAM_READ);

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

void fs_SandboxedIFileSystem_TestClass::runAllTests(void)
{
	testSandboxRootPath();
	testCreateFile();
	testOpenFile();
	testRemoveFile();
	testCreateDirectory();
	testdeleteDirectory();
	testGetDirectoryListing();
	testNavigateUpSandboxEscape();
	testOpenFileOutsideSandbox();
}