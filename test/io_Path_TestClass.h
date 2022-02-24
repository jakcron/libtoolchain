#pragma once
#include "ITestClass.h"
#include <tc/io.h>
#include <tc/string.h>

class io_Path_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	
	// generic tests
	void testPathComposition(const std::string& test_name, const std::string& raw_path, const std::string& expected_path, size_t expected_element_count, tc::io::Path::Format path_format);
	void testPathComposition(const std::string& test_name, const std::string& raw_path, size_t expected_element_count, tc::io::Path::Format path_format);
	
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
	void test_Operator_LessThanTest();
};