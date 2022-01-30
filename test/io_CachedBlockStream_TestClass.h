#pragma once
#include "ITestClass.h"

#include <tc/io.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotImplementedException.h>

class io_CachedBlockStream_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
};