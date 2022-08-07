#include "crypto_Sha512Generator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/Sha512Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_Sha512Generator_TestClass::crypto_Sha512Generator_TestClass() :
	mTestTag("tc::crypto::Sha512Generator"),
	mTestResults()
{
}

void crypto_Sha512Generator_TestClass::runAllTests(void)
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

const std::string& crypto_Sha512Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Sha512Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Sha512Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check hash size
		static const size_t kExpectedHashSize = 64;
		if (tc::crypto::Sha512Generator::kHashSize != kExpectedHashSize)
		{				
			throw tc::TestException(fmt::format("kHashSize had value {:d} (expected {:d})", tc::crypto::Sha512Generator::kHashSize, kExpectedHashSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 128;
		if (tc::crypto::Sha512Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Sha512Generator::kBlockSize, kExpectedBlockSize));
		}

		// check ASN.1 OID data
		static size_t kAsn1OidDataSize = tc::crypto::Sha512Generator::kAsn1OidDataSize;
		tc::ByteData kExpectedAsn1OidData = tc::cli::FormatUtil::hexStringToBytes("3051300D060960864801650304020305000440");
		if (kAsn1OidDataSize != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidDataSize had value {:d} (expected {:d})", kAsn1OidDataSize, kExpectedAsn1OidData.size()));
		}
		if (tc::crypto::Sha512Generator::kAsn1OidData.size() != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidData.size() had value {:d} (expected {:d})", tc::crypto::Sha512Generator::kAsn1OidData.size(), kExpectedAsn1OidData.size()));
		}
		if (memcmp(tc::crypto::Sha512Generator::kAsn1OidData.data(), kExpectedAsn1OidData.data(), kExpectedAsn1OidData.size()) != 0)
		{
			throw tc::TestException(fmt::format("kAsn1OidData.data() had data {:s} (expected {:s})", tc::cli::FormatUtil::formatBytesAsString(tc::crypto::Sha512Generator::kAsn1OidData.data(), tc::crypto::Sha512Generator::kAsn1OidData.size(), true, ""), tc::cli::FormatUtil::formatBytesAsString(kExpectedAsn1OidData, true, "")));
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

void crypto_Sha512Generator_TestClass::test_SingleUpdateCall()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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

void crypto_Sha512Generator_TestClass::test_MultiUpdateCall()
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
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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

void crypto_Sha512Generator_TestClass::test_UtilFunc()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909")},
		};

		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(hash.data(), 0xff, hash.size());
			tc::crypto::GenerateSha512Hash(hash.data(), (const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
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

void crypto_Sha512Generator_TestClass::test_NoInitNoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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

void crypto_Sha512Generator_TestClass::test_NoInitDoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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

void crypto_Sha512Generator_TestClass::test_DoInitNoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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

void crypto_Sha512Generator_TestClass::test_CallGetHashRepeatedly()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F")},
			{ "long string" ,"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", tc::cli::FormatUtil::hexStringToBytes("8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909")},
		};

		tc::crypto::Sha512Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha512Generator::kHashSize);

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