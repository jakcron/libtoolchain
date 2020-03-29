#pragma once
#include "ITestClass.h"

#include <tc/io/OverlayedSource.h>

class io_OverlayedSource_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
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

	void pullTestHelper(tc::io::ISource& source, int64_t offset, size_t len, size_t expected_len, const byte_t* expected_data);
};
