#pragma once
#include "ITestClass.h"

class io_EmptyStream_TestClass : public ITestClass
{
public:
	io_EmptyStream_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	// test constructor sets properties properly
	void testCreateEmptyStream_DefaultConstructor();
	
	// test seek() throws exceptions where it should, but ultimately return 0
	void testSeekBeginToZero();
	void testSeekBeginPastEnd();
	void testSeekBeginNegative();
	void testSeekCurrentByZero();
	void testSeekCurrentPastEnd();
	void testSeekCurrentNegative();
	void testSeekEndByZero();
	void testSeekEndPastEnd();
	void testSeekEndNegative();
	void testSeekThrowsOnBadOriginValue();

	// test read() ultimately reads no data into buffer
	void testReadDataIsAlwaysZero();
	void testReadThrowsOnNullptr();

	// test that write()/setLength() throw not support exception
	void testWriteThrowsUnsupported();
	void testSetLengthThrowsUnsupported();

	// test that flush/dispose does nothing
	void testFlushDoesNothing();
	void testDisposeDoesNothing();
};
