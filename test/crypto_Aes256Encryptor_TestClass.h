#pragma once
#include "ITestClass.h"

#include <vector>
#include <tc/ByteData.h>

class crypto_Aes256Encryptor_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_Constants();
	void test_UseClassEnc();
	void test_UseClassDec();

	struct TestCase
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData plaintext;
		tc::ByteData ciphertext;
	};

	void util_Setup_TestCases(std::vector<crypto_Aes256Encryptor_TestClass::TestCase>& test_cases);
};