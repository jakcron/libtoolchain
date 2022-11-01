#include "io_LocalFileSystem_TestClass.h"

#include <fmt/format.h>

#include <tc/io/LocalFileSystem.h>

#include <vector>
#include <algorithm>

//---------------------------------------------------------

std::string io_LocalFileSystem_TestClass::kDirPath = "./testdir";
std::string io_LocalFileSystem_TestClass::kUtf8DirPath = "./ЀЁЂЃЄЅテスト/";
std::string io_LocalFileSystem_TestClass::kAsciiFilePath = "LocalFileTest.bin";
std::string io_LocalFileSystem_TestClass::kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
std::string io_LocalFileSystem_TestClass::kNotExistFilePath = "ThisDoesNotExist.bin";

//---------------------------------------------------------

io_LocalFileSystem_TestClass::io_LocalFileSystem_TestClass() :
	mTestTag("tc::io::LocalFileSystem"),
	mTestResults()
{
}

void io_LocalFileSystem_TestClass::runAllTests(void)
{
	test_CreateFile_NotExist();
	test_CreateFile_DoesExist();
	test_CreateFile_UnicodePath();
	test_RemoveFile_DoesExist();
	test_RemoveFile_NotExist();
	test_RemoveFile_UnicodePath();
	
	test_CreateDirectory_NotExist();
	test_CreateDirectory_DoesExist();
	test_CreateDirectory_UnicodePath();
	test_RemoveDirectory_DoesExist();
	test_RemoveDirectory_NotExist();
	test_RemoveDirectory_UnicodePath();
	test_RemoveDirectory_HasChildren();
	test_RemoveDirectory_NotDirectoryActuallyFile();

	test_GetDirectoryListing_DoesExist();
	test_GetDirectoryListing_NotExist();
	test_GetDirectoryListing_UnicodePath();
	test_ChangeWorkingDirectory_DoesExist();
	test_ChangeWorkingDirectory_NotExist();
	test_ChangeWorkingDirectory_UnicodePath();

	test_CreateDirectoryPath_NotExist();
	test_CreateDirectoryPath_DoesExist();
	test_CreateDirectoryPath_UnicodePath();
}

const std::string& io_LocalFileSystem_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_LocalFileSystem_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_LocalFileSystem_TestClass::test_CreateFile_NotExist()
{
	TestResult test;
	test.test_name = "test_CreateFile_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createFile(kAsciiFilePath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateFile_DoesExist()
{
	TestResult test;
	test.test_name = "test_CreateFile_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createFile(kAsciiFilePath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateFile_UnicodePath()
{
	TestResult test;
	test.test_name = "test_CreateFile_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createFile(kUtf8TestPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveFile_DoesExist()
{
	TestResult test;
	test.test_name = "test_RemoveFile_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.removeFile(kAsciiFilePath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveFile_NotExist()
{
	TestResult test;
	test.test_name = "test_RemoveFile_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		try
		{
			local_fs.removeFile(kNotExistFilePath);

			throw tc::TestException(".removeFile() with path that does not exist did not throw tc::io::FileNotFoundException");
		}
		catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".removeFile() with path that does not exist threw the wrong exception ({:s})", e.what()));
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveFile_UnicodePath()
{
	TestResult test;
	test.test_name = "test_RemoveFile_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.removeFile(kUtf8TestPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectory_NotExist()
{
	TestResult test;
	test.test_name = "test_CreateDirectory_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createDirectory(kDirPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectory_DoesExist()
{
	TestResult test;
	test.test_name = "test_CreateDirectory_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createDirectory(kDirPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectory_UnicodePath()
{
	TestResult test;
	test.test_name = "test_CreateDirectory_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.createDirectory(kUtf8DirPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveDirectory_DoesExist()
{
	TestResult test;
	test.test_name = "test_RemoveDirectory_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.removeDirectory(kDirPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveDirectory_NotExist()
{
	TestResult test;
	test.test_name = "test_RemoveDirectory_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		try
		{
			local_fs.removeDirectory(kDirPath);

			throw tc::TestException(".removeDirectory() with path that does not exist did not throw tc::io::DirectoryNotFoundException");
		}
		catch (const tc::io::DirectoryNotFoundException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".removeDirectory() with path that does not exist threw the wrong exception ({:s})", e.what()));
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveDirectory_UnicodePath()
{
	TestResult test;
	test.test_name = "test_RemoveDirectory_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		local_fs.removeDirectory(kUtf8DirPath);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_RemoveDirectory_HasChildren()
{
	TestResult test;
	test.test_name = "test_RemoveDirectory_HasChildren";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;

		// env setup
		tc::io::Path dir_child_path = tc::io::Path(kDirPath) + tc::io::Path(kUtf8DirPath);
		tc::io::Path stream_child_path = tc::io::Path(kDirPath) + tc::io::Path(kAsciiFilePath);

		local_fs.createDirectory(kDirPath);
		local_fs.createDirectory(dir_child_path);
		local_fs.createFile(stream_child_path);

		// test
		try
		{
			try
			{
				local_fs.removeDirectory(kDirPath);

				throw tc::TestException(".removeDirectory() with path to a directory not empty did not throw tc::io::DirectoryNotEmptyException");
			}
			catch (const tc::io::DirectoryNotEmptyException&) { /* do nothing */ }
			catch (const tc::Exception& e) 
			{
				throw tc::TestException(fmt::format(".removeDirectory() with path to a directory not empty threw the wrong exception ({:s})", e.what()));
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// env teardown
		local_fs.removeDirectory(dir_child_path);
		local_fs.removeFile(stream_child_path);
		local_fs.removeDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));

}

void io_LocalFileSystem_TestClass::test_RemoveDirectory_NotDirectoryActuallyFile()
{
	TestResult test;
	test.test_name = "test_RemoveDirectory_NotDirectoryActuallyFile";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;

		// env setup
		local_fs.createFile(kAsciiFilePath);

		// test
		try
		{
			try
			{
				local_fs.removeDirectory(kAsciiFilePath);

				throw tc::TestException(".removeDirectory() with path to a file did not throw tc::io::DirectoryNotFoundException");
			}
			catch (const tc::io::DirectoryNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e) 
			{
				throw tc::TestException(fmt::format(".removeDirectory() with path to a file threw the wrong exception ({:s})", e.what()));
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// env teardown
		local_fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_GetDirectoryListing_DoesExist()
{
	TestResult test;
	test.test_name = "test_GetDirectoryListing_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;

		// env setup
		std::vector<std::string> file_list;
		std::vector<std::string> dir_list;
		
		file_list.push_back("streamA.bin");
		file_list.push_back("streamB.bin");
		file_list.push_back("streamC.bin");
		file_list.push_back("streamD.bin");

		dir_list.push_back("dir000");
		dir_list.push_back("dir001");
		dir_list.push_back("dir002");
		dir_list.push_back("dir003");

		local_fs.createDirectory(kDirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_fs.createFile(tc::io::Path(kDirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_fs.createDirectory(tc::io::Path(kDirPath) + tc::io::Path(dir_list[i]));
		}

		// test
		try
		{
			tc::io::sDirectoryListing info;

			local_fs.getDirectoryListing(kDirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::TestException("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::TestException("Unexpected stream count");
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// env teardown
		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_fs.removeFile(tc::io::Path(kDirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_fs.removeDirectory(tc::io::Path(kDirPath) + tc::io::Path(dir_list[i]));
		}

		local_fs.removeDirectory(tc::io::Path(kDirPath));
	
		
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_GetDirectoryListing_NotExist()
{
	TestResult test;
	test.test_name = "test_GetDirectoryListing_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;
		tc::io::sDirectoryListing info;

		try 
		{
			local_fs.getDirectoryListing(kNotExistFilePath, info);

			throw tc::TestException(".getDirectoryListing() with invalid path did not throw tc::io::DirectoryNotFoundException");
		}
		catch (const tc::io::DirectoryNotFoundException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".getDirectoryListing() with invalid path threw the wrong exception ({:s})", e.what()));
		}
	
		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_GetDirectoryListing_UnicodePath()
{
	TestResult test;
	test.test_name = "test_GetDirectoryListing_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;

		// env setup
		std::vector<std::string> file_list;
		std::vector<std::string> dir_list;
		
		file_list.push_back("streamA.bin");
		file_list.push_back("streamB.bin");
		file_list.push_back("streamC.bin");
		file_list.push_back("streamD.bin");

		dir_list.push_back("dir000");
		dir_list.push_back("dir001");
		dir_list.push_back("dir002");
		dir_list.push_back("dir003");

		local_fs.createDirectory(kUtf8DirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_fs.createFile(tc::io::Path(kUtf8DirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_fs.createDirectory(tc::io::Path(kUtf8DirPath) + tc::io::Path(dir_list[i]));
		}

		// test
		try
		{
			tc::io::sDirectoryListing info;

			local_fs.getDirectoryListing(kUtf8DirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::TestException("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::TestException("Unexpected stream count");
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// env teardown
		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_fs.removeFile(tc::io::Path(kUtf8DirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_fs.removeDirectory(tc::io::Path(kUtf8DirPath) + tc::io::Path(dir_list[i]));
		}

		local_fs.removeDirectory(tc::io::Path(kUtf8DirPath));
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_DoesExist()
{
	TestResult test;
	test.test_name = "test_ChangeWorkingDirectory_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;
		
		// setup env
		tc::io::Path old_dir;
		local_fs.getWorkingDirectory(old_dir);
		local_fs.createDirectory(kDirPath);

		// test
		try 
		{
			local_fs.setWorkingDirectory(kDirPath);

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// teardown env
		local_fs.setWorkingDirectory(old_dir);
		local_fs.removeDirectory(tc::io::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_NotExist()
{
	TestResult test;
	test.test_name = "test_ChangeWorkingDirectory_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;
		
		try 
		{
			local_fs.setWorkingDirectory(kNotExistFilePath);

			throw tc::TestException(".setWorkingDirectory() with invalid path did not throw tc::io::DirectoryNotFoundException");
		}
		catch (const tc::io::DirectoryNotFoundException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(fmt::format(".setWorkingDirectory() with invalid path threw the wrong exception ({:s})", e.what()));
		}
	
		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::Exception& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.error();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_UnicodePath()
{
	TestResult test;
	test.test_name = "test_ChangeWorkingDirectory_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_fs;
		
		// env setup
		tc::io::Path old_dir;
		local_fs.getWorkingDirectory(old_dir);
		local_fs.createDirectory(kUtf8DirPath);

		// test
		try
		{
			local_fs.setWorkingDirectory(kUtf8DirPath);

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// env teardown
		local_fs.setWorkingDirectory(old_dir);
		local_fs.removeDirectory(kUtf8DirPath);
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectoryPath_NotExist()
{
	TestResult test;
	test.test_name = "test_CreateDirectoryPath_NotExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		std::string long_dir_path = "./a/path/with///./many/elements/../hey/../oi";
		std::vector<std::string> created_dir_paths = {"./a/path/with/many/elements", "./a/path/with/many/hey", "./a/path/with/many/oi", "./a/path/with/many", "./a/path/with", "./a/path", "./a"};

		
		// because this test requires cleanup, we want to still attempt a cleanup even if a test fails
		try
		{
			// create directory path
			try 
			{
				local_fs.createDirectoryPath(long_dir_path);
			}
			catch (const tc::Exception& e)
			{
				throw tc::TestException(fmt::format("Failed to create directory path (error: {:s})", e.what()));
			}
			

			// confirm directories were created
			tc::io::sDirectoryListing tmp_dir_listing;
			for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
			{
				try
				{
					local_fs.getDirectoryListing(*itr, tmp_dir_listing);
				}
				catch (const tc::io::DirectoryNotFoundException&)
				{
					// test failed!
					throw tc::TestException(fmt::format("Directory was not created: \"{:s}\"", *itr));
				}
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// cleanup created directories
		for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
		{
			try
			{
				local_fs.removeDirectory(*itr);
			}
			catch (const tc::io::DirectoryNotFoundException&)
			{
				// ignore where directories were not created 
			}
			
		}
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectoryPath_DoesExist()
{
	TestResult test;
	test.test_name = "test_CreateDirectoryPath_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		std::string long_dir_path = "./a/path/with///./many/elements/../hey/../oi";
		std::vector<std::string> created_dir_paths = {"./a/path/with/many/elements", "./a/path/with/many/hey", "./a/path/with/many/oi", "./a/path/with/many", "./a/path/with", "./a/path", "./a"};

		
		// create directories
		std::vector<std::string> dir_create_order = created_dir_paths;
		std::reverse(dir_create_order.begin(), dir_create_order.end());
		for (auto itr = dir_create_order.begin(); itr != dir_create_order.end(); itr++)
		{
			local_fs.createDirectory(*itr);
		}

		// because this test requires cleanup, we want to still attempt a cleanup even if a test fails
		try
		{
			// create directory path
			try 
			{
				local_fs.createDirectoryPath(long_dir_path);
			}
			catch (const tc::Exception& e)
			{
				throw tc::TestException(fmt::format("Failed to create directory path (error: {:s})", e.what()));
			}
			

			// confirm directories were created
			tc::io::sDirectoryListing tmp_dir_listing;
			for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
			{
				try
				{
					local_fs.getDirectoryListing(*itr, tmp_dir_listing);
				}
				catch (const tc::io::DirectoryNotFoundException&)
				{
					// test failed!
					throw tc::TestException(fmt::format("Directory was not created: \"{:s}\"", *itr));
				}
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// cleanup created directories
		for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
		{
			try
			{
				local_fs.removeDirectory(*itr);
			}
			catch (const tc::io::DirectoryNotFoundException&)
			{
				// ignore where directories were not created 
			}
			
		}
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_LocalFileSystem_TestClass::test_CreateDirectoryPath_UnicodePath()
{
	TestResult test;
	test.test_name = "test_CreateDirectoryPath_UnicodePath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_fs;

		std::string long_dir_path = "./ЀЁЂЃЄЅ/מבחן/тест///./テスト/පරීක්ෂණය/../测试/../ਟੈਸਟ";
		std::vector<std::string> created_dir_paths = {"./ЀЁЂЃЄЅ/מבחן/тест/テスト/පරීක්ෂණය", "./ЀЁЂЃЄЅ/מבחן/тест/テスト/测试", "./ЀЁЂЃЄЅ/מבחן/тест/テスト/ਟੈਸਟ", "./ЀЁЂЃЄЅ/מבחן/тест/テスト", "./ЀЁЂЃЄЅ/מבחן/тест", "./ЀЁЂЃЄЅ/מבחן", "./ЀЁЂЃЄЅ"};

		
		// because this test requires cleanup, we want to still attempt a cleanup even if a test fails
		try
		{
			// create directory path
			try 
			{
				local_fs.createDirectoryPath(long_dir_path);
			}
			catch (const tc::Exception& e)
			{
				throw tc::TestException(fmt::format("Failed to create directory path (error: {:s})", e.what()));
			}
			

			// confirm directories were created
			tc::io::sDirectoryListing tmp_dir_listing;
			for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
			{
				try
				{
					local_fs.getDirectoryListing(*itr, tmp_dir_listing);
				}
				catch (const tc::io::DirectoryNotFoundException&)
				{
					// test failed!
					throw tc::TestException(fmt::format("Directory was not created: \"{:s}\"", *itr));
				}
			}

			// record result
			test.result = "PASS";
			test.comments = "";
		}
		catch (const tc::TestException& e)
		{
			// record result
			test.result = "FAIL";
			test.comments = e.what();
		}

		// cleanup created directories
		for (auto itr = created_dir_paths.begin(); itr != created_dir_paths.end(); itr++)
		{
			try
			{
				local_fs.removeDirectory(*itr);
			}
			catch (const tc::io::DirectoryNotFoundException&)
			{
				// ignore where directories were not created 
			}
			
		}
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}