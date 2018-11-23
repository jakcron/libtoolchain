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
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_CREATE);

		if ((*file)->size() != 0)
		{
			throw tc::Exception("main.cpp", "file opened in create mode does not have a size of 0");
		}

		(*file)->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

		
		if ((*file)->size() != kRandomString.length())
		{
			throw tc::Exception("main.cpp", "after writing data, file size is not correct");
		}
		

		std::cout << "[LocalFileSystem-test] testFileCreate() : PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[LocalFileSystem-test] testFileCreate() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testFileRead()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		if ((*file)->size() != kRandomString.length())
		{
			throw tc::Exception("main.cpp", "Unexpected file size");
		}

		tc::SharedPtr<byte_t> check = new byte_t[kRandomString.length()];
		(*file)->read(*check, kRandomString.length());

		if (memcmp(*check, kRandomString.c_str(), kRandomString.size()) != 0)
		{
			throw tc::Exception("main.cpp", "Data in file was not correct");
		}

		std::cout << "[LocalFileSystem-test] testFileRead() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testFileRead() : FAIL (Test opening file in read mode and confirming the data is correct(" << e.what() << "))" << std::endl;
	}
}

void testFileEdit()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_EDIT);

		if ((*file)->size() != kRandomString.length())
		{
			throw tc::Exception("main.cpp", "Unexpected file size");
		}

		(*file)->seek(kRandomString.length());
		(*file)->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

		(*file)->seek(7);
		(*file)->write((const byte_t*)kTestPhrase.c_str(), kTestPhrase.length());

		tc::SharedPtr<byte_t> check = new byte_t[kRandomString.length()*2];
		(*file)->seek(0);
		(*file)->read(*check, kRandomString.length()*2);

		if (memcmp(*check + kRandomString.length(), kRandomString.c_str(), kRandomString.size()) != 0)
		{
			throw tc::Exception("main.cpp", "Data(kRandomStr[1][:]) in file was not correct");
		}

		if (memcmp(*check + 7, kTestPhrase.c_str(), kTestPhrase.size()) != 0)
		{
			throw tc::Exception("main.cpp", "Data(kTestPhrase[:]) in file was not correct");
		}

		if (memcmp(*check, kRandomString.c_str(), 7) != 0)
		{
			throw tc::Exception("main.cpp", "Data(kRandomStr[0][0:7]) in file was not correct");
		}

		std::cout << "[LocalFileSystem-test] testFileEdit() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testFileEdit() : FAIL (Test opening file in edit mode and confirming the data is correct (" << e.what() << "))" << std::endl;
	}
}

void testUnicodePath()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kUtf8TestPath, tc::filesystem::FAM_CREATE);

		if ((*file)->size() != 0)
		{
			throw tc::Exception("main.cpp", "file opened in create mode does not have a size of 0\n");
		}

		(*file)->write((const byte_t*)kRandomString.c_str(), kRandomString.length());


		std::cout << "[LocalFileSystem-test] testUnicodePath() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testUnicodePath() : FAIL (Test opening file in create mode and writing data (" << e.what() << "))" << std::endl;
	}
}

void testNotPresentFileReadOnly()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kNotExistFilePath, tc::filesystem::FAM_READ);

		std::cout << "[LocalFileSystem-test] testNotPresentFileReadOnly() : FAIL (Did not throw on failure to open for read access file)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testNotPresentFileReadOnly() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testNotPresentFileEdit()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kNotExistFilePath, tc::filesystem::FAM_EDIT);

		std::cout << "[LocalFileSystem-test] testNotPresentFileEdit() : FAIL (Did not throw on failure to open for edit access file)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testNotPresentFileEdit() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testTryWriteInReadOnlyMode()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		(*file)->write((const byte_t*)kRandomString.c_str(), kRandomString.length());

		std::cout << "[LocalFileSystem-test] testTryWriteInReadOnlyMode() : FAIL (Did not throw exception when write() was called)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testTryWriteInReadOnlyMode() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testTryReadBeyondFileSize()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_READ);

		tc::SharedPtr<byte_t> buffer = new byte_t[0x10000];

		(*file)->read(*buffer, 0x10000);

		std::cout << "[LocalFileSystem-test] testTryReadBeyondFileSize() : FAIL (Did not throw exception when read() attemped to read beyond file size)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testTryReadBeyondFileSize() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testDeleteAsciiFile()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.deleteFile(kAsciiFilePath);
		std::cout << "[LocalFileSystem-test] testDeleteAsciiFile() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testDeleteAsciiFile() : FAIL" << std::endl;
	}
}

void testDeleteUnicodeFile()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.deleteFile(kUtf8TestPath);
		std::cout << "[LocalFileSystem-test] testDeleteUnicodeFile() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testDeleteUnicodeFile() : FAIL" << std::endl;
	}
}

void testDeleteFileThatDoesNotExist()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.deleteFile(kNotExistFilePath);
		std::cout << "[LocalFileSystem-test] testDeleteFileThatDoesNotExist() : FAIL (Did not throw exception when file was not present on FS)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testDeleteFileThatDoesNotExist() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testCreateDirectory()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.createDirectory(kDirPath);
		std::cout << "[LocalFileSystem-test] testCreateDirectory() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testCreateDirectory() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testCreateDirectoryWhereDirectoryAlreadyExists()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.createDirectory(kDirPath);
		std::cout << "[LocalFileSystem-test] testCreateDirectoryWhereDirectoryAlreadyExists() : FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testCreateDirectoryWhereDirectoryAlreadyExists() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectory()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.removeDirectory(kDirPath);
		std::cout << "[LocalFileSystem-test] testRemoveDirectory() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testRemoveDirectory() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectoryWhereDirectoryDoesNotExist()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.removeDirectory(kDirPath);
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryWhereDirectoryDoesNotExist() : FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryWhereDirectoryDoesNotExist() : PASS (" << e.error() << ")" << std::endl;
	}
}

void testCreateDirectoryWithUnicodePath()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.createDirectory(kUtf8DirPath);
		std::cout << "[LocalFileSystem-test] testCreateDirectoryWithUnicodePath() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testCreateDirectoryWithUnicodePath() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectoryWithUnicodePath()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		fs.removeDirectory(kUtf8DirPath);
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryWithUnicodePath() : PASS" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryWithUnicodePath() : FAIL (" << e.error() << ")" << std::endl;
	}
}

void testRemoveDirectoryThatIsActuallyAFile()
{
	tc::filesystem::LocalFileSystem fs;
	
	try 
	{
		tc::SharedPtr<tc::filesystem::IFile> file = fs.openFile(kAsciiFilePath, tc::filesystem::FAM_CREATE);
		fs.removeDirectory(kAsciiFilePath);
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatIsActuallyAFile() : FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatIsActuallyAFile() : PASS (" << e.error() << ")" << std::endl;
	}

	fs.deleteFile(kAsciiFilePath);
}

void testRemoveDirectoryThatHasChildren()
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
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatHasChildren() : FAIL (did not throw exception on expected error)" << std::endl;
	}
	catch (const tc::Exception& e) 
	{
		std::cout << "[LocalFileSystem-test] testRemoveDirectoryThatHasChildren() : PASS (" << e.error() << ")" << std::endl;
	}

	fs.removeDirectory(dir_child_path);
	fs.deleteFile(file_child_path);
	fs.removeDirectory(kDirPath);
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
	testCreateDirectoryWhereDirectoryAlreadyExists();
	testRemoveDirectory();
	testRemoveDirectoryWhereDirectoryDoesNotExist();
	testCreateDirectoryWithUnicodePath();
	testRemoveDirectoryWithUnicodePath();
	testRemoveDirectoryThatIsActuallyAFile();
	testRemoveDirectoryThatHasChildren();
}