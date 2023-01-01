#pragma once
#include "ITestClass.h"

class bn_endian_TestClass : public ITestClass
{
public:
	bn_endian_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void testLocalBSwap16();
	void testLocalBSwap32();
	void testLocalBSwap64();
	void testBeUint64Inline();
	void testBeUint32Inline();
	void testBeUint16Inline();
	void testLeUint64Inline();
	void testLeUint32Inline();
	void testLeUint16Inline();

	void testBeSwap64Inline();
	void testBeSwap32Inline();
	void testBeSwap16Inline();
	void testLeSwap64Inline();
	void testLeSwap32Inline();
	void testLeSwap16Inline();

	void testBe64TemplateClass();
	void testBe32TemplateClass();
	void testBe16TemplateClass();
	void testLe64TemplateClass();
	void testLe32TemplateClass();
	void testLe16TemplateClass();
};