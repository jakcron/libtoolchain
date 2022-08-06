#include "io_FileStream_TestClass.h"
#include "StreamTestUtil.h"

#include <fstream>
#include <fmt/format.h>

#include <tc/io/LocalFileSystem.h>
#include <tc/io/FileStream.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

std::string io_FileStream_TestClass::kAsciiFilePath = "LocalFileTest.bin";
std::string io_FileStream_TestClass::kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
std::string io_FileStream_TestClass::kNotExistFilePath = "ThisDoesNotExist.bin";
std::string io_FileStream_TestClass::kTestPhrase = "Hello world!\n";
std::string io_FileStream_TestClass::kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";

//---------------------------------------------------------

io_FileStream_TestClass::io_FileStream_TestClass() :
	mTestTag("tc::io::FileStream"),
	mTestResults()
{
}

void io_FileStream_TestClass::runAllTests(void)
{
	test_DefaultConstructor();

	test_Constructor_CreateNew_Read_FileExists();
	test_Constructor_CreateNew_Read_FileNotExist();
	test_Constructor_CreateNew_Write_FileExists();
	test_Constructor_CreateNew_Write_FileNotExist();
	test_Constructor_CreateNew_ReadWrite_FileExists();
	test_Constructor_CreateNew_ReadWrite_FileNotExist();

	test_Constructor_Create_Read_FileExists();
	test_Constructor_Create_Read_FileNotExist();
	test_Constructor_Create_Write_FileExists();
	test_Constructor_Create_Write_FileNotExist();
	test_Constructor_Create_ReadWrite_FileExists();
	test_Constructor_Create_ReadWrite_FileNotExist();

	test_Constructor_Open_Read_FileExists();
	test_Constructor_Open_Read_FileNotExist();
	test_Constructor_Open_Write_FileExists();
	test_Constructor_Open_Write_FileNotExist();
	test_Constructor_Open_ReadWrite_FileExists();
	test_Constructor_Open_ReadWrite_FileNotExist();

	test_Constructor_OpenOrCreate_Read_FileExists();
	test_Constructor_OpenOrCreate_Read_FileNotExist();
	test_Constructor_OpenOrCreate_Write_FileExists();
	test_Constructor_OpenOrCreate_Write_FileNotExist();
	test_Constructor_OpenOrCreate_ReadWrite_FileExists();
	test_Constructor_OpenOrCreate_ReadWrite_FileNotExist();

	test_Constructor_Truncate_Read_FileExists();
	test_Constructor_Truncate_Read_FileNotExist();
	test_Constructor_Truncate_Write_FileExists();
	test_Constructor_Truncate_Write_FileNotExist();
	test_Constructor_Truncate_ReadWrite_FileExists();
	test_Constructor_Truncate_ReadWrite_FileNotExist();

	test_Constructor_Append_Read_FileExists();
	test_Constructor_Append_Read_FileNotExist();
	test_Constructor_Append_Write_FileExists();
	test_Constructor_Append_Write_FileNotExist();
	test_Constructor_Append_ReadWrite_FileExists();
	test_Constructor_Append_ReadWrite_FileNotExist();

	test_Constructor_IllegalMode();
	test_Constructor_IllegalAccess();

	test_Constructor_DirectoryPath();
	test_Constructor_CreateThenReopenFileWithUnicodePath();

	test_Seek_EmptyFile();
	test_Seek_CreatedFile();
	test_Seek_AppendMode();
	test_Seek_PositionBeforeFileBegin();
	test_Seek_PositionAfterFileEnd();

	test_Read_NoData();
	test_Read_SomeDataFromZero();
	test_Read_SomeDataFromMiddle();
	test_Read_AllData();
	test_Read_TooMuchData();
	test_Read_BeyondEnd();
	test_Read_CanReadFalse();
	test_Read_NullDstPointer();

	test_Write_NoData();
	test_Write_OverwriteSomeDataFromZero();
	test_Write_OverwriteSomeDataFromMiddle();
	test_Write_ExtendStreamSizeThruWritingDataFromZero();
	test_Write_ExtendStreamSizeThruWritingDataFromMiddle();
	test_Write_BeyondEnd();
	test_Write_CanWriteFalse();
	test_Write_NullSrcPointer();
}

const std::string& io_FileStream_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_FileStream_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_FileStream_TestClass::test_DefaultConstructor()
{
	TestResult test;
	test.test_name = "test_DefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream();

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, false, false);

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

// Constructor_CreateNew

void io_FileStream_TestClass::test_Constructor_CreateNew_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::CreateNew & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::CreateNew & FileAccess::Read) threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_CreateNew_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor when supplied invalid arg combination (FileMode::CreateNew & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor when supplied invalid arg combination (FileMode::CreateNew & FileAccess::Read) threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_CreateNew_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::Write);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
				
				throw tc::TestException("Attempting to (FileMode::CreateNew,FileAccess::Write) when the file already exists did not throw tc::io::FileExistsException");
			}
			catch (const tc::io::FileExistsException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::CreateNew,FileAccess::Write) when the file already exists threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_CreateNew_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_CreateNew_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::ReadWrite);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
				
				throw tc::TestException("Attempting to (FileMode::CreateNew,FileAccess::ReadWrite) when the file already exists did not throw tc::io::FileExistsException");
			}
			catch (const tc::io::FileExistsException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::CreateNew,FileAccess::ReadWrite) when the file already exists threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_CreateNew_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateNew_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);

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
		helper_DeleteFile(kAsciiFilePath);
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

// Constructor_Create

void io_FileStream_TestClass::test_Constructor_Create_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Create & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Create & FileAccess::Read) threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Create_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Create & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Create & FileAccess::Read) threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Create_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Create_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Create_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Create_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Create_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

// Constructor_Open

void io_FileStream_TestClass::test_Constructor_Open_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, true, false, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Open_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::Read) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::Read) when the file does not exist threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Open_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, false, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Open_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
				
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::Write) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::Write) when the file does not exist threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Open_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, true, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Open_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Open_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
				
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::ReadWrite) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::Open,FileAccess::ReadWrite) when the file does not exist threw the wrong exception");
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

// Constructor_OpenOrCreate

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::Read);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, true, false, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Attempting to (FileMode::OpenOrCreate,FileAccess::Read) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::OpenOrCreate,FileAccess::Read) when the file does not exist threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, false, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), 0, true, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_OpenOrCreate_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_OpenOrCreate_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

// Constructor_Truncate

void io_FileStream_TestClass::test_Constructor_Truncate_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Truncate & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Truncate & FileAccess::Read) threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Truncate_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::Read);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Truncate & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Truncate & FileAccess::Read) threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Truncate_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Truncate_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::Write);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, true);
				
				throw tc::TestException("Attempting to (FileMode::Truncate,FileAccess::Write) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::Truncate,FileAccess::Write) when the file does not exist threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Truncate_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::ReadWrite);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Truncate_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Truncate_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Truncate, tc::io::FileAccess::ReadWrite);

				StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);
				
				throw tc::TestException("Attempting to (FileMode::Truncate,FileAccess::ReadWrite) when the file does not exist did not throw tc::io::FileNotFoundException");
			}
			catch (const tc::io::FileNotFoundException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to (FileMode::Truncate,FileAccess::ReadWrite) when the file does not exist threw the wrong exception");
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

// Constructor_Append

void io_FileStream_TestClass::test_Constructor_Append_Read_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_Read_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::Read);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::Read) threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Append_Read_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_Read_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::Read);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::Read) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::Read) threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_Append_Write_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_Write_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, kRandomString.size(), kRandomString.size(), false, true, false);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Append_Write_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_Write_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::Write);

			StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, true, false);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Append_ReadWrite_FileExists()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_ReadWrite_FileExists";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.length());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::ReadWrite);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::ReadWrite) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::ReadWrite) threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_Append_ReadWrite_FileNotExist()
{
	TestResult test;
	test.test_name = "test_Constructor_Append_ReadWrite_FileNotExist";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::ReadWrite);
				
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::ReadWrite) did not throw tc::ArgumentException");
			}
			catch (const tc::ArgumentException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with invalid arg combination (FileMode::Append & FileAccess::ReadWrite) threw the wrong exception");
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

// illegal constructor args

void io_FileStream_TestClass::test_Constructor_IllegalMode()
{
	TestResult test;
	test.test_name = "test_Constructor_IllegalMode";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode(55), tc::io::FileAccess::ReadWrite);
				
				throw tc::TestException("Constructor with an unrecognised value for FileMode did not throw tc::ArgumentOutOfRangeException");
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with an unrecognised value for FileMode threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_IllegalAccess()
{
	TestResult test;
	test.test_name = "test_Constructor_IllegalAccess";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::CreateNew, tc::io::FileAccess(55));
				
				throw tc::TestException("Constructor with an unrecognised value for FileAccess did not throw tc::ArgumentOutOfRangeException");
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Constructor with an unrecognised value for FileAccess threw the wrong exception");
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

void io_FileStream_TestClass::test_Constructor_DirectoryPath()
{
	TestResult test;
	test.test_name = "test_Constructor_DirectoryPath";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateDirectory(kAsciiFilePath);

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);
				
				throw tc::TestException("Attempting to open a directory as a file did not throw tc::io::IOException or tc::UnauthorisedAccessException");
			}
			catch (const tc::io::IOException&) { /* do nothing */ }
			catch (const tc::UnauthorisedAccessException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Attempting to open a directory as a file threw the wrong exception");
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
		helper_DeleteDirectory(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Constructor_CreateThenReopenFileWithUnicodePath()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateThenReopenFileWithUnicodePath";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// test
		try 
		{
			auto stream = tc::io::FileStream(kUtf8TestPath, tc::io::FileMode::Create, tc::io::FileAccess::ReadWrite);

			stream.dispose();

			stream = tc::io::FileStream(kUtf8TestPath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

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
		helper_DeleteFile(kUtf8TestPath);
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

// seek() tests
void io_FileStream_TestClass::test_Seek_EmptyFile()
{
	TestResult test;
	test.test_name = "test_Seek_EmptyFile";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, nullptr, 0);

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, 0);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, 0, 0);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::End, 0, 0);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Seek_CreatedFile()
{
	TestResult test;
	test.test_name = "test_Seek_CreatedFile";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, 0);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, 0, 0);
			StreamTestUtil::seek_TestHelper(stream, 100, tc::io::SeekOrigin::Current, 100, 100);
			StreamTestUtil::seek_TestHelper(stream, 50, tc::io::SeekOrigin::Current, 150, 150);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::End, 200, 200);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, 200, 200);
			StreamTestUtil::seek_TestHelper(stream, 1, tc::io::SeekOrigin::Begin, 1, 1);
			StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, 1, 1);
			StreamTestUtil::seek_TestHelper(stream, -1, tc::io::SeekOrigin::End, 199, 199);
			StreamTestUtil::seek_TestHelper(stream, -198, tc::io::SeekOrigin::Current, 1, 1);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Seek_AppendMode()
{
	TestResult test;
	test.test_name = "test_Seek_AppendMode";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Append, tc::io::FileAccess::Write);

				StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, 0);
				
				throw tc::TestException(".seek() when stream was opened in FileMode::Append did not throw tc::io::IOException");
			}
			catch (const tc::io::IOException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException(".seek() when stream was opened in FileMode::Append threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Seek_PositionBeforeFileBegin()
{
	TestResult test;
	test.test_name = "test_Seek_PositionBeforeFileBegin";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

				StreamTestUtil::seek_TestHelper(stream, -1, tc::io::SeekOrigin::Begin, -1, -1);
				
				throw tc::TestException(".seek() when attempting to seek before the start of the file did not throw tc::ArgumentOutOfRangeException");
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException(".seek() when attempting to seek before the start of the file threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Seek_PositionAfterFileEnd()
{
	TestResult test;
	test.test_name = "test_Seek_PositionAfterFileEnd";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::seek_TestHelper(stream, stream.length(), tc::io::SeekOrigin::Begin, stream.length(), stream.length());

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
		helper_DeleteFile(kAsciiFilePath);
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

// read tests

void io_FileStream_TestClass::test_Read_NoData()
{
	TestResult test;
	test.test_name = "test_Read_NoData";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), 0, 0, 0);
			StreamTestUtil::read_TestHelper(stream, stream.length()/2, tc::io::SeekOrigin::Begin, kRandomString.size(), 0, 0, stream.length()/2);
			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::End, kRandomString.size(), 0, 0, stream.length());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_SomeDataFromZero()
{
	TestResult test;
	test.test_name = "test_Read_SomeDataFromZero";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), 0x01, 0x01, 0x01, (const byte_t*)kRandomString.c_str());
			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), 0x20, 0x20, 0x20, (const byte_t*)kRandomString.c_str());
			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), kRandomString.size()/2, kRandomString.size()/2, kRandomString.size()/2, (const byte_t*)kRandomString.c_str());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_SomeDataFromMiddle()
{
	TestResult test;
	test.test_name = "test_Read_SomeDataFromMiddle";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			int64_t offset;
			size_t size;

			offset = 01;
			size = 20;
			StreamTestUtil::read_TestHelper(stream, offset, tc::io::SeekOrigin::Begin, kRandomString.size(), size, size, offset + size, (const byte_t*)kRandomString.c_str() + offset);

			offset = 67;
			size = 100;
			StreamTestUtil::read_TestHelper(stream, offset, tc::io::SeekOrigin::Begin, kRandomString.size(), size, size, offset + size, (const byte_t*)kRandomString.c_str() + offset);

			offset = stream.length() / 2;
			size = 80;
			StreamTestUtil::read_TestHelper(stream, offset, tc::io::SeekOrigin::Begin, kRandomString.size(), size, size, offset + size, (const byte_t*)kRandomString.c_str() + offset);
			
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_AllData()
{
	TestResult test;
	test.test_name = "test_Read_AllData";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), kRandomString.size(), kRandomString.size(), kRandomString.size(), (const byte_t*)kRandomString.c_str());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_TooMuchData()
{
	TestResult test;
	test.test_name = "test_Read_TooMuchData";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size()*2, kRandomString.size()*2, kRandomString.size(), kRandomString.size(), (const byte_t*)kRandomString.c_str());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_BeyondEnd()
{
	TestResult test;
	test.test_name = "test_Read_BeyondEnd";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			StreamTestUtil::read_TestHelper(stream, 1, tc::io::SeekOrigin::End, kRandomString.size(), kRandomString.size(), 0, kRandomString.size() + 1, (const byte_t*)kRandomString.c_str());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_CanReadFalse()
{
	TestResult test;
	test.test_name = "test_Read_CanReadFalse";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

				StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, kRandomString.size(), kRandomString.size(), 0, kRandomString.size(), (const byte_t*)kRandomString.c_str());
				
				throw tc::TestException("Using .read() on a file with no read permissions did not throw tc::NotSupportedException");
			}
			catch (const tc::NotSupportedException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Using .read() on a file with no read permissions threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Read_NullDstPointer()
{
	TestResult test;
	test.test_name = "test_Read_NullDstPointer";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), kRandomString.size());

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

				StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, kRandomString.size(), 0, kRandomString.size(), (const byte_t*)kRandomString.c_str());
				
				throw tc::TestException(".read() when passed a nullptr did not throw tc::ArgumentNullException");
			}
			catch (const tc::ArgumentNullException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException(".read() when passed a nullptr threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

// write() test

void io_FileStream_TestClass::test_Write_NoData()
{
	TestResult test;
	test.test_name = "test_Write_NoData";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, nullptr, 0);

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			StreamTestUtil::write_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, (const byte_t*)kRandomString.c_str(), 0, 0);

			stream.dispose();

			helper_ValidateFileContents(kAsciiFilePath, (const byte_t*)kRandomString.c_str(), 0);

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_OverwriteSomeDataFromZero()
{
	TestResult test;
	test.test_name = "test_Write_OverwriteSomeDataFromZero";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		auto padding = tc::io::PaddingSource(0xff, kRandomString.size());
		auto padding_data = padding.pullData(0, padding.length());
		helper_CreateFileForReading(kAsciiFilePath, padding_data.data(), padding_data.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			const byte_t* original_ptr = padding_data.data();
			size_t original_size = padding_data.size();

			const byte_t* written_data_ptr = (const byte_t*)kRandomString.c_str();
			size_t written_data_size = 30;
			size_t written_data_offset = 0;

			StreamTestUtil::write_TestHelper(stream, written_data_offset, tc::io::SeekOrigin::Begin, written_data_ptr, written_data_size, written_data_offset + written_data_size);
			stream.dispose();

			auto expected_file_layout = tc::ByteData(std::max<size_t>(original_size, written_data_offset + written_data_size));

			memcpy(expected_file_layout.data(), original_ptr, original_size);
			memcpy(expected_file_layout.data() + written_data_offset, written_data_ptr, written_data_size);

			helper_ValidateFileContents(kAsciiFilePath, expected_file_layout.data(), expected_file_layout.size());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_OverwriteSomeDataFromMiddle()
{
	TestResult test;
	test.test_name = "test_Write_OverwriteSomeDataFromMiddle";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		auto padding = tc::io::PaddingSource(0xee, kRandomString.size());
		auto padding_data = padding.pullData(0, padding.length());
		helper_CreateFileForReading(kAsciiFilePath, padding_data.data(), padding_data.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			const byte_t* original_ptr = padding_data.data();
			size_t original_size = padding_data.size();

			const byte_t* written_data_ptr = (const byte_t*)kRandomString.c_str();
			size_t written_data_size = 90;
			size_t written_data_offset = 50;

			StreamTestUtil::write_TestHelper(stream, written_data_offset, tc::io::SeekOrigin::Begin, written_data_ptr, written_data_size, written_data_offset + written_data_size);
			stream.dispose();

			auto expected_file_layout = tc::ByteData(std::max<size_t>(original_size, written_data_offset + written_data_size));

			memcpy(expected_file_layout.data(), original_ptr, original_size);
			memcpy(expected_file_layout.data() + written_data_offset, written_data_ptr, written_data_size);

			helper_ValidateFileContents(kAsciiFilePath, expected_file_layout.data(), expected_file_layout.size());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_ExtendStreamSizeThruWritingDataFromZero()
{
	TestResult test;
	test.test_name = "test_Write_ExtendStreamSizeThruWritingDataFromZero";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		auto padding = tc::io::PaddingSource(0xee, 0x20);
		auto padding_data = padding.pullData(0, padding.length());
		helper_CreateFileForReading(kAsciiFilePath, padding_data.data(), padding_data.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			const byte_t* original_ptr = padding_data.data();
			size_t original_size = padding_data.size();

			const byte_t* written_data_ptr = (const byte_t*)kRandomString.c_str();
			size_t written_data_size = 90;
			size_t written_data_offset = 0;

			StreamTestUtil::write_TestHelper(stream, written_data_offset, tc::io::SeekOrigin::Begin, written_data_ptr, written_data_size, written_data_offset + written_data_size, written_data_offset + written_data_size);
			stream.dispose();

			auto expected_file_layout = tc::ByteData(std::max<size_t>(original_size, written_data_offset + written_data_size));

			memcpy(expected_file_layout.data(), original_ptr, original_size);
			memcpy(expected_file_layout.data() + written_data_offset, written_data_ptr, written_data_size);

			helper_ValidateFileContents(kAsciiFilePath, expected_file_layout.data(), expected_file_layout.size());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_ExtendStreamSizeThruWritingDataFromMiddle()
{
	TestResult test;
	test.test_name = "test_Write_ExtendStreamSizeThruWritingDataFromMiddle";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		auto padding = tc::io::PaddingSource(0xee, 0x20);
		auto padding_data = padding.pullData(0, padding.length());
		helper_CreateFileForReading(kAsciiFilePath, padding_data.data(), padding_data.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

			const byte_t* original_ptr = padding_data.data();
			size_t original_size = padding_data.size();

			const byte_t* written_data_ptr = (const byte_t*)kRandomString.c_str();
			size_t written_data_size = 90;
			size_t written_data_offset = 0x10;

			StreamTestUtil::write_TestHelper(stream, written_data_offset, tc::io::SeekOrigin::Begin, written_data_ptr, written_data_size, written_data_offset + written_data_size, written_data_offset + written_data_size);
			stream.dispose();

			auto expected_file_layout = tc::ByteData(std::max<size_t>(original_size, written_data_offset + written_data_size));

			memcpy(expected_file_layout.data(), original_ptr, original_size);
			memcpy(expected_file_layout.data() + written_data_offset, written_data_ptr, written_data_size);

			helper_ValidateFileContents(kAsciiFilePath, expected_file_layout.data(), expected_file_layout.size());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_BeyondEnd()
{
	TestResult test;
	test.test_name = "test_Write_BeyondEnd";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		auto padding = tc::io::PaddingSource(0xee, 0x20);
		auto padding_data = padding.pullData(0, padding.length());
		helper_CreateFileForReading(kAsciiFilePath, padding_data.data(), padding_data.size());

		// test
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::OpenOrCreate, tc::io::FileAccess::Write);

			const byte_t* original_ptr = padding_data.data();
			size_t original_size = padding_data.size();

			const byte_t* written_data_ptr = (const byte_t*)kRandomString.c_str();
			size_t written_data_size = 90;
			size_t written_data_offset = original_size + 4;

			StreamTestUtil::write_TestHelper(stream, written_data_offset, tc::io::SeekOrigin::Begin, written_data_ptr, written_data_size, written_data_offset + written_data_size, written_data_offset + written_data_size);
			stream.dispose();

			auto expected_file_layout = tc::ByteData(std::max<size_t>(original_size, written_data_offset + written_data_size));
			memcpy(expected_file_layout.data(), original_ptr, original_size);
			memcpy(expected_file_layout.data() + written_data_offset, written_data_ptr, written_data_size);

			helper_ValidateFileContents(kAsciiFilePath, expected_file_layout.data(), expected_file_layout.size());

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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_CanWriteFalse()
{
	TestResult test;
	test.test_name = "test_Write_CanWriteFalse";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env setup
		helper_CreateFileForReading(kAsciiFilePath, nullptr, 0);

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

				StreamTestUtil::write_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, (const byte_t*)kRandomString.c_str(), kRandomString.size(), kRandomString.size());
				
				throw tc::TestException("Using .write() on a file with no write permissions did not throw tc::NotSupportedException");
			}
			catch (const tc::NotSupportedException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException("Using .write() on a file with no write permissions threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

void io_FileStream_TestClass::test_Write_NullSrcPointer()
{
	TestResult test;
	test.test_name = "test_Write_NullSrcPointer";
	test.result = "NOT RUN";
	test.comments = "";
	
	try
	{
		// env set
		helper_CreateFileForReading(kAsciiFilePath, nullptr, 0);

		// test
		try 
		{
			try 
			{
				auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Write);

				StreamTestUtil::write_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, nullptr, kRandomString.size(), kRandomString.size());

				throw tc::TestException(".write() when passed a nullptr did not throw tc::ArgumentNullException");
			}
			catch (const tc::ArgumentNullException&) { /* do nothing */ }
			catch (const tc::Exception& e)
			{
				throw tc::TestException(".write() when passed a nullptr threw the wrong exception");
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
		helper_DeleteFile(kAsciiFilePath);
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

// helper code

void io_FileStream_TestClass::helper_CreateFileForReading(const std::string& path, const uint8_t* data, size_t data_len)
{
	auto test_file = std::ofstream(path, std::ios::binary);
	if (data != nullptr && data_len != 0)
	{
		test_file.write((char*)data, data_len);
	}
	test_file.close();
}

void io_FileStream_TestClass::helper_ValidateFileContents(const std::string& path, const uint8_t* data, size_t data_len)
{
	auto test_file = std::ifstream(path, std::ios::binary);

	if (test_file.fail())
	{
		throw tc::TestException("helper_ValidateFileContents : Failed to open file");
	}

	if (data == nullptr || data_len == 0)
	{
		return;
	}

	auto datablob = tc::ByteData(data_len);
	test_file.read((char*)datablob.data(), data_len);

	if (test_file.fail())
	{
		throw tc::TestException("helper_ValidateFileContents : Failed to read file");
	}

	test_file.close();

	if (memcmp(datablob.data(), data, data_len) != 0)
	{
		throw tc::TestException("helper_ValidateFileContents : Invalid file contents");
	}
} 

void io_FileStream_TestClass::helper_DeleteFile(const std::string& path)
{
	tc::io::LocalFileSystem s;
	s.removeFile(path);
}

void io_FileStream_TestClass::helper_CreateDirectory(const std::string& path)
{
	tc::io::LocalFileSystem s;
	s.createDirectory(path);
}

void io_FileStream_TestClass::helper_DeleteDirectory(const std::string& path)
{
	tc::io::LocalFileSystem s;
	s.removeDirectory(path);
}