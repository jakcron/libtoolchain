#pragma once
#include "ITestClass.h"

class ByteData_TestClass : public ITestClass
{
public:
	ByteData_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constructor_DefaultConstructor();
	void test_Constructor_InitializerList();
	void test_Constructor_CreateZeroSized();
	void test_Constructor_CreateSmallSized();
	void test_Constructor_CreateLargeSized();
	void test_Constructor_ThrowExceptForBadAlloc();
	void test_Constructor_CreateFromPtr();
	void test_ImplicitCopy_CopyInSameScope();
	void test_ImplicitCopy_CopyOntoInitiallisedByteData();
	void test_ImplicitMove_CopyInSameScope();
	void test_ImplicitMove_MoveOntoInitiallisedByteData();
	void test_EqualityOperator();
	void test_InequalityOperator();
};