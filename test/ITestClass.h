#pragma once
#include <tc/types.h>
#include "TestException.h"

class ITestClass
{
public:
	struct TestResult
	{
		std::string test_name;
		std::string result;
		std::string comments;
	};

	virtual ~ITestClass() = default;

		// this will run the tests
	virtual void runAllTests() = 0;

		// this is the label for this test (for filtering purposes)
	virtual const std::string& getTestTag() const = 0;

		// these are the test results (only populated after running runAllTests())
	virtual const std::vector<ITestClass::TestResult>& getTestResults() const = 0;

	virtual bool isSlowTest() const { return false; }
};