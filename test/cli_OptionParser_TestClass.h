#pragma once
#include "ITestClass.h"
#include <tc/cli/OptionParser.h>

class cli_OptionParser_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_Constructor_DefaultConstructor();
};