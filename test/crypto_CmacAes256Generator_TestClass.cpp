#include "crypto_CmacAes256Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/CmacAes256Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_CmacAes256Generator_TestClass::crypto_CmacAes256Generator_TestClass() :
	mTestTag("tc::crypto::CmacAes256Generator"),
	mTestResults()
{
}

void crypto_CmacAes256Generator_TestClass::runAllTests(void)
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

const std::string& crypto_CmacAes256Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_CmacAes256Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_CmacAes256Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check key size
		static const size_t kExpectedKeySize = 32;
		size_t kKeySize = tc::crypto::CmacAes256Generator::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{				
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
		}

		// check mac size
		static const size_t kExpectedMacSize = 16;
		if (tc::crypto::CmacAes256Generator::kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", tc::crypto::CmacAes256Generator::kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::CmacAes256Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::CmacAes256Generator::kBlockSize, kExpectedBlockSize));
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

void crypto_CmacAes256Generator_TestClass::test_SingleUpdateCall()
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

		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

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

void crypto_CmacAes256Generator_TestClass::test_MultiUpdateCall()
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

		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

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

void crypto_CmacAes256Generator_TestClass::test_UtilFunc()
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

		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateCmacAes256Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
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

void crypto_CmacAes256Generator_TestClass::test_NoInitNoUpdateDoMac()
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

		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);
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

void crypto_CmacAes256Generator_TestClass::test_NoInitDoUpdateDoMac()
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

		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);
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

void crypto_CmacAes256Generator_TestClass::test_InvalidKeyThrowsExceptionClass()
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


		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

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

void crypto_CmacAes256Generator_TestClass::test_InvalidKeyThrowsExceptionUtilFunc()
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


		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			tc::crypto::GenerateCmacAes256Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
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
			tc::crypto::GenerateCmacAes256Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
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
			tc::crypto::GenerateCmacAes256Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), 0);
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
			tc::crypto::GenerateCmacAes256Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), nullptr, test_cases[0].in_key.size());
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

void crypto_CmacAes256Generator_TestClass::test_CallGetMacRepeatedly()
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

		tc::crypto::CmacAes256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes256Generator::kMacSize);

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

void crypto_CmacAes256Generator_TestClass::util_Setup_TestCases(std::vector<crypto_CmacAes256Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// NIST 800-38B
	tmp.test_name = "NIST 800-38B Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes(""); //  Mlen 0  <empty string>
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("028962f61b7bf89efc6b551f4667d983");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a"); // Mlen 128-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("28a7023f452e8f82bd4bf28d8c37c35c");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411"); // Mlen 320-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("aaf3d8f1de5640c232f5b169b9c911e6");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710"); // Mlen 512-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e1992190549f6ed5696a2c056c315410");
	test_cases.push_back(tmp);

	// CAVS 11.0 CMACGen Test Vectors
	tmp.test_name = "CVAS 11.0 TestVector 0";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("95d8afb8a4b7245ce79f9f9c5ddd40de61b35905dcb638f2b875404a985b3f7a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("68adfc9b59");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("96a085fe88bc98c763c1064da4c9c8b4aa4ad42abaff407a4626abde6fecd915");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d8dc6726d8");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("903e8108f35f8503288cd8c10ebdde1fdcd9355aab295025350d62f9dced7ead");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("31bf37f719");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a52345bcb4e95e70dcdf729681ec997a0edd3c6dddb71dbd574b97e45c0c2800");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d4b4e580aa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("baf5afafd7d0c8ad42a44e4e0a90fd2cecaf8df1828686d2b79e56597e71a068");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9746cbe3ff");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ad632ff35d6a1399b7be3611e5ac40b7e8054e83e822e82dc8243294fe806660");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9c3e317928");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("52c557d2fa26693640467709122afb2be6423a1b4ea6795ccc9f6e1ee869f51a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("883c7b812f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f4b9a81167255b58b9fab6f31a7d7eee7ca6599dea24cacb1ba0621547463590");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("683c3be756");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 8";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f0a3e4c237d86718d84c43185e70f9cef0dc92b378e3e0db046b06716cfb3b61");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("38ba46602f3411a58b2e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 9";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("71afe8d00c6f2ea8c8b050d4cd45e3686f84f60361a6ea54257184ddc71440f7");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("93057873b0630ff6de7e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 10";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("14cbb770baaadfdefb86af89e5453acac11cba813a17d44ec1f61d042f3bdc5a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dde61fa1342b15a74d5d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 11";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("13835e3d8085bc369a69b8851dcc0e49c15458030e39813f72047c7791973634");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0cb93914be23792dc288");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 12";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e6bd0010c98e60b9af7cf905c58e0653bc425e2ccc809bd4f9cd7b1f95c18786");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b1685b1d2bb24fbcfb33");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 13";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("da79b90f78efa89246c79f75868814248991018722b8f0cc5c32556868b32158");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("83a88e0679bc915386e6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 14";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5cfa6e5a2e9a8b49ccbc73e442ca3904d095bb1cee46c9cd8d9789b4a0431987");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8e36aaec763c6690bae6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 15";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4551c0ae63369ac860a655b09c50791e063c7dfcea513a100a1aa0dcf1caa8c2");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e8eeeb5415a2ab24f176");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 16";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("916cd8119a4d7e825e01a86f93b0eee4a46d29216115cc9ef67a784c19c1ca1e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3310fc5bc910f4c9b9cf4957ac638ae7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("03f045f886");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 17";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("009f47f180e085776be6644aeac0070be64c289f84a7ba3dece7cdc54f0db354");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("41b98538c752795d9d48702b56f334d9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b961aeec5d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 18";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7ad491ec57187d4243c36603cefe682c0c56675c310448395e71600fbbf92cbb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0ba21b260ee894147853a14328cecf1d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1dd6cdc6a7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 19";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("29fcbbc506989671909510f08c723f51de5836aa58a17cb7d098bdc5757fc0ce");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c00f1b8066677c63e898fddfb8a1b482");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("097a7c5ce1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 20";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5fb57eb6861dedb1fdc0319e4cd33bfb086669fba8e9fd2b94eece557f313da4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d4dbe3de674d48c2c16e9be544637f2f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fa8fde4a5e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 21";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f76c24a362e1e252db2549c5c4e3e5ad1de8e2d19de2c4f801685909a53beb71");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("972996d5b4b6829913d5acc3dddda2f8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("46c87e989d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 22";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("213c55808de5d1e4147bd0e64f41570711cf6ebb4b6625622c81d9798cacb412");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f94df6392add216cb8f9b8264c3a41e8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ba01dea290");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 23";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("28d44a24d539170f5ff419afcd0032efacc7f2adb1375f6ea019f1506c9ee140");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d9aa092708e53d1ac81b7b0070586e71");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1ae6edcfcf");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 24";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3a75a9d2bdb8c804ba4ab4983573a6b253160dd90f8eddfb2fdc2ab17604f5c5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("42f35d5aa533a7a0a5f74e144f2a5f20");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f1532f8732d9f5903007");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 25";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ceedd503bdedaf238945bb060f6772ce36b67b118b98748d29ccee17dcfeb9d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4064b1cddf29c0c9adb380b2c1525074");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("35b4b77e20cc372f5675");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 26";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("739d3c7e0b5ea38678becd6fcae05a26c9bc79f22d7db6fb0d27140c9a7d5c98");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f3c1888da16bb2de8579915debdde521");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("16342e2b828eaef6969d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 27";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4216333f61d3e89d149d274913d51cd2849cb6767d435039c4039134d9ef9030");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ffead34ac26e21158212d07c367c3a7c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("29a70e4692d6acb92b79");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 28";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("20225e1131dda70ef888ddfcb7f4e7400ccfff34bb63a079ae81a68f3ab7b1a2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a233fed49f866ba32f1c14a57b8e0542");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("956f17e83094b9d762ca");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 29";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c286bff65def16797bdfa7e70fd10c429e8127b53a09b5d6b44a26280e8dade4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("218b8756540fec98772183aee7ffa265");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4956abf4a4e05d59e8a0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 30";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("13ccb08a580efea53dfba6a59626bbe2a6dc26333eb8ec1a2572af3bbcf87813");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("868058aa92f27a1eec013570a509c602");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("66249fa56ee9b3dd4520");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 31";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6e0fcede3647b6b739d490e5b68836f0e74454de856c114b8f98f1bc488cf931");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8c09d421e09dac1d9d966f02a3a52097");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("01e776d3c54f825d9ce1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 32";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dcba2ce01633937b1cdab12b2e83598a49c51609efae0f4026b62d82c3f280b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9aa3e8ad92777dfeb121a646ce2e918d1e12b30754bc09470d6da4af6cc9642b012f041ff046569d4fd8d0dccfe448e5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("816282fb33");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 33";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b122ac8f34ed1fe082a3625d157561454167ac145a10bbf77c6a70596d574f1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("498b53fdec87edcbf07097dccde93a084bad7501a224e388df349ce18959fe8485f8ad1537f0d896ea73bedc7214713f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f62c46329b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 34";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7511f3a04e0ea0e7ceda9e06666d1553ab5863840ba76db6b80b37b5e939b377");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("30834308187b8be1be405d4b274d97b5d8ab71905064185fd73b990d769a018447ccc27bef6c598f681e2e96047dbc30");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c04ff71638");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 35";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ae7e255de0c5fd0f59e634ddd8f7953697975a3bc68a428239a3e4135ee743b7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f8e4c7147fbc3b09f4a1feae73112224afc5107b87efc217dac033589b2d147a28f3c1b9d7d873b9d234b72626b11f97");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5582966899");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 36";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ea68a20612f3310649e7c63246b26a7efd016030677a083a85ae03c7a3499814");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a0629aaac155fe0363ab8bf0221e621bcece73c86f369c66865f156396530b45e3d58bf77a4fa260710cc33a70a76822");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("eac72a8229");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 37";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9b1e7e52ea1a12444d884866e11dcf367b70b816460936fdaebba36d7d35c4a5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eb80a43c5986deee6925d7c6d53cbdcbe11194843ea133f72d3590d8e8363efa3d4234097c7fd07b93301cc478864fc9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ea1a350fc8");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 38";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("50f5ecc3b95a1b5db44ae5706a9bd91d061c9b4a697937a21e5eb4dd90dfed42");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ab23b53c5d8a477721201a77ee927c6a0d92a6b320cce185621cedb130fea2bcc946d835521185451dfb25882a925f1b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("61778985d9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 39";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("45c2c86fc0ad37d8abbed5cc9dbc9c76e64af2add11a16c9265ebeb6f37fff47");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e5267407c93e225cebb9503966568f7406c1af33ac653e5cf4814b4d167e6fce0a800f43f03bdb27ae089ab5db372ae8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("073e125891");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 40";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d1abde73d927eef381f37abc254ed995fed933d499419523871d4484571a5293");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("21ed22abc7bbb62fb2d51d1fb8830ca95b16213f56291af976274934ab0d43805f71d9b906c44973f7d4b59b7a94d35c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3ad12df7acebdf36ee1a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 41";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("615b79304be63ee74cb1b63581f5863862d78a6b48e177c22db3bef7b3f6b31e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("99aeb57d7f95703abbca5a215a3197534916139c75c1c6a5304b376bd7b03fefb12410301bab7556e2e45c30f12591e0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f3f16805e1c7326524bd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 42";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("506e8f2efc8733b454fba43a74c7fa4d428b6626a2ea0a2ee9340ec19542f032");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ac087420feb1e1e8c2546c2a8b8a5af0d03b05f7e5bf74fa29432e33826f50200646de83fb4d57ac02ef8cfa8f20b1a0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("32c77c481821184a3e72");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 43";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cdb6ef161bd4be6f0381ca5479f048b8f2d2f7edca26a617e353f8e19074646e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1341a69f685f376cc53cff3252347bce8d9a42cbe2fd39ca7baa06275972c7d9a4ae039a3f80e049a05b978cdfc526b9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c663efb93209a0ea1068");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 44";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7bef8d35616108922aab78936967204980b8a4945b31602f5ef2feec9b144841");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("40affd355416200191ba64edec8d7d27ead235a7b2e01a12662273deb36379b8a748c422c31e046152d6f196f94e852b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b2d078071e318ec88de9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 45";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3237b8b4b19b31a220dfe63882937f8d5ead677608c42a57217f2239614c521d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cb4239f3d724c00fad64f8bddd638d8b10370e5becfcef5b386fd43841b90d8f7c885ca56c64ff57c641ea54d4505589");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("810dc0f31bfbcc8f5633");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 46";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0f7b1420258e1d82cd6949ff87e327c4611b668db35f2fb00c4db95d6c381724");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2feacaa68aa5706f4288e5ee677067fbc50bb8e2c3321f5c8b79afbe6b04cb717b9ceaa28101983a1182be11f9cc225e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7c25582e24ce3317a63d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 47";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("85e3e6391b13c2a32369b23680504cbf1c127b10d2367ff68c0c356ba886990c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("674a7b4be56996d4fa5a6d8a64b6cc5b6a7947d76c4f7392be0e56cab7831b4a04710a8e42d7b828cd727b63d2832125");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3df3b0296892b03b24d0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 48";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6c0b2c3c5fec961ab84e68f56ca166586e5942fb2594b18a1dfdc4a8fdf07634");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f08f890875e139480489");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b49c2239e7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 49";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c69f7c5a50f3e72123371bbfd6bdf532b99ef78500508dfe237a949884061cb3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("047840ea96850ee5c0fc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e5a8fa8047");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 50";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7e8ea82d1137c1e233522da12626e90a5f66a988e70664cb014c12790d2ab520");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("19ebfde2d5468ba0a303");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8f3d3d12bb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 51";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("de8e84440ad97d0ae5001b3590b5182b2f9b5cc09158c2f00fec1fd4b64181cf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0cfcd5f96da1c6c66cbd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("082b5ab895");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 52";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8de30b07e8352f91ac06aa967c3a62b48d035053b9a63188cf837e3a2e509f83");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d3b27343119c0ac00a98");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("71530400ab");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 53";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("91ab9c7b77abc6bdb043758bfb87802d0da566f48610e57b24ddc92d366d0307");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d40d2736e8669c98ba42");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ad41f7f8d9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 54";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6364071a20bf787b16cbcc58397abcd135957d970401f253bf402046b43ae22c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fa490aeb51b2c516f49a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0421c439f7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 55";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4ebe07d03c93e849b4bbfe9f2d2294bf6ccab457f76d3f99cb643d3c51c771c3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a38231af405dc7b70c8d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("41e5c8068d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 56";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("712e6cc33d3d1f442776d546f4d5a25b7d23402a5fd65e6ef3333a4281b5729b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("56c026b8a71974ff7ecd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("df8dc096f5b385faaffa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 57";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("bd05d26ebfcb5f6e102e79976fbd038e02da6a64a6be90bb84bd092be5cb8ae4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bd637f707f9e8d4f0cb7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a7cc46fa9fc37800339d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 58";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("afa88f18ae879a38cbfb2138484a22b0afe90aea71947797cd9d42c0f385bdff");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("deef247a0573e87a6474");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("03b5a18924f92f3ebc76");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 59";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("273cc5013785baeb5abc79c8bde73af71085d7018e7be92a37512e46609e2fce");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e30f71cca7fd341551b1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8291ac51a937856300c0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 60";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b97e055e3306cf1de468859fb2445c1695012ec84db5ca1250448fad07cb3930");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b204fe3357150f7289f6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d9e121bb4ee358df64cd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 61";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f8c3eb48608018d3c7701c956146e68bc19fb7c6499e3326e5d3b966f962f058");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("405056131c3293f9d9f0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c549b625c6cab8360d2e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 62";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7c7c857ade97ace0595fed960efe1939f61991b12502af094f30617d8bed17d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("95534b3d85495a7bc8c5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8f5c9dddac54694499dc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 63";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ffb795d9a4f1af7847c82560eb0728545921f1f6b773f8315cc867d4e322ce7f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fb7ffb9ede5639dc7ea9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c68f3e63165d07170cad");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 64";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f64e41e62cae5c26fbd3738916f5f39b67a62f3202fef8ac57f56e78ab1015d8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("449f3e3ce08b72f4f9bcad194acdad");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4019fda078");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 65";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7a07d53dfd8390b9c2cd25e4c190def22ebd3c6c4338e0813fd1ab9eaf75253e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("73cd8c9b7502796e75dd9e1a5ab2cf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c74145e986");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 66";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cf3b0ebee6b4ac11aa7678b2f5453c1307af5cda7c34672a7baaec252fe08faf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e4bd45e31e1d3cf9276096c18d2d70");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("326b023904");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 67";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("479720cddaa5e008fa194bb859ec3fce76b2d696c229a0e702122f9df43fd948");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3a987eb87958080128f08dcdf91e63");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1ebeca94ae");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 68";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d32ffd217fb41ef4a2b31d3a47a5e8386925fb90fbe980ca2cf6ba34e814a3ec");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("af87b347b59e37a424004a00907dcb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d628508d13");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 69";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("55b59eb434dd1ba3723ee0dc7286731a0afc956e21be759a7d4d23bbd64c472c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5e22dffb5ff90aabfc5d6a24013c46");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7a5e2b2481");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 70";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("94897ce2de8d0aa884f9ecd4c61ff580abfa0c89e7792d89021bb005b7bccee8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4a5810b121c91bb4eb31cd1a8059e0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cb940e9579");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 71";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f95d64a513a9f3e6c95c9ed27b22fafd7dd10da52636029523142149116aff53");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fd940ba0ea21a9341cfc088df2171e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b099d3f2b4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 72";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2f4a6501d8fe7b65f607757ddff6ed87ae0681b98b53331d2d46109f9c541065");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4fa9ac1b544afcd85ac32ac0909c74");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c02e8b66f9fc263b8fb0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 73";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("012b4cfce8a1acd89de5f6f78794e2813bbcdb89959dafec08ac8a7c32de255e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7cabdc7eacd764001509c925edef0d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0da78ac83b1c0141968c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 74";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("bb3087d1b5b0f6f14a532c3604c82874fb15e97a4b3883dfc50e71ffe5752d40");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("90a10e977c80cd885ff45487e90365");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6fdc6c626e9a8be6c34c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 75";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("569d50d2ea793302102714e517416e1bee942fe59f8d623a1aee0b1834c55219");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c2c5846614fba01347ed69221daab9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6b475d0667255b5a49ab");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 76";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("698bf4fc0b9c2196162d9405b5ce7460ef7e8dd884094fa617951a429277b9d6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("03c0dff0253a0dcc9afd9fc6dbeef4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f00b02485fc68158f84f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 77";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7b352c47a4718938f842f6924684edb8f6512f33f9245cfa003ec1f0ec4971af");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e48dfaa53b6807ea6f01d8dca67960");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1b5818e13a629caf728b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 78";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b331553cfe0308f1be6b162d11a12ff9ab144f6b1da42b785711ce0a6cb38452");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("240ac67c0bfb4254d8cc6183ecf213");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f5a1d5715ceaaefe1734");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 79";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("397e826e6f0e7eb141087b3c5eb6aa47b399950827526bc289c398fec6719918");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("72142aa104b778564edf32daebcb64");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("834a790b5c40f4cf7692");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 80";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("166cc49ca548d5bd871751ce05c604bc6a4b97dace2e07822d4856ffbccb80aa");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("065ff9e8d511c61da3a554d598aebd51419a8592ee8723c95858bd0f87083456f33f609fea239d6e3171867beecc00ab");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("150d928f7e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 81";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("80441013c0cce59292a799e58a2fee5b0758daa15741d0ef2209417f05e46343");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6fd89e3eb7b048eaf66beeb2ae543ede159b3ab66855319f81c5ee88acda2f84b7f859b848fc6978737a2ead8c48b67a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0e7679e2db");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 82";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e0e54be32dca732c5780f9e68816fdc17de4cde68c79078be5d5fec518d95f9e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f706a3e09df95d3e21d2e0c886dc5dbd9eeb6a2fc53f5108cfacae4a3ef8399bb885e000b92f19e98678766e62e379d8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d913ea746b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 83";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4767cfb06f010a20fdfa790dc91acb391fccd9ebb8363636e9aa087d1b3d1737");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cf38216a33db0f5b6c4c9f413ba29f8001ffb5f4bfb7f63340b5b313951b966dc229ee20b760485882e73f10c22d95d5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("84056758cc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 84";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b8244a86f99f5b0d7533c599b1205a0627c9816e99b82c4ca4e10ae1982bfdd7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f12ee9d37946cfd88516cbe4a046f08c9bbba76a3973ff1e2cb14493405bd384d7a02c3e95dd49a75cc22f7f7bb1c2e6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d70c237f94");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 85";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9523f53f92b6e4ba86e56e11e0fa09f2672b6269c411fcf8415c19e9d0c4dde3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f0b3522e21a33992e9af29c48d58b3e33d5da15b4726d2678b6245d52ff0730a94fbe245886af728bd770c74799dc214");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4bed0d0a2b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 86";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9caa7d82a499d92ab491bb6c7bd66256617e9d4fbdd5989f48fff532d2df1e98");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("effcea4e4dbc57410426b39fcf51c9daecd9d310888590d77827973a29c4ebffdaf5cf2c088ddcc92a7c50e69ff4a9e0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3cada30439");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 87";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("68c2249c8a338f6358963638bd016c71c027a600a1202f5225681d772e298382");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e6ffb8b4bc6127e2fe74a8773628b517466ad733a9560eddfda873dabe741cf9551840a4516e9bb5f446148bf1139e5c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d9f205e453");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 88";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a4b91d7d6b655945d711c203f7e2f99da891e3380a12b7ff3073551f1c06da16");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ad17e9724a19959a92425cbb099193ec38fca8edb0614eba4dbfda60b8a6ed102fec547289a22c3b74464a02023ada50");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("34f439ba9d90c8555b21");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 89";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("97b9814d6cb36376c4730dfde6349c19741b743095c784035229cb2741961ab4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("635f20accf83befe972cfdcbcdf79e2549256aff43e3699021cf55fd8db94e32cba6cf10491be1ce78988f99db62997e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e0e61b45ff5ac43b504d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 90";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8a981033d7b4eb4cc9648ba26ad9679c1550dcf32df17fb80ef6b299440f7560");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ad7883c7bec55f31ccf6f62bda15fc2fcb890ef6c8e738e8e10bbad6f7680cebd99c1fe0ad47e670921e150c833b29cf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2665bb30e4fd690d485c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 91";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1bbf5a21762dd5a9371ea48fc6e919f494cdc3325d27dbb8aae8de1599477c52");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5c98dae543dd618cd6c9ed391864335f01d9869321859d40874e959ce13639dae52f82a2ef325abeeb8ba516757782de");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("02ce2699e19f7d1da2b2");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 92";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f81ea615e48c0a25410ff15c1566b10a83fb9d839b667dc577333b5b83e5df81");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("17fabce1237e7a0cb5cbc6d1ab5dfcace0ab85f698ff555c1e86b890aba34f3e8a8955427a09271854a80494edf511d3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5202993b20642a8f3cfc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 93";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("23e5422e8d7560a9e65642b5e723a47536c16791f3a0cf918d3dee8adbec60fd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b9ee1400186c0c0774401a815bcde30d3be1d4f87f42646cfb8a99e48a35cee3f5f9b3e6175695973f6de043d615e28e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1775847019ca9b88683e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 94";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7cfc086d10659d7cb9247208358dd82c03b8dbd8233223231df218e2448f4a79");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a3af8f99703a601086c2a1ffe55fde4c2c4153dbff8d6601ab68743c0d50d021b0b3099535ba6c40f866ca3ff0df7c19");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9d713a1944b8eb649584");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 95";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d0f46fb37d516cc957aaefd3be2a8bede885330a8edb96f3e5e0ab8cd03a8c59");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("60c5ec2170e9bf2b0d24174a7bbbf41056e778a3772cefb71ce60cb94225754d56ba83fb0d9242259143c03ddde58435");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("03f592d81ce503133129");
	test_cases.push_back(tmp);
}