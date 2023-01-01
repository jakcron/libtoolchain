#pragma once
#include "ITestClass.h"
#include <tc.h>

class cli_FormatUtil_TestClass : public ITestClass
{
public:
	cli_FormatUtil_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void testHexStringToBytes();
	void testFormatBytesAsString();
	void testFormatBytesAsStringWithLineLimit();
	void testFormatListWithLineLimit();
	void testFormatBytesAsHxdHexString();
};