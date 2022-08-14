#include "crypto_Pbkdf1Md5KeyDeriver_TestClass.h"
#include "PbkdfUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Pbkdf1Md5KeyDeriver.h>
#include <tc/cli/FormatUtil.h>

//---------------------------------------------------------

crypto_Pbkdf1Md5KeyDeriver_TestClass::crypto_Pbkdf1Md5KeyDeriver_TestClass() :
	mTestTag("tc::crypto::Pbkdf1Md5KeyDeriver"),
	mTestResults()
{
}

void crypto_Pbkdf1Md5KeyDeriver_TestClass::runAllTests(void)
{
	test_Constants();
	test_ConfirmTestVector_Class();
	test_ConfirmTestVector_UtilFunc();
	test_WillThrowExceptionOnZeroRounds();
	test_WillThrowExceptionOnTooLargeDkSize();
	test_GetBytesWithoutInitDoesNothing();
}

const std::string& crypto_Pbkdf1Md5KeyDeriver_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Pbkdf1Md5KeyDeriver_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check max derivable size
		static const uint64_t kExpectedMaxDerivableSize = tc::crypto::Md5Generator::kHashSize;
		if (tc::crypto::Pbkdf1Md5KeyDeriver::kMaxDerivableSize != kExpectedMaxDerivableSize)
		{
			throw tc::TestException(fmt::format("kMaxDerivableSize had value {:d}  (expected {:d})", tc::crypto::Pbkdf1Md5KeyDeriver::kMaxDerivableSize, kExpectedMaxDerivableSize));
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

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_ConfirmTestVector_Class()
{
	TestResult test_result;
	test_result.test_name = "test_ConfirmTestVector_Class";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf1TestVectors_Custom(tests, PbkdfUtil::MD5);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		tc::crypto::Pbkdf1Md5KeyDeriver keydev;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{	
			keydev.initialize((const byte_t*)test->in_password.c_str(), test->in_password.size(), (const byte_t*)test->in_salt.c_str(), test->in_salt.size(), test->in_rounds);
			
			auto dk = tc::ByteData(test->in_dk_len);
			keydev.getBytes(dk.data(), dk.size());

			if (memcmp(dk.data(), test->out_dk.data(), dk.size()) != 0)
			{					
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong DK: {:s} (expected {:s})", tc::cli::FormatUtil::formatBytesAsString(dk, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->out_dk, true, "")));
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

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_ConfirmTestVector_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_ConfirmTestVector_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf1TestVectors_Custom(tests, PbkdfUtil::MD5);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}



		for (auto test = tests.begin(); test != tests.end(); test++)
		{				
			auto dk = tc::ByteData(test->in_dk_len);

			tc::crypto::DeriveKeyPbkdf1Md5(dk.data(), dk.size(), (const byte_t*)test->in_password.c_str(), test->in_password.size(), (const byte_t*)test->in_salt.c_str(), test->in_salt.size(), test->in_rounds);

			if (memcmp(dk.data(), test->out_dk.data(), dk.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed. Had wrong DK: {:s} (expected {:s})", tc::cli::FormatUtil::formatBytesAsString(dk, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->out_dk, true, "")));
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

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_WillThrowExceptionOnZeroRounds()
{
	TestResult test_result;
	test_result.test_name = "test_WillThrowExceptionOnZeroRounds";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf1TestVectors_Custom(tests, PbkdfUtil::MD5);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		auto dk = tc::ByteData(tests[0].in_dk_len);

		try 
		{
			tc::crypto::DeriveKeyPbkdf1Md5(dk.data(), dk.size(), (const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), 0);

			throw tc::TestException("DeriveKeyPbkdf1Md5() Did not throw tc::crypto::CryptoException where the round count was set to zero.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("DeriveKeyPbkdf1Md5() Threw the wrong exception where the round count was set to zero.");
		}

		try 
		{
			tc::crypto::Pbkdf1Md5KeyDeriver keydev;

			keydev.initialize((const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), 0);

			throw tc::TestException("Pbkdf1Md5KeyDeriver::initialize() Did not throw exception where the round count was set to zero.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Pbkdf1Md5KeyDeriver::initialize() Threw the wrong exception where the round count was set to zero.");
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

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_WillThrowExceptionOnTooLargeDkSize()
{
	TestResult test_result;
	test_result.test_name = "test_WillThrowExceptionOnTooLargeDkSize";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		if (sizeof(size_t) != 4 && sizeof(size_t) != 8)
		{
			throw tc::TestException("This test can only run on systems where size_t is 32bit or 64bit");
		}

		// create tests		
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf1TestVectors_Custom(tests, PbkdfUtil::MD5);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}

		// derive a small key
		auto dk = tc::ByteData(tc::crypto::Pbkdf1Md5KeyDeriver::kMaxDerivableSize + 1);

		try 
		{
			tc::crypto::DeriveKeyPbkdf1Md5(dk.data(), dk.size(), (const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), tests[0].in_rounds);

			throw tc::TestException("DeriveKeyPbkdf1Md5() Did not throw tc::crypto::CryptoException where the derived data length would exceed the maximum.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("DeriveKeyPbkdf1Md5() Threw the wrong exception where the derived data length would exceed the maximum.");
		}	
		

		try 
		{
			tc::crypto::Pbkdf1Md5KeyDeriver keydev;

			keydev.initialize((const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), tests[0].in_rounds);
			keydev.getBytes(dk.data(), dk.size());

			throw tc::TestException("Pbkdf1Md5KeyDeriver::getBytes() Did not throw tc::crypto::CryptoException where the derived data length would exceed the maximum.");
		} 
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Pbkdf1Md5KeyDeriver::getBytes() Threw the wrong exception where the derived data length would exceed the maximum.");
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

void crypto_Pbkdf1Md5KeyDeriver_TestClass::test_GetBytesWithoutInitDoesNothing()
{
	TestResult test_result;
	test_result.test_name = "test_GetBytesWithoutInitDoesNothing";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf1TestVectors_Custom(tests, PbkdfUtil::MD5);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		auto dk = tc::ByteData(tests[0].in_dk_len);
		memset(dk.data(), 0xab, dk.size());

		tc::crypto::Pbkdf1Md5KeyDeriver keydev;
		keydev.getBytes(dk.data(), dk.size());

		byte_t cmp = 1;
		for (size_t i = 0; i < dk.size(); i++)
		{
			cmp &= dk[i] == 0xab;
		}

		if (cmp != 1)
		{
			throw tc::TestException("getBytes() operated inspite of not being initialized.");
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