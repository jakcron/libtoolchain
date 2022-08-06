#include "bn_bitarrayByteLEBitBE_TestClass.h"

#include <fmt/format.h>

#include <tc/bn/bitarray.h>

//---------------------------------------------------------

bn_bitarrayByteLEBitBE_TestClass::bn_bitarrayByteLEBitBE_TestClass() :
	mTestTag("tc::bn::bitarray<LE,BE>"),
	mTestResults()
{
}

void bn_bitarrayByteLEBitBE_TestClass::runAllTests(void)
{
	test_Size();
	test_TestBit();
	test_SetBit();
	test_ResetBit();
	test_FlipBit();
}

const std::string& bn_bitarrayByteLEBitBE_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& bn_bitarrayByteLEBitBE_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void bn_bitarrayByteLEBitBE_TestClass::test_Size()
{
	TestResult test;
	test.test_name = "test_Size";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		// check size
		static const size_t kBitArraySize = sizeof(uint32_t);
		tc::bn::bitarray<kBitArraySize, true, false> bf;
		if (sizeof(bf) != kBitArraySize)
		{
			throw tc::TestException(fmt::format("sizeof(bf) had value {:d} (expected {:d})", sizeof(bf), kBitArraySize));
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_bitarrayByteLEBitBE_TestClass::test_TestBit()
{
	TestResult test;
	test.test_name = "test_TestBit";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		// check size
		testtype_t bf;
		
		// clear all bits
		*((uint32_t*)&bf) = 0;
		helper_TestBit("All bits clear", bf, {});

		// set all bits
		*((uint32_t*)&bf) = -1;
		helper_TestBit("All bits set", bf, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31});

		// test endianness calculation
		byte_t* bf_raw = (byte_t*)&bf;

		// set byte0 bit0
		*((uint32_t*)&bf) = 0;
		bf_raw[0] = 0x01;
		helper_TestBit("byte0bit0 test", bf, {7});

		// set byte0 bit7
		*((uint32_t*)&bf) = 0;
		bf_raw[0] = 0x80;
		helper_TestBit("byte0bit7 test", bf, {0});

		// set byte3 bit0
		*((uint32_t*)&bf) = 0;
		bf_raw[3] = 0x01;
		helper_TestBit("byte3bit0 test", bf, {31});

		// set byte3 bit7
		*((uint32_t*)&bf) = 0;
		bf_raw[3] = 0x80;
		helper_TestBit("byte3bit7 test", bf, {24});

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_bitarrayByteLEBitBE_TestClass::test_SetBit()
{
	TestResult test;
	test.test_name = "test_SetBit";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		testtype_t bf;
		
		for (size_t i = 0; i < bf.bit_size(); i++)
		{
			// clear all bits
			*((uint32_t*)&bf) = 0;

			// set bit i
			bf.set(i);

			// check bit i
			if (bf.test(i) != true)
			{
				throw tc::TestException(fmt::format("set({:d}) failed to set bit {:d}", i, i));
			}

			// check non i bits aren't set
			for (size_t j = 0; j < bf.bit_size(); j++)
			{
				// skip bit i
				if (i == j)
					continue;

				if (bf.test(j) == true)
				{
					throw tc::TestException(fmt::format("set({:d}) set bit {:d}", i, j));
				}
			}
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_bitarrayByteLEBitBE_TestClass::test_ResetBit()
{
	TestResult test;
	test.test_name = "test_ResetBit";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		testtype_t bf;

		for (size_t i = 0; i < bf.bit_size(); i++)
		{
			// set all bits
			*((uint32_t*)&bf) = -1;

			// reset bit i
			bf.reset(i);

			// check bit i
			if (bf.test(i) != false)
			{
				throw tc::TestException(fmt::format("reset({:d}) failed to reset bit {:d}", i, i));
			}

			// check non i bits aren't set
			for (size_t j = 0; j < bf.bit_size(); j++)
			{
				// skip bit i
				if (i == j)
					continue;

				if (bf.test(j) == false)
				{
					throw tc::TestException(fmt::format("reset({:d}) cleared bit {:d}", i, j));
				}
			}
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_bitarrayByteLEBitBE_TestClass::test_FlipBit()
{
	TestResult test;
	test.test_name = "test_FlipBit";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		testtype_t bf;

		for (size_t i = 0; i < bf.bit_size(); i++)
		{
			// set all bits
			*((uint32_t*)&bf) = -1;

			// flip bit i
			bf.flip(i);

			// check bit i
			if (bf.test(i) != false)
			{
				throw tc::TestException(fmt::format("flip({:d}) failed to flip bit {:d}", i, i));
			}

			// check non i bits aren't set
			for (size_t j = 0; j < bf.bit_size(); j++)
			{
				// skip bit i
				if (i == j)
					continue;

				if (bf.test(j) == false)
				{
					throw tc::TestException(fmt::format("flip({:d}) flipped bit {:d}", i, j));
				}
			}
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_bitarrayByteLEBitBE_TestClass::helper_TestBit(const std::string& test_name, const testtype_t& bitarray, const std::vector<size_t>& expected_set_bits)
{
	for (size_t i = 0; i < bitarray.bit_size(); i++)
	{
		bool res = bitarray.test(i);
		bool expected_res = std::find(expected_set_bits.begin(), expected_set_bits.end(), i) != expected_set_bits.end();
		if (res != expected_res)
		{
			std::string error_str = "";

			if (test_name.empty() == false)
				error_str += fmt::format("{:s} : ", test_name);
			
			error_str += fmt::format("bitarray.test({:d}) had value {} (expected {})", i, res, expected_res);
			throw tc::TestException(error_str);
		}
	}
}