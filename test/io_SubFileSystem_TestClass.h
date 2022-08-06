#pragma once
#include "ITestClass.h"

class io_SubFileSystem_TestClass : public ITestClass
{
public:
	io_SubFileSystem_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void testBaseFileSystemRetainsWorkingDirectory();
	void testGetSetWorkingDirectory();
	void testCreateFile();
	void testOpenFile();
	void testRemoveFile();
	void testCreateDirectory();
	void testRemoveDirectory();
	void testGetDirectoryListing();
	void testNavigateUpSubFileSystemEscape();
	void testOpenFileOutsideSubFileSystem();
};