#pragma once
#include "ITestClass.h"

#include <vector>
#include <tc/ByteData.h>

class crypto_Aes256XtsEncryptor_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_Constants();
	void test_UseClassEnc();
	void test_UseClassDec();
	void test_UseUtilFuncEnc();
	void test_UseUtilFuncDec();

	struct TestCase
	{
		std::string test_name;
		tc::ByteData key1;
		tc::ByteData key2;
		uint64_t data_unit;
		uint64_t data_unit_sequence_number;
		tc::ByteData plaintext;
		tc::ByteData ciphertext;
	};

	void util_Setup_IEEE1619_2007_TestCases(std::vector<crypto_Aes256XtsEncryptor_TestClass::TestCase>& test_cases);
};