#include <tc/Exception.h>
#include <iostream>

#include "io_SubFileSystem_TestClass.h"
#include "FileSystemTestUtil.h"

void io_SubFileSystem_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::SubFileSystem] START" << std::endl;
	testSubFileSystemRootPath();
	testCreateFile();
	testOpenFile();
	testRemoveFile();
	testCreateDirectory();
	testRemoveDirectory();
	testGetDirectoryListing();
	testNavigateUpSubFileSystemEscape();
	testOpenFileOutsideSubFileSystem();
	std::cout << "[tc::io::SubFileSystem] END" << std::endl;
}

void io_SubFileSystem_TestClass::testSubFileSystemRootPath()
{
	std::cout << "[tc::io::SubFileSystem] testSubFileSystemRootPath : " << std::flush;
	try
	{
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sub_storage_relative_root = testdir_path + tc::io::Path("substorage");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + sub_storage_relative_root);

			// save substorage real path
			tc::io::Path sub_storage_real_root;
			sub_storage.setWorkingDirectory(tc::io::Path("/"));
			storage.getWorkingDirectory(sub_storage_real_root);

			// check the substorage is generating the correct path
			if (sub_storage_real_root != dummyio_curdir + sub_storage_relative_root)
			{
				throw tc::Exception("SubFileSystem root directory did not have expected absolute real path");
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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void createFile(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyStorage", "file had incorrect path");
				}
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// attempt to create file
			sub_storage.createFile(tc::io::Path("/a_dir/testfile"));
			
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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (mode != tc::io::FileMode::Open || access != tc::io::FileAccess::Read)
				{
					throw tc::Exception("DummyStorage", "file had incorrect access permissions");
				}
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyStorage", "file had incorrect path");
				}
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// attempt to open file
			std::shared_ptr<tc::io::IStream> file;
			sub_storage.openFile(tc::io::Path("/a_dir/testfile"), tc::io::FileMode::Open, tc::io::FileAccess::Read, file);
			
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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void removeFile(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testfile"))
				{
					throw tc::Exception("DummyStorage", "file had incorrect path");
				}
			}
		};
	
		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// attempt to delete file
			sub_storage.removeFile(tc::io::Path("/a_dir/testfile"));

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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void createDirectory(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyStorage", "dir had incorrect path");
				}
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// attempt to create directory
			sub_storage.createDirectory(tc::io::Path("/a_dir/testdir/hey"));

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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void removeDirectory(const tc::io::Path& path)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyStorage", "dir had incorrect path");
				}
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// attempt to remove directory
			sub_storage.removeDirectory(tc::io::Path("/a_dir/testdir/hey"));

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
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& dir_info)
			{
				tc::io::Path cur_dir;
				getWorkingDirectory(cur_dir);
				if (path != cur_dir + tc::io::Path("a_dir/testdir/hey"))
				{
					throw tc::Exception("DummyStorage", "dir had incorrect path");
				}

				dir_info.abs_path = path;
				dir_info.dir_list = std::vector<std::string>({ "dir0", "dir1", "dir2" });
				dir_info.file_list = std::vector<std::string>({ "file0", "file1" });
			}
		};

		DummyStorage storage;

		// define directory names
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");
		tc::io::Path testdir_path = tc::io::Path("testdir");

		// test substorage creation & test real substorage root path
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + testdir_path);

			// save substorage dir info
			tc::io::sDirectoryListing sb_dir_info;
			sub_storage.getDirectoryListing(tc::io::Path("/a_dir/testdir/hey"), sb_dir_info);

			// save real dir info
			tc::io::sDirectoryListing real_dir_info;
			storage.getDirectoryListing(dummyio_curdir + tc::io::Path("testdir/a_dir/testdir/hey"), real_dir_info);

			if (sb_dir_info.file_list != real_dir_info.file_list)
			{
				throw tc::Exception("DummyStorage", "File list was not as expected");
			}

			if (sb_dir_info.dir_list != real_dir_info.dir_list)
			{
				throw tc::Exception("DummyStorage", "Directory list was not as expected");
			}

			tc::io::Path fixed_sub_storage_path;
			for (tc::io::Path::const_iterator itr = sb_dir_info.abs_path.begin(); itr != sb_dir_info.abs_path.end(); itr++)
			{
				if (*itr == "" && itr == sb_dir_info.abs_path.begin())
				{
					continue;
				}

				fixed_sub_storage_path.push_back(*itr);
			}

			if ((dummyio_curdir + testdir_path + fixed_sub_storage_path) != real_dir_info.abs_path)
			{
				throw tc::Exception("DummyStorage", "Directory path was not as expected");
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


void io_SubFileSystem_TestClass::testNavigateUpSubFileSystemEscape()
{
	std::cout << "[tc::io::SubFileSystem] testNavigateUpSubFileSystemEscape : " << std::flush;
	try
	{
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage() :
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

		DummyStorage storage;

		// save the current directory
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sub_storage_relative_root = testdir_path + tc::io::Path("substorage");

		// test navigating outside of substorage with ".." navigation
		try
		{
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + sub_storage_relative_root);

			// get info about current directory
			tc::io::sDirectoryListing dir_info;
			sub_storage.getDirectoryListing(tc::io::Path("./../../../../../../../../../../../../../..///./././"), dir_info);
			
			if (dir_info.abs_path != tc::io::Path("/"))
			{
				throw tc::Exception("SubFileSystem directory path not as expected");
			}

			if (storage.getLastUsedPath() != dummyio_curdir + sub_storage_relative_root)
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

void io_SubFileSystem_TestClass::testOpenFileOutsideSubFileSystem()
{
	std::cout << "[tc::io::SubFileSystem] testOpenFileOutsideSubFileSystem : " << std::flush;
	try
	{
		class DummyStorage : public StorageTestUtil::DummyStorageBase
		{
		public:
			DummyStorage()
			{
			}

			void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream)
			{
				tc::io::Path mCurDir;
				getWorkingDirectory(mCurDir);
				if (mode != tc::io::FileMode::Open || access != tc::io::FileAccess::Read)
				{
					throw tc::Exception("DummyStorage", "file had incorrect access mode");
				}
				if (path == tc::io::Path("/home/jakcron/source/LibToolChain/testdir/inaccessible_file0"))
				{
					throw tc::Exception("DummyStorage", "escaped substorage");
				}
				if (path != tc::io::Path("/home/jakcron/source/LibToolChain/testdir/substorage/inaccessible_file0"))
				{
					throw tc::Exception("DummyStorage", "substorage path was not as expected");
				}
			}
		};

		DummyStorage storage;

		// save the current directory
		tc::io::Path dummyio_curdir = tc::io::Path("/home/jakcron/source/LibToolChain");

		// define directory names
		tc::io::Path testdir_path = tc::io::Path("testdir");
		tc::io::Path sub_storage_relative_root = testdir_path + tc::io::Path("substorage");

		// test accessing file outside of substorage
		try {
			// get substorage filesystem
			tc::io::SubFileSystem sub_storage(std::make_shared<DummyStorage>(storage), dummyio_curdir + sub_storage_relative_root);
			  
			// try to open the file just outside the substorage
			sub_storage.setWorkingDirectory(tc::io::Path("/"));
			std::shared_ptr<tc::io::IStream> inaccessible_file;
			sub_storage.openFile(tc::io::Path("../inaccessible_file0"), tc::io::FileMode::Open, tc::io::FileAccess::Read, inaccessible_file);

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