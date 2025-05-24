#include "crypto_CmacTdes112Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/CmacTdes112Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_CmacTdes112Generator_TestClass::crypto_CmacTdes112Generator_TestClass() :
	mTestTag("tc::crypto::CmacTdes112Generator"),
	mTestResults()
{
}

void crypto_CmacTdes112Generator_TestClass::runAllTests(void)
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

const std::string& crypto_CmacTdes112Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_CmacTdes112Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_CmacTdes112Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check key size
		static const size_t kExpectedKeySize = 16;
		size_t kKeySize = tc::crypto::CmacTdes112Generator::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{				
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
		}
		
		// check mac size
		static const size_t kExpectedMacSize = 8;
		size_t kMacSize = tc::crypto::CmacTdes112Generator::kMacSize;
		if (kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 8;
		size_t kBlockSize = tc::crypto::CmacTdes112Generator::kBlockSize;
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

void crypto_CmacTdes112Generator_TestClass::test_SingleUpdateCall()
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

		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

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

void crypto_CmacTdes112Generator_TestClass::test_MultiUpdateCall()
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

		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

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

void crypto_CmacTdes112Generator_TestClass::test_UtilFunc()
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

		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateCmacTdes112Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
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

void crypto_CmacTdes112Generator_TestClass::test_NoInitNoUpdateDoMac()
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

		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);
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

void crypto_CmacTdes112Generator_TestClass::test_NoInitDoUpdateDoMac()
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

		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);
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

void crypto_CmacTdes112Generator_TestClass::test_InvalidKeyThrowsExceptionClass()
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


		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

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

void crypto_CmacTdes112Generator_TestClass::test_InvalidKeyThrowsExceptionUtilFunc()
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


		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

		// try invalid key - key size == kKeySize-1 expected
		try
		{
			tc::crypto::GenerateCmacTdes112Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() - 1);
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
			tc::crypto::GenerateCmacTdes112Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), test_cases[0].in_key.size() + 1);
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
			tc::crypto::GenerateCmacTdes112Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), test_cases[0].in_key.data(), 0);
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
			tc::crypto::GenerateCmacTdes112Mac(mac.data(), test_cases[0].in_data.data(), test_cases[0].in_data.size(), nullptr, test_cases[0].in_key.size());
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

void crypto_CmacTdes112Generator_TestClass::test_CallGetMacRepeatedly()
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

		tc::crypto::CmacTdes112Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::CmacTdes112Generator::kMacSize);

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

void crypto_CmacTdes112Generator_TestClass::util_Setup_TestCases(std::vector<crypto_CmacTdes112Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// NIST 800-38B
	tmp.test_name = "NIST 800-38B Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4cf15134a2850dd58a3d10ba80570d38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes(""); //  Mlen 0  <empty string>
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("bd2ebf9a3ba00361");
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4cf15134a2850dd58a3d10ba80570d38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96"); // Mlen 64-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4FF2AB813C53CE83"); // test data incorrectly had this as bd2ebf9a3ba00361
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4cf15134a2850dd58a3d10ba80570d38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a57"); // Mlen 160-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("62DD1B471902BD4E"); // test data incorrectly had this as 8ea92435b52660e0
	test_cases.push_back(tmp);

	tmp.test_name = "NIST 800-38B Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4cf15134a2850dd58a3d10ba80570d38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e51"); // Mlen 256-bit
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("31b1e431dabc4eb8"); 
	test_cases.push_back(tmp);

	// CAVS 11.0 CMACGen Test Vectors
	tmp.test_name = "CVAS 11.0 TestVector 0";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("dc047368023252d90ebccdc21661e3ab");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("72619dc7da");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("76fd92070429d33d29029b461a8a2f57");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("63929877f1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d0b3bff4ec1a86d9e3807f6d8c6470fe");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("36f7b98700");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("70701c80cd750434685d9df83d5b6b76");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4e6bf8c25d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("15b55dc2ad0e34cde5ba52aee357fe6b");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b5686e2670");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("52524f109daecd25f24004a14a4a02a1");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8ea3b28647");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7ad398d0b9b55e7a9429e0869134feb3");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("87f71c5b94");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("325e3416f2d6f1b685f746d367f8914c");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c4ec48b175");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 8";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3d4cf2641376aec213a8265d529b7a20");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cdd2e2c84931c1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 9";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2f57e6190ef1b0297f388ff7ae2a6e6e");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5c5e84e3c765b5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 10";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("aeea40d064103ecbbf43a2a461626b1a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("caa4d94fb18348");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 11";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2f1a15e36d5ba47c7568fe13c78f7349");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8f27a15c2a9f6d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 12";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("57a7dfb6e5a42c373779e0d373619e73");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a62b538942d222");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 13";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("32b34f58083dc7e97f928f9b62757c5e");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6333260aaa2103");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 14";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("add537b5bae3aeab3467c401c7ae2a4a");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c97113e9d2c64c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 15";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c834086e049ea73d19f4d679adef01ef");
	tmp.in_data = tc::ByteData();
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0d1d169b26b29d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 16";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d3948aa4527ae5ba1a5432e9085410dc");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("392e557930d304d5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0c01233c9a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 17";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e62f08d02604fdcb2c166d620e10e507");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("95848f940562ae51");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("876d6a3869");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 18";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("523ef45db564e0b5cd5454bacd7ab379");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8f0a886f031f3004");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f11e5f16fd");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 19";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e94f9ed0cb61851f2c1f4ce523027cec");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d332f055ba7b5b83");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3777f9db5a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 20";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("51f4ecc2b95b1a5d0ea86b23f2ced5a2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("30123b47bb03efd0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("449d3f6859");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 21";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5d7af14685ba3b86fbd515dc1a0eceae");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("937179a7bc4d1c61");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("945d6b90ed");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 22";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("a14f3ef1fe5ed032f78c0754e3bae6c1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("ef36c84fb38c265e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("48b6cb2a78");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 23";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9ee9fd1f0716868592daec9ebcfddc04");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3a871632f22818bf");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fe702a5077");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 24";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f84c02fe1568a27f1cd56b295da78661");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("97d86405c839a843");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("13fb40188a3908");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 25";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("2f07b34549c79775dca1eabfdcadec8c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f4da8ac3e8fe5ec6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("98258fbcb8cc7e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 26";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("efc8b3c291dcc7dc5b203775260208d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f7addc4754b5a87b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cf406ff782a89b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 27";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("49d9929e76eacbf154c7074094ba4c45");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("fd771c22a410e256");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("52b248b38433b4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 28";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fb0179abad894940014c23ec589d6e92");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e304e9ce0f6e1d19");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("84a3822f641961");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 29";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d9316d9d4fa7c79defc8b3c291dcc7dc");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5b203674260208d5");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1eff0c7837de36");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 30";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9df1d6b6dfbffdd3a119086b1c2a802c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e12ca51c429ed734");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3891b71407dc40");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 31";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fd761c23a410e3570776fd1f1ca47304");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a6c0b14ca3da7512");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5c579b91dece53");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 32";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5db9b0d6b5d92546861cbf5bf8f2f1e6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eb00224e03652eb1842a477354ae191f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6175a0f36f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 33";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("511c6825fb97da7070b5d5190bec499e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("25d87c4402f34ea59b3898beaa401e96");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1876c6a272");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 34";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fb529eb5ae79a183fd1975016d2c544f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d4291c99901345afe29f58912a414a74");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9120c409c5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 35";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d00b7fb5891cdc23bf8fe345eac4493e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("57473e7a105c80686737919409219f40");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0877129e11");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 36";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("734383ababa470d52a8f5b85086bbad6");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("63d22287ca5e79d624b874037f424296");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8a81246256");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 37";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("df3d5e3b08e626c7618629b9948a76f1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b6cf7cfb99644353ca5ee9e5c59ddb40");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1bb0ab6d51");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 38";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f868f2833426abbcce7cd323e964b3ec");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3f2bd2c69eacb04de67998e479fba546");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("995628b4d4");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 39";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("672f8cc7c4ab8f972ad307575b577c2f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e45caa8daa717262ecadfb51bca9066d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2f9fe28670");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 40";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("b9026ebada6238d9207f073e1c1cb6d5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("233282ca3e2afc6f4c471326751ed25a");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fe6ac1bf3a1589");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 41";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("40345bcb10e908a88392fe1c0d156467");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b4998b470cc0cf8d414fda8937e9cda4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3093c36fd9f026");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 42";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("202064f792798946618ac84fb68a15ce");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d44af86b89fda8448a9b2fcae20ea156");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("dcd0998b8c0a45");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 43";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f1ce4998a4fe230858fdb320cecee5cb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7ae5ff5166360f5cda5c588f57e306f8");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("7ef1d5591b6887");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 44";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("52a76854b515a2572fc8efda6b684f38");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("39aed28cd9b254993e284de7ee871fdc");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d82f16bbbcff39");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 45";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("34f8ae73a4fecbc816f7ce8c6ea4df57");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("090e882cf7a1f2c0017004542d72a2c6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("f2e180eaaea9e5");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 46";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("793470131f522519165770ce1f9bcb85");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("babbd1b44cae3af06e0150bf0e3d898f");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("349c9ef22d3940");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 47";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1aaeecba670e458f2cb3e5b9e68c7fba");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2e722055e5db77dfe44c1c3f0f24c7e4");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3ba35fbd85aeda");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 48";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("c2755776b06e6797261aef15a138388f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3094b16e28991c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("15a37f1a7b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 49";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("f8f1492cb5ae70cd5e979419c8fbc7ad");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("53534f17775c0e");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("2c2a553296");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 50";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("9e4c8aa8b58a8fab2fdf43a8f1165873");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("22f8a9a9604ace");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0cea6bb2f6");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 51";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3e7cf8cea19d0891f8407a017ad98a80");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("90c6d7b74e958c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a624e28fb1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 52";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("587f29493b6413f757a13d20c2a48f58");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("67299f79ec7f33");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("26eb5358a9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 53";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e5b6645b2f7c62b526ef8a460ebfbffe");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("071c4250989882");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b6fbf7ca85");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 54";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("40839b64c29da470b9f10d1ab5d02ace");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("2bed02a7404e47");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("28457d8ce9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 55";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("574f1616c2b337157a4f2f761057f4c1");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f479ea8812b6b2");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("96a4efda3a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 56";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("01adc808b6d3ba3b0bf14ffdd513aec8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0c2933e39d7e60");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("126a83c2e0af5b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 57";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("04d3fbc2d0ec80f43ece1fd9a28f5ed5");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("993dacbc221ed3");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e5637562cc529d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 58";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7a8fecfb8a195dc28f8cfe9770b55d31");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("32c8a90817d972");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("22380d8ad152ba");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 59";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("896bb343cd2a1094942001047c4067cd");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c5d6acf9cf8a55");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6b8b44f28ceb03");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 60";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e5a4fde05da8f4317c7a8c671ae0ce79");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("03e1bbc21e2470");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("6495e81827572b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 61";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("892cefd5161f86fbefc4c18f5715894c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e45bb06d326012");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("efebadfe02374d");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 62";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ba10a41f34d9f283cd62d0f27a7f4964");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("512cd1b05c730d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0ad09488985436");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 63";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("85467aa82c23ab012954c7377f1967d3");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("036138d4c704c1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("84e43420e9255a");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 64";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0413b367c2bf491f5eeab54043fe7f16");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("70b2dbfe6d892ad8d0d048ec8a04c9");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("d525aa3643");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 65";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("31d083a4c83129a732670eb97fdae9c2");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("90af89c950d6221473a358dd0f2802");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a6f4a58b42");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 66";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("944f9de079bf3b8acee5014692859851");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8e5bb5588dff28210a427345d48502");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3310eea2e9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 67";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("98e3f2e9c264a179e61f9b673d3b2a51");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("100fa71462277d76ca81f2cfdb3d39");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("74840bb6ef");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 68";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1c31192ff726f4a1e6407051d386adad");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9a56a80c07149fd9d166e0b59a3148");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5829df67c0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 69";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("76dfa8684607ad3731b0a7d3d046c413");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3eac4fd36ddebfb187b41372526be6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("76f0cb9ce0");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 70";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1c4a5e31b99b3d6849499b5ed5616702");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("0b427aeb39a0e8457e14feee072be6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e0ee6b667f");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 71";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("151010a8ce7f45e5750764c22f91e910");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("be530b2ae8915b5b315f3544559bce");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3c4531679e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 72";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fec8fd5851735e5bdc13f47f3825899d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a35c6f70f637a9a5e6f215c694fdf6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("0f757a6a9c36f9");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 73";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("374002cd32e58ff7c1831675fea75402");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("df7b23a4e4456e0152b24853fe0d5d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("39ac6b851c0923");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 74";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fb795b08bc579bfdabdf0b642fef43bf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("f60f769cc761731264d092a70600fd");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("fd3c4a27d0b91b");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 75";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("73f73b23bfa7b0768a51732c49feec64");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("3881759dcf287ae14a2872541a7490");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("57e6517b9d9c02");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 76";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("1649f4977097349bda07b6347c15ecba");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("22941c1fb1d6c70686fbad9747a23c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("8561c2de5700be");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 77";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("40fd37f17cdc1cef8fa8ef199173646e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7fa99e979492ab59d57a2b6c19723d");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("585a9d0632b5fe");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 78";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3ebfb06db9c28c5b6e430b497a16e6f4");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("b620a30a7503dcf629b97e03651e42");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("c080401be14b3c");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 79";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("ecad022a6210b9a4fd43dfb66140b016");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8f997acd1eb8f31a501b2a9f8860cb");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("533a477a9ee423");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 80";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("bc4f6b8feae57c1ceceac79b1a1c433e");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1bcecf72c294895b060c942044f051f0");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("4fb02f9ac1");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 81";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e34f2f57fd6ddc765b1a94df04026bf7");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("443da4e76ddfa85dbe0813a87849447c");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("e854a92112");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 82";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("fe2c91c8628346b9150883c4d3524ab0");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cedf60b17185fc71b957cb75926039d1");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("a8e031ad01");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 83";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4c4c43e032ab2979f7160b6725294c7f");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("8db9a152f420d2c8b4bbb259b2e9f082");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("153dae5136");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 84";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("d03140e91fe976756458402f943d6779");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("1cde3ddeac605bd517707acc74d70b05");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("1890e97e35");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 85";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("7c10196e1a310dd5451fc12f10586291");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("9caa7d82a499d92ab491bb6c7bd66256");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("753268300e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 86";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("efdc0d767a25b34f7a13575b0e2507dc");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("15c5d008431b65c0f7b1d61c1fc43867");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("73307b3281");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 87";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("988545e329e5323815130bc8468fa20d");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("53ff2ff4d807987948f455f20b622672");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("3856942264");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 88";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("51fe7aad8f3254f198adba62e3315173");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("d36dc871beae4867b381f33afe9bfa69");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("40eab4135ffd68");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 89";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("674980314604790defcba7fda75145cb");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("a2d35d99ca3dbfd436dd70505bea1c17");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("25283d50ed44ec");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 90";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3bf81ff8294cf42fce40fb07e531c708");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("c6eac2e13df2a67fc27eeb3559dabf46");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("991b115966e997");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 91";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("5b3298154a9416dfec43941ac7fdd93b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("eb61c284fe009921039ef6a9ce50e702");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("50478569d11ada");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 92";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("3ba207bcec94615d838585e55d10ce7c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("006669ef1a11b65b1d78719c496b7825");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("cfee82be7da52e");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 93";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("e083b66e430d496e34a48f4f07ab54bf");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("934222a9cabaa5a0a91100b158a3aeb6");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b679cb63d478d8");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 94";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("91b37cfd8a9e5ea226d0a2a8519d97f8");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("08d0bddcb8a6c84df0a22e54777c9195");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("58156edc27f570");
	test_cases.push_back(tmp);

	tmp.test_name = "CVAS 11.0 TestVector 95";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("89fe91f1c1ef2f01efc4c18f5715894c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("e45bb06d3260123b316d101664c76a0b");
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("87ee7efaf38af8");
	test_cases.push_back(tmp);

}