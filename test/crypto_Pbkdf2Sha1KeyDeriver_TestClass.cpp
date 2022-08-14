#include "crypto_Pbkdf2Sha1KeyDeriver_TestClass.h"
#include "PbkdfUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Pbkdf2Sha1KeyDeriver.h>
#include <tc/cli/FormatUtil.h>

//---------------------------------------------------------

crypto_Pbkdf2Sha1KeyDeriver_TestClass::crypto_Pbkdf2Sha1KeyDeriver_TestClass() :
	mTestTag("tc::crypto::Pbkdf2Sha1KeyDeriver"),
	mTestResults()
{
}

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::runAllTests(void)
{
	test_Constants();
	test_ConfirmTestVector_Class();
	test_ConfirmTestVector_UtilFunc();
	test_WillThrowExceptionOnZeroRounds();
	test_WillThrowExceptionOnTooLargeDkSize();
	test_GetBytesWithoutInitDoesNothing();
}

const std::string& crypto_Pbkdf2Sha1KeyDeriver_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Pbkdf2Sha1KeyDeriver_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check max derivable size
		static const uint64_t kExpectedMaxDerivableSize = uint64_t(0xffffffff) *  uint64_t(tc::crypto::Sha1Generator::kHashSize);
		if (tc::crypto::Pbkdf2Sha1KeyDeriver::kMaxDerivableSize != kExpectedMaxDerivableSize)
		{
			throw tc::TestException(fmt::format("kMaxDerivableSize had value {:d}  (expected {:d})", tc::crypto::Pbkdf2Sha1KeyDeriver::kMaxDerivableSize, kExpectedMaxDerivableSize));
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

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_ConfirmTestVector_Class()
{
	TestResult test_result;
	test_result.test_name = "test_ConfirmTestVector_Class";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf2TestVectors_RFC6070(tests, PbkdfUtil::SHA1);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		tc::crypto::Pbkdf2Sha1KeyDeriver keydev;

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

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_ConfirmTestVector_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_ConfirmTestVector_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf2TestVectors_RFC6070(tests, PbkdfUtil::SHA1);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}



		for (auto test = tests.begin(); test != tests.end(); test++)
		{				
			auto dk = tc::ByteData(test->in_dk_len);

			tc::crypto::DeriveKeyPbkdf2Sha1(dk.data(), dk.size(), (const byte_t*)test->in_password.c_str(), test->in_password.size(), (const byte_t*)test->in_salt.c_str(), test->in_salt.size(), test->in_rounds);

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

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_WillThrowExceptionOnZeroRounds()
{
	TestResult test_result;
	test_result.test_name = "test_WillThrowExceptionOnZeroRounds";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf2TestVectors_RFC6070(tests, PbkdfUtil::SHA1);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		auto dk = tc::ByteData(tests[0].in_dk_len);

		try 
		{
			tc::crypto::DeriveKeyPbkdf2Sha1(dk.data(), dk.size(), (const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), 0);

			throw tc::TestException("DeriveKeyPbkdf2Sha1() Did not throw tc::crypto::CryptoException where the round count was set to zero.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("DeriveKeyPbkdf2Sha1() Threw the wrong exception where the round count was set to zero.");
		}

		try 
		{
			tc::crypto::Pbkdf2Sha1KeyDeriver keydev;

			keydev.initialize((const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), 0);

			throw tc::TestException("Pbkdf2Sha1KeyDeriver::initialize() Did not throw exception where the round count was set to zero.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Pbkdf2Sha1KeyDeriver::initialize() Threw the wrong exception where the round count was set to zero.");
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

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_WillThrowExceptionOnTooLargeDkSize()
{
	TestResult test_result;
	test_result.test_name = "test_WillThrowExceptionOnTooLargeDkSize";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		if (std::numeric_limits<size_t>::max() < std::numeric_limits<uint64_t>::max())
		{
			test_result.result = "SKIP";
			test_result.comments = "This test is only valid in environments where size_t is 64bit";
		}

		// create tests		
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf2TestVectors_RFC6070(tests, PbkdfUtil::SHA1);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}

		try 
		{
			// nullptr because we expect this to fail outright and allocating kMaxDerivableSize+1 is too large
			tc::crypto::DeriveKeyPbkdf2Sha1(nullptr, tc::crypto::Pbkdf2Sha1KeyDeriver::kMaxDerivableSize + 1, (const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), tests[0].in_rounds);

			throw tc::TestException("DeriveKeyPbkdf2Sha1() Did not throw tc::crypto::CryptoException where the derived data length would exceed the maximum.");
		}
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("DeriveKeyPbkdf2Sha1() Threw the wrong exception where the derived data length would exceed the maximum.");
		}	
		

		try 
		{
			tc::crypto::Pbkdf2Sha1KeyDeriver keydev;

			keydev.initialize((const byte_t*)tests[0].in_password.c_str(), tests[0].in_password.size(), (const byte_t*)tests[0].in_salt.c_str(), tests[0].in_salt.size(), tests[0].in_rounds);
			
			// nullptr because we expect this to fail outright and allocating kMaxDerivableSize+1 is too large
			keydev.getBytes(nullptr, tc::crypto::Pbkdf2Sha1KeyDeriver::kMaxDerivableSize + 1);

			throw tc::TestException("Pbkdf2Sha1KeyDeriver::getBytes() Did not throw tc::crypto::CryptoException where the derived data length would exceed the maximum.");
		} 
		catch (const tc::crypto::CryptoException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Pbkdf2Sha1KeyDeriver::getBytes() Threw the wrong exception where the derived data length would exceed the maximum.");
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

void crypto_Pbkdf2Sha1KeyDeriver_TestClass::test_GetBytesWithoutInitDoesNothing()
{
	TestResult test_result;
	test_result.test_name = "test_GetBytesWithoutInitDoesNothing";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<PbkdfUtil::TestVector> tests;
		PbkdfUtil::generatePbkdf2TestVectors_RFC6070(tests, PbkdfUtil::SHA1);
		if (tests.empty())
		{
			throw tc::TestException("No test vectors");
		}


		auto dk = tc::ByteData(tests[0].in_dk_len);
		memset(dk.data(), 0xab, dk.size());

		tc::crypto::Pbkdf2Sha1KeyDeriver keydev;
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