#pragma once
#include "ITestClass.h"

class fs_LocalFileSystem_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testFileCreate();
	void testFileRead();
	void testFileEdit();
	void testUnicodePath();
	void testNotPresentFileReadOnly();
	void testNotPresentFileEdit();
	void testTryWriteInReadOnlyMode();
	void testTryReadBeyondFileSize();
	void testRemoveAsciiFile();
	void testRemoveUnicodeFile();
	void testRemoveFileThatDoesNotExist();
	void testCreateDirectory();
	void testRemoveDirectory();
	void testCreateDirectoryWhereDirectoryAlreadyExists();
	void testRemoveDirectoryWhereDirectoryDoesNotExist();
	void testCreateDirectoryWithUnicodePath();
	void testRemoveDirectoryWithUnicodePath();
	void testRemoveDirectoryThatIsActuallyAFile();
	void testRemoveDirectoryThatHasChildren();
	void testGetDirectoryListing();
	void testGetDirectoryListingWhereDirectoryDoesNotExist();
	void testChangeDirectory();
};