#include <tc/filesystem.h>
#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

static std::string kDirPath = "./testdir";
static std::string kUtf8DirPath = "./ЀЁЂЃЄЅテスト/";
static std::string kAsciiFilePath = "LocalFileTest.bin";
static std::string kUtf8TestPath = "ЀЁЂЃЄЅ-מבחן-тест-テスト.bin";
static std::string kNotExistFilePath = "ThisDoesNotExist.bin";
static std::string kTestPhrase = "Hello world!\n";
static std::string kRandomString = "uUkMx4MYhJdwUnr38Jk7nZvXQnW0IhGNQqjMRyKoRuxXwmxBS3p2Alzrv7BijPN2LDI1QGkEfQ3vrpoOGwKciwidTyuOPRRg9sj8QggPk7QSvJrrWKN3PfzN7JvEwax3vX3QaHIoX0afJtUiulzVf9SMlotimwrdOHbeAhLzQUSCAz6moIHhZd6DO0hFxjCxGpHUnDKE";


void testFileCreate()
{
	std::cout << "[LocalFileSystem-test] testFileCreate : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_CREATE);

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
}

void testFileRead()
{
	std::cout << "[LocalFileSystem-test] testFileRead : ";	
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		if (file->size() != kRandomString.length())
		{
			throw tc::Exception("Unexpected file size");
		}

		tc::SharedPtr<byte_t> check = new byte_t[kRandomString.length()];
		file->read(check.get(), kRandomString.length());

		if (memcmp(check.get(), kRandomString.c_str(), kRandomString.size()) != 0)
		{
			throw tc::Exception("Data in file was not correct");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (Test opening file in read mode and confirming the data is correct(" << e.what() << "))" << std::endl;
	}
}

void testFileEdit()
{
	std::cout << "[LocalFileSystem-test] testFileEdit : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_EDIT);

		if (file->size() != kRandomString.length())
		{
			throw tc::Exception("Unexpected file size");
		}

		file->seek(kRandomString.length());
		file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

		file->seek(7);
		file->write((const byte_t*)kTestPhrase.c_str(), kTestPhrase.length());

		tc::SharedPtr<byte_t> check = new byte_t[kRandomString.length()*2];
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
}

void testUnicodePath()
{
	std::cout << "[LocalFileSystem-test] testUnicodePath : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kUtf8TestPath, tc::filesystem::FAM_CREATE);

		if (file->size() != 0)
		{
			throw tc::Exception("file opened in create mode does not have a size of 0\n");
		}

		file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());


		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (Test opening file in create mode and writing data (" << e.what() << "))" << std::endl;
	}
}

void testNotPresentFileReadOnly()
{
	std::cout << "[LocalFileSystem-test] testNotPresentFileReadOnly : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kNotExistFilePath, tc::filesystem::FAM_READ);

		std::cout << "FAIL (Did not throw on failure to open for read access file)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testNotPresentFileEdit()
{
	std::cout << "[LocalFileSystem-test] testNotPresentFileEdit : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kNotExistFilePath, tc::filesystem::FAM_EDIT);

		std::cout << "FAIL (Did not throw on failure to open for edit access file)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testTryWriteInReadOnlyMode()
{
	std::cout << "[LocalFileSystem-test] testTryWriteInReadOnlyMode : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		file->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

		std::cout << "FAIL (Did not throw exception when write() was called)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testTryReadBeyondFileSize()
{
	std::cout << "[LocalFileSystem-test] testTryReadBeyondFileSize : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		tc::SharedPtr<byte_t> buffer = new byte_t[0x10000];

		file->read(buffer.get(), 0x10000);

		std::cout << "FAIL (Did not throw exception when read() attemped to read beyond file size)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testDeleteAsciiFile()
{
	std::cout << "[LocalFileSystem-test] testDeleteAsciiFile : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.deleteFile(kAsciiFilePath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testDeleteUnicodeFile()
{
	std::cout << "[LocalFileSystem-test] testDeleteUnicodeFile : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.deleteFile(kUtf8TestPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testDeleteFileThatDoesNotExist()
{
	std::cout << "[LocalFileSystem-test] testDeleteFileThatDoesNotExist : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.deleteFile(kNotExistFilePath);
		std::cout << "FAIL (Did not throw exception when file was not present on FS)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testCreateDirectory()
{
	std::cout << "[LocalFileSystem-test] testCreateDirectory : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectory()
{
	std::cout << "[LocalFileSystem-test] testRemoveDirectory : ";
	tc::filesystem::LocalFileSystem fs;

	try
	{
		fs.removeDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}


void testCreateDirectoryWhereDirectoryAlreadyExists()
{
	std::cout << "[LocalFileSystem-test] testCreateDirectoryWhereDirectoryAlreadyExists : ";
	try
	{
		tc::filesystem::LocalFileSystem fs;

		try 
		{
			fs.createDirectory(kDirPath);
			fs.createDirectory(kDirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.removeDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
	
}


void testRemoveDirectoryWhereDirectoryDoesNotExist()
{
	std::cout << "[LocalFileSystem-test] testRemoveDirectoryWhereDirectoryDoesNotExist : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.removeDirectory(kDirPath);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testCreateDirectoryWithUnicodePath()
{
	std::cout << "[LocalFileSystem-test] testCreateDirectoryWithUnicodePath : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.createDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectoryWithUnicodePath()
{
	std::cout << "[LocalFileSystem-test] testRemoveDirectoryWithUnicodePath : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		fs.removeDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectoryThatIsActuallyAFile()
{
	std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatIsActuallyAFile : ";
	try
	{
		tc::filesystem::LocalFileSystem fs;
		try 
		{
			tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_CREATE);
			fs.removeDirectory(kAsciiFilePath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.deleteFile(kAsciiFilePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testRemoveDirectoryThatHasChildren()
{
	std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatHasChildren : ";
	try
	{
		tc::filesystem::LocalFileSystem fs;
	
		tc::filesystem::Path dir_child_path = tc::filesystem::Path(kDirPath) + tc::filesystem::Path(kUtf8DirPath);
		tc::filesystem::Path file_child_path = tc::filesystem::Path(kDirPath) + tc::filesystem::Path(kAsciiFilePath);

		try 
		{
			fs.createDirectory(kDirPath);
			fs.createDirectory(dir_child_path);
			tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(file_child_path, tc::filesystem::FAM_CREATE);
			fs.removeDirectory(kDirPath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.removeDirectory(dir_child_path);
		fs.deleteFile(file_child_path);
		fs.removeDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testGetDirectoryListing()
{
	std::cout << "[LocalFileSystem-test] testGetDirectoryListing : ";
	try
	{
		tc::filesystem::LocalFileSystem fs;

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
			tc::filesystem::IFile* fp = fs.openFile(tc::filesystem::Path(kDirPath) + tc::filesystem::Path(file_list[i]), tc::filesystem::FAM_CREATE);
			delete fp;
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.createDirectory(tc::filesystem::Path(kDirPath) + tc::filesystem::Path(dir_list[i]));
		}

		try
		{
			tc::filesystem::DirectoryInfo info;

			fs.getDirectoryInfo(kDirPath, info);
			
			// + 2 for "." & ".."
			if (info.getChildDirectoryList().size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.getChildFileList().size() != file_list.size())
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
			fs.deleteFile(tc::filesystem::Path(kDirPath) + tc::filesystem::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.removeDirectory(tc::filesystem::Path(kDirPath) + tc::filesystem::Path(dir_list[i]));
		}

		fs.removeDirectory(tc::filesystem::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testGetDirectoryListingWhereDirectoryDoesNotExist()
{
	std::cout << "[LocalFileSystem-test] testGetDirectoryListingWhereDirectoryDoesNotExist : ";
	try 
	{
		tc::filesystem::LocalFileSystem fs;

		tc::filesystem::DirectoryInfo info;
		fs.getDirectoryInfo(kNotExistFilePath, info);
		std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "PASS (" << e.error() << ")" << std::endl;
	}
}

void testChangeDirectory()
{
	std::cout << "[LocalFileSystem-test] testChangeDirectory : ";
	try
	{
		tc::filesystem::LocalFileSystem fs;
		
		tc::filesystem::Path old_dir;
		fs.getCurrentDirectory(old_dir);

		try 
		{
			fs.createDirectory(kDirPath);
			fs.setCurrentDirectory(kDirPath);
			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}

		fs.setCurrentDirectory(old_dir);
		fs.removeDirectory(tc::filesystem::Path(kDirPath));
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

int main(int argc, char** argv)
{
	testFileCreate();
	testFileRead();
	testFileEdit();
	testUnicodePath();
	testNotPresentFileReadOnly();
	testNotPresentFileEdit();
	testTryWriteInReadOnlyMode();
	testTryReadBeyondFileSize();
	testDeleteAsciiFile();
	testDeleteUnicodeFile();
	testDeleteFileThatDoesNotExist();
	testCreateDirectory();
	testRemoveDirectory();
	testCreateDirectoryWhereDirectoryAlreadyExists();
	testRemoveDirectoryWhereDirectoryDoesNotExist();
	testCreateDirectoryWithUnicodePath();
	testRemoveDirectoryWithUnicodePath();
	testRemoveDirectoryThatIsActuallyAFile();
	testRemoveDirectoryThatHasChildren();
	testGetDirectoryListing();
	testGetDirectoryListingWhereDirectoryDoesNotExist();
	testChangeDirectory();

}