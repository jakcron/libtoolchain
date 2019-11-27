#pragma once
#include "ITestClass.h"

#include <tc/json.h>

class json_NumberUtils_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testToDoubleCase(const std::string& testName, const tc::json::Number& inputData, double expectedOutput);
	void testToDouble();
	void testToIntCase(const std::string& testName, const tc::json::Number& inputData, int64_t expectedOutput);
	void testToInt();
};