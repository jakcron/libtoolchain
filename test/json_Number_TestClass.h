#pragma once
#include "ITestClass.h"

#include <tc/json.h>

class json_Number_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testEqualityOperatorCase(const std::string& testName, const tc::json::Number& a, const tc::json::Number& b, bool shouldEqual);
	void testEqualityOperator();
	void testParametisedConstructorCase(const std::string& testName, uint64_t i_val, bool i_pos, uint64_t f_val, size_t f_digits, uint64_t e_val, bool e_pos);
	void testParametisedConstructor();
	void testDefaultConstructor();
	void testIntConstructorCase(const std::string& testName, int64_t inputData, const tc::json::Number& expectedOutput);
	void testIntConstructor();
};