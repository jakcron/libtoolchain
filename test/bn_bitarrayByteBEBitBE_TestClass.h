#pragma once
#include "ITestClass.h"

class bn_bitarrayByteBEBitBE_TestClass : public ITestClass
{
public:
	bn_bitarrayByteBEBitBE_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Size();
	void test_TestBit();
	void test_SetBit();
	void test_ResetBit();
	void test_FlipBit();

	using testtype_t = tc::bn::bitarray<sizeof(uint32_t), false, false>;

	void helper_TestBit(const std::string& test_name, const testtype_t& bitarray, const std::vector<size_t>& expected_set_bits);
};