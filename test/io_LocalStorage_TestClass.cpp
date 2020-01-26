#include <tc/io.h>
#include <tc/Exception.h>
#include <iostream>

#include "io_LocalStorage_TestClass.h"

static std::string kDirPath = "./testdir";
static std::string kUtf8DirPath = "./ЀЁЂЃЄЅテスト/";
static std::string kAsciiFilePath = "LocalFileTest.bin";
static std::string kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
static std::string kNotExistFilePath = "ThisDoesNotExist.bin";
static std::string kTestPhrase = "Hello world!\n";
static std::string kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";

void io_LocalStorage_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::LocalStorage] START" << std::endl;
	test_CreateFile_NotExist();
	test_CreateFile_DoesExist();
	test_CreateFile_UnicodePath();
	test_RemoveFile_DoesExist();
	test_RemoveFile_NotExist();
	test_RemoveFile_UnicodePath();

	test_OpenFileCreate_NotExist();
	test_OpenFileCreate_DoesExist();
	test_OpenFileRead_DoesExist();
	test_OpenFileRead_NotExist();
	test_OpenFileRead_UnicodePath();
	test_OpenFileRead_TryWrite();
	test_OpenFileRead_TryReadBeyondEnd();
	test_OpenFileEdit_DoesExist();
	test_OpenFileEdit_NotExist();	
	
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
	std::cout << "[tc::io::LocalStorage] END" << std::endl;
}

void io_LocalStorage_TestClass::test_CreateFile_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_CreateFile_NotExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_CreateFile_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_CreateFile_DoesExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_CreateFile_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_CreateFile_UnicodePath : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createFile(kUtf8TestPath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveFile_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveFile_DoesExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveFile_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveFile_NotExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeFile(kNotExistFilePath);
		std::cout << "FAIL (Did not throw exception when stream was not present on FS)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveFile_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveFile_UnicodePath : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeFile(kUtf8TestPath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_OpenFileCreate_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileCreate_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, stream);

			if (stream->length() != 0)
			{
				throw tc::Exception("stream opened in create mode does not have a size of 0");
			}

			stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (stream->length() != kRandomString.length())
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

void io_LocalStorage_TestClass::test_OpenFileCreate_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileCreate_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		local_storage.createFile(kAsciiFilePath);

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, stream);

			if (stream->length() != 0)
			{
				throw tc::Exception("stream opened in create mode does not have a size of 0");
			}

			stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (stream->length() != kRandomString.length())
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

void io_LocalStorage_TestClass::test_OpenFileRead_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileRead_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> tmp_stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, tmp_stream);
		tmp_stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream->dispose();

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read, stream);

			if (stream->length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			stream->read(check.get(), kRandomString.length());

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

void io_LocalStorage_TestClass::test_OpenFileRead_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileRead_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read, stream);
		
		std::cout << "FAIL (Did not throw exception where stream did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_OpenFileRead_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileRead_UnicodePath : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> tmp_stream;

		local_storage.openFile(kUtf8TestPath, tc::io::FileMode::Create, tc::io::FileAccess::Write, tmp_stream);
		tmp_stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream->dispose();

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kUtf8TestPath, tc::io::FileMode::Open, tc::io::FileAccess::Read, stream);

			if (stream->length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			stream->read(check.get(), kRandomString.length());

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

void io_LocalStorage_TestClass::test_OpenFileRead_TryWrite()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileRead_TryWrite : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> tmp_stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, tmp_stream);
		tmp_stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream->dispose();

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read, stream);

			stream->seek(stream->length(), tc::io::SeekOrigin::Begin);
		
			stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
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

void io_LocalStorage_TestClass::test_OpenFileRead_TryReadBeyondEnd()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileRead_TryReadBeyondEnd : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> tmp_stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, tmp_stream);
		tmp_stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream->dispose();

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::Read, stream);

			stream->seek(0, tc::io::SeekOrigin::End);
			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);

			size_t read_len = stream->read(check.get(), kRandomString.length());

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

void io_LocalStorage_TestClass::test_OpenFileEdit_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileEdit_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> tmp_stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Create, tc::io::FileAccess::Write, tmp_stream);
		tmp_stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_stream->dispose();

		try 
		{
			std::shared_ptr<tc::io::IStream> stream;
			local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite, stream);

			if (stream->length() != kRandomString.length())
			{
				throw tc::Exception("Unexpected stream size");
			}

			stream->seek(kRandomString.length(), tc::io::SeekOrigin::Begin);
			stream->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

			stream->seek(7, tc::io::SeekOrigin::Begin);
			stream->write((const byte_t*)kTestPhrase.c_str(), kTestPhrase.length());

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()*2]);
			stream->seek(0, tc::io::SeekOrigin::Begin);
			stream->read(check.get(), kRandomString.length()*2);

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

void io_LocalStorage_TestClass::test_OpenFileEdit_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_OpenFileEdit_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		std::shared_ptr<tc::io::IStream> stream;

		local_storage.openFile(kAsciiFilePath, tc::io::FileMode::Open, tc::io::FileAccess::ReadWrite, stream);
		
		std::cout << "FAIL (Did not throw exception where stream did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_CreateDirectory_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_CreateDirectory_NotExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_CreateDirectory_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_CreateDirectory_DoesExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_CreateDirectory_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_CreateDirectory_UnicodePath : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.createDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveDirectory_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveDirectory_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveDirectory_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveDirectory_NotExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeDirectory(kDirPath);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveDirectory_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveDirectory_UnicodePath : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		local_storage.removeDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveDirectory_HasChildren()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveDirectory_HasChildren : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
	
		tc::io::Path dir_child_path = tc::io::Path(kDirPath) + tc::io::Path(kUtf8DirPath);
		tc::io::Path stream_child_path = tc::io::Path(kDirPath) + tc::io::Path(kAsciiFilePath);

		try 
		{
			local_storage.createDirectory(kDirPath);
			local_storage.createDirectory(dir_child_path);
			local_storage.createFile(stream_child_path);
			local_storage.removeDirectory(kDirPath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		local_storage.removeDirectory(dir_child_path);
		local_storage.removeFile(stream_child_path);
		local_storage.removeDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_RemoveDirectory_NotDirectoryActuallyFile()
{
	std::cout << "[tc::io::LocalStorage] test_RemoveDirectory_NotDirectoryActuallyFile : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		try 
		{
			local_storage.createFile(kAsciiFilePath);
			local_storage.removeDirectory(kAsciiFilePath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
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

void io_LocalStorage_TestClass::test_GetDirectoryListing_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_GetDirectoryListing_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

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

		try
		{
			tc::io::sDirectoryListing info;

			local_storage.getDirectoryListing(kDirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::Exception("Unexpected stream count");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

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
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_GetDirectoryListing_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_GetDirectoryListing_NotExist : " << std::flush;
	try 
	{
		tc::io::LocalStorage local_storage;

		tc::io::sDirectoryListing info;
		local_storage.getDirectoryListing(kNotExistFilePath, info);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_GetDirectoryListing_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_GetDirectoryListing_UnicodePath : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;

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

		try
		{
			tc::io::sDirectoryListing info;

			local_storage.getDirectoryListing(kUtf8DirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::Exception("Unexpected stream count");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

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
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_ChangeWorkingDirectory_DoesExist()
{
	std::cout << "[tc::io::LocalStorage] test_ChangeWorkingDirectory_DoesExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		tc::io::Path old_dir;
		local_storage.getWorkingDirectory(old_dir);

		try 
		{
			local_storage.createDirectory(kDirPath);
			local_storage.setWorkingDirectory(kDirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		local_storage.setWorkingDirectory(old_dir);
		local_storage.removeDirectory(tc::io::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_ChangeWorkingDirectory_NotExist()
{
	std::cout << "[tc::io::LocalStorage] test_ChangeWorkingDirectory_NotExist : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		local_storage.setWorkingDirectory(kNotExistFilePath);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void io_LocalStorage_TestClass::test_ChangeWorkingDirectory_UnicodePath()
{
	std::cout << "[tc::io::LocalStorage] test_ChangeWorkingDirectory_UnicodePath : " << std::flush;
	try
	{
		tc::io::LocalStorage local_storage;
		
		tc::io::Path old_dir;
		local_storage.getWorkingDirectory(old_dir);

		try 
		{
			local_storage.createDirectory(kUtf8DirPath);
			local_storage.setWorkingDirectory(kUtf8DirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		local_storage.setWorkingDirectory(old_dir);
		local_storage.removeDirectory(kUtf8DirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}