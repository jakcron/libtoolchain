#include <iostream>
#include <sstream>

#include "io_FileStream_TestClass.h"

#include <tc.h>

std::string io_FileStream_TestClass::kAsciiFilePath = "LocalFileTest.bin";
std::string io_FileStream_TestClass::kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
std::string io_FileStream_TestClass::kNotExistFilePath = "ThisDoesNotExist.bin";
std::string io_FileStream_TestClass::kTestPhrase = "Hello world!\n";
std::string io_FileStream_TestClass::kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";

void io_FileStream_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::FileStream] START" << std::endl;
	test_OpenFileCreate_NotExist();
	test_OpenFileCreate_DoesExist();
	test_OpenFileRead_DoesExist();
	test_OpenFileRead_NotExist();
	test_OpenFileRead_UnicodePath();
	test_OpenFileRead_TryWrite();
	test_OpenFileRead_TryReadBeyondEnd();
	test_OpenFileEdit_DoesExist();
	test_OpenFileEdit_NotExist();
	std::cout << "[tc::io::FileStream] END" << std::endl;
}

void io_FileStream_TestClass::test_OpenFileCreate_NotExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileCreate_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);

			if (stream.length() != 0)
			{
				throw tc::Exception("stream opened in create mode does not have a size of 0");
			}

			stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (stream.length() != kRandomString.length())
			{
				throw tc::Exception("after writing data, stream length is not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileCreate_DoesExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileCreate_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

		auto tmp_stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);

			if (stream.length() != 0)
			{
				throw tc::Exception("stream opened in create mode does not have a size of 0");
			}

			stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (stream.length() != kRandomString.length())
			{
				throw tc::Exception("after writing data, stream size is not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileRead_DoesExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileRead_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

		auto tmp_stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			if (stream.length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			stream.read(check.get(), kRandomString.length());

			if (memcmp(check.get(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data in stream was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening stream in read mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileRead_NotExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileRead_NotExist : " << std::flush;
	try
	{
		auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);
		
		std::cout << "FAIL (Did not throw exception where stream did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileRead_UnicodePath()
{
	std::cout << "[tc::io::FileStream] test_OpenFileRead_UnicodePath : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

		auto tmp_stream = tc::io::FileStream(kUtf8TestPath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kUtf8TestPath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			if (stream.length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			stream.read(check.get(), kRandomString.length());

			if (memcmp(check.get(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data in stream was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening stream in read mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		local_storage.removeFile(kUtf8TestPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileRead_TryWrite()
{
	std::cout << "[tc::io::FileStream] test_OpenFileRead_TryWrite : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		auto tmp_stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			stream.seek(stream.length(), tc::io::SeekOrigin::Begin);
		
			stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			std::cout << "FAIL (Did not throw exception when write() was called)" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileRead_TryReadBeyondEnd()
{
	std::cout << "[tc::io::FileStream] test_OpenFileRead_TryReadBeyondEnd : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		auto tmp_stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read);

			stream.seek(0, tc::io::SeekOrigin::End);
			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);

			size_t read_len = stream.read(check.get(), kRandomString.length());

			if (read_len != 0)
			{
				throw tc::Exception("read() returned a non-zero response when reading past end of file");
			}
		
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileEdit_DoesExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileEdit_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		auto tmp_stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write);
		tmp_stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream.dispose();

		try 
		{
			auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite);

			if (stream.length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			stream.seek(kRandomString.length(), tc::io::SeekOrigin::Begin);
			stream.write((const byte_t*)kRandomString.c_str(), kRandomString.length());

			stream.seek(7, tc::io::SeekOrigin::Begin);
			stream.write((const byte_t*)kTestPhrase.c_str(), kTestPhrase.length());

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()*2]);
			stream.seek(0, tc::io::SeekOrigin::Begin);
			stream.read(check.get(), kRandomString.length()*2);

			if (memcmp(check.get() + kRandomString.length(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data(kRandomStr[1][:]) in stream was not correct");
			}

			if (memcmp(check.get() + 7, kTestPhrase.c_str(), kTestPhrase.size()) != 0)
			{
				throw tc::Exception("Data(kTestPhrase[:]) in stream was not correct");
			}

			if (memcmp(check.get(), kRandomString.c_str(), 7) != 0)
			{
				throw tc::Exception("Data(kRandomStr[0][0:7]) in stream was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening stream in edit mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		local_storage.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_FileStream_TestClass::test_OpenFileEdit_NotExist()
{
	std::cout << "[tc::io::FileStream] test_OpenFileEdit_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

		auto stream = tc::io::FileStream(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite);
		
		std::cout << "FAIL (Did not throw exception where stream did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}