#pragma once
#include "ITestClass.h"

class endian_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testLocalBSwap16();
	void testLocalBSwap32();
	void testLocalBSwap64();
	void testBeUint64Inline();
	void testBeUint32Inline();
	void testBeUint16Inline();
	void testLeUint64Inline();
	void testLeUint32Inline();
	void testLeUint16Inline();
	void testBeUint64Class();
	void testBeUint32Class();
	void testBeUint16Class();
	void testLeUint64Class();
	void testLeUint32Class();
	void testLeUint16Class();
};