#include "crypto_CmacAes128Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/CmacAes128Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_CmacAes128Generator_TestClass::crypto_CmacAes128Generator_TestClass() :
	mTestTag("tc::crypto::CmacAes128Generator"),
	mTestResults()
{
}

void crypto_CmacAes128Generator_TestClass::runAllTests(void)
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

const std::string& crypto_CmacAes128Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_CmacAes128Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_CmacAes128Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check key size
		static const size_t kExpectedKeySize = 16;
		size_t kKeySize = tc::crypto::CmacAes128Generator::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{				
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
		}
		
		// check mac size
		static const size_t kExpectedMacSize = 16;
		if (tc::crypto::CmacAes128Generator::kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", tc::crypto::CmacAes128Generator::kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::CmacAes128Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::CmacAes128Generator::kBlockSize, kExpectedBlockSize));
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

void crypto_CmacAes128Generator_TestClass::test_SingleUpdateCall()
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
		
		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

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

void crypto_CmacAes128Generator_TestClass::test_MultiUpdateCall()
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
		
		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

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

void crypto_CmacAes128Generator_TestClass::test_UtilFunc()
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
		
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateCmacAes128Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
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

void crypto_CmacAes128Generator_TestClass::test_NoInitNoUpdateDoMac()
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
		
		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);
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

void crypto_CmacAes128Generator_TestClass::test_NoInitDoUpdateDoMac()
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
		
		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);
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

void crypto_CmacAes128Generator_TestClass::test_InvalidKeyThrowsExceptionClass()
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


		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

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

void crypto_CmacAes128Generator_TestClass::test_InvalidKeyThrowsExceptionUtilFunc()
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


		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			tc::crypto::GenerateCmacAes128Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
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
			tc::crypto::GenerateCmacAes128Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
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
			tc::crypto::GenerateCmacAes128Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), 0);
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
			tc::crypto::GenerateCmacAes128Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), nullptr, test_cases[0].in_key.size());
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

void crypto_CmacAes128Generator_TestClass::test_CallGetMacRepeatedly()
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
		
		tc::crypto::CmacAes128Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacAes128Generator::kMacSize);

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

void crypto_CmacAes128Generator_TestClass::util_Setup_TestCases(std::vector<crypto_CmacAes128Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// NIST 800-38B
	tmp.test_name = "NIST 800-38B Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes(""); //  Mlen 0  <empty string>
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("bb1d6929e95937287fa37d129b756746");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a"); // Mlen 128-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("070a16b46b4d4144f79bdd9dd04a287c");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411"); // Mlen 320-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dfa66747de9ae63030ca32611497c827");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710"); // Mlen 512-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("51f0bebf7e3b9d92fc49741779363cfe");
	test_cases.push_back(tmp);

	// sample 128bit BDK
	tmp.test_name = "Test 128bit BDK";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("102030405060708090A0B0C0D0E0F011");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000000");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("CEE9F355CF79633777514B192C0317C9");
	test_cases.push_back(tmp);

	// CAVS 11.0 CMACGen Test Vectors 0-79
	tmp.test_name = "CVAS 11.0 TestVector 0";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e4b7645b2f7d63b4674cd01970c9d1ec");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f266a187");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8eeca0d146fd09ffbbe0d47edcddfcec");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c3642ce5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5cb7bc9c9e63a6593c4fce571f510a28");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("de4e9727");
	test_cases.push_back(tmp);
		
	tmp.test_name = "CVAS 11.0 TestVector 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("bb3180eb531415b88bc82352b5a8a88c");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9f0ee665");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("756025761538bb9b308151cefd2b60b1");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4768148a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0020c4fe4f1295db0b21dfd7c3314718");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5dabe0b7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("81689a41c5406817caddcc79371cc1c9");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("06052c57");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c498e1aa90902b7b55d3e7f227fadc13");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a1298d31");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 8";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("553421ad3f584d9f4cce5a6d3f184e57");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("995a02bdca8a07002ce58cd7505faa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 9";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e6e1cf16fe3f00ddd962be75e01c5f66");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a479258c00fcc3062aa283a27b1f2b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 10";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f2f7be13829e01e4876d3d7541305d1a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f4b5861154181a9115fa36fdc4469d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 11";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f65ea9718e8b8ec6c776456f9dbe4912");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cd9971df4de72a33c7146a62b2b4ee");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 12";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("134e27b1c4a42bd11eaa174e21767c08");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3f00d8d6f145a375d086c48f5dfa0b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 13";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0c7c530c1781178987c3dcd70162123a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("febaa6b8bc93ed413f850ec798be93");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 14";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("67ceeb8cef62e2c61d7fd64ea0e70e99");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c377279e88e463d1e9277314e10af3");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 15";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("aba13f15f1f4194c3f71a9ce6442bc44");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("98cb784e3170c362f2fcca2a4808eb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 16";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e380798d0575d1269cc8caa231354437");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("66eae0eabd624a7ecc11e9db462e2b86");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9f19065a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 17";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e1dc724d5621fdde4a8c276005d61575");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("879855ff5196862cc77e323f8c76b5b0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d1c2a70e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 18";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("561052ade555eeda9cb38b1cca8d118c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("79fc4d3a8a47385db73e19a5572a2741");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1ec924eb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 19";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("195e059e5710e652744fa6dbbd04190d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("16bdf18c09d60f3a2a32fbb24e64d033");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5cfd2c86");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 20";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("89bdd94dcf1c69d8baf4500e9145247f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c5335420e11c23559835604bf2b6719e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ccfe259f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 21";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4277cd9baf2cf393c81cb7d88b5ba15e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("372aaefeac3785bed8a895a42313ab9a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0d736ca4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 22";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("27fa0d5e45b2f4c20bc4ca564c4e8c34");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7353e93033d56117d52cdf505086ae8c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d6bc6ee7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 23";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8f75b1a872f6f3d06bf47af415f0d630");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f6b1cf75b5cfa4ab323cf04ff13b7a59");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c0a303be");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 24";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6708c9887b847084f123d3dd9c3a8136");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a8de55170c6dc0d80de32f508bf49b70");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cfef9b7839841fdbccbb6c2cf238f7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 25";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e39c6ff1ad22793dc525d34e7d7e7d6d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f23877b77471c80dd565ece7b2ca0bdd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1a5c33d54e6de6d9fa61cb9636053f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 26";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5fcad38ae778394912f8f1b8413cf773");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("07185502bf6d275c84e3ac4f5f77c3d4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fd44fbc0dd9719e8b569ff10421df4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 27";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f084010adc52224b72c562fa57842305");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("539f95998aad8d839476c66393dca1e6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9c0825b0d256a5cff17a05b5385cba");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 28";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f2991112c2cbd3038ae37b772a509069");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("dd63206f9db2c11a327538be6e820a97");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("98c5cf3c917216d645f02d7bb8d809");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 29";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f7f922c86706277a4e98d28e1197413b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("33ce44bdb1ea6fffe5a29004e2cbf66c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b8768355644df5a9fdff2def763f63");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 30";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("26ef8b4034117d9ebec0c7fc31085469");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("189049effd7cf9c8f35965bcb0978fd4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("295f2f71fc58e6f63d32654c6623c5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 31";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fd60ce34a65278f65b7d53904da42775");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cc1a837f5136656e04df65c0565217cc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d76f70b0979a7659043586a3d2f9d1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 32";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("77a77faf290c1fa30c683df16ba7a77b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("020683e1f0392f4cac54318b6029259e9c553dbc4b6ad998e64d58e4e7dc2e13");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fbfea41b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 33";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6533780fc328a88d605268d62f295dc6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("02749f4f9ad82fa7ba41d935a6f1aa6376b30b8775b6445ac89b3eac50cd8d56");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0bfa134a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 34";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("492dacdcb4a35fc438a6eaa35e26d2f6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("992c3e5613ff420fd91be878d0e1d62e71f5f1106f5023f399915c980394d6db");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b0581ed0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 35";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2bb22a8b3c1b5afa34a990f89998a742");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("25560cfd1e4cc153fe483bdac80dc11012adaa3d144d1456ff2cd92190e2bf9a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9ebff540");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 36";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("30b49320a9722069409539d6111df002");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9d66d2ab77fed672e3af1fc4a77cb2610cd54ce3d7bdf6ff7b2cd8088db252b4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("736b240a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 37";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5fd754a11d6b6f0de531fff2b68012f5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7cc7cb01cc966c3ef8a5bd0c911be24cfc919a150d5d730fd8173a1cc356b63e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1019ca65");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 38";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("947b01b10a37b51c704ae87ea0fb59e5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("43e1f6daf8b1f8becde9676b1565403bd4e3d8821809cab88caa34da4a45230d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d3612b36");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 39";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("365df14977f556d6dde65f6670a30518");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1b4e4c7f91c698bfa7470fad1d6092fcefed1d022a9a415effa2d4dd16dde79f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("644ec802");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 40";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("534c6f8f88bc353faee52664995d5457");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4981c51fcc0935f619ec6bf862683b0025cc48724839bc1e67aa3c686d321ba6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6377c6cfe8dd605ef0a62a845ab3f7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 41";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a17c96faa64ccab2c45d93a063893681");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f268c7d4df159ef4d284be92429b80726ef134734eebb9ccc9254c9628139e8b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b73dfe7c491b2d692e170481971e4e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 42";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c5581d40b331e24003901bd6bf244aca");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5d44bac1a388eb81b0c3571f6d0566b69bdef5ff21664b73a4804eb05960f61e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a1447d0b0b0283249e766f838db9f4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 43";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c851f8ec4baf6e1b4562ae917f235df1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("62e97075c81ce3367a652b38268c7f27d837788812b3c59d1ef12188a3cf82b2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("457ad0ade82dfcc8419fdd49f988a0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 44";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e4abe343f98a2df09413c3defb85b56a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f799876d19ac1b849a1a43fe9912bcaf6e1e3896ea58bcb2dfdc4716e379b440");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e08428dbbc13ff9432048c0ad95731");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 45";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("30d276dedfa5a69520e60f12be0be213");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e12ca51c429ed7343367e509f692448ad31a923268f2842e414820bea80b2cdd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dc94042e5f57241361de8b97ff3d4c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 46";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c74a5d4265f9f3d5f1c870e377625f1b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("314e0c7d5c9afb7c4282bc132bf805749554614c865526eb2062a7a57616ac78");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("86f7e503ffe55c187d7fc0e00f7b01");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 47";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c595ee7655c8eeecd3e8fbbbc439dbe2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("39fb12288a67f15fa4191d597c834dc0a049a4fc6ca686b1810ca988730a6f33");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8398e6153ba580cf3c42054bcdda2f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 48";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("499db5a3ecc83d34fd885fde06931097");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f2783540c9e1706ee3e7a43e71833987bb72441c1e2eab58501c8bfaec07d6332a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8e9649db");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 49";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a586d92bc5f946ce58080322045083d6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1295c5bd2d076b187277a02d57912d2e9e2771903182600351f6cca7efb9e47d5a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6e554464");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 50";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("52573c65508869db3259cf5ecb627565");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b11a4c2155d379d1dfa3fcb432f65cc5acc487ca4b1d17871406d331b583792569");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2e8b8844");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 51";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("30e3ea2476b2d889fc3f1565f00ee47f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("255312e95b96e3eb369e3adebd2f5b40835aa058c147271da732c855f4b44afac5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("244ad8ad");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 52";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("db814ed9d5b683ff55a0c95de62bae5c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c1093518efd80245e3c42371f220b21f2034e6738fe02ef43e828190f01aefe169");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("397a193e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 53";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("478a9fb5a3b3aa4327e03d7de4a8244c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cbc2bce02e45704c925f88105ef13236c768f5b3399239e2f9b00a3108cc191b4a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b0ac1e74");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 54";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a8e1484b4734fc6790cd1c87eeb59ca2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("692e47f5701bb2569fd9dde7f8eb8d670c336be77865acdcb0bcf173fbec6c24bf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("99e0224d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 55";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4b03f1935c21e6083ef72d1f7bfc2e2a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("32579b66327335100d9bd236e37e3b0d681354784274a17cb2ef0af4775adb86ef");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a5a7c8c9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 56";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a0c334ff3501c99a9d5f2660f4a2cc5f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b4693a2aa11cf9a5442f08dfa718590feff8d38fdf15f8ee9d8ac541b93dd9b96b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6d4bf50d3a13a26d9dc7566dee1223");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 57";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d26533a760e76dfaa4a7c9529df86031");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("80f3ea04e42d4cef334c04c7eaae86832faf52f2aa286b5a96360b60183d9527cf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("ecee84f81924ee3c20829e3d97ebf9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 58";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c2ca6ace8b8b19314cc14390e22cbc37");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8a782e7b7c2ea77f63ddaa8563ed90d3b57c8c2242a6dd00710448733d72c6df8a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("771a53ea364973cc5c0177db250ac7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 59";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("363d0f98f61d5268f12a73680fb94a98");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2e4d583513c6b8f479f161b442b7eeb87988591e939462b5f53e350eb7cd47d6a8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b52dad0e62d1b05fd23934c2e9c0d0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 60";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a60269f095ad3c3bafae907c6f215de0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cead1c5af16ca89bc0821775f8cba8c25620a03dfd27d6f1186f75f1c0bcfe4a20");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("172084c3fe99fde4af29aa8e6e5fe1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 61";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ebf0b3e3199a5c3773c761c725c7600a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("825b192f69fb73b2716fb35e69d9c09006a8a2422ac7e4e065143c58bd146e71aa");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("77742a4c6087c170beefc8a41d4f63");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 62";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c9def036a29354c9eee018b3cbbc712a");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3a871632f22818bfd717b00618572936f4ba57e57d9c7a609cd0663f56dbe13d4d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("bf51db9d0471613c4d9275e972586f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 63";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("644cbf12859df0557ea91f08e051ff27");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e2b4b6f9484402645c47809ed5a83a17b378cf85224174d9a097397162f18e8ff4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4e6ec56ff95d0eae1cf83efcf44beb");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 64";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("8c9eabe871c6e9511194b48ebf9e9b03");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0549eaeca4f397247f1d259612e6867e7d788c71d03c5136864ad6d84f24eaf913a34e6933");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0c1e97d0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 65";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dd42449da4c95e858b796085b6b5b3b5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4da6feba6d119b8850bed945f57adcd3c3e84f85d581553b95dac3ce8c258cae78fb7dc99f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("afa8c401");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 66";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e2d592cb412e65f9044257d78e7491f9");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("512cd890e461adea7fceebe7a93067d20ed150ee75afc2b9f2da97715d1e81d802e256359a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("35b21ee1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 67";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("46f02659f08ad03125f3bb40cacd0fda");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eb2e7e32589486aa849437c8dbbd713b60d76fa34123f9f6afe4db23ec1d97f6a69d573c83");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2313fdbe");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 68";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("42c7fa8a13ba2d0f6c3760bcd4fa6cd5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("11c90809f9c53d2f77b56af0a42287ac6920e3d2921cceb824d496caf1a7b6e7690f4908b3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0930b0aa");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 69";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("49db86d2b3b1088053164aa464a78566");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("dc787b2386fcae8b8c6d0c9d0c092aaedadd31500d37846bbe5fa3900c82508963eff035ff");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("63744714");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 70";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("cb30d16d4ff5d0cd5b8c1cf6fc9b535d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2e523e9d8a5532127ec63b220838f11b0f8a09e9a317c1e4872d7fececc1b4b88060076ba7");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("121c667a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 71";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("467e1d9893123320dadc3a23c961ec81");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("162ff9478ca06aebfc7f86afa9cdd743916563ebfd3adbdd56e015ea3a4ebc61cfe2473157");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4d077def");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 72";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("6990db6a5cd8dc1494cd63922151920c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8ceddebd38f00406743a6756565ce762d3464435d50bd61b8de57fbe0b79df8f0c5cc66713");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e52cd4fa3cf72b2f06eece112242e6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 73";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("07f77f114d7264a122a7e9db4fc8d091");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("bb5de4bae58d8f49c48811aa31d99bd7877a0ec04de9bcf8157f73afa3feb8e0526950cbb4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("78ecc7997744d4b83db0f8a4b42b04");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 74";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e1895224dc1e4674a9bc9c27b3752c83");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2bed02a7404e47dec28c79c2ecceb740031291fd2cb978f580467263626313e01025a8ce79");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("994e0c7f6689c6e3a13621d38395fc");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 75";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b93d47dbb843681b50b1c268998d4ab4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("60c6e63b0e4ddef24f990e652c9b75293ba8e4567bcc068380629ff1d0e111068cf924fd53");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("395f279ce3191863b4fa84f2dab3c7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 76";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c9408a8b163f1e602894b3239c3fdb6d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ae1009f03626fcb54bf98c32912f0f70bd398c709c3ed8bf5754fe4bf5f6e47521b32c672e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("58c3c804c2985df47c5c4bfcfe8837");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 77";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1f0769a7ae82bd985661e031c4a892c1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a0a64582eff002bb348d2798f67812102377c334544e3e065332318ddb80d7299eaf1c258c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3ac1f80aee7d9ec5284373e43a56d7");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 78";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("184215145da49db417e8bdd573d6282d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5788f61e02304791b52f40057abb4e0446403ef3740253df72059679bb2a6e5e059a709cbb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8da8cca9b36f68571c6c0e40a3f410");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 79";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1874596cddbdf18a10bc71d60c6bb93d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("12a340ef015dc0a38625a4847eb6cac9cab9450548e9f96402756531a6a5bf9c37c146bb01");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("26a5fd25805129756b5b1ac33d8774");
	test_cases.push_back(tmp);
}