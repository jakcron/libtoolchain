#pragma once
#include "ITestClass.h"

class io_VirtualFileSystem_TestClass : public ITestClass
{
public:
	io_VirtualFileSystem_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_CreateUninitializedFs_DefaultConstructor();
	void test_BadFsSnapshot_CreateConstructor();
	void test_CreateFs_CreateConstructor();
	void test_ThrowsOnBadPermissions_OpenFile();
	void test_ThrowsOnBadFileEntry_OpenFile();
	void test_ThrowsOnBadFileEntry_GetDirectoryListing();
	void test_ThrowsOnBadFileEntry_SetWorkingDirectory();
	void test_ThrowsOnBadFileEntry_GetCanonicalPath();
	void test_WorksForAllValidPaths_OpenFile();
	void test_WorksForAllValidPaths_GetDirectoryListing();
	void test_WorksForAllValidPaths_SetWorkingDirectory();
	void test_WorksForAllValidPaths_GetWorkingDirectory();
	void test_WorksForAllValidPaths_GetCanonicalPath();
	void test_DisposeWillChangeStateToUninitialized();
};