#pragma once
#include "ITestClass.h"

class bn_string_TestClass : public ITestClass
{
public:
	bn_string_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_EncodedSizeVersusLogicalSize();
	void test_StringSizeNeverExceedsLogicalSize();
	void test_EncodeStringRespectsLogicalSize();
};