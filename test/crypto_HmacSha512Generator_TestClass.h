#pragma once
#include "ITestClass.h"

#include <tc/ByteData.h>

class crypto_HmacSha512Generator_TestClass : public ITestClass
{
public:
	crypto_HmacSha512Generator_TestClass();

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
	void test_SingleUpdateCall();
	void test_MultiUpdateCall();
	void test_UtilFunc();

	void test_NoInitNoUpdateDoMac();
	void test_NoInitDoUpdateDoMac();
	void test_DoInitNoUpdateDoMac();
	void test_DoInitNoKeyDoUpdateDoMac();
	void test_DoInitNoKeyNoUpdateDoMac();

	void test_CallGetMacRepeatedly();

	struct TestCase
	{
		std::string test_name;
		tc::ByteData in_data;
		tc::ByteData in_key;
		tc::ByteData out_mac;
	};

	void util_Setup_Rfc2202_TestCases(std::vector<crypto_HmacSha512Generator_TestClass::TestCase>& test_cases);
};