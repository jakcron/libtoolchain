#include "crypto_CmacTdes168Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/CmacTdes168Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_CmacTdes168Generator_TestClass::crypto_CmacTdes168Generator_TestClass() :
	mTestTag("tc::crypto::CmacTdes168Generator"),
	mTestResults()
{
}

void crypto_CmacTdes168Generator_TestClass::runAllTests(void)
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

const std::string& crypto_CmacTdes168Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_CmacTdes168Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_CmacTdes168Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check key size
		static const size_t kExpectedKeySize = 24;
		size_t kKeySize = tc::crypto::CmacTdes168Generator::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{				
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
		}

		// check mac size
		static const size_t kExpectedMacSize = 8;
		size_t kMacSize = tc::crypto::CmacTdes168Generator::kMacSize;
		if (kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 8;
		size_t kBlockSize = tc::crypto::CmacTdes168Generator::kBlockSize;
		if (kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", kBlockSize, kExpectedBlockSize));
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

void crypto_CmacTdes168Generator_TestClass::test_SingleUpdateCall()
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

		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

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

void crypto_CmacTdes168Generator_TestClass::test_MultiUpdateCall()
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

		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

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

void crypto_CmacTdes168Generator_TestClass::test_UtilFunc()
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

		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateCmacTdes168Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
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

void crypto_CmacTdes168Generator_TestClass::test_NoInitNoUpdateDoMac()
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

		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);
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

void crypto_CmacTdes168Generator_TestClass::test_NoInitDoUpdateDoMac()
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

		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);
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

void crypto_CmacTdes168Generator_TestClass::test_InvalidKeyThrowsExceptionClass()
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


		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

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

void crypto_CmacTdes168Generator_TestClass::test_InvalidKeyThrowsExceptionUtilFunc()
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


		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			tc::crypto::GenerateCmacTdes168Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
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
			tc::crypto::GenerateCmacTdes168Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
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
			tc::crypto::GenerateCmacTdes168Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), 0);
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
			tc::crypto::GenerateCmacTdes168Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), nullptr, test_cases[0].in_key.size());
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

void crypto_CmacTdes168Generator_TestClass::test_CallGetMacRepeatedly()
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

		tc::crypto::CmacTdes168Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes168Generator::kMacSize);

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

void crypto_CmacTdes168Generator_TestClass::util_Setup_TestCases(std::vector<crypto_CmacTdes168Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// NIST 800-38B
	tmp.test_name = "NIST 800-38B Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8aa83bf8cbda10620bc1bf19fbb6cd58bc313d4a371ca8b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes(""); //  Mlen 0  <empty string>
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b7a688e122ffaf95");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8aa83bf8cbda10620bc1bf19fbb6cd58bc313d4a371ca8b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96"); // Mlen 64-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8E8F293136283797"); // test data incorrectly had this as b7a688e122ffaf95
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8aa83bf8cbda10620bc1bf19fbb6cd58bc313d4a371ca8b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a57"); // Mlen 160-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("743DDBE0CE2DC2ED"); // test data incorrectly had this as d32bcebe43d23d80
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8aa83bf8cbda10620bc1bf19fbb6cd58bc313d4a371ca8b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e51"); // Mlen 256-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("33e6b1092400eae5");
	test_cases.push_back(tmp);

	// CAVS 11.0 CMACGen Test Vectors
	tmp.test_name = "CVAS 11.0 TestVector 0";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c479f813ad1a45d5dc43459da4c85e851cda518af886bf1f");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fea01c84a7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("731331866754588fd332ef51e0ce1925d586cba70440f44f");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("164bdb8582");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5b913e348379a4e610efcb4943ea5b4061dcf43d1a194f4a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("408144b60f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2ff83813757043e9202fd36857f29b20fdf4a7011329f789");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fe5364098e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c737fda24067e5cd62e97075c81ce3376220545d9189928a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c7b4cdd935");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f7f823ce40b368d994d3c84a527a6bdfc4bab69726dcadd6");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("06134938fd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ece9d567df5404b09e10b96d3b4543a11f57949decbc3773");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f88f1e9387");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5b37855d491332d51faea1088a91c775a2c1f7191cba10f2");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("bf8e807fc3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 8";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f87c4c3df71fd98ce532f41ffe315820514fad7c7aae2f46");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("19fbd3dc154bc139");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 9";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b352310ef7ec6b85700208efd0166254085bc2ecfb15310d");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("adb19782ae6b048e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 10";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7fa89e979492ab5873f73b23bfa7b0768a51732c49feec64");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4cbe8146c8df4984");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 11";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0d046bc2cb68a1329be69b6b23ae62ef75294089731fc8e6");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7f42a0854699dabb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 12";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8cc723645164c72c5b014fdc438c232ff81cadfb4629ea5e");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("269445959d377a25");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 13";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("921f52a29408047cad34d9f1912a5b796dfbbfd651ce04fe");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b3d72c414792825f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 14";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9b2a45434f4964a72ce32ff7cb40b5c8f4d3a4614c1c2607");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d99da5f05453c6eb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 15";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2aeffbc1dcb367a42cfb7cd915a49b6b191c4cfb643d2029");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f8510a650241a785");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 16";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d961b6d557aeba4a0ec1bff2797adfda04706168839276fe");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d768975c454f93906cd35e6a6d5f4453");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("967252e4f3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 17";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("df10fb6b766eab34d5cb7579582fb6a8025e459bb38f4337");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("350723c4f1677f7bacdb78d12a22a19b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b4d91d08e4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 18";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3b73bc7f08df2a4f4f37a461d080a126ce8c34c8e9a40254");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c0c6c8328edd3af4450610bf3f4708e8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6e8b65d1f1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 19";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c11c97b9156b104f923e345416e008eaf7bf4aad62d33b97");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bf58b3a092809913030f87bbfa9bcb79");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3dee26006f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 20";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f475fd3e153898feec675d3e73bfd685b661618cefc443f8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("12b894c361b80c3b9c5d649d731f8641");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9fd96ac6b3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 21";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("49526e16251c3d769eda89cebaaed5d39101b5b9b5645b91");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("23f0d00daef3177fbcda6e9953a5a37d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("421b81b373");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 22";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("490ec23ef78038bf34c7644076a41979342af2c44a6bdf3e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c382d2a884c4bb23b880c495fa308af8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a93320077d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 23";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d0aed0a715ef2a830101e34cce38916d4c73c1494f9429ea");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8d5513c36bff8a437d523593d7a36ac4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e172b7aeeb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 24";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("01c125c279cbe90ddfc2c1b04ca8ae491616ad64433d834a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0a258b6719e2e0079b780a0863ff115b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a7bcbe720ac2a7e5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 25";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a252daad731c1097454638abf1f8406dd0aecbc78c018aa8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1d99920c5973997cc059d442467f7659");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7c149012d6120ec6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 26";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5ec14a86753de0ec57b64c20ce70feb0686d1345ae16dcc8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("79fc4d3a8a47385db73e19a5572a2741");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c11e5b01f23b8b9b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 27";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0d6de5a12cb5450e4ceaa8919bad9e40a215163dbc1086fd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7ac423806d4cabc8336080569e16ae16");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("27edafca30c24478");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 28";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("156b1634e562320ef4343eb6bfc8f19d49f2ceda4fd391a7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("00845287fe859c01c8bf667ff875b28d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("68b06080e0d8bbaa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 29";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("988cdf91e949efdf734575dfe66dad648c6d6791f1ad947a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6dc488564948f6599a8dc16f336b6ddc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4a7d85b43ef3ed43");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 30";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d3079267b0f180cbdac4fe918a402691cdb008a8cb9802f2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5787fcfe8a1ee76afaef54cb22d8b2a2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0bb78720fc91e2d4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 31";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c407fd163b2f2ad6c185108f9d0b75cb75076ba2b67f89ea");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2d07f8169c5672b4df7f6cac851b2707");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a10650c22f17e49b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 32";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e6e0d5fd61dae3155b32980e70e6d67fd99d8ff4348fe98f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e43bd49c3976afa78a7138ddabfa132a72e7d1a422b40a582a6dac4a10ce92b7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d44f710b81");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 33";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("204040ce67102c3b3129435d8a853d916d378a2c687670d3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9b758bc93d482505b1b7b6f147203a72e81bf19004a5fac1cb7e236aa0cf00a3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("49001a2a10");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 34";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d092dc436d40836bcbbfce92541a15f4573bb67c76cd686b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f6dd2c64bf597e63263ccae1c54e0805fef6588284aba0b11dac77e3a7f142f5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("095b6b1203");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 35";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ae49efd6fe92ad0b209461ec2ab961e6d0b5ab49a1f2238f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("08711c9b08b1db1f7c9994e0b0d68d22abe79d68b08ad88b0b746f0a0a45d1a1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("999657269a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 36";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fb34b516f1577a7f43b598eaef261f077c75a4f8cba415fb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("44690e968747c3c83c8816c69c989a66781246531d1d78037afb39ea85dfc3ee");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8a7d945c08");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 37";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b0b94fe9786f791574f1cf74aa2d6ef04e55d5d1ad34f9e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4b8ffb7f4bd1ad42b6b5d392bfed6e3e8869b8634dc000eae0d1b45255aac0af");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("88d4b0f762");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 38";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ab322a89ce45b9cbef294c1cdf34d0d323517049853bc24f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("aba045f579e3b9258431bd930c5f1fe3f942b5a66520fb745a65fd3bdd9778d6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("41e6c844c5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 39";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("bf087aea4567df8525a24a9ea8ae9e792076795449437c40");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("44d91d3d465a4111462ba0c7ec223da6735f4f5200453cf132c3c58dfad87eb9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("10726d16d7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 40";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f245f8d585133e3104d3fbc2d0ec80f43ece1fd9a28f5ed5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("993dacbc221ed32a6fb3d90559c674fb68089eea8df9eaec14071991d4fae86b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("25fb962ea93b897f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 41";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("89bcd952a8c8ab371af48ac7d07085d5eff702e6d62cdc23");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fa620c1bbe97319e9a0cf0492121f7a20eb08a6a709dcbd00aaf38e4f99e754e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8f49a1b7d6aa2258");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 42";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f12cefb9dce3b0103843b6137ab9d37f68a243e52fad4a97");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1f3aa619ccff2f3590aa8a4d0f1da4eabad4970ca36a20cc8f5f53404d188d9f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("412031aab6d04fe7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 43";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b151cfd2f160e8c68fdfdbc6813bfa7107cc2800bc77cd0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bedf10354f5282bb635ec7f1f16faa4a2844fd17a7507808f060c4ef1a7fd2c8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6a8e092537cdbd3e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 44";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4cc7da8c67fbfe1c319b463e5e0e38c8b0024aea0d40cdea");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6101be5dec2d0c365747ec4e26d3a0704a0d41e0457f03908ed2ba9637e59dde");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4b585b7cd82b0df0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 45";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("43d575bce610809b752c2cdc25f8679dbaf7a8ce4fe026d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("68b0bd1cddb1e08180894f90823c4e8ce4548d737ed7508e4676cd46cf07d539");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0bcdd13308a7c685");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 46";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("983bb989e657979b70838ae002e554f1effbf71a13f41ab3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("185577b48237acbdaa3590b8057fe374f875ce829b62c98fbd67bcf128b5647f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("74f077d02135d3e5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 47";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("62f4f87361abfb325decf2295b4537bf4c8ffd85267fefa1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("50f6e6dd57bd3a24f6bfdc8b1c7b5a36ebdd07fd6d194e6e82da47151d9c88fb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4d56f473b4159e2a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 48";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ef0d5e94e5c88934bfcbb5806708974a70c14a7031023db0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8d3244bd364eea1f53");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("65527eeb1b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 49";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dfd6d0b058751fa17a1fd67345163da137ad251f3e1f708a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9aa7d5fb6ba2d85575");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5c08414931");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 50";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e5987cc24c087f0dce3b0ebfe6b5ad10f2c768158f0b8a23");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c8f34bea8bdc403a48");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ccd92819de");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 51";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("89dfb51fc807cd6dec6857523775b5ec89ec2970156d801f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("93736ce1d2c29a4fe7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("634129a27a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 52";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("10c80808f8c43d2f9e07dfd6629dcd52012a4cfde9a1add9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ed96b43d65524e4607");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("01b17745b0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 53";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f4324c838501b30e0e9dea0dbada9edf76ea2a8657a7235b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("17943b1e5e96f5f8fc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("486fff5120");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 54";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("15d92ac207139291150d6832258f042f7cb56486f8c1fdba");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d95cd06ce01f402da7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7421ec71fe");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 55";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4c465d7f97c8efb91340ad7ff14cd6455b4f86976b52201c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5504d18fd4b477b74f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b0e9c00e1c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 56";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9e98d02ac8da0da83820da4383ce6eea1619a47fe0a1a113");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a1b0d365ea1bfbf084");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9cf6ad27deb84ee7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 57";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c29ec12ca483c261c1fea734f4ad08108ac27502682c67dc");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("195c0b84baacc88a33");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e3ebff9612494245");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 58";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ce40fb07e531c708c7eac2e03df2a77f232601b30738c7ab");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("af46fba3c3ca707bd5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("37245b1bdd83d0a0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 59";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8a15a1f1cdba9e58bf3eb651ad89ce64b6a7c1ad67348938");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a6dea0cae8eb3cf0ca");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f033ccd7e3320e0f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 60";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3225570eb05be03b8cb9a7327c0e73a1015b9d19524583bf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("66119c44a5ec865833");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("703e74ce50ffc783");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 61";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cb1f70cd2a62c1c42a576eb9dc62294916bfeaa7a73b2c01");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("87ea81e9db767e49f1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ce3cb6297282b3ed");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 62";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f761a28a2aefad8fd0700758d5f4010e3e790d86a120ef9b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2222135e545f2af53b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("95869470a9e3d205");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 63";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e6292368b07683ad6e0ddaa420d338c8ec9d94c454f2268a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d9b0eaaff786165f88");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("67d75ed0db843d1c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 64";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ea5ec86b619d7a58bf7c75dfdca7b6253df8d540732338b6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4cdb3b20d6338b6796719923f4ebb86b74");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("46e2d2a78c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 65";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a1ade61337435e3bd3d64349454cabe562452562c43834ae");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("359421e9f78cc4a31f4f019977d7fd2978");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ff99e6cc7c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 66";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("707ca4798c57dad33be3c445400408bf85c4fda1389edcfd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7c6924e094b1de3740dc0fd22258793a33");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a75c8ab76d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 67";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("16ad890783a71ff810fd467a1643aecd4c160d612c2519d3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d2851559e1bf71689063b550fee21bb15f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("13c59f89b0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 68";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a8fe31e90457236db558cdc491fe688af2792f5b67458f37");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0e403cff47adee3ec5bb6b178dabfc7d53");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d2c676bb1b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 69";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2a52895167d3ae2a6bec439ea2cb6e15aeea40d064103ecb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c737fca24066e4cc5e7a9d00e4baa4d4e6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7aeb378344");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 70";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("da94a89298adb0d0342af8abae07c17943e0fdba80a19897");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e2a92ffbb0b5eb68cb82687f12449fae51");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e1ad71c0d1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 71";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9b2564ba61a88c62a41ab6d3df1025dc406d45973df19b37");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5eef9ba9b98df7347d53ac430eaad09fe0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ef35b7c901");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 72";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f7eca791b902928fbf58b3a1928098132cf883c451efbf01");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7d55c926d1bab1666c1945d4decf3edb36");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cb753ed5b0ad26ad");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 73";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("165e4a6bd0f28032e59883a2d5f71fe6b69e26fda7d0cd92");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7d71b8aaf179b9a44fb639bb82fb1372ca");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("03816a5967bbd836");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 74";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2c94f73ba27ab6dcb0d3f8c8c8efb5a273b3914c910badbf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("31dff7f61598dc59f3201d4d3350fe96d5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f77efebe1695da9a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 75";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("07fd6479c401dcbfe654853843effe3dd34557d08c51c807");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("33d32b2b02272a7d63425f914e4f141800");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7385dfb50d006a70");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 76";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5734dcdaeac8705ed68a6d4301efd58cfd8983a251929238");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("75b53fb352f1506e98fbdd045a6bae73ae");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8e253c8d3bbf5485");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 77";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c161466ecbf4b5e02a19ab4926579eae2afd76f2b008ba31");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("004f1b011c524cfbc7cbbb66a2223b944b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e08b259a68462fc6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 78";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("756704f8292a52806d2a081532833b0e68ec8f5758f42c8c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ede8d466df5405b0a748865d5467f8d7b8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("66613ee2ffc53da9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 79";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8fa8ef15b6c4250e9ec81a68ab9143b96b6ebac70e5e9d40");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("385224798ad7639ad33eab8be4a000527b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("30340585cc81f9fb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 80";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3e7ff2e93e012658bf97790e498c23add352cd26b364bf19");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("75559898f4ba03c55afc25ea91aa61a93c2f8270a5fa51b6f6dc6881adb1412c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e421b43074");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 81";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9d169ed5b0d5babfa123d540e5f7b6c85eaee307c7ba310b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f969ec9dd28ac983e156c0d298837a1e8973a6e784c141cbff1a14f9bb4e7ee9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f90b7b056f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 82";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b64c07d9077c5786c8408a863b91dc014c7a9beada9820f7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9f07e6b7ea8b6d2bb301d6ce7019e0f27ad55abbb799e6d47681fe609af63434");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c021abf3e5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 83";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7c9b6e199db9d3e6766e9bcd3b4fb0ad9bd03eb63b64757f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("991ad7d6667e932d010d00d0951bb7499422d8834c07442fbb9f0c67a4722991");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c5ca5c16cd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 84";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3b2c10adb6f168f4d5a7ad58861af8bcfd5b2c9e8552da19");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("831ffd411139aa8e6ba72ed84d05473484be440300cfbdd12bce827d792bd19a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("30a1d9a173");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 85";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0823e3e6ba9820915e6d25834cf8cb08807cef1a0149f40e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e225c59a2dab3f4eec1e15807f30c10e585776b654ce0e334bde44a8e65b2342");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fbe35cc6f3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 86";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b676708ffb91b351622643a48f07ae836e374a3e768376cb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e2b6b013e6a8202c9ebc76ba8788bb3098393b3826e28ca40513cba8f0ae2947");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7580e56be7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 87";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dc4a1658ce317558a834686ee68a7373c70d98cdd54029da");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("509fd965048f2763928f6d00b679effb7e31cf83af7e8baa6618c718fb024dfc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dbaf3ad0e7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 88";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b5ecb04a3204e67073684ac4a20def6179bf89cbd33baec2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2f65604be24705b4deef860e7a5fa5a42269bef1b5804c132cc8ae7c7d6f2ceb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5a335b8080099905");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 89";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("75767a49759207327302c2205737c875fbce2f73a4805491");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f04636bb9d57f8d861f88cfaa18d12d50d9170c26c3f3d119c92dea1d470eeaf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("087e22d80172924c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 90";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("156437b3d06e9b29fe1f16978f2cf22c29cd6ba2c1467f2a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a1a05f1a7861889d2fb94d2b30f710ad8d75136944cbe0d7c243e8afa58d6a47");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4414d27fd2b9aa62");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 91";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1c04b56164ae7a10b6d07034aed9c14058b35ecd1c9762fb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("744629263041f0eccfce4a1ebcc18c4c984010f9241d35966263a8b2f72ee26b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d9730aaa702885ae");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 92";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("208f806b16c4c801e3e315e379209bbcd5c7834af715ba79");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9e4009917f9759e6f21f5a588010f57e6d6eae178d8b20ab59cda66f42b15c6a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("84c4482a3751c217");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 93";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f71cf7ae23a76776a443266d34c261df1fa126d6b63b73ea");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ce6e57f0140e5f606e404b5991f51679eee7626ad92dbd14ea0c2410a311c560");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c8463d049cbf725b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 94";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("79c17afe0e02ea5267bf7c1a2ae9ceec5ecdcd9eab2f16b0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("799ea038ca740a7cbab457a7404a5b90e9611e6b296ed4eeee710fb37b7834de");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d8ba85e2bb73fed6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 95";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7c34e67a2a8fef581cc4f7dceaea130dad52c189739e401f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eb3365a0a9d141270334065547418fe64c47823c024082b94d54a66d149f2af1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e1d7c3736739e726");
	test_cases.push_back(tmp);

}