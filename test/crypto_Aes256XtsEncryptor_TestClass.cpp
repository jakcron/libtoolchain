#include "crypto_Aes256XtsEncryptor_TestClass.h"
#include "AesXtsEncryptorUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Aes256XtsEncryptor.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

crypto_Aes256XtsEncryptor_TestClass::crypto_Aes256XtsEncryptor_TestClass() :
	mTestTag("tc::crypto::Aes256XtsEncryptor"),
	mTestResults()
{
}

void crypto_Aes256XtsEncryptor_TestClass::runAllTests(void)
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

const std::string& crypto_Aes256XtsEncryptor_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Aes256XtsEncryptor_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Aes256XtsEncryptor_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::Aes256XtsEncryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Aes256XtsEncryptor::kBlockSize, kExpectedBlockSize));
		}

		// check key size
		static const size_t kExpectedKeySize = 256 >> 3;
		if (tc::crypto::Aes256XtsEncryptor::kKeySize != kExpectedKeySize)
		{
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", tc::crypto::Aes256XtsEncryptor::kKeySize, kExpectedKeySize));
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

void crypto_Aes256XtsEncryptor_TestClass::test_UseClassEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->plaintext.size());

			// initialize key
			cryptor.initialize(test->key1.data(), test->key1.size(), test->key2.data(), test->key2.size(), test->data_unit, true);
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// encrypt data
			cryptor.encrypt(data.data(), test->plaintext.data(), data.size(), test->data_unit_sequence_number);
			
			// validate cipher text
			if (memcmp(data.data(), test->ciphertext.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
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

void crypto_Aes256XtsEncryptor_TestClass::test_UseClassDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->plaintext.size());
			
			// initialize key
			cryptor.initialize(test->key1.data(), test->key1.size(), test->key2.data(), test->key2.size(), test->data_unit, true);
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// decrypt data
			cryptor.decrypt(data.data(), test->ciphertext.data(), data.size(), test->data_unit_sequence_number);

			// test plain text
			if (memcmp(data.data(), test->plaintext.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->plaintext, true, "")));
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

void crypto_Aes256XtsEncryptor_TestClass::test_UseUtilFuncEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->plaintext.size());
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// encrypt data
			tc::crypto::EncryptAes256Xts(data.data(), test->plaintext.data(), data.size(), test->data_unit_sequence_number, test->key1.data(), test->key1.size(), test->key2.data(), test->key2.size(), test->data_unit, true);
			
			// validate cipher text
			if (memcmp(data.data(), test->ciphertext.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
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

void crypto_Aes256XtsEncryptor_TestClass::test_UseUtilFuncDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->plaintext.size());
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// decrypt data
			tc::crypto::DecryptAes256Xts(data.data(), test->ciphertext.data(), data.size(), test->data_unit_sequence_number, test->key1.data(), test->key1.size(), test->key2.data(), test->key2.size(), test->data_unit, true);

			// test plain text
			if (memcmp(data.data(), test->plaintext.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->plaintext, true, "")));
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

void crypto_Aes256XtsEncryptor_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		tc::crypto::Aes256XtsEncryptor cryptor;

		// create data
		tc::ByteData control_data = tc::io::PaddingSource(0xee, tc::crypto::Aes256XtsEncryptor::kBlockSize).pullData(0, tc::crypto::Aes256XtsEncryptor::kBlockSize);
		tc::ByteData data = tc::ByteData(control_data.data(), control_data.size());

		// check sector size is zero when not initialized
		if (cryptor.sector_size() != 0)
		{
			throw tc::TestException("Failed: sector_size() reported a non-zero answer when not initialized");
		}

		// try to decrypt without calling initialize()
		cryptor.decrypt(data.data(), data.data(), data.size(), 0);

		// test plain text
		if (memcmp(data.data(), control_data.data(), data.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on data when not initialized");
		}

		// try to encrypt without calling initialize()
		cryptor.encrypt(data.data(), data.data(), data.size(), 0);

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

void crypto_Aes256XtsEncryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		// reference initialize call
		//cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);

		try
		{
			cryptor.initialize(nullptr, tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentNullException where key1==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key1==nullptr");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), 0, tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key1_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key1_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tc::crypto::Aes256XtsEncryptor::kKeySize-1, tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key1_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key1_size==kKeySize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tc::crypto::Aes256XtsEncryptor::kKeySize+1, tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key1_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key1_size==kKeySize+1");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), nullptr, tests[0].key2.size(), tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentNullException where key2==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key2==nullptr");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), 0, tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key2_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key2_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tc::crypto::Aes256XtsEncryptor::kKeySize-1, tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key2_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key2_size==kKeySize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tc::crypto::Aes256XtsEncryptor::kKeySize+1, tests[0].data_unit, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key2_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key2_size==kKeySize+1");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), 0, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where sector_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where sector_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), tc::crypto::Aes256XtsEncryptor::kBlockSize-1, true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where sector_size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where sector_size==kBlockSize-1");
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

void crypto_Aes256XtsEncryptor_TestClass::test_EncryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_EncryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);

		tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

		// reference encrypt call
		//cryptor.encrypt(data.data(), tests[0].plaintext.data(), data.size(), 0);

		try
		{
			cryptor.encrypt(nullptr, tests[0].plaintext.data(), data.size(), 0);
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.encrypt(data.data(), nullptr, data.size(), 0);
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.encrypt(data.data(), tests[0].plaintext.data(), 0, 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.encrypt(data.data(), tests[0].plaintext.data(), cryptor.sector_size()-1, 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==cryptor.sector_size()-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==cryptor.sector_size()-1");
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

void crypto_Aes256XtsEncryptor_TestClass::test_DecryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_DecryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesXtsEncryptorUtil::TestVector> tests;
		AesXtsEncryptorUtil::generateAesXtsTestVectors_IEEE1619_2007(tests, 256);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes256XtsEncryptor cryptor;

		cryptor.initialize(tests[0].key1.data(), tests[0].key1.size(), tests[0].key2.data(), tests[0].key2.size(), tests[0].data_unit, true);

		tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

		// reference encrypt call
		//cryptor.decrypt(data.data(), tests[0].ciphertext.data(), data.size(), 0);

		try
		{
			cryptor.decrypt(nullptr, tests[0].ciphertext.data(), data.size(), 0);
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.decrypt(data.data(), nullptr, data.size(), 0);
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.decrypt(data.data(), tests[0].ciphertext.data(), 0, 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.decrypt(data.data(), tests[0].ciphertext.data(), cryptor.sector_size()-1, 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==cryptor.sector_size()-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==cryptor.sector_size()-1");
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