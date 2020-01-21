#include <tc/fs.h>
#include <tc/Exception.h>
#include <iostream>

#include "fs_LocalFileSystem_TestClass.h"

static std::string kDirPath = "./testdir";
static std::string kUtf8DirPath = "./ЀЁЂЃЄЅテスト/";
static std::string kAsciiFilePath = "LocalFileTest.bin";
static std::string kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
static std::string kNotExistFilePath = "ThisDoesNotExist.bin";
static std::string kTestPhrase = "Hello world!\n";
static std::string kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";

void fs_LocalFileSystem_TestClass::runAllTests(void)
{
	std::cout << "[tc::fs::LocalFileSystem] START" << std::endl;
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
	std::cout << "[tc::fs::LocalFileSystem] END" << std::endl;
}

void fs_LocalFileSystem_TestClass::test_CreateFile_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateFile_NotExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_CreateFile_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateFile_DoesExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_CreateFile_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateFile_UnicodePath : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createFile(kUtf8TestPath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveFile_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveFile_DoesExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.removeFile(kAsciiFilePath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveFile_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveFile_NotExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.removeFile(kNotExistFilePath);
		std::cout << "FAIL (Did not throw exception when file was not present on FS)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveFile_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveFile_UnicodePath : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.removeFile(kUtf8TestPath);		

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileCreate_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileCreate_NotExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, file);

			if (file->size() != 0)
			{
				throw tc::Exception("file opened in create mode does not have a size of 0");
			}

			file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (file->size() != kRandomString.length())
			{
				throw tc::Exception("after writing data, file size is not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileCreate_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileCreate_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		fs.createFile(kAsciiFilePath);

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, file);

			if (file->size() != 0)
			{
				throw tc::Exception("file opened in create mode does not have a size of 0");
			}

			file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			if (file->size() != kRandomString.length())
			{
				throw tc::Exception("after writing data, file size is not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileRead_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileRead_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> tmp_file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, tmp_file);
		tmp_file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_file->close();

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_READ, file);

			if (file->size() != kRandomString.length())
			{
				throw tc::Exception("Unexpected file size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			file->read(check.get(), kRandomString.length());

			if (memcmp(check.get(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data in file was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening file in read mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileRead_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileRead_NotExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_READ, file);
		
		std::cout << "FAIL (Did not throw exception where file did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileRead_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileRead_UnicodePath : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> tmp_file;

		fs.openFile(kUtf8TestPath, tc::fs::FILEACCESS_CREATE, tmp_file);
		tmp_file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_file->close();

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kUtf8TestPath, tc::fs::FILEACCESS_READ, file);

			if (file->size() != kRandomString.length())
			{
				throw tc::Exception("Unexpected file size");
			}

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);
			file->read(check.get(), kRandomString.length());

			if (memcmp(check.get(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data in file was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening file in read mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		fs.removeFile(kUtf8TestPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileRead_TryWrite()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileRead_TryWrite : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> tmp_file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, tmp_file);
		tmp_file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_file->close();

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_READ, file);

			file->seek(file->size());
		
			file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
			
			std::cout << "FAIL (Did not throw exception when write() was called)" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileRead_TryReadBeyondEnd()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileRead_TryReadBeyondEnd : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> tmp_file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, tmp_file);
		tmp_file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_file->close();

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_READ, file);

			file->seek(file->size());
			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()]);

			file->read(check.get(), kRandomString.length());
		
			std::cout << "FAIL (Did not throw exception when read() was called)" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileEdit_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileEdit_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> tmp_file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_CREATE, tmp_file);
		tmp_file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());
		tmp_file->close();

		try 
		{
			std::shared_ptr<tc::fs::IFileObject> file;
			fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_EDIT, file);

			if (file->size() != kRandomString.length())
			{
				throw tc::Exception("Unexpected file size");
			}

			file->seek(kRandomString.length());
			file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

			file->seek(7);
			file->write((const byte_t*)kTestPhrase.c_str(), kTestPhrase.length());

			std::shared_ptr<byte_t> check(new byte_t[kRandomString.length()*2]);
			file->seek(0);
			file->read(check.get(), kRandomString.length()*2);

			if (memcmp(check.get() + kRandomString.length(), kRandomString.c_str(), kRandomString.size()) != 0)
			{
				throw tc::Exception("Data(kRandomStr[1][:]) in file was not correct");
			}

			if (memcmp(check.get() + 7, kTestPhrase.c_str(), kTestPhrase.size()) != 0)
			{
				throw tc::Exception("Data(kTestPhrase[:]) in file was not correct");
			}

			if (memcmp(check.get(), kRandomString.c_str(), 7) != 0)
			{
				throw tc::Exception("Data(kRandomStr[0][0:7]) in file was not correct");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (Test opening file in edit mode and confirming the data is correct (" << e.what() << "))" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_OpenFileEdit_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_OpenFileEdit_NotExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		std::shared_ptr<tc::fs::IFileObject> file;

		fs.openFile(kAsciiFilePath, tc::fs::FILEACCESS_EDIT, file);
		
		std::cout << "FAIL (Did not throw exception where file did not exist)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_CreateDirectory_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateDirectory_NotExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_CreateDirectory_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateDirectory_DoesExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_CreateDirectory_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_CreateDirectory_UnicodePath : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.createDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveDirectory_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveDirectory_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;

		fs.removeDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveDirectory_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveDirectory_NotExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.removeDirectory(kDirPath);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveDirectory_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveDirectory_UnicodePath : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.removeDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveDirectory_HasChildren()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveDirectory_HasChildren : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
	
		tc::fs::Path dir_child_path = tc::fs::Path(kDirPath) + tc::fs::Path(kUtf8DirPath);
		tc::fs::Path file_child_path = tc::fs::Path(kDirPath) + tc::fs::Path(kAsciiFilePath);

		try 
		{
			fs.createDirectory(kDirPath);
			fs.createDirectory(dir_child_path);
			fs.createFile(file_child_path);
			fs.removeDirectory(kDirPath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.removeDirectory(dir_child_path);
		fs.removeFile(file_child_path);
		fs.removeDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_RemoveDirectory_NotDirectoryActuallyFile()
{
	std::cout << "[tc::fs::LocalFileSystem] test_RemoveDirectory_NotDirectoryActuallyFile : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		try 
		{
			fs.createFile(kAsciiFilePath);
			fs.removeDirectory(kAsciiFilePath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.removeFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_GetDirectoryListing_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_GetDirectoryListing_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;

		std::vector<std::string> file_list;
		std::vector<std::string> dir_list;
		
		file_list.push_back("fileA.bin");
		file_list.push_back("fileB.bin");
		file_list.push_back("fileC.bin");
		file_list.push_back("fileD.bin");

		dir_list.push_back("dir000");
		dir_list.push_back("dir001");
		dir_list.push_back("dir002");
		dir_list.push_back("dir003");

		fs.createDirectory(kDirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			fs.createFile(tc::fs::Path(kDirPath) + tc::fs::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.createDirectory(tc::fs::Path(kDirPath) + tc::fs::Path(dir_list[i]));
		}

		try
		{
			tc::fs::sDirectoryListing info;

			fs.getDirectoryListing(kDirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::Exception("Unexpected file count");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		for (size_t i = 0; i < file_list.size(); i++)
		{
			fs.removeFile(tc::fs::Path(kDirPath) + tc::fs::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.removeDirectory(tc::fs::Path(kDirPath) + tc::fs::Path(dir_list[i]));
		}

		fs.removeDirectory(tc::fs::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_GetDirectoryListing_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_GetDirectoryListing_NotExist : " << std::flush;
	try 
	{
		tc::fs::LocalFileSystem fs;

		tc::fs::sDirectoryListing info;
		fs.getDirectoryListing(kNotExistFilePath, info);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_GetDirectoryListing_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_GetDirectoryListing_UnicodePath : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;

		std::vector<std::string> file_list;
		std::vector<std::string> dir_list;
		
		file_list.push_back("fileA.bin");
		file_list.push_back("fileB.bin");
		file_list.push_back("fileC.bin");
		file_list.push_back("fileD.bin");

		dir_list.push_back("dir000");
		dir_list.push_back("dir001");
		dir_list.push_back("dir002");
		dir_list.push_back("dir003");

		fs.createDirectory(kUtf8DirPath);

		for (size_t i = 0; i < file_list.size(); i++)
		{
			fs.createFile(tc::fs::Path(kUtf8DirPath) + tc::fs::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.createDirectory(tc::fs::Path(kUtf8DirPath) + tc::fs::Path(dir_list[i]));
		}

		try
		{
			tc::fs::sDirectoryListing info;

			fs.getDirectoryListing(kUtf8DirPath, info);
			
			// + 2 for "." & ".."
			if (info.dir_list.size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.file_list.size() != file_list.size())
			{
				throw tc::Exception("Unexpected file count");
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		for (size_t i = 0; i < file_list.size(); i++)
		{
			fs.removeFile(tc::fs::Path(kUtf8DirPath) + tc::fs::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.removeDirectory(tc::fs::Path(kUtf8DirPath) + tc::fs::Path(dir_list[i]));
		}

		fs.removeDirectory(tc::fs::Path(kUtf8DirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_DoesExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_ChangeWorkingDirectory_DoesExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		
		tc::fs::Path old_dir;
		fs.getWorkingDirectory(old_dir);

		try 
		{
			fs.createDirectory(kDirPath);
			fs.setWorkingDirectory(kDirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.setWorkingDirectory(old_dir);
		fs.removeDirectory(tc::fs::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_NotExist()
{
	std::cout << "[tc::fs::LocalFileSystem] test_ChangeWorkingDirectory_NotExist : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		
		fs.setWorkingDirectory(kNotExistFilePath);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void fs_LocalFileSystem_TestClass::test_ChangeWorkingDirectory_UnicodePath()
{
	std::cout << "[tc::fs::LocalFileSystem] test_ChangeWorkingDirectory_UnicodePath : " << std::flush;
	try
	{
		tc::fs::LocalFileSystem fs;
		
		tc::fs::Path old_dir;
		fs.getWorkingDirectory(old_dir);

		try 
		{
			fs.createDirectory(kUtf8DirPath);
			fs.setWorkingDirectory(kUtf8DirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.setWorkingDirectory(old_dir);
		fs.removeDirectory(kUtf8DirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}