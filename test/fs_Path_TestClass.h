#pragma once
#include "ITestClass.h"
#include <tc/fs.h>
#include <tc/string.h>

class fs_Path_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	enum PathType
	{
		UNIX_PATH,
		WIN32_PATH
	};
	
	void pathToUnixUtf8(const tc::fs::Path& path, std::string& out);
	void pathToWindowsUtf8(const tc::fs::Path& path, std::string& out);
	void testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, PathType path_type);
	void testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, PathType path_type);
	void testEqualComparisonOperator();
	void testUnequalComparisonOperator();
	void testAdditionOperator();
	void testAppendOperator();
	void testAppendStressTest();
};