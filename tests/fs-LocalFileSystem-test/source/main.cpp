#include <tc/fs.h>
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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_CREATE);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_READ);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_EDIT);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kUtf8TestPath, tc::fs::FAM_CREATE);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kNotExistFilePath, tc::fs::FAM_READ);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kNotExistFilePath, tc::fs::FAM_EDIT);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_READ);

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
		tc::fs::LocalFileSystem fs;

		tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_READ);

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
		tc::fs::LocalFileSystem fs;

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
		tc::fs::LocalFileSystem fs;

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
		tc::fs::LocalFileSystem fs;

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
		tc::fs::LocalFileSystem fs;

		fs.createDirectory(kDirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testDeleteDirectory()
{
	std::cout << "[LocalFileSystem-test] testDeleteDirectory : ";
	tc::fs::LocalFileSystem fs;

	try
	{
		fs.deleteDirectory(kDirPath);
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
		tc::fs::LocalFileSystem fs;

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

		fs.deleteDirectory(kDirPath);
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
	
}


void testDeleteDirectoryWhereDirectoryDoesNotExist()
{
	std::cout << "[LocalFileSystem-test] testDeleteDirectoryWhereDirectoryDoesNotExist : ";
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.deleteDirectory(kDirPath);
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
		tc::fs::LocalFileSystem fs;

		fs.createDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testDeleteDirectoryWithUnicodePath()
{
	std::cout << "[LocalFileSystem-test] testDeleteDirectoryWithUnicodePath : ";
	try 
	{
		tc::fs::LocalFileSystem fs;

		fs.deleteDirectory(kUtf8DirPath);
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void testDeleteDirectoryThatIsActuallyAFile()
{
	std::cout << "[LocalFileSystem-test] testDeleteDirectoryThatIsActuallyAFile : ";
	try
	{
		tc::fs::LocalFileSystem fs;
		try 
		{
			tc::SharedPtr<tc::fs::IFile> file = fs.openFile(kAsciiFilePath, tc::fs::FAM_CREATE);
			fs.deleteDirectory(kAsciiFilePath);
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

void testDeleteDirectoryThatHasChildren()
{
	std::cout << "[LocalFileSystem-test] testDeleteDirectoryThatHasChildren : ";
	try
	{
		tc::fs::LocalFileSystem fs;
	
		tc::fs::Path dir_child_path = tc::fs::Path(kDirPath) + tc::fs::Path(kUtf8DirPath);
		tc::fs::Path file_child_path = tc::fs::Path(kDirPath) + tc::fs::Path(kAsciiFilePath);

		try 
		{
			fs.createDirectory(kDirPath);
			fs.createDirectory(dir_child_path);
			tc::SharedPtr<tc::fs::IFile> file = fs.openFile(file_child_path, tc::fs::FAM_CREATE);
			fs.deleteDirectory(kDirPath);
			std::cout << "FAIL (did not throw exception on expected error)" << std::endl;
		}
		catch (const tc::Exception& e) 
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}

		fs.deleteDirectory(dir_child_path);
		fs.deleteFile(file_child_path);
		fs.deleteDirectory(kDirPath);
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
			tc::fs::IFile* fp = fs.openFile(tc::fs::Path(kDirPath) + tc::fs::Path(file_list[i]), tc::fs::FAM_CREATE);
			delete fp;
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.createDirectory(tc::fs::Path(kDirPath) + tc::fs::Path(dir_list[i]));
		}

		try
		{
			tc::fs::DirectoryInfo info;

			fs.getDirectoryListing(kDirPath, info);
			
			// + 2 for "." & ".."
			if (info.getDirectoryList().size() != (dir_list.size() + 2))
			{
				throw tc::Exception("Unexpected directory count");
			}

			if (info.getFileList().size() != file_list.size())
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
			fs.deleteFile(tc::fs::Path(kDirPath) + tc::fs::Path(file_list[i]));
		}

		for (size_t i = 0; i < dir_list.size(); i++)
		{
			fs.deleteDirectory(tc::fs::Path(kDirPath) + tc::fs::Path(dir_list[i]));
		}

		fs.deleteDirectory(tc::fs::Path(kDirPath));
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
		tc::fs::LocalFileSystem fs;

		tc::fs::DirectoryInfo info;
		fs.getDirectoryListing(kNotExistFilePath, info);
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
		tc::fs::LocalFileSystem fs;
		
		tc::fs::Path old_dir;
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
		fs.deleteDirectory(tc::fs::Path(kDirPath));
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
	testDeleteDirectory();
	testCreateDirectoryWhereDirectoryAlreadyExists();
	testDeleteDirectoryWhereDirectoryDoesNotExist();
	testCreateDirectoryWithUnicodePath();
	testDeleteDirectoryWithUnicodePath();
	testDeleteDirectoryThatIsActuallyAFile();
	testDeleteDirectoryThatHasChildren();
	testGetDirectoryListing();
	testGetDirectoryListingWhereDirectoryDoesNotExist();
	testChangeDirectory();

}