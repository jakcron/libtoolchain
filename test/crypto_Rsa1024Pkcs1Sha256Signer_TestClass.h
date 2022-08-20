#pragma once
#include "ITestClass.h"

class crypto_Rsa1024Pkcs1Sha256Signer_TestClass : public ITestClass
{
public:
	crypto_Rsa1024Pkcs1Sha256Signer_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constants();
	void test_UseClassSign();
	void test_UseClassVerify();
	void test_UseUtilFuncSign();
	void test_UseUtilFuncVerify();

	void test_DoesNothingWhenNotInit();
	void test_InitializeThrowsExceptionOnBadInput();
	void test_SignReturnsFalseOnBadInput();
	void test_VerifyReturnsFalseOnBadInput();
};