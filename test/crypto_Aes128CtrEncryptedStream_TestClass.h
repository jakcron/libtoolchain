#pragma once
#include "ITestClass.h"

#include <tc/ByteData.h>

class crypto_Aes128CtrEncryptedStream_TestClass : public ITestClass
{
public:
	crypto_Aes128CtrEncryptedStream_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_CreateEmptyStream_DefaultConstructor();
	void test_CreateValidStream_CreateConstructor();
	void test_RunTestCases();

	struct TestCase
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData counter;
		tc::ByteData ciphertext;
		int64_t read_offset;
		size_t read_size;
		tc::ByteData read_plaintext;
	};

	void util_Setup_TestCases(std::vector<crypto_Aes128CtrEncryptedStream_TestClass::TestCase>& test_cases);
};