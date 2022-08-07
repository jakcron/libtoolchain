#include "crypto_Sha1Generator_TestClass.h"

#include <fmt/format.h>
#include <iostream>

#include <tc/Exception.h>
#include <tc/crypto/Sha1Generator.h>
#include <tc/cli/FormatUtil.h>
#include <tc/ByteData.h>

//---------------------------------------------------------

crypto_Sha1Generator_TestClass::crypto_Sha1Generator_TestClass() :
	mTestTag("tc::crypto::Sha1Generator"),
	mTestResults()
{
}

void crypto_Sha1Generator_TestClass::runAllTests(void)
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

const std::string& crypto_Sha1Generator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Sha1Generator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Sha1Generator_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check hash size
		static const size_t kExpectedHashSize = 20;
		if (tc::crypto::Sha1Generator::kHashSize != kExpectedHashSize)
		{				
			throw tc::TestException(fmt::format("kHashSize had value {:d} (expected {:d})", tc::crypto::Sha1Generator::kHashSize, kExpectedHashSize));
		}

		// check block size
		static const size_t kExpectedBlockSize = 64;
		if (tc::crypto::Sha1Generator::kBlockSize != kExpectedBlockSize)
		{				
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Sha1Generator::kBlockSize, kExpectedBlockSize));
		}

		// check ASN.1 OID data
		static size_t kAsn1OidDataSize = tc::crypto::Sha1Generator::kAsn1OidDataSize;
		tc::ByteData kExpectedAsn1OidData = tc::cli::FormatUtil::hexStringToBytes("3021300906052B0E03021A05000414");
		if (kAsn1OidDataSize != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidDataSize had value {:d} (expected {:d})", kAsn1OidDataSize, kExpectedAsn1OidData.size()));
		}
		if (tc::crypto::Sha1Generator::kAsn1OidData.size() != kExpectedAsn1OidData.size())
		{				
			throw tc::TestException(fmt::format("kAsn1OidData.size() had value {:d} (expected {:d})", tc::crypto::Sha1Generator::kAsn1OidData.size(), kExpectedAsn1OidData.size()));
		}
		if (memcmp(tc::crypto::Sha1Generator::kAsn1OidData.data(), kExpectedAsn1OidData.data(), kExpectedAsn1OidData.size()) != 0)
		{
			throw tc::TestException(fmt::format("kAsn1OidData.data() had data {:s} (expected {:s})", tc::cli::FormatUtil::formatBytesAsString(tc::crypto::Sha1Generator::kAsn1OidData.data(), tc::crypto::Sha1Generator::kAsn1OidData.size(), true, ""), tc::cli::FormatUtil::formatBytesAsString(kExpectedAsn1OidData, true, "")));
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

void crypto_Sha1Generator_TestClass::test_SingleUpdateCall()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("A9993E364706816ABA3E25717850C26C9CD0D89D")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("84983E441C3BD26EBAAE4AA1F95129E5E54670F1")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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

void crypto_Sha1Generator_TestClass::test_MultiUpdateCall()
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
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("A9993E364706816ABA3E25717850C26C9CD0D89D")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("84983E441C3BD26EBAAE4AA1F95129E5E54670F1")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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

void crypto_Sha1Generator_TestClass::test_UtilFunc()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("A9993E364706816ABA3E25717850C26C9CD0D89D")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("84983E441C3BD26EBAAE4AA1F95129E5E54670F1")},
		};

		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

		for (auto test_case = test_cases.begin(); test_case != test_cases.end(); test_case++)
		{
			memset(hash.data(), 0xff, hash.size());
			tc::crypto::GenerateSha1Hash(hash.data(), (const byte_t*)test_case->in_string.c_str(), test_case->in_string.size());
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

void crypto_Sha1Generator_TestClass::test_NoInitNoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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

void crypto_Sha1Generator_TestClass::test_NoInitDoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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

void crypto_Sha1Generator_TestClass::test_DoInitNoUpdateDoHash()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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

void crypto_Sha1Generator_TestClass::test_CallGetHashRepeatedly()
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
			{ "empty string", "", tc::cli::FormatUtil::hexStringToBytes("DA39A3EE5E6B4B0D3255BFEF95601890AFD80709")},
			{ "short string", "abc", tc::cli::FormatUtil::hexStringToBytes("A9993E364706816ABA3E25717850C26C9CD0D89D")},
			{ "long string" ,"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", tc::cli::FormatUtil::hexStringToBytes("84983E441C3BD26EBAAE4AA1F95129E5E54670F1")},
		};

		tc::crypto::Sha1Generator calc;
		tc::ByteData hash = tc::ByteData(tc::crypto::Sha1Generator::kHashSize);

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