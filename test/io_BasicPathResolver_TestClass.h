#pragma once
#include "ITestClass.h"

#include <tc/io/Path.h>

class io_BasicPathResolver_TestClass : public ITestClass
{
public:
	io_BasicPathResolver_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_EmptyStateAfterDefaultConstructor();
	void test_setCurrentDirectory();
	void test_setExplicitRootLabels();
	void test_ResolveRootDirRelativePaths();
	void test_ResolveWorkingDirectoryRelativePaths();
	void test_ResolvePathsWithCustomRootLabels();

	void util_RunResolutionTest(const tc::io::Path& in_path, const tc::io::Path& in_working_dir_path, const tc::io::Path& expected_resolved_path);
	void util_RunResolutionTest(const tc::io::Path& in_path, const tc::io::Path& in_working_dir_path, const std::vector<std::string>& root_labels, const tc::io::Path& expected_resolved_path);
};