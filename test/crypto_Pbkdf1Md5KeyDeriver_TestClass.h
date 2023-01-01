#pragma once
#include "ITestClass.h"

class crypto_Pbkdf1Md5KeyDeriver_TestClass : public ITestClass
{
public:
	crypto_Pbkdf1Md5KeyDeriver_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;

	bool isSlowTest() const { return true; }
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constants();
	void test_ConfirmTestVector_Class();
	void test_ConfirmTestVector_UtilFunc();
	void test_WillThrowExceptionOnZeroRounds();
	void test_WillThrowExceptionOnTooLargeDkSize();
	void test_GetBytesWithoutInitDoesNothing();
};