#include <tc/Exception.h>
#include <iostream>
#include <climits>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

#include "json_NumberUtils_TestClass.h"

void json_NumberUtils_TestClass::runAllTests()
{
	std::cout << "[tc::json::NumberUtils] START" << std::endl;
	testToDouble();
	testToInt();
	std::cout << "[tc::json::NumberUtils] END" << std::endl;
}

void json_NumberUtils_TestClass::testToDoubleCase(const std::string& testName, const tc::json::Number& inputData, double expectedOutput)
{
	double x = tc::json::toDouble(inputData);

	double epsilon = 1.00 / pow(10, inputData.f_digits);
	epsilon /= 2;

	if (fabs(x - expectedOutput) >= epsilon)
	{
		std::stringstream error_desc;

		error_desc << "Data {";
		error_desc << "epsilon=" << std::dec << epsilon << ", ";
		error_desc << "toDouble()=" << x << " (expected " << std::dec << expectedOutput << ")";
		error_desc << "}";
		
		throw tc::Exception(testName, error_desc.str());
	}
}

void json_NumberUtils_TestClass::testToDouble()
{
	std::cout << "[tc::json::NumberUtils] testToDouble : " << std::flush;
	try
	{
		struct sTestCase 
		{
			std::string case_name;
			tc::json::Number input_data;
			double expected_output;
		};
		
		std::vector<sTestCase> cases = 
		{
			{".f_val digits match .f_digits", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)3456ULL, (size_t)4UL, (uint64_t)0ULL, (bool)true), 12.3456},
			{".f_val sig figures > .f_digits, rounded up", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)3456ULL, (size_t)2UL, (uint64_t)0ULL, (bool)true), 12.35},
			{".f_val sig figures > .f_digits, not rounded", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)3416ULL, (size_t)2UL, (uint64_t)0ULL, (bool)true), 12.34},
			{".f_val non-zero .f_digits==0 rounded up", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)9456ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), 13},
			{".f_val non-zero .f_digits==0 not rounded", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)3456ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), 12},
			{".f_val sig figures < .f_digits)", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)3456ULL, (size_t)6UL, (uint64_t)0ULL, (bool)true), 12.003456},
			{".f_val==0, .f_digits==0)", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), 12},
			{".f_val==0, .f_digits==6)", tc::json::Number((uint64_t)12, (bool)true, (uint64_t)0ULL, (size_t)6UL, (uint64_t)0ULL, (bool)true), 12.000000},
			{"1.234 e+4)", tc::json::Number((uint64_t)1, (bool)true, (uint64_t)234ULL, (size_t)3UL, (uint64_t)4ULL, (bool)true), 12340},
			{"1234.5678 e+3)", tc::json::Number((uint64_t)1234, (bool)true, (uint64_t)5678ULL, (size_t)4UL, (uint64_t)3ULL, (bool)true), 1234567.8},
			{"1234.5678 e-3)", tc::json::Number((uint64_t)1234, (bool)true, (uint64_t)5678ULL, (size_t)4UL, (uint64_t)3ULL, (bool)false), 1.2345678},
			//{"WillFail", tc::json::Number((uint64_t)5, (bool)false, (uint64_t)5ULL, (size_t)5UL, (uint64_t)5ULL, (bool)true), 0.0}
		};

		for (auto itr = cases.begin(); itr != cases.end(); itr++)
		{
			testToDoubleCase(itr->case_name, itr->input_data, itr->expected_output);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void json_NumberUtils_TestClass::testToIntCase(const std::string& testName, const tc::json::Number& inputData, int64_t expectedOutput)
{
	int64_t x = tc::json::toInt64(inputData);

	if (x != expectedOutput)
	{
		std::stringstream error_desc;

		error_desc << "Data {";
		error_desc << "toInt64()=" << std::dec << x << " (expected " << std::dec << expectedOutput << ")";
		error_desc << "}";
		
		throw tc::Exception(testName, error_desc.str());
	}
}

void json_NumberUtils_TestClass::testToInt()
{
	std::cout << "[tc::json::NumberUtils] testToInt : " << std::flush;
	try
	{
		struct sTestCase 
		{
			std::string case_name;
			tc::json::Number input_data;
			int64_t expected_output;
		};
		
		std::vector<sTestCase> cases = 
		{
			{"i_val = 0", tc::json::Number((uint64_t)0, (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), 0},
			{"i_val = std::numeric_limits<int64_t>::max()", tc::json::Number((uint64_t)std::numeric_limits<int64_t>::max(), (bool)true, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), std::numeric_limits<int64_t>::max()},
			{"i_val = std::numeric_limits<int64_t>::min()", tc::json::Number((uint64_t)std::llabs(std::numeric_limits<int64_t>::min()), (bool)false, (uint64_t)0ULL, (size_t)0UL, (uint64_t)0ULL, (bool)true), std::numeric_limits<int64_t>::min()},
			//{"WillFail", tc::json::Number((uint64_t)5, (bool)false, (uint64_t)0ULL, (size_t)0UL, (uint64_t)5ULL, (bool)true), 0}
		};

		for (auto itr = cases.begin(); itr != cases.end(); itr++)
		{
			testToIntCase(itr->case_name, itr->input_data, itr->expected_output);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}