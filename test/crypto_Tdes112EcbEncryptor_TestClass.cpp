#include "crypto_Tdes112EcbEncryptor_TestClass.h"
#include "TdesDesEcbEncryptorUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Tdes112EcbEncryptor.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

crypto_Tdes112EcbEncryptor_TestClass::crypto_Tdes112EcbEncryptor_TestClass() :
	mTestTag("tc::crypto::Tdes112EcbEncryptor"),
	mTestResults()
{
}

void crypto_Tdes112EcbEncryptor_TestClass::runAllTests(void)
{
	test_Constants();
	test_UseClassEnc();
	test_UseClassDec();
	test_UseUtilFuncEnc();
	test_UseUtilFuncDec();

	test_DoesNothingWhenNotInit();
	test_InitializeThrowsExceptionOnBadInput();
	test_EncryptThrowsExceptionOnBadInput();
	test_DecryptThrowsExceptionOnBadInput();
}

const std::string& crypto_Tdes112EcbEncryptor_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Tdes112EcbEncryptor_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Tdes112EcbEncryptor_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 8;
		if (tc::crypto::Tdes112EcbEncryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Tdes112EcbEncryptor::kBlockSize, kExpectedBlockSize));
		}

		// check key size
		static const size_t kExpectedKeySize = 16;
		if (tc::crypto::Tdes112EcbEncryptor::kKeySize != kExpectedKeySize)
		{
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", tc::crypto::Tdes112EcbEncryptor::kKeySize, kExpectedKeySize));
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

void crypto_Tdes112EcbEncryptor_TestClass::test_UseClassEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size());
			
			// encrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				cryptor.encrypt(data.data(), data.data(), data.size());
			}
			
			// validate cipher text
			if (memcmp(data.data(), test->enc_data.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->enc_data, true, "")));
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

void crypto_Tdes112EcbEncryptor_TestClass::test_UseClassDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size());
			
			// decrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				cryptor.decrypt(data.data(), data.data(), data.size());
			}

			// test plain text
			if (memcmp(data.data(), test->dec_data.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->dec_data, true, "")));
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

void crypto_Tdes112EcbEncryptor_TestClass::test_UseUtilFuncEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);

			// encrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				tc::crypto::EncryptTdes112Ecb(data.data(), data.data(), data.size(), test->key.data(), test->key.size());
			}
			
			// validate cipher text
			if (memcmp(data.data(), test->enc_data.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->enc_data, true, "")));
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

void crypto_Tdes112EcbEncryptor_TestClass::test_UseUtilFuncDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);

			// decrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				tc::crypto::DecryptTdes112Ecb(data.data(), data.data(), data.size(), test->key.data(), test->key.size());
			}

			// test plain text
			if (memcmp(data.data(), test->dec_data.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->dec_data, true, "")));
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

void crypto_Tdes112EcbEncryptor_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		tc::crypto::Tdes112EcbEncryptor cryptor;

		// create data
		tc::ByteData control_data = tc::io::PaddingSource(0xee, tc::crypto::Tdes112EcbEncryptor::kBlockSize).pullData(0, tc::crypto::Tdes112EcbEncryptor::kBlockSize);
		tc::ByteData data = tc::ByteData(control_data.data(), control_data.size());

		// try to decrypt without calling initialize()
		cryptor.decrypt(data.data(), data.data(), data.size());

		// test plain text
		if (memcmp(data.data(), control_data.data(), data.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on data when not initialized");
		}

		// try to encrypt without calling initialize()
		cryptor.encrypt(data.data(), data.data(), data.size());

		// test plain text
		if (memcmp(data.data(), control_data.data(), data.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on data when not initialized");
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

void crypto_Tdes112EcbEncryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		try
		{
			cryptor.initialize(nullptr, tests[0].key.size());
			throw tc::TestException("Failed to throw ArgumentNullException where key==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key==nullptr");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tc::crypto::Tdes112EcbEncryptor::kKeySize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tc::crypto::Tdes112EcbEncryptor::kKeySize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize+1");
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

void crypto_Tdes112EcbEncryptor_TestClass::test_EncryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_EncryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size());

		tc::ByteData data = tc::ByteData(tests[0].base_data.size());

		// reference encrypt call
		//cryptor.encrypt(data.data(), tests[0].plaintext.data(), data.size());

		try
		{
			cryptor.encrypt(nullptr, tests[0].base_data.data(), data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.encrypt(data.data(), nullptr, data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.encrypt(data.data(), tests[0].base_data.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.encrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112EcbEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize-1");
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

void crypto_Tdes112EcbEncryptor_TestClass::test_DecryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_DecryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesEcbEncryptorUtil::TestVector> tests;
		TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112EcbEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size());

		tc::ByteData data = tc::ByteData(tests[0].base_data.size());

		// reference decrypt call
		//cryptor.decrypt(data.data(), tests[0].ciphertext.data(), data.size());

		try
		{
			cryptor.decrypt(nullptr, tests[0].base_data.data(), data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.decrypt(data.data(), nullptr, data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.decrypt(data.data(), tests[0].base_data.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.decrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112EcbEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize-1");
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