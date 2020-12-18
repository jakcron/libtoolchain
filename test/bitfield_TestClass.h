#pragma once
#include "ITestClass.h"

class bitfield_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_BEByteOrderBEBitOrder();
	void test_LEByteOrderBEBitOrder();
	void test_BEByteOrderLEBitOrder();
	void test_LEByteOrderLEBitOrder();
};