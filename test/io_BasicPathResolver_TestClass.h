#pragma once
#include "ITestClass.h"

#include <tc/io/Path.h>

class io_BasicPathResolver_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_ResolveRootDirRelativePaths();
	void test_ResolveWorkingDirectoryRelativePaths();

	void util_RunResolutionTest(const tc::io::Path& in_path, const tc::io::Path& in_working_dir_path, const tc::io::Path& expected_resolved_path);
};