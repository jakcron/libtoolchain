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
	void testDeleteAsciiFile();
	void testDeleteUnicodeFile();
	void testDeleteFileThatDoesNotExist();
	void testCreateDirectory();
	void testDeleteDirectory();
	void testCreateDirectoryWhereDirectoryAlreadyExists();
	void testDeleteDirectoryWhereDirectoryDoesNotExist();
	void testCreateDirectoryWithUnicodePath();
	void testDeleteDirectoryWithUnicodePath();
	void testDeleteDirectoryThatIsActuallyAFile();
	void testDeleteDirectoryThatHasChildren();
	void testGetDirectoryListing();
	void testGetDirectoryListingWhereDirectoryDoesNotExist();
	void testChangeDirectory();
};