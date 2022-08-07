#include "crypto_Md5Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/Md5Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_Md5Generator_TestClass::crypto_Md5Generator_TestClass() :
	mTestTag("tc::crypto::Md5Generator"),
	mTestResults()
{
}

void crypto_Md5Generator_TestClass::runAllTests(void)
{
	test_Constants();
	test_SingleUpdateCall();
	test_MultiUpdateCall();
	test_UtilFunc();

	test_NoInitNoUpdateDoHash();
	test_NoInitDoUpdateDoHash();
	test_DoInitNoUpdateDoHash();

	test_CallGetHashRepeatedly();
}

const std::string& crypto_Md5Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Md5Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Md5Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check hash size
		static const size_t kExpectedHashSize = 16;
		if (tc::crypto::Md5Generator::kHashSize != kExpectedHashSize)
		{				
			throw tc::TestException(fmt::format("kHashSize had value {:d} (expected {:d})", tc::crypto::Md5Generator::kHashSize, kExpectedHashSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 64;
		if (tc::crypto::Md5Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Md5Generator::kBlockSize, kExpectedBlockSize));
		}

		// check ASN.1 OID data
		static size_t kAsn1OidDataSize = tc::crypto::Md5Generator::kAsn1OidDataSize;
		tc::ByteData kExpectedAsn1OidData = tc::cli::FormatUtil::hexStringToBytes("3020300C06082A864886F70D020505000410");
		if (kAsn1OidDataSize != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidDataSize had value {:d} (expected {:d})", kAsn1OidDataSize, kExpectedAsn1OidData.size()));
		}
		if (tc::crypto::Md5Generator::kAsn1OidData.size() != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidData.size() had value {:d} (expected {:d})", tc::crypto::Md5Generator::kAsn1OidData.size(), kExpectedAsn1OidData.size()));
		}
		if (memcmp(tc::crypto::Md5Generator::kAsn1OidData.data(), kExpectedAsn1OidData.data(), kExpectedAsn1OidData.size()) != 0)
		{
			throw tc::TestException(fmt::format("kAsn1OidData.data() had data {:s} (expected {:s})", tc::cli::FormatUtil::formatBytesAsString(tc::crypto::Md5Generator::kAsn1OidData.data(), tc::crypto::Md5Generator::kAsn1OidData.size(), true, ""), tc::cli::FormatUtil::formatBytesAsString(kExpectedAsn1OidData, true, "")));
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

void crypto_Md5Generator_TestClass::test_SingleUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_SingleUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("0CC175B9C0F1B6A831C399E269772661")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("900150983CD24FB0D6963F7D28E17F72")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("F96B697D7CB7938D525A2F31AAF161D0")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("C3FCD3D76192E4007DFB496CCA67E13B")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("D174AB98D277D9F5A5611C2C9F419D9F")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("57EDF4A22BE3C955AC49DA2E2107B67A")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize();
			calc.update((const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			memset(hash.data(), 0xff, hash.size());
			calc.getHash(hash.data());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{					
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_MultiUpdateCall()
{
	TestResult test_result;
	test_result.test_name = "test_MultiUpdateCall";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests
		std::vector<TestCase> test_cases = 
		{
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("0CC175B9C0F1B6A831C399E269772661")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("900150983CD24FB0D6963F7D28E17F72")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("F96B697D7CB7938D525A2F31AAF161D0")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("C3FCD3D76192E4007DFB496CCA67E13B")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("D174AB98D277D9F5A5611C2C9F419D9F")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("57EDF4A22BE3C955AC49DA2E2107B67A")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize();

			// pick an offset to split the in_string at
			size_t offset = test_case->in_string.size() / 2;

			// update with first half
			calc.update((const byte_t*)test_case->in_string.c_str(), offset);

			// update with second half
			calc.update((const byte_t*)test_case->in_string.c_str() + offset, test_case->in_string.size() - offset);
			
			memset(hash.data(), 0xff, hash.size());
			calc.getHash(hash.data());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("0CC175B9C0F1B6A831C399E269772661")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("900150983CD24FB0D6963F7D28E17F72")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("F96B697D7CB7938D525A2F31AAF161D0")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("C3FCD3D76192E4007DFB496CCA67E13B")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("D174AB98D277D9F5A5611C2C9F419D9F")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("57EDF4A22BE3C955AC49DA2E2107B67A")},
		};

		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(hash.data(), 0xff, hash.size());
			tc::crypto::GenerateMd5Hash(hash.data(), (const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_NoInitNoUpdateDoHash()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitNoUpdateDoHash";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests (when not initalized getHash() should not populate the hash buffer, and so the hash buffer should remain as what we set it)
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize();
			//calc.update((const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			memset(hash.data(), 0xff, hash.size());
			calc.getHash(hash.data());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_NoInitDoUpdateDoHash()
{
	TestResult test_result;
	test_result.test_name = "test_NoInitDoUpdateDoHash";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests (when not initalized getHash() should not populate the hash buffer, and so the hash buffer should remain as what we set it)
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			//calc.initialize();
			calc.update((const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			memset(hash.data(), 0xff, hash.size());
			calc.getHash(hash.data());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_DoInitNoUpdateDoHash()
{
	TestResult test_result;
	test_result.test_name = "test_DoInitNoUpdateDoHash";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests (.getHash() should return the hash for an empty string if update is not called since they are logically the same thing)
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize();
			//calc.update((const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			memset(hash.data(), 0xff, hash.size());
			calc.getHash(hash.data());
			if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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

void crypto_Md5Generator_TestClass::test_CallGetHashRepeatedly()
{
	TestResult test_result;
	test_result.test_name = "test_CallGetHashRepeatedly";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		struct TestCase
		{
			std::string test_name;
			std::string in_string;
			tc::ByteData out_hash;
		};

		// create tests
		std::vector<TestCase> test_cases = 
		{
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("D41D8CD98F00B204E9800998ECF8427E")},
			{ "short string (\"a\")", "a", tc::cli::FormatUtil::hexStringToBytes("0CC175B9C0F1B6A831C399E269772661")},
			{ "short string (\"abc\")", "abc", tc::cli::FormatUtil::hexStringToBytes("900150983CD24FB0D6963F7D28E17F72")},
			{ "long string (\"message digest\")", "message digest", tc::cli::FormatUtil::hexStringToBytes("F96B697D7CB7938D525A2F31AAF161D0")},
			{ "long string (alphabet)", "abcdefghijklmnopqrstuvwxyz", tc::cli::FormatUtil::hexStringToBytes("C3FCD3D76192E4007DFB496CCA67E13B")},
			{ "long string (alphanum)", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", tc::cli::FormatUtil::hexStringToBytes("D174AB98D277D9F5A5611C2C9F419D9F")},
			{ "long string (numerals)", "12345678901234567890123456789012345678901234567890123456789012345678901234567890", tc::cli::FormatUtil::hexStringToBytes("57EDF4A22BE3C955AC49DA2E2107B67A")},
		};

		tc::crypto::Md5Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Md5Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			calc.initialize();
			calc.update((const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
			for (size_t i = 0; i < 100; i++)
			{
				// by resetting the hash here we can tell if it is updated each time
				memset(hash.data(), 0xff, hash.size());
				calc.getHash(hash.data());
				if (memcmp(hash.data(), test_case->out_hash.data(), hash.size()) != 0)
				{
					throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong hash value: {:s} (expected {:s})", test_case->test_name, tc::cli::FormatUtil::formatBytesAsString(hash, true, ""), tc::cli::FormatUtil::formatBytesAsString(test_case->out_hash, true, "")));
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