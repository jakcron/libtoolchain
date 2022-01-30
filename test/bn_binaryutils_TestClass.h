#pragma once
#include "ITestClass.h"

#include <tc/bn.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotImplementedException.h>

class bn_binaryutils_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
};