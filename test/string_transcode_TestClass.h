#pragma once
#include "ITestClass.h"

#include <tc/string.h>

class string_transcode_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testUtf8ToUtf16();
	void testUtf16ToUtf8();
};