#include "crypto_CmacAes192Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/CmacAes192Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_CmacAes192Generator_TestClass::crypto_CmacAes192Generator_TestClass() :
	mTestTag("tc::crypto::CmacAes192Generator"),
	mTestResults()
{
}

void crypto_CmacAes192Generator_TestClass::runAllTests(void)
{
	test_Constants();
	test_SingleUpdateCall();
	test_MultiUpdateCall();
	test_UtilFunc();

	test_NoInitNoUpdateDoMac();
	test_NoInitDoUpdateDoMac();
	test_InvalidKeyThrowsExceptionClass();
	test_InvalidKeyThrowsExceptionUtilFunc();

	test_CallGetMacRepeatedly();
}

const std::string& crypto_CmacAes192Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_CmacAes192Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_CmacAes192Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check key size
		static const size_t kExpectedKeySize = 24;
		size_t kKeySize = tc::crypto::CmacAes192Generator::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{				
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
		}
		
		// check mac size
		static const size_t kExpectedMacSize = 16;
		if (tc::crypto::CmacAes192Generator::kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", tc::crypto::CmacAes192Generator::kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::CmacAes192Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::CmacAes192Generator::kBlockSize, kExpectedBlockSize));
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_SingleUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_SingleUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
			{					
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_MultiUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_MultiUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());

			// pick an offset to split the in_data at
			size_t offset = test_case->in_data.size() / 2;

			// update with first half
			calc.update(test_case->in_data.data(), offset);

			// update with second half
			calc.update(test_case->in_data.data() + offset, test_case->in_data.size() - offset);
			
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateCmacAes192Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
			if (memcmp(mac.data(), test_case->out_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_NoInitNoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitNoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);
		tc::ByteData expected_uninitialized_mac = tc::ByteData(mac.size());
		memset(expected_uninitialized_mac.data(), 0xff, expected_uninitialized_mac.size());

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			//calc.update(test_case->in_data.data(), test_case->in_data.size());
			memcpy(mac.data(), expected_uninitialized_mac.data(), mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), expected_uninitialized_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_NoInitDoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitDoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);
		tc::ByteData expected_uninitialized_mac = tc::ByteData(mac.size());
		memset(expected_uninitialized_mac.data(), 0xff, expected_uninitialized_mac.size());

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			memcpy(mac.data(), expected_uninitialized_mac.data(), mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), expected_uninitialized_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_InvalidKeyThrowsExceptionClass()
{
	TestResult test_result;
	test_result.test_name = "test_InvalidKeyThrowsExceptionClass";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}


		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			calc.initialize(test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize-1");
		}

		// try invalid key - key size == kKeySize+1 expected
		try
		{
			calc.initialize(test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize+1");
		}

		// try invalid key - key size == 0 expected
		try
		{
			calc.initialize(test_cases[0].in_key.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==0");
		}

		// try invalid key - key is null
		try
		{
			calc.initialize(nullptr, test_cases[0].in_key.size());
			throw tc::TestException("Failed to throw ArgumentNullException where key==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key==nullptr");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_InvalidKeyThrowsExceptionUtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_InvalidKeyThrowsExceptionUtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}


		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			tc::crypto::GenerateCmacAes192Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize-1");
		}

		// try invalid key - key size == kKeySize+1 expected
		try
		{
			tc::crypto::GenerateCmacAes192Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize+1");
		}

		// try invalid key - key size == 0 expected
		try
		{
			tc::crypto::GenerateCmacAes192Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==0");
		}

		// try invalid key - key is null
		try
		{
			tc::crypto::GenerateCmacAes192Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), nullptr, test_cases[0].in_key.size());
			throw tc::TestException("Failed to throw ArgumentNullException where key==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key==nullptr");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::test_CallGetMacRepeatedly()
{
	TestResult test_result;
	test_result.test_name = "test_CallGetMacRepeatedly";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_TestCases(test_cases);
		if (test_cases.begin() == test_cases.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::CmacAes192Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes192Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			for (size_t i = 0; i < 100; i++)
			{
				// by resetting the mac here we can tell if it is updated each time
				memset(mac.data(), 0xff, mac.size());
				calc.getMac(mac.data());
				if (memcmp(mac.data(), test_case->out_mac.data(), std::min<size_t>(mac.size(), test_case->out_mac.size())) != 0)
				{
					throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong MAC: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_mac, true, "")));
				}
			}
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_CmacAes192Generator_TestClass::util_Setup_TestCases(std::vector<crypto_CmacAes192Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// NIST 800-38B
	tmp.test_name = "NIST 800-38B Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes(""); //  Mlen 0  <empty string>
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d17ddf46adaacde531cac483de7a9367");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a"); // Mlen 128-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9e99a7bf31e710900662f65e617c5184");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411"); // Mlen 320-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8a1de5be2eb31aad089a82e6ee908b0e");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710"); // Mlen 512-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a1d5df0eed790f794d77589659f39a11");
	test_cases.push_back(tmp);

	// CAVS 11.0 CMACGen Test Vectors
	tmp.test_name = "CVAS 11.0 TestVector 0";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("af189eb993eed7225bd3b61af2d3a9a854c8b01ba32211f1");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("771b8f673b2daf2ff054");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("33f01aa94838f15bcd135e584b78ce673f833ea51a6b591f");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8fee179b1e678707de7f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("85d27eb394e3d162d191d56f9f881292e9d1ffb5fe53769e");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b92f5da88efa8da0f8f2");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1f984e40df91fe9cc23f2da524e22844d84e877e634905f5");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6d5c7013378234d81e63");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f2a5922af9be09c75d1c89b19f94aceb47d769611fdfe571");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("bb42ed0ace961365c1cc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2d5537b24d0b0f7a45703c1e131656ec9edc12cdf71dae1c");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dfaadaf9c2258b82839f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1ec203a8af24d67e772ed6645fef677228f76962b95e22ad");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("eb6afe4452ae3134ab55");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("212ce614a419ff6a0417ea3a20599df2c44e5e127b2334d6");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e81db4efa236b5cd5fb2");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 8";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("91a8a9473ce48a2e2d59885498c67efc42248e8f7eceb6e4");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7c4d12c6087639ec7c68b664");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 9";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("14acced8d636fa38513fbaa6363b00629d773931040874f5");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f846c9d809015d0a8677d883");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 10";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1caeedc041bc85ed1a50a821e3069670f3287926ee193e53");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("756a4835af08564c684949f3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 11";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("627961ce090965ed70c3a137d601dce8dcea6e892f8b01af");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ae7e4f80118b9c6693e7627e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 12";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3a987ebe53054a60a2bb82ec9f217eac7d6a350f021aae4b");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e7142592e6235dbc0a75c75b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 13";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dd4537d1df909b140d634dbc1976b4e7b8755c40fb03ec23");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7577752bf9acb84a1a726582");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 14";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("64ca49eb1807c2299cfaae5e56003e02af70c3331689cf4f");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("feea641b952c7531ddbb13ac");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 15";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f1d9d676c47cdbde625b5373eb24076913d0dba380795326");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("31449de440a6acd033b6f1f1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 16";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3364169ee077cafb9b15cbabafa4f3f1ea138bbc09756470");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("57aab646105c5e5b80214b87fffa3847");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 17";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("30834308187b8be1be405d4b274d97b5d8ab71905064185f");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f4891369691f0329fb3b3160d1bcd710");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 18";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b822517136e97ea5ae89c49da642f5369877788945b13f14");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c2d140417892dacbf0026b35556047cf");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 19";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("83b4dae82b50879c24648729121b263e39b27f1c29894047");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b088a52d4a5eff371531ea26c6362cf6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 20";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cd941a2a84873c131a10fcff0f4370bdc87dcfb7d79bd5c7");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ab46bec76a2e76ca823b2e2b0a2723ea");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 21";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6fd6aa04a13bcafbfab60c5ba5912164f4acff82af7ad774");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d1e17cf8edd738f3948178d9daaf14f7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 22";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b9ae557c9daaa405e08857494216d1abece82b7356a733c3");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5cad436ec51e080df056925ab3cd4589");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 23";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7b32391369aa4ca97558095be3c3ec862bd057cef1e32d62");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e4d9340b03e67defd4969cc1ed3735e6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 24";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b19041308b767138ee196022480301683d1441933ec83aa3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("86617012af7d947841ba408df5ff8b9a44f25985ccc5dc44f5525a97d46b30f7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8efc4d25b692c34ddbbc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 25";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7fea563a866571822472dade8a0bec4b98202d47a3443129");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a206a1eb70a9d24bb5e72f314e7d91de074f59055653bdd24aab5f2bbe112436");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3bfe96f05e9cf96a98bd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 26";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3f29d9b2dbf5d3e51fcf96e86e1d40756692020966a8c5f1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5e5136ff2c39c2cbb80746b3df2e39e2744c8f119a0238fb7002e911f4691e6e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0a891a799a356ec6241c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 27";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3362226aa5b08d6c182ade754de4f1bf2091b357013435d9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f576f759b19cb7c6a35806859e066a5a632cd7b3b9476a8ac0cb5a8d82652b7d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c90289d87cb97db36fcb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 28";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b0034305aba4ebb101dbe23b544c8991ad74bf2978970395");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("402e802885e4119df17fe85f141c3d1af7727fcdb00f8e2c34e42a436d04ac5b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("184c6701fed75c5c07d1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 29";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9d65d88bffed764c286f34894f991600d1a67d622382b3a0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4b4e3dfbd10f464022fe105aa6365bdc3a700fdd2525cf414df3d03aab42ec0d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b75daf02260c710b8b42");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 30";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2b0ede783938ab72698850fba59a0f2248a64d811aa4317a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5787fcfe8a1ee76afaef54cb22d8b2a20b116f72bfc7117f010783d63bdeac8d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8a4cd3aae3d13be0c7e5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 31";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("16ef35e38aef630f2407afb2e7f961437e9b88e689daec93");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e98d6b26e408f0f1b44381bd131f43aaf2d660cb62480822b48fb6cbdfd9b577");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("625ba8822deb6a9be6ba");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 32";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("09891ed14f4488069cd6a5744061e06f8ff8d1bc87b10448");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3c3d7f18a0bd3b6f366c1b497c602e889cac88feedd7e683bd8d95454e958f60");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a737ae846c1fecea1cf77a17");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 33";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a92e820d4aa83ab32bc9ce537a9582303896064840d29ee4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6f6c7ce5d1c725f7b0284703736a1de9ca8f75cf9110b415f770198bdf1746e2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("087006cea64c265cb2331a93");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 34";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3314e9af7ce9917ff7f922c86706277a4e98d28e1197413b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ca2b30d72df532efce9cde44ffb9bb5611e746ba1a76dc6af464d95f89880262");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a1f0e1a5d23160f052b3aa83");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 35";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7ccdb1694225e55cfd7a9679569ce4b091934bdf1de0d13e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bed48837b7c36abfd299b0d12d0b0ee0c6330107982a0f3f07d950d47e0c2d1a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3ec528a3418fbcbaa8df51da");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 36";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7867bb4b275b18c734f065f5aad3317aa57d9a4767fd0778");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("081568ae0b948aa647b9d4dda5d42641ad5de72aa9874d8d0717d872007720a8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d18bc40cc5d772e6b6f263f1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 37";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e5069836d054bfc844bd7800ad893892c12df3b0be7a84d8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d788790ec62797fe588f4a68ce4a00d329a8d7b39a65b22f3a868d27fb840d76");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f1b9602ac97e8a10656f0127");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 38";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dd472b0bf50519020a182f122239d161d9659773b4df454e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7bc03632942150716f019d048a752ccc0f93139c55df0f4aaa066a0550cf22e8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("670ab4297c1e8ef9677abcf8");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 39";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ffead92a4a5dc1eec6d2e441de9a9e1b7a88c607c9a79079");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9be0b302ab1fe8d13cba71652b27be06f7f8e7f626b035ece4d5e4c3ee462774");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e5012815fdeae3b1117dfde3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 40";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2051af34762ebe556f72a5c6edc7771eb9245fad76f034be");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ae8e93c9c991cf896a491a8907df4e4be5186ae496cd340dc19b237821db7b60");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("74f74608c04f0f4e47fa640433b6e6fb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 41";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4513f55f243b70544fd97fafe65a68ed82c4acdcc9f739ff");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bb525cbd4cfe784d33c4fa8b6e75006e256911b03ec4542f2cf8ff94078b1332");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("52d23939e598a7e554d3604dddf790b5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 42";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cd9806785db29769de6fdf5223e4f20878bf13cfe37d1c2a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("dfddb719d00398bf48a6cefd27736389e654a93b8595cd5ac446af1996e0f161");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("09c4d337db146f920d937ed283cc6944");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 43";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8759909675383ef1753b652324a023671f9d9fd6693c90dd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2e6d3ae7949ebc6165ad4db2a3a1a93982ed4621cd44dada86ae1dc9cddcd03e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("296d7f3d432d491f514c836ace9a9560");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 44";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("82b8c736037ce2f2e8c36a7b26bca889e9f4c333356b87aa");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("940ee53e86ea7462e9924ab4b330b7d64e9c067af62cffd262ccb147a6516e6e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c168a195c3cae1cff58a7e358f8bc936");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 45";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f6ef9ac4f4c9ce1e4309c64fa8318b899f9ba28ef2b93d16");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d80f90cb55bd6207c62ef9c3567d59fecdd845849f79607b28d79238361ead57");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7c9ff40d08ee17b14ebe89abe8cf92d3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 46";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ff3812e67323bedbe803a0eec47868604b81a7d0b9438416");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0a1423e291b2f0c6499f2d408237d72d3ad7e6744941238bdb423a3d239210aa");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6864cb7f9a9c5f6854a697669309661a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 47";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e8e477975d89c1539ea7fa2ad320929c091336766e49a152");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("12865171bb4cf9c51c53a5bc808c107a8cd53068167ab1d73bfca1e6ab116da5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("316b5f37859ca7508d5bc5f989a3329c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 48";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2cc839876d3989f35731be371f60de140e3c916231ec780e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2eaef86b0f602364f86510eabc58bc9ad1e6f0a6f6df0b83188c01e17744a4e0053a22810e99cf5a1ed3258f203509fd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("806a7c69eebc6041e6f9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 49";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("45028dd99d0c7f13fd00a2e805922ebf4f833080f5142fa7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f8229264bdb7657c056ed4af2a073355333de29ba748c428a4a6f2012b1bb1aabef7a28f2d9739a2ad2e70442ac6bd69");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4288ca11a17f4364125f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 50";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7effb0ee6eaf5df37e69aebe27920c6240741e39cecf4084");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("373b1b64bb5516d96e408631acf84966d2764653a280f323e9c51b0a5e29de33ce5ef9f976b44759b13288a7d3e56281");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2e2f7779698b5306e567");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 51";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b62e1d3c495a30823e6783598b43dfb36d0d7650b51cd1df");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e534ee399d9576e8ff67548f8c7b2c0f325384a8c3ccd6bda6ffe3d7cd6a4bede64b5be3d64d26506366d784300045ca");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("47f348def1ab06f0e435");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 52";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("32f40dd7a952ec8bd63355700837b450b396b33c72125e23");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("728a1ad0b26ccfe41895818358baa69db6ddc4e91b142ccc688de47c0acfe565cf4286ccf7f239b28f9075fbfabaf3cf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6387377d71d324f4ebe9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 53";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("24bd86db8099642ff8109bf2b7f5c918766b8f91f0919f12");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("50f00655681d61e035ab16e3fe18bb721aab88b2a85baee080eee994695e59478c808e1328e7e2bb88070beb3296f0c1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ccecb18d294f160860f1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 54";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e0a1a00c002f6f74869e5d3db4bc4dcc283b7d7ba66265eb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5a14af768d73f1d92b892231a5d25b7e0dec5cd929533658c67047324ed26b239dbb711211deccf2e0678be6af3c8ca8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5039f8367bc57a43f768");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 55";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("edc31127952ee79f81addf982f17824a870614b80e386936");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("da54f1efa6dae9a7db6be4eab91a3bf894bb01ec28ebf0e52d51a2642b2305f590eb0912008b9b44ec7ed78b66627900");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9a9a88ddea48f9dcb85f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 56";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f56396ba8c08a8be100b33a20b5daf134a2aefa5e1c34967");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6c2b091433833a0ed915354dcb70d982095b614dc51a95a22cec417184d8e78677a9b1aeae38a91ba2e92c09af789ca2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("76f40a3044b1102db48ecb74");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 57";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0d578aec456c589e1c67214c34f4380e1bfa3629ce139b29");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f75abc23b55f32700317621d891dc7c74015ca447a99e534237609d846193d28d244891f9f06125aace986e1ab6dba45");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2efb7fc379e301855402e3aa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 58";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5d27cb435e7724a246f158576fdbac685cfadf62eff703e6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("44d91d3d465a4111462ba0c7ec223da6735f4f5200453cf132c3c58dfad87eb9ad56827857e6645a534c69e818ecf442");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ad55c7339fdcfe791c93c97e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 59";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ba593c3f60f11032790dca14e5d783eaa02c2d2d52e7ca2a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b0a3a2cad55c3fe2079c3ee634a9a066ffa7c6d365b23033a02a8b194b4eebd5c80d55e8df1880bba73cdc90aaefd4b8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3667e42b88a1029fe20b8336");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 60";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dfddb719d00398bf48a6cefd27736389e654a93b8595cd5a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c365e32b3eb3f4444eaec5cdfc07d0a9af5bcd01fcb826e5bf5eac366bc288c39ed974b2f9922b222ea51d0e5a8b6874");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4f83b43cdf2da1e75688b022");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 61";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2a48014cf39655cf2fdbdf650f8f0865e4d03f0e40fc40bd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c1ac8710555793056c6f6c53353dca263de8c482843c8b2ad6a958c1588fa32f62b996468c27c1a60c100fdd3f27f9d3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e2ef607ddcad3ac32cce8542");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 62";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("668a3fafe71a9eafd2d24586268a425c7c4422dce0ae62dc");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3ef3eedfd640fff8da809b5289869778086fea97a8d710476c4db0a9c6037cb2a2ca58c6a53ebf89b73e63f2bfa014a1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b14da00d64322c05ea5d923e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 63";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2885116e87205b81b78e52228e2483f2313c74b372359664");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("62244890cc50d01a0949140279c18e26902e71432acb97171fe0bbc21844e872a120313f7ff5a35443e178501f1e8dec");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("726d0b6a013cde5381f29504");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 64";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("50d024a3e7455d7249ef2ae59d2d00f111469aaf6eab36bb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b6219c241267fabe6b2e751e17ffc331263c0d8da256514a154105134c25fd7c5b578e96e187f4c28d3bf1c2e17cb716");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dedaed2fe49cc9ead5b6c622d57a37a1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 65";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("317a704cee13750d7b42aa6ba729f7bf3cf91ae084654838");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0213fe13c49083d7c00335e1864dc139c9e7123162d171f997cbf16e9ec80a335da08403740596457db850e192fc3653");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("079824e11466823db9e26a0770f28a40");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 66";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("105358cc17b12107e023a23d57b44c66a2c58d8db0510031");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a42a2b1e50cb962f67e857e5a16b80944e718a693c9f5159dbb960579f706fcaa67c2a3e9beb3459dab96c11d4a06f1d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5769c65b91d010673cd9fa8b7a52e70f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 67";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8e9e603595486c3855ef030c4ee2ce088fc862b68429b97c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1b0c9ac2018fb3ce17da6a20fbe66220800538494923b689974b4aeb5f6db673a05e0849f320cd1b646482bc804d4b11");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("439c5c929e5b80e0ae9b5e85782bd577");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 68";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a206a1eb70a9d24bb5e72f314e7d91de074f59055653bdd2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a24666544c071b86072afb4db5532327708897d87b4dd6af780db10cdbbc5c1f9ebbc6f237fc26aac766d60a947b6538");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e690dfcb1ca782b5eb90d96a1636447e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 69";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7cdc26bb8e8d990fcd68860ad4a31dacf953eed5e982acfe");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("016d049fda747301ebdda569f72e9144c5e4538f727322f50b8882375c91bad1027f89dbc8ca152d30b624c64fd68e6f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("58533e9f0cb94d916f8054cfce77be43");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 70";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a6ac5692e0e347418cf3180cbaff73be98cc16f1e56be2d4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0cfcd5f96da1c6c66cbd6c2a82f0b6e5c7011d1d1675e5986b61a02e8f7cf57ef8789fe1ea93b89ce369385a360cb9d9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("da6e08eed7f5f5ae509ec32f6279497e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 71";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("647a161552dda7753a54fb96bf42f3a3f8b676b7214cc4e6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0d737f50ed1901b544c42af8803e7244741edf14fbe1cbebdf3ce946f9b183ce996105d32821bff60bcfe725cbe7ddcd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("363f136d53ff69be32a881c8ba872330");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 72";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d80e97b1b759444085b903a7a49cd9e6e817d9d29bd848af");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3e7ef2e93e0126590c7f2efe255a72ee5ce09c80b9cd05f687116c60a9d4eebd2db83262245ee5a0b02b66a15e4cc293b6f7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8abaa9d9fd219cf3b369");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 73";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("04a891080129e4ccbd1bdeb0daa7d348f016b7462ee6e239");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d3111a64498098c8c26247fd9ab6f627b3e348f16004b47e8183cfa3efe9ce531af4465af0eb374e012e49c3e11155bfceea");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5ab6f953de6117c86cc5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 74";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b2b5c57e08fc54e4e1907ff14cd1703768f5ddaa27b5e6f6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3c282a443f62f0d720345b2f87f77210b829c88b0d1196c8a4a60c0355aee9d5e7234ab583dabfbe6867a4b3e13baf40740f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f2caac13b1154003e00d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 75";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d14e2a8cb7b8dfdac5dfafd9bf4e8dfd56bde06442d834b9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ca095aec96a8b093e62b10f0950ce35ce7921d8427eb0a1a8e7a4bca67721c7071a4d8888595bee578d4f5a7438ace676153");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("51edf6f5a9ffa69dff26");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 76";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2edf42a21768171336f9d9b0fe0ab1490d8c590403728bff");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6f6b82cb336407306fb351e8c28a9dd0e4cf091c8d6f9c4992f58754515baa2a501f5a5f219a6222898e4771e1fed189bb42");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e53931cba4a209604cd5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 77";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8bcd02e664585f1253739afef78d7437384425e43586f303");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fc6aa1eaf50c4d6b24b1105027c7ac23fbae11e4271c2f9537c008fc6c2509a4b2da9a25d2d0f4a5e903329f195cabe37ed6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9c5ec095e3173080ebe1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 78";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3e402d7a87f59cbf40716cc31781c55c9d39fcdfe438c185");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eaf69a4b9029d655789b3a35eb48626d72614d4d314c561476ec6658922267a8e894fc6f43ad6f1b6de5eb7ffd42eb76701e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c264abd4714d4ad3b700");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 79";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8c4e7813ab9bce9dafee01c628e050a566d3aa3eec91c048");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("da76c6db3c276b03c3dcb23e23c713f2be1029221a77c135933a31f94d39ebe76d5851a98925cbd95cbb170cbfe6e10fd587");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e03607a8085ae2f17b94");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 80";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e63e7c1d98c06f1d50b675939efe4760afa31406ce5027ba");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9797ab62d666e11adc023fa87c87c41f4ac64bfba23bb3b3ec403c921f7f34c284add4aabd76657a05b3a603b9e372cd18d9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ad16cbab7cf3f38b57a21ea0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 81";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b122ac8f34ed1fe082a3625d157561454167ac145a10bbf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cd149d17dba7ec50000b8c5390d114697fafb61025301f4e3eaa9f4535718a08a24adead112225a305009d463c3997b135e3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e0ea9dfe9c083cbf3ee63105");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 82";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8f2a6540fd08939987ee96b9eab6a97ee339149f951fae2b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e7b819a853ffe79baaa72097ff0d04f02640ae62bcfd3da567de32415fce19a42ec06c72b4a1b41c6d8af1b4f73b3c00cec5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3529e08c1d060a15acd33ab0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 83";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6e4018153f4faa66776859abf73a2b9e23ebbc3b93ff91c8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bfa9d9af6e1f32b6626a1cd89b1c32513b5b50a18ddab028470953f20c89a3d435e356b8d1799535eabd5e630ba027edfe4e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dfa0d685b25aacad5a860208");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 84";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fba4bede287c57eea4448af5e99d41c7d307d1f202af7f38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ff6669e9406375fba3ad7c7ca2695cddbda738c8bf95d5fb42f2445775c6c2341d51dcf8da41d7e8ac284e3eb52c1d7b4101");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("31375dea1c04c2750dd37b60");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 85";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("31aac06a59b74bf478617c1637fa6c5593df168b8d58b1e9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("26c228767c46436dffcbcec35bd97d6799e73ea5a0ced43ffb7ec1c0dcf06a0d615c763d17ab77aabd2fcc484a92c636310c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dca9a0d21add67590ea19227");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 86";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2d345be05421ace69e7465e55b4aff0a5948564a0832f598");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("19e07bc5c4a6147d56ff18844755da32a355e33a5df2e8d1e5adfa13fc14fda2c8895b902345fa7f399d6b0652836457ec4f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("351d55860f24be09221092c7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 87";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("635e2792321f9f3756b707b01b161e0c6464fe4c3f4352c5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("42e7dc426f4071dcd2be41d9dbe6439e69e5884c288c29e71d997eb87f3890efc9c9d18d0de40b818b9a971182fecf7c46e5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a1f09d3901a4efb793cf1431");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 88";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1159f381b1c21e0d2853cb29ac7981cea902a954642f4c2a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("59397e76e777509ddba4f1811a5e9949c7928df36fe5f4e08353e6930c16c7b69acad35d7dcef98f38eded03333e7927b048");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("351bdcb858f7dbcf66b1a130c22e7cde");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 89";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1fe8800fcb0dd8f1ab1aeb4e159e575a3999722ba7ece6cb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("934ea4c100addb647c4a0debcce7ca389c95b0001ec7307bf4aa956050b941105a8c3a11d2f0e6bff63d133ea6e43ab3c648");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3d05c0d6e14e06f54b7eb421175b1fd0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 90";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c218a9693b3fb6f8b3b213027027ea1b88f489695b8209b4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0e6c9fced82669cffe7b5a6f09dceec8f95bc397e7bd55f0e9d10c3036017a348b27ddc8cda2ec62efa8d01116dd70b0fb25");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("643bbd262be43655392f685718c9ae43");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 91";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("90841f19366f06a9f62355c0ebdaab8e5271c1f9491c4cf1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("57d922078c103faedf7ff4ca1c57fe328c4c9553bc464b807f59388a36f754914f6424190c6b9960865035f0f1056f7021a0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1a0fc66cc8605d7bc956253a42ac7365");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 92";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("813e2aab493d6b748ed2bf77c5aeebf871562ad747be71bf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3384f8563cfd0fc8019bacc9b691c9ba4ae6dc8cf4c006290fe18d0f27728c3e54ffe955c6c488f8a227be740d8509a68531");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a906f46509965a3a353501a1450b59f7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 93";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("84adfa66165defb6de1bb7a09ab9a3c3beef639f1566ca4c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ca5893a1e5c06b218d91d87dd4e89259621d9c7f66ecd324d3d7c86dc8c6cb314ff148014bff5765ac6f8e69e5381958a0ac");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7a401f27996cb868c76e9d3d7636c5f4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 94";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("22b7f1056e760703f5a186cc0b4df84f33ffa549887811b9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("deee257fdf2129d9de3ebf8ab0580155dd675516a43d95523fbc6d12684504f21b73de759e0a019bbf2a56b65dc953792960");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8b16dc6d0159115618c48a507a372bdc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 95";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b41cfb8816b91b806473424e731a0fe203bf5e79f2191c1c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("27cabc40da0e1eda0ea5f8abbb7c179e30776250a7b30d711b0e106c5ee9d84a662c3cd3e78bb2f72808c36d0fb9bc9a7dcc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8bca66651da0dd4086774941b814aa91");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 96";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9a995ac9974c84c960d28542bcab773ca1c222aa4a37b849");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7d49422e13d9dbc9542023d4c16dbeba2a201f6fc46941547b52975b8900456b48359006441a9329953c34736cd4578aeb4b52bb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5a674fb036e33db526a6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 97";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("90059c2605a1160d965dd04dc44aeb9a44d177d34bedd8d6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c5a463c2c682603f280cf52d9c3ef8954ea0a74f10d3eb2db469de76b9fa8a962b73f413c4b259c35750b73d6fbe8f8d3394e92c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("27217f9dd2539b156498");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 98";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1dc5f6d6103ed2ae7f4ecd7b1bae4d5b9c0adef9100527b1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c40aea65135a862d271f73ef8263e423926f516f333b1cbe76287592a0f17b9b76dfa388b83d5e1dec0cf6865cf8b9eb628a5a44");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e68e002449a5e39e6b7f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 99";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c36f71095f31ab1a2532f1b26888cfb1d53dfb9056a34d4f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("aae4f0cda67ebddd5513593ce0b9cfd84eeb05124a389d1427381a6521c444bae666cd10550f34f78508ea31092bb47b725350ab");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f72b4c179b349713d249");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 100";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("06ac39896073a44283611a66ccab067e2dd2faa8da82ff9a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("07d79d5fcc99603336ecfeddeede141129e5160a882d4b7b3d3119c970898377e102f0e2cef42e2e17d0b680a0f9326df7d53cb3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("31a4aca813bc78979cff");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 101";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2ecddb226ae668315eecf107c344926330b94077e029ac3b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("993dacbc221ed32a6fb3d90559c674fb68089eea8df9eaec14071991d4fae86ba98f2dd0246322db801301b4d8a2d111981b7ffd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("57d76d9a94021270139f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 102";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1af884db9327613ebbfc3dde7ffd911e4c36480d7eded22f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("90150a8c14bfa7282df6c1da4d2f89673ce423ad6a959fcf840d2b9245e687078f4fb96bba0d014b2cc00feb296874e9ed27571e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("90a1ac3772d18430b7ed");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 103";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("63ddaa8563ed90d3b57c8c2242a6dd00710448733d72c6df");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("66b002ee3140bcc1f86deb4c4bdbb8e9ad48f1f88fb7a42380cdede79e7b0c4f50ddba033762be82612ebbacc0bc4c83dbc85232");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a5c56844128fd06019cf");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 104";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("82147b230098336b1ea32b7e32be0f69e67e79723c6e12a8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("49fd5cbe4aff89dc3b8718f9ce545d612cbbebb289ecbf42fb77babb8c0f55088e8d90752e382b114c4319578a97320ea3d3286e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2be36727d457ab8283f82f9d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 105";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("20b53dbe24a2c57b2c102c6d220ce29317329d1b95b84d83");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("51cf2a8949e13eaa087a34c9ec4d7fd92b862efd6a0b1fef8b016fa2c6933426fbee6fcd46903c8cd5c34ca3f664958074e948e1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("506f1a30ee00a9ee13ff5b45");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 106";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e0a0a7f262cb51ad4529672202dccdb3437a11c8a2c14d1f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cc2ce41f76ca7477972d38a3e8fad1122db34ee80c379fa01f884cf648d1670445a8bfab8490563438c21537ac2dbfbcd7bb24a1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cb57405aa262b3be96f2f7e1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 107";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("effcea4e4dbc57410426b39fcf51c9daecd9d310888590d7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ef9e432c15d8c93a4b5c0666608e61c824cd466d7940d642acd3dc33057c03959cc347c16f81aa02b2e828b266c3ec9f2dffc4b4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c80b11e7623bc4c54122da5c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 108";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c803bf3022e9722e2431f2e49a4593ac89e79fefc272948d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9c87ad77953bf8a811e001ddb946eefafbfaa598150e85f0701853fa307d77d609f0686a5435654d622b66e3100952ca9be87275");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("434a91dc02020a7e67693d0d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 109";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1d70dc99d3853edb17d34146be6e009a504ee1b30c45bd18");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("27861168ac731a223dc35c03e82267aadbce11e4c19b6bd14f3bf44219bc0c66ab52aba6d55752cd4690426c5cb2ed7d3b24aa46");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("82c86008448593da2418b3f4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 110";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ada1fa439c653d0cc88c0d129ba252e86c7d20a3087be93e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("50b52e3965ea73fba7c72d19abe2ab7361b58ef68f43db667eff4f5af4e9f38861faf0425dc2a3415250f4a27652e42efd7d66de");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("53142f4dff316843b47fe012");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 111";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cbf013ead53369cbc8d459bee3e441fb8ffce87af07eb55b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3ab56d3c9916103f0c8d81b49d4a38fbbc4e4aac3488f6d85d3e7b9293af2daee8f7c8c91632048ab8e46a26b999652a0cc89c75");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9972b8ceb96578868451e82a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 112";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1d674eb5d85945a6c7842042adebe549d4fe515501c06c1b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a120e20ca92f79398e7ed29d5787cfa09b155d9042fb54f18f059f145f2f9cebab15c51b54ab9153202e95dcff5aef7294dee453");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8492b0304ef44f1166185c8cd708f4b8");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 113";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f680853dacc7b0fcf4a72789b08984abdf7c6710c4ccbb88");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("37b7ac22b15bcae64b1b1e6c70c707281494b814986f38a6ee90acfffd51d9654741e5f3c9745d8f221e7d1df860abf29862448c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f90e54cf7386b7ebf1d3d367d0775ed3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 114";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a4a8b5f7e33569048539e53b161abf6f755067dd362eaea7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("947c01ab308974bdf67ff25ffaf83d9c28fad44520786a94441b96100e42ccb0a8478c43b604d90f7695edb90c602b651753551d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5a0dce29985f07cddfa43c1b118cd7fc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 115";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b111be3d59a8809c8f54dbb0217342742f74f76c4099c589");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eae81f13e125406aea2241c01e22aa8aef611609694b9420b8ec4c63e9a86670f52c2782fba45d43cd2efee2ae8f0c665a26bb42");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8416520121ffdf5e01dba3768001efa0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 116";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f800bd782769e3201dfd065ac05a5b5a08e8b965b5bcf3d8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("548e2152f3a15b8fb81dc01062d99f7b4fc8f074e5cbdc1030c97f8ccc02ec3f06a071cd3e8f1d9e908f808eb388b2e6201d978c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a8f83574a207ee91638696a25aed154a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 117";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7cec94219eab2a29630177975d88bb78f1669bb0082b73f6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3a75afb245a668ddff0ac85ddd910a5117e73e585a539b9cbedf160ff7b934f4cfd91ca2d4e4f0844d505d6573ca71eaded4ad60");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("474ed0c98c4ff08ac3ab80ff9a2ef53a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 118";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("228a8e3cb6abced136ac8d93351f214ce3c84f843b0219ff");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("539407bb6930d5adbdf19a7e285ba1dee5caa03ef54e3a3fc1b8c86a02f55921de9bf7d553c22d7ad915c6384329d664e70dffae");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("41b8bb6318f9a303793820597d267cb3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 119";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8759909675383ef1753b652324a023671f9d9fd6693c90dd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2e6d3ae7949ebc6165ad4db2a3a1a93982ed4621cd44dada86ae1dc9cddcd03e02b8fea72e4182049f96c99bd350d9ed981592e8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9c8a610b382ee655601ebee3633d9ef1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 120";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e764fa85b3a9709084a28a7d54ad3648c0451dcfbcdeebd8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fa263ae51c0125f2cbb410641c0c668b70f925fd53e5e18aa4440b72f76c73d637a70c6d9087ef788b7aa3f87b9e9c1e19d701036b1eb399ea1c8ae2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("25e0f9b2550245f997fe");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 121";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cb51b31fd0cdd33b474807f45d860edde75a7f0252c95d29");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0f26fbe2e8d488af66eebdca2aa3d90315606947afa0c617c504df3a57a638afb1ab33e6d7178f3026e52e7339581b220a8ccb6c5950a3b45238bb42");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("76fbedf301195852dba1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 122";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8016b32a90ef4b391872b4715d1e7bf87bf3b55b569096d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9fdb82e85812f29a7a41e776f4e9eda7d431a228b988c4868b8c8ee8692a454ce3070e136a1f02c004ad84fd454ad2df7a58db6a27a15158b43cfe16");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b8259fecdf17578803bf");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 123";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ec1a1d980dafb8006b125904ef17d23d9e43ea641a390266");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("362ca7126fed62279f5296a02ef1106a6ab5a25dd6de1963c5496edd28f24142a5b78209e95f72ca3edacaa060ca39d18c4314b1dbcf4ac3ceb69622");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8ee67f1b57150a32311f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 124";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("60d36753444013b722d21ba0a1df91ab82794d198e938717");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("30655a6b5a5965db992e7248d24141055e988d726abb8e729dc5c21ffcbaedbc0b1b5fea35b8751f6ec6625517312fff2234014176269b6095972378");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c22b02c50481bef8f8c3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 125";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b320c7f4fd416cb6eb11742d8432dddb4eaca922febad78");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("66921951731e95bbd45c014af5cf623933350dd9a90d1a36465716f8239bf887142c56737eaed91268d6ef6bd471bf524fa862d5c78250d79daa18fb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0d5cbdbe319d3c8c26c1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 126";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4b9d70d0973961f485a4c3223df4a63af02a5c591962daaa");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("598f91cdc2930337839374d2297e6723f80ff7eb774675442f1853edaf6640e3d32c953146fbf00846a91e12a7473f041b532473b02ffce89ad23036");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("336a43dabdf226d9843d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 127";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f0b3522e21a33992e9af29c48d58b3e33d5da15b4726d267");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c96de875451bb7b9a3c99897ca504ed145a05bf246b224dfebbe50afc1ad71bc87d1e6fa34d400883bee63850d5baf25df0d6004ae9ef3ba81884baf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9fa2b672b9a34526a16a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 128";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("897f0dfd90213f64a9277a0eda4f134f303fa89f56ca54fb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d2e8a9c8f2cf5ac60c8c45dc8147050ed8bf67c26a35c1c85e868599d89715dc6ef5d92fdcbd9023f8bae388e8ce40ec9293e55e54413b78f5d3669c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("973303b9a9555751cb12fa8f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 129";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a206a1eb70a9d24bb5e72f314e7d91de074f59055653bdd2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a24666544c071b86072afb4db5532327708897d87b4dd6af780db10cdbbc5c1f9ebbc6f237fc26aac766d60a947b6538b938e8c41c3c90e6a12d8207");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7ab7a6b4ca59d458144edf97");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 130";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7c977be461f29657fc86eb6100496db7a5aa9d6a036b095e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fe6c4f52b7f2ef19a88156ea68ea5f4053a9e893cf18342bd4e28e35abb92f17f54c6201f073e6c4f6ad94e846cd41f807f0e6218ab2fffcd0a230a7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ee04fb9e42e7396cb0c726ee");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 131";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a92c8ed33533bcc52f14ecfd71d265b617a7cb1487f644b8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("565d9248960a8ba102a45c8e588840704a2d2391c65707fe7a8ea69598cf585ed681381fbaaa822a1463407acc8a26feddb6ba35a270b8fb51a0b4a3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c471dc3c3b9c39b246fd725f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 132";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("919c282f05f1546a5a207a1923826279fb5326cc6b08364f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ad46407517594cba4dec384ae7838768aa2139e5b6b39f9f00ab6f4803ec1469b3e647a6b302e343c740f5e78c1e13a067bdf028bb3f2d675f737138");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b34c7bf6b81e492f769e329b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 133";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8efe0751f37eb9e193eebc2717a31bd101658d8be3d44a7e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("565011315f1755dd2f6b4e54e34424ee025cbacfb39186692d8ba0426ea018f730f48d8219e5fbb832a6d5159a2954bc7c430eba3e0bca8bfb8393df");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("103abd42dc248163752f4368");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 134";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("089f739fd5f1933f3843706f8fc8809e1c0d2e61b6dc2a70");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("af39806b14c6db90478fa21852bd65285d2d9e1dddd28916085435b28cfddb1b80d670439b0d766da49a17f029227437741c3b0dbb32771797eaada2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f7bd26969204d9e0f5ce5f77");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 135";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("444a2bdf2bc17efbd60235a895abc49d183ef68332d3d64b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("314f069dd4ac5aa3fdc2a74e83daa1d5d18330cd3b90684a9260bb48f5626d49ebd7493fafda93abcb9e3d07e8f85d62e51ddf4a26ac77ee2fefda84");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a57a3bed720815dccaac385b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 136";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("be5e932881207358c3234c6318ff693d35e3473da580ec22");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8ff821e97cef3fc38e19e2b95121186e6c63dcc1d351eb4f3d15d338d9784d273c02cc8c9e62562c471193dc443324895ebe357c4ddd56dc28978675");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ba445d3dd3feb1aeab21d4fd99097752");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 137";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8598a0b22e1402458423e2c1fd3383ac169b72adeadbbbf0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d4a9a08cc1e1354c4265dd0451d10968a593c56b345a5356f7cc1317ed78a7dc620b53e171c6aa86c82f67a5ab0799223c7d03c4f9a1c243861b30a2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0c9a2a9127e90b0768253aa2aadb014f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 138";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a537a656fecf2c1af562505a6d923878d071c1ad04a1144d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9e60eb43006f5c54dedb4656e1fab0fe77d39c19c73a97d0ea3d8f2a58bfe5d2a063c31b5dacb041656261f24337d20ce8aa96a99d2c6c593c8112ae");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("38820063ae422d7cf8c2847737a8eb3c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 139";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4322ae7dea85bee71ce116dd86feeffe5d0a5088f5df3dc0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6a35dbc4a890ce23287efdeeff9042e7f931f26030e410a1ddcdc18a6f73007adac4936f325a3e6e78fc3625b468d8cf434f9b5873a244c14d0c59c7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fccf8b23a997babfbc0732ba276eb8a2");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 140";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a12a70ebcaad310f6502fe82c308cfa8c1f68b1f9ce57b5a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e19ac08aeb3cd78e40548db43c5aca50ad7860fe923eeff02397068611fc8a1f0ee75c30908b3693d2c2d6211c475f824525fc44766fc62b3032e8c8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("86c44150fed84d2e1897666127e3b56e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 141";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("62b8263dc015ef873cd16272e4da89799b910f2b04204420");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8b4d85d9952650aeb2391f701f1d342b45e46f0a33b6671d4cb8b9593d32a0e133f2c6844aeb5a86482263a38bcb545140aee046d6d00f3ab25092ee");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ca558a0bea31ff1299eeb94bc06cda38");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 142";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3da1c7cffaa167557b250634e8052fa030c662e8fbbeabb3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d1de1be5f7a46191bb3d24d86fc3eabd5b6fd6655fb06fcbda7aa4b5cae10ce734e67296c691901fbb401bf9ff3e00e89397ee74342b149a37022cc1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a9226f20db947f835e8575421c05a241");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 143";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("012d3f35fe162ac6999ad84d9057fffb5cac15bc4e780917");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("940cec23e887569aa81d5499025037be68db9ac7f28be806fd501e101994d2b622cb7536ac4cd5b2a45fe5e03597c104e962ed1b11dedd5966eebbd6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d1f90c9f6529db7c7bfa8e7924805925");
	test_cases.push_back(tmp);

}