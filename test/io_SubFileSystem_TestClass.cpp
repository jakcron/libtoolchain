#include <tc/Exception.h>
#include <iostream>

#include "io_SubFileSystem_TestClass.h"

const std::string io_SubFileSystem_TestClass::DummyFileSystemBase::kClassName = "DummyFileSystemBase";

void io_SubFileSystem_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::SubFileSystem] START" << std::endl;
	testSandboxRootPath();
	testCreateFile();
	testOpenFile();
	testRemoveFile();
	testCreateDirectory();
	testRemoveDirectory();
	testGetDirectoryListing();
	testNavigateUpSandboxEscape();
	testOpenFileOutsideSandbox();
	std::cout << "[tc::io::SubFileSystem] END" << std::endl;
}

void io_SubFileSystem_TestClass::testSandboxRootPath()
{
	std::cout << "[tc::io::SubFileSystem] testSandboxRootPath : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sandbox_relative_root = testdir_path + tc::io::Path("sandbox");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + sandbox_relative_root);

			// save sandbox real path
			tc::io::Path sandbox_real_root;
			sb_fs.setWorkingDirectory(tc::io::Path("/"));
			fs.getWorkingDirectory(sandbox_real_root);

			// check the sandbox is generating the correct path
			if (sandbox_real_root != dummyio_curdir + sandbox_relative_root)
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

void io_SubFileSystem_TestClass::testCreateFile()
{
	std::cout << "[tc::io::SubFileSystem] testCreateFile : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void createFile(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// attempt to create file
			sb_fs.createFile(tc::io::Path("/a_dir/testfile"));
			
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

void io_SubFileSystem_TestClass::testOpenFile()
{
	std::cout << "[tc::io::SubFileSystem] testOpenFile : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void openFile(const tc::io::Path& path, tc::io::FileAccessMode mode, std::shared_ptr<tc::io::IFileObject>& file)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (mode != tc::io::FILEACCESS_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access permissions");
				}
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// attempt to open file
			std::shared_ptr<tc::io::IFileObject> file;
			sb_fs.openFile(tc::io::Path("/a_dir/testfile"), tc::io::FILEACCESS_READ, file);
			
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

void io_SubFileSystem_TestClass::testRemoveFile()
{
	std::cout << "[tc::io::SubFileSystem] testRemoveFile : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void removeFile(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect path");
				}
			}
		};
	
		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// attempt to delete file
			sb_fs.removeFile(tc::io::Path("/a_dir/testfile"));

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


void io_SubFileSystem_TestClass::testCreateDirectory()
{
	std::cout << "[tc::io::SubFileSystem] testCreateDirectory : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void createDirectory(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// attempt to create directory
			sb_fs.createDirectory(tc::io::Path("/a_dir/testdir/hey"));

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

void io_SubFileSystem_TestClass::testRemoveDirectory()
{
	std::cout << "[tc::io::SubFileSystem] testRemoveDirectory : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void removeDirectory(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// attempt to remove directory
			sb_fs.removeDirectory(tc::io::Path("/a_dir/testdir/hey"));

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

void io_SubFileSystem_TestClass::testGetDirectoryListing()
{
	std::cout << "[tc::io::SubFileSystem] testGetDirectoryListing : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& dir_info)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyFileSystem", "dir had incorrect path");
				}

				dir_info.abs_path = path;
				dir_info.dir_list = std::vector<std::string>({ "dir0", "dir1", "dir2" });
				dir_info.file_list = std::vector<std::string>({ "file0", "file1" });
			}
		};

		DummyFileSystem fs;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test sandbox creation & test real sandbox root path
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + testdir_path);

			// save sandbox dir info
			tc::io::sDirectoryListing sb_dir_info;
			sb_fs.getDirectoryListing(tc::io::Path("/a_dir/testdir/hey"), sb_dir_info);

			// save real dir info
			tc::io::sDirectoryListing real_dir_info;
			fs.getDirectoryListing(dummyio_curdir + tc::io::Path("testdir/a_dir/testdir/hey"), real_dir_info);

			if (sb_dir_info.file_list != real_dir_info.file_list)
			{
				throw tc::Exception("DummyFileSystem", "File list was not as expected");
			}

			if (sb_dir_info.dir_list != real_dir_info.dir_list)
			{
				throw tc::Exception("DummyFileSystem", "Directory list was not as expected");
			}

			tc::io::Path fixed_sandbox_path;
			for (tc::io::Path::const_iterator itr = sb_dir_info.abs_path.begin(); itr != sb_dir_info.abs_path.end(); itr++)
			{
				if (*itr == "" && itr == sb_dir_info.abs_path.begin())
				{
					continue;
				}

				fixed_sandbox_path.push_back(*itr);
			}

			if ((dummyio_curdir + testdir_path + fixed_sandbox_path) != real_dir_info.abs_path)
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


void io_SubFileSystem_TestClass::testNavigateUpSandboxEscape()
{
	std::cout << "[tc::io::SubFileSystem] testNavigateUpSandboxEscape : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem() :
				mLastUsedPath(new tc::io::Path())
			{
			}

			void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& dir_info)
			{			
				dir_info.abs_path = path;
				*mLastUsedPath = path;
			}

			const tc::io::Path& getLastUsedPath()
			{
				return *mLastUsedPath;
			}
		private:
			std::shared_ptr<tc::io::Path> mLastUsedPath;
		};

		DummyFileSystem fs;

		// save the current directory
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sandbox_relative_root = testdir_path + tc::io::Path("sandbox");

		// test navigating outside of sandbox with ".." navigation
		try
		{
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + sandbox_relative_root);

			// get info about current directory
			tc::io::sDirectoryListing dir_info;
			sb_fs.getDirectoryListing(tc::io::Path("./../../../../../../../../../../../../../..///./././"), dir_info);
			
			if (dir_info.abs_path != tc::io::Path("/"))
			{
				throw tc::Exception("Sandbox directory path not as expected");
			}

			if (fs.getLastUsedPath() != dummyio_curdir + sandbox_relative_root)
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

void io_SubFileSystem_TestClass::testOpenFileOutsideSandbox()
{
	std::cout << "[tc::io::SubFileSystem] testOpenFileOutsideSandbox : " << std::flush;
	try
	{
		class DummyFileSystem : public DummyFileSystemBase
		{
		public:
			DummyFileSystem()
			{
			}

			void openFile(const tc::io::Path& path, tc::io::FileAccessMode mode, std::shared_ptr<tc::io::IFileObject>& file)
			{
				tc::io::Path mCurDir;
				getWorkingDirectory(mCurDir);
				if (mode != tc::io::FILEACCESS_READ)
				{
					throw tc::Exception("DummyFileSystem", "file had incorrect access mode");
				}
				if (path == tc::io::Path("/home/jakcron/source/LibToolChain/testdir/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "escaped sandbox");
				}
				if (path != tc::io::Path("/home/jakcron/source/LibToolChain/testdir/sandbox/inaccessible_file0"))
				{
					throw tc::Exception("DummyFileSystem", "sandbox path was not as expected");
				}
			}
		};

		DummyFileSystem fs;

		// save the current directory
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sandbox_relative_root = testdir_path + tc::io::Path("sandbox");

		// test accessing file outside of sandbox
		try {
			// get sandbox filesystem
			tc::io::SubFileSystem sb_fs(std::make_shared<DummyFileSystem>(fs), dummyio_curdir + sandbox_relative_root);
			  
			// try to open the file just outside the sandbox
			sb_fs.setWorkingDirectory(tc::io::Path("/"));
			std::shared_ptr<tc::io::IFileObject> inaccessible_file;
			sb_fs.openFile(tc::io::Path("../inaccessible_file0"), tc::io::FILEACCESS_READ, inaccessible_file);

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