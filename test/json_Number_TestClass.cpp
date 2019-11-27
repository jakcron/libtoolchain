#include <tc/Exception.h>
#include <iostream>
#include <climits>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

#include "json_Number_TestClass.h"

void json_Number_TestClass::runAllTests()
{
	std::cout << "[tc::json::Number] START" << std::endl;
	testEqualityOperator();
	testParametisedConstructor();
	testDefaultConstructor();
	testIntConstructor();
	std::cout << "[tc::json::Number] END" << std::endl;
}

void json_Number_TestClass::testEqualityOperatorCase(const std::string& testName, const tc::json::Number& a, const tc::json::Number& b, bool shouldEqual)
{
	if ((a == b) != shouldEqual)
	{
		throw tc::Exception(testName, std::string("operator==() returned ") + (shouldEqual ? "false" : "true") + std::string(". When a,b were ") + (shouldEqual ? "equal" : "not equal"));
	}

	if ((a != b) != !shouldEqual)
	{
		throw tc::Exception(testName, std::string("operator!=() returned ") + (!shouldEqual ? "false" : "true") + std::string(". When a,b were ") + (shouldEqual ? "equal" : "not equal"));
	}
}

void json_Number_TestClass::testEqualityOperator()
{
	std::cout << "[tc::json::Number] testEqualityOperator : " << std::flush;
	try
	{
		tc::json::Number x,y;

		// test 0 KnownSameZeros
		x.i_val = y.i_val = 0;
		x.i_pos = y.i_pos = false;
		x.f_val = y.f_val = 0;
		x.f_digits = y.f_digits = 0;
		x.e_val = y.e_val = 0;
		x.e_pos = y.e_pos = false;
		testEqualityOperatorCase("KnownSameZeros", x, y, true);

		// test 1 KnownSameMaxVal
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;
		testEqualityOperatorCase("KnownSameMaxVal", x, y, true);

		// test 2 KnownSameMaxVal except i_val differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.i_val = 0;
		testEqualityOperatorCase("Different i_val", x, y, false);

		// test 3 KnownSameMaxVal except i_pos differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.i_pos = false;
		testEqualityOperatorCase("Different i_pos", x, y, false);

		// test 4 KnownSameMaxVal except f_val differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.f_val = 0;
		testEqualityOperatorCase("Different f_val", x, y, false);

		// test 5 KnownSameMaxVal except f_digits differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.f_digits = 0;
		testEqualityOperatorCase("Different f_digits", x, y, false);

		// test 6 KnownSameMaxVal except e_val differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.e_val = 0;
		testEqualityOperatorCase("Different e_val", x, y, false);

		// test 7 KnownSameMaxVal except e_pos differs
		x.i_val = y.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = y.i_pos = true;
		x.f_val = y.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = y.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = y.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = y.e_pos = true;

		x.e_pos = false;
		testEqualityOperatorCase("Different e_pos", x, y, false);

		// test 8 Completely different
		x.i_val = std::numeric_limits<uint64_t>::max();
		x.i_pos = true;
		x.f_val = std::numeric_limits<uint64_t>::max();
		x.f_digits = std::numeric_limits<size_t>::max();
		x.e_val = std::numeric_limits<uint64_t>::max();
		x.e_pos = true;

		y.i_val = 0;
		y.i_pos = false;
		y.f_val = 0;
		y.f_digits = 0;
		y.e_val = 0;
		y.e_pos = false;
		testEqualityOperatorCase("Completely different", x, y, false);

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void json_Number_TestClass::testParametisedConstructorCase(const std::string& testName, uint64_t i_val, bool i_pos, uint64_t f_val, size_t f_digits, uint64_t e_val, bool e_pos)
{
	tc::json::Number testNum, expectedNum;

	expectedNum.i_val = i_val;
	expectedNum.i_pos = i_pos;
	expectedNum.f_val = f_val;
	expectedNum.f_digits = f_digits;
	expectedNum.e_val = e_val;
	expectedNum.e_pos = e_pos;

	testNum  = tc::json::Number(expectedNum.i_val, expectedNum.i_pos, expectedNum.f_val, expectedNum.f_digits, expectedNum.e_val, expectedNum.e_pos);

	if (testNum != expectedNum)
	{
		std::stringstream error_desc;

		error_desc << "Data {";
		error_desc << ".i_val=" << std::dec << testNum.i_val << " (expected " << std::dec << expectedNum.i_val << ")" << ", ";
		error_desc << ".i_pos=" << (testNum.i_pos? "true" : "false") << " (expected " << (expectedNum.i_pos? "true" : "false") << ")" << ", ";
		error_desc << ".f_val=" << std::dec << testNum.f_val << " (expected " << std::dec << expectedNum.f_val << ")" << ", ";
		error_desc << ".f_digits=" << std::dec << testNum.f_digits << " (expected " << std::dec << expectedNum.f_digits << ")" << ", ";
		error_desc << ".e_val=" << std::dec << testNum.e_val << " (expected " << std::dec << expectedNum.e_val << ")" << ", ";
		error_desc << ".e_pos=" << (testNum.e_pos? "true" : "false") << " (expected " << (expectedNum.e_pos? "true" : "false") << ")";
		error_desc << "}";
		
		throw tc::Exception(testName, error_desc.str());
	}
}

void json_Number_TestClass::testParametisedConstructor()
{
	std::cout << "[tc::json::Number] testParametisedConstructor : " << std::flush;
	try
	{
		struct sTestCase 
		{
			const std::string& case_name;
			uint64_t i_val;
			bool i_pos;
			uint64_t f_val;
			size_t f_digits;
			uint64_t e_val;
			bool e_pos;
		};
		
		std::vector<sTestCase> cases = 
		{
			{"MiscDataFalseBools", 213, false, 8441, 4, 9878656, false},
			{"MiscDataTrueBools", 135, true, 589342444, 9, 991, true},
			{"MiscDataMixedBools", 987, false, 99, 2, 21333, true}
		};

		for (auto itr = cases.begin(); itr != cases.end(); itr++)
		{
			testParametisedConstructorCase(itr->case_name, itr->i_val, itr->i_pos, itr->f_val, itr->f_digits, itr->e_val, itr->e_pos);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void json_Number_TestClass::testDefaultConstructor()
{
	std::cout << "[tc::json::Number] testDefaultConstructor : " << std::flush;
	try
	{
		tc::json::Number x;

		if (x.i_val != 0 ||
			x.i_pos != true ||
			x.f_val != 0 ||
			x.f_digits != 0 ||
			x.e_val != 0 ||
			x.e_pos != true)
		{
			throw tc::Exception("Number state was not as expected post default constructor");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void json_Number_TestClass::testIntConstructorCase(const std::string& testName, int64_t inputData, const tc::json::Number& expectedOutput)
{
	tc::json::Number x(inputData);

	if (x != expectedOutput)
	{
		std::stringstream error_desc;

		error_desc << "Data {";
		error_desc << ".i_val=" << std::dec << x.i_val << " (expected " << std::dec << expectedOutput.i_val << ")" << ", ";
		error_desc << ".i_pos=" << (x.i_pos? "true" : "false") << " (expected " << (expectedOutput.i_pos? "true" : "false") << ")";
		error_desc << "}";
		
		throw tc::Exception(testName, error_desc.str());
	}
}

void json_Number_TestClass::testIntConstructor()
{
	std::cout << "[tc::json::Number] testIntConstructor : " << std::flush;
	try
	{
		struct sTestCase 
		{
			std::string case_name;
			int64_t input_data;
			tc::json::Number expected_output;
		};
		
		std::vector<sTestCase> cases = 
		{
			{"Number(0)", 0LL, tc::json::Number((uint64_t)0ULL, (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true)},
			{"Number(1)", 1LL, tc::json::Number((uint64_t)1ULL, (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true)},
			{"Number(-1)", -1LL, tc::json::Number((uint64_t)1ULL, (bool)false, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true)},
			{"Number(std::numeric_limits<int64_t>::max())", std::numeric_limits<int64_t>::max(), tc::json::Number((uint64_t)std::numeric_limits<int64_t>::max(), (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true)},
			{"Number(std::numeric_limits<int64_t>::min())", std::numeric_limits<int64_t>::min(), tc::json::Number((uint64_t)llabs(std::numeric_limits<int64_t>::min()), (bool)false, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true)},
			//{"WillFail", 0, tc::json::Number((uint64_t)5, (bool)false, (uint64_t)5ULL, (size_t)5UL, (uint64_t)5ULL, (bool)true)},
		};

		for (auto itr = cases.begin(); itr != cases.end(); itr++)
		{
			testIntConstructorCase(itr->case_name, itr->input_data, itr->expected_output);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}