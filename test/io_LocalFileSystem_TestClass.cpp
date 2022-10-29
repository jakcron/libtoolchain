#include "io_LocalFileSystem_TestClass.h"

#include <fmt/format.h>

#include <tc/io/LocalFileSystem.h>

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
	test_CreateDirectoryPath();

	test_GetDirectoryListing_DoesExist();
	test_GetDirectoryListing_NotExist();
	test_GetDirectoryListing_UnicodePath();
	test_ChangeWorkingDirectory_DoesExist();
	test_ChangeWorkingDirectory_NotExist();
	test_ChangeWorkingDirectory_UnicodePath();
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
		tc::io::LocalFileSystem local_storage;

		local_storage.createFile(kAsciiFilePath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.createFile(kAsciiFilePath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.createFile(kUtf8TestPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.removeFile(kAsciiFilePath);

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
		tc::io::LocalFileSystem local_storage;

		try
		{
			local_storage.removeFile(kNotExistFilePath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.removeFile(kUtf8TestPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.createDirectory(kDirPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.createDirectory(kDirPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.createDirectory(kUtf8DirPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.removeDirectory(kDirPath);

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
		tc::io::LocalFileSystem local_storage;

		try
		{
			local_storage.removeDirectory(kDirPath);

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
		tc::io::LocalFileSystem local_storage;

		local_storage.removeDirectory(kUtf8DirPath);

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
		tc::io::LocalFileSystem local_storage;

		// env setup
		tc::io::Path dir_child_path = tc::io::Path(kDirPath) + tc::io::Path(kUtf8DirPath);
		tc::io::Path stream_child_path = tc::io::Path(kDirPath) + tc::io::Path(kAsciiFilePath);

		local_storage.createDirectory(kDirPath);
		local_storage.createDirectory(dir_child_path);
		local_storage.createFile(stream_child_path);

		// test
		try
		{
			try
			{
				local_storage.removeDirectory(kDirPath);

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
		local_storage.removeDirectory(dir_child_path);
		local_storage.removeFile(stream_child_path);
		local_storage.removeDirectory(kDirPath);
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
		tc::io::LocalFileSystem local_storage;

		// env setup
		local_storage.createFile(kAsciiFilePath);

		// test
		try
		{
			try
			{
				local_storage.removeDirectory(kAsciiFilePath);

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
		local_storage.removeFile(kAsciiFilePath);
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

void io_LocalFileSystem_TestClass::test_CreateDirectoryPath()
{
	TestResult test;
	test.test_name = "test_CreateDirectoryPath";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::io::LocalFileSystem local_storage;

		// create directory path
		std::string long_dir_path = "./a/path/with///./many/elements/../hey/../oi";
		local_storage.createDirectoryPath(long_dir_path);

		// cleanup created directories
		std::vector<std::string> remove_dir_paths = {"./a/path/with/many/elements", "./a/path/with/many/hey", "./a/path/with/many/oi", "./a/path/with/many", "./a/path/with", "./a/path", "./a"};
		for (auto itr = remove_dir_paths.begin(); itr != remove_dir_paths.end(); itr++)
		{
			local_storage.removeDirectory(*itr);
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

void io_LocalFileSystem_TestClass::test_GetDirectoryListing_DoesExist()
{
	TestResult test;
	test.test_name = "test_GetDirectoryListing_DoesExist";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::LocalFileSystem local_storage;

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

		local_storage.createDirectory(kDirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_storage.createFile(tc::io::Path(kDirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_storage.createDirectory(tc::io::Path(kDirPath) + tc::io::Path(dir_list[i]));
		}

		// test
		try
		{
			tc::io::sDirectoryListing info;

			local_storage.getDirectoryListing(kDirPath, info);
			
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
			local_storage.removeFile(tc::io::Path(kDirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_storage.removeDirectory(tc::io::Path(kDirPath) + tc::io::Path(dir_list[i]));
		}

		local_storage.removeDirectory(tc::io::Path(kDirPath));
	
		
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
		tc::io::LocalFileSystem local_storage;
		tc::io::sDirectoryListing info;

		try 
		{
			local_storage.getDirectoryListing(kNotExistFilePath, info);

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
		tc::io::LocalFileSystem local_storage;

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

		local_storage.createDirectory(kUtf8DirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			local_storage.createFile(tc::io::Path(kUtf8DirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_storage.createDirectory(tc::io::Path(kUtf8DirPath) + tc::io::Path(dir_list[i]));
		}

		// test
		try
		{
			tc::io::sDirectoryListing info;

			local_storage.getDirectoryListing(kUtf8DirPath, info);
			
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
			local_storage.removeFile(tc::io::Path(kUtf8DirPath) + tc::io::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			local_storage.removeDirectory(tc::io::Path(kUtf8DirPath) + tc::io::Path(dir_list[i]));
		}

		local_storage.removeDirectory(tc::io::Path(kUtf8DirPath));
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
		tc::io::LocalFileSystem local_storage;
		
		// setup env
		tc::io::Path old_dir;
		local_storage.getWorkingDirectory(old_dir);
		local_storage.createDirectory(kDirPath);

		// test
		try 
		{
			local_storage.setWorkingDirectory(kDirPath);

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
		local_storage.setWorkingDirectory(old_dir);
		local_storage.removeDirectory(tc::io::Path(kDirPath));
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
		tc::io::LocalFileSystem local_storage;
		
		try 
		{
			local_storage.setWorkingDirectory(kNotExistFilePath);

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
		tc::io::LocalFileSystem local_storage;
		
		// env setup
		tc::io::Path old_dir;
		local_storage.getWorkingDirectory(old_dir);
		local_storage.createDirectory(kUtf8DirPath);

		// test
		try
		{
			local_storage.setWorkingDirectory(kUtf8DirPath);

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
		local_storage.setWorkingDirectory(old_dir);
		local_storage.removeDirectory(kUtf8DirPath);
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