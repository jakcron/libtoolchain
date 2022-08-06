#pragma once
#include "ITestClass.h"

class bn_binaryutils_TestClass : public ITestClass
{
public:
	bn_binaryutils_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_RoundUpFunc();
	void util_RoundUpFuncTestCase(uint32_t value, uint32_t alignment, uint32_t expected_result);

	void test_AlignFunc();
	void util_AlignFuncTestCase(uint32_t value, uint32_t alignment, uint32_t expected_result);

	void test_MakeStructMagicU32Func();
	void util_MakeStructMagicU32FuncTestCase(const char* struct_magic_str, uint32_t expected_result);

	void test_MakeStructMagicU64Func();
	void util_MakeStructMagicU64FuncTestCase(const char* struct_magic_str, uint64_t expected_result);
	
};