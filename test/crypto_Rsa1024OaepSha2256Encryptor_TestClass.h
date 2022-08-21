#pragma once
#include "ITestClass.h"

class crypto_Rsa1024OaepSha2256Encryptor_TestClass : public ITestClass
{
public:
	crypto_Rsa1024OaepSha2256Encryptor_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;

	bool isSlowTest() const { return true; }
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constants();
	void test_UseClassDec();
	void test_UseClassEnc();
	void test_UseUtilFuncDec();
	void test_UseUtilFuncEnc();
	void test_UnspecifiedSeedProducesDifferentBlock();

	void test_DoesNothingWhenNotInit();
	void test_InitializeThrowsExceptionOnBadInput();
	void test_EncryptReturnsFalseOnBadInput();
	void test_DecryptReturnsFalseOnBadInput();
};