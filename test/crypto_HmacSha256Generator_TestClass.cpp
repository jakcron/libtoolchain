#include "crypto_HmacSha256Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/HmacSha256Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_HmacSha256Generator_TestClass::crypto_HmacSha256Generator_TestClass() :
	mTestTag("tc::crypto::HmacSha256Generator"),
	mTestResults()
{
}

void crypto_HmacSha256Generator_TestClass::runAllTests(void)
{
	test_Constants();
	test_SingleUpdateCall();
	test_MultiUpdateCall();
	test_UtilFunc();

	test_NoInitNoUpdateDoMac();
	test_NoInitDoUpdateDoMac();
	test_DoInitNoUpdateDoMac();
	test_DoInitNoKeyDoUpdateDoMac();
	test_DoInitNoKeyNoUpdateDoMac();

	test_CallGetMacRepeatedly();
}

const std::string& crypto_HmacSha256Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_HmacSha256Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_HmacSha256Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check mac size
		static const size_t kExpectedMacSize = 32;
		if (tc::crypto::HmacSha256Generator::kMacSize != kExpectedMacSize)
		{				
			throw tc::TestException(fmt::format("kMacSize had value {:d} (expected {:d})", tc::crypto::HmacSha256Generator::kMacSize, kExpectedMacSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 64;
		if (tc::crypto::HmacSha256Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::HmacSha256Generator::kBlockSize, kExpectedBlockSize));
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

void crypto_HmacSha256Generator_TestClass::test_SingleUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_SingleUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_MultiUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_MultiUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);

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
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(mac.data(), 0xff, mac.size());
			tc::crypto::GenerateHmacSha256Mac(mac.data(), test_case->in_data.data(), test_case->in_data.size(), test_case->in_key.data(), test_case->in_key.size());
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_NoInitNoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitNoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);
		tc::ByteData expected_uninitialized_mac = tc::ByteData(mac.size());
		memset(expected_uninitialized_mac.data(), 0xff, expected_uninitialized_mac.size());

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			//calc.update(test_case->in_data.data(), test_case->in_data.size());
			memcpy(mac.data(), expected_uninitialized_mac.data(), mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), expected_uninitialized_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_NoInitDoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitDoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);
		tc::ByteData expected_uninitialized_mac = tc::ByteData(mac.size());
		memset(expected_uninitialized_mac.data(), 0xff, expected_uninitialized_mac.size());

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			memcpy(mac.data(), expected_uninitialized_mac.data(), mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), expected_uninitialized_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_DoInitNoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_DoInitNoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);

		// override expected MAC for when no update() is called
		test_cases[0].out_mac = tc::cli::FormatUtil::hexStringToBytes("999A901219F032CD497CADB5E6051E97B6A29AB297BD6AE722BD6062A2F59542");
		test_cases[1].out_mac = tc::cli::FormatUtil::hexStringToBytes("923598CA6D64AF2A5DBA79DCD021A8A0FE5C5F557519ADAAF0AD532D4506DD30");
		test_cases[2].out_mac = tc::cli::FormatUtil::hexStringToBytes("86E54FD448725D7E5DCFE22353C828AF48781EB48CAE8106A7E1D498949F3E46");
		test_cases[3].out_mac = tc::cli::FormatUtil::hexStringToBytes("1B5713E10977DA96A5FE201005976A240544079C2724F6A9EAEAE42B9DE00F28");
		test_cases[4].out_mac = tc::cli::FormatUtil::hexStringToBytes("4D36C675D91E0512D1B1BA412FE2F7D8A6595FD305BDEADF651B465D4251781F");
		test_cases[5].out_mac = tc::cli::FormatUtil::hexStringToBytes("44B545DEF5B97EB719D856A15E327833E520E4770619C0E3EEFBDE24B71285A7");
		test_cases[6].out_mac = tc::cli::FormatUtil::hexStringToBytes("44B545DEF5B97EB719D856A15E327833E520E4770619C0E3EEFBDE24B71285A7");

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			//calc.update(test_case->in_data.data(), test_case->in_data.size());
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_DoInitNoKeyDoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_DoInitNoKeyDoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);
	
		// override expected MAC for when no key is used during initialize()
		test_cases[0].in_key = tc::ByteData();
		test_cases[0].out_mac = tc::cli::FormatUtil::hexStringToBytes("E48411262715C8370CD5E7BF8E82BEF53BD53712D007F3429351843B77C7BB9B");
		test_cases[1].in_key = tc::ByteData();
		test_cases[1].out_mac = tc::cli::FormatUtil::hexStringToBytes("76D9E7194E7DBC3AA00BBE8FFB9F6FCB5A932170F971F948BB2AB61607D2B9D6");
		test_cases[2].in_key = tc::ByteData();
		test_cases[2].out_mac = tc::cli::FormatUtil::hexStringToBytes("658C192B47D1C84BC7D5EE38CAA75864FBF43E79BD18DB6C5FA814ED0D9C4AB3");
		test_cases[3].in_key = tc::ByteData();
		test_cases[3].out_mac = tc::cli::FormatUtil::hexStringToBytes("367352007EE6CA9FA755CE8352347D092C17A24077FD33C62F655574A8CF906D");
		test_cases[4].in_key = tc::ByteData();
		test_cases[4].out_mac = tc::cli::FormatUtil::hexStringToBytes("53273BDCBDF6DE9AFB0CDBD1E1CF133FE7529237B5A1FBA41F34CC8792430B16");
		test_cases[5].in_key = tc::ByteData();
		test_cases[5].out_mac = tc::cli::FormatUtil::hexStringToBytes("79E2A6536CB16B4A1E9C2AF81759764AFD026173526F79F7816E9A3BC5FBABA8");
		test_cases[6].in_key = tc::ByteData();
		test_cases[6].out_mac = tc::cli::FormatUtil::hexStringToBytes("4DA63281EA396C9E8FBFE3D6483A602CE18760273914D9DF5FF385FB639A696F");

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_DoInitNoKeyNoUpdateDoMac()
{
	TestResult test_result;
	test_result.test_name = "test_DoInitNoKeyNoUpdateDoMac";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);
	
		// override expected MAC for when no key is used during initialize() and update is not called
		test_cases[0].in_key = tc::ByteData();
		test_cases[0].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[1].in_key = tc::ByteData();
		test_cases[1].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[2].in_key = tc::ByteData();
		test_cases[2].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[3].in_key = tc::ByteData();
		test_cases[3].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[4].in_key = tc::ByteData();
		test_cases[4].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[5].in_key = tc::ByteData();
		test_cases[5].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");
		test_cases[6].in_key = tc::ByteData();
		test_cases[6].out_mac = tc::cli::FormatUtil::hexStringToBytes("B613679A0814D9EC772F95D778C35FC5FF1697C493715653C6C712144292C5AD");

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			//calc.update(test_case->in_data.data(), test_case->in_data.size());
			memset(mac.data(), 0xff, mac.size());
			calc.getMac(mac.data());
			if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::test_CallGetMacRepeatedly()
{
	TestResult test_result;
	test_result.test_name = "test_CallGetMacRepeatedly";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TestCase> test_cases;
		util_Setup_Rfc2202_TestCases(test_cases);

		tc::crypto::HmacSha256Generator calc;
		tc::ByteData mac = tc::ByteData(tc::crypto::HmacSha256Generator::kMacSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize(test_case->in_key.data(), test_case->in_key.size());
			calc.update(test_case->in_data.data(), test_case->in_data.size());
			for (size_t i = 0; i < 100; i++)
			{
				// by resetting the mac here we can tell if it is updated each time
				memset(mac.data(), 0xff, mac.size());
				calc.getMac(mac.data());
				if (memcmp(mac.data(), test_case->out_mac.data(), mac.size()) != 0)
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

void crypto_HmacSha256Generator_TestClass::util_Setup_Rfc2202_TestCases(std::vector<crypto_HmacSha256Generator_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	tmp.test_name = "RFC 2202 Test 1";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("4869205468657265"); // "Hi There"
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 2";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("4a656665"); // "Jefe"
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("7768617420646f2079612077616e7420666f72206e6f7468696e673f"); // "what do ya want for nothing?"
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 3";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"); // 50 x 0xdd
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 4";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0102030405060708090a0b0c0d0e0f10111213141516171819");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd"); // 50 x 0xcd
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("82558a389a443c0ea4cc819899f2083a85f0faa3e578f8077a2e3ff46729665b");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 5";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c0c");
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("546573742057697468205472756e636174696f6e"); // "Test With Truncation"
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("A3B6167473100EE06E0C796C2955552BFA6F7C0A6A8AEF8B93F860AAB0CD20C5");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 6";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); // 131 x 0xaa
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("54657374205573696e67204c6172676572205468616e20426c6f636b2d53697a65204b6579202d2048617368204b6579204669727374"); // "Test Using Larger Than Block-Size Key - Hash Key First"
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54");
	test_cases.push_back(tmp);

	tmp.test_name = "RFC 2202 Test 7";
	tmp.in_key = tc::cli::FormatUtil::hexStringToBytes("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); // 131 x 0xaa
	tmp.in_data = tc::cli::FormatUtil::hexStringToBytes("5468697320697320612074657374207573696e672061206c6172676572207468616e20626c6f636b2d73697a65206b657920616e642061206c6172676572207468616e20626c6f636b2d73697a6520646174612e20546865206b6579206e6565647320746f20626520686173686564206265666f7265206265696e6720757365642062792074686520484d414320616c676f726974686d2e"); // "This is a test using a larger than block-size key and a larger than block-size data. The key neds to be hashed before being used by the HMAC algorithm."
	tmp.out_mac = tc::cli::FormatUtil::hexStringToBytes("9b09ffa71b942fcb27635fbcd5b0e944bfdc63644f0713938a7f51535c3a35e2");
	test_cases.push_back(tmp);
}