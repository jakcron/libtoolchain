#pragma once
#include "ITestClass.h"

class io_OverlayedSource_TestClass : public ITestClass
{
public:
	io_OverlayedSource_TestClass();

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
	void testSingleOverlayConstructor();
	void testMultiOverlayConstructor();
	void testNullBaseStream();
	void testNullOverlayStream();
	void testOverlayStreamTooSmallForOverlayRegion();
	void testOverlayRegionBeforeBaseStream();
	void testOverlayRegionPartlyBeforeBaseStream();
	void testOverlayRegionAfterBaseStream();
	void testOverlayRegionPartlyAfterBaseStream();
};
