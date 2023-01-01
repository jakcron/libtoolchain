#pragma once
#include "ITestClass.h"


class io_MemoryStream_TestClass : public ITestClass
{
public:
	io_MemoryStream_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void testCreateEmptyStream_DefaultConstructor();
	void testCreateEmptyStream_SizedConstructor();
	void testCreatePopulatedStream();
	void testInitializeByCopyWithByteData();
	void testInitializeByMoveWithByteData();
	void testInitializeByCopyWithMemoryPointer();
	void testSeekBeginToZero();
	void testSeekBeginToMiddle();
	void testSeekBeginToEnd();
	void testSeekBeginPastEnd();
	void testSeekBeginNegative();
	void testSeekCurrentByZero();
	void testSeekCurrentToMiddle();
	void testSeekCurrentToEnd();
	void testSeekCurrentPastEnd();
	void testSeekCurrentNegative();
	void testSeekEndByZero();
	void testSeekEndPastEnd();
	void testSeekEndNegative();
	void testSeekEndTooNegative();
	void testReadAllDataAvailable();
	void testReadRequestsSubsetOfAvailableData();
	void testReadSomeDataAvailable();
	void testReadNoDataAvailable();
	void testWriteAllDataWritable();
	void testWriteToSomeOfDataAvailable();
	void testWriteSomeDataWritable();
	void testWriteNoDataWritable();
	void testWriteReadDataPersistence();
	void testResizeStreamLarger();
	void testResizeStreamSmaller();
	void testDispose();
};
