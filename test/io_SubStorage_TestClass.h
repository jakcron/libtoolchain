#pragma once
#include "ITestClass.h"

class io_SubStorage_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testSubStorageRootPath();
	void testCreateFile();
	void testOpenFile();
	void testRemoveFile();
	void testCreateDirectory();
	void testRemoveDirectory();
	void testGetDirectoryListing();
	void testNavigateUpSubStorageEscape();
	void testOpenFileOutsideSubStorage();
};