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
	
	// helpers
	void pathToUnixUtf8(const tc::fs::Path& path, std::string& out);
	void pathToWindowsUtf8(const tc::fs::Path& path, std::string& out);
	
	// generic tests
	void testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, PathType path_type);
	void testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, PathType path_type);
	
	// specific tests
	void test_Constructor_Default();
	void test_Method_pop_front();
	void test_Method_pop_back();
	void test_Method_push_front();
	void test_Method_push_back();
	void test_Method_clear();
	void test_Operator_Addition();
	void test_Operator_Append();
	void test_Scenario_AppendStressTest();
	void test_Operator_EqualityTest();
	void test_Operator_InequalityTest();
};