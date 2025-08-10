#pragma once
#include "ITestClass.h"
#include <tc/crypto/EccCurveType.h>

class crypto_EccKeyGenerator_TestClass : public ITestClass
{
public:
	crypto_EccKeyGenerator_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_sbox();

	void test_Class();
	void test_UtilFunc();

	void test_MultipleObjectsCreateDifferentData();
	void test_RepeatedCallsCreateDifferentData();

	struct sCurveInfo {
		std::string curve_name;
		tc::crypto::EccCurveType curve_type;
		size_t integer_bit_size;
		bool curve_defines_Q_y;
	};

	void getCurveTestList(std::vector<sCurveInfo>& curve_test_list) const;
};