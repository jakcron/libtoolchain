#pragma once
#include "ITestClass.h"

class io_StreamSource_TestClass : public ITestClass
{
public:
	io_StreamSource_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void testDefaultConstructor();
	void testCreateConstructor();
	void testCreateFromStreamWithoutSeek();
	void testCreateFromStreamWithoutRead();
	void testCreateFromStreamWithoutWrite();
	void testNegativeOffset();
	void testTooLargeOffset();
};
