#pragma once
#include "ITestClass.h"

class crypto_Sha1Generator_TestClass : public ITestClass
{
public:
	crypto_Sha1Generator_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constants();
	void test_SingleUpdateCall();
	void test_MultiUpdateCall();
	void test_UtilFunc();

	void test_NoInitNoUpdateDoHash();
	void test_NoInitDoUpdateDoHash();
	void test_DoInitNoUpdateDoHash();
	void test_CallGetHashRepeatedly();
};