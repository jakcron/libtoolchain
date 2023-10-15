#include "crypto_Tdes112CbcEncryptor_TestClass.h"
#include "TdesDesCbcEncryptorUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Tdes112CbcEncryptor.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//#include <mbedtls/des.h>

//---------------------------------------------------------

crypto_Tdes112CbcEncryptor_TestClass::crypto_Tdes112CbcEncryptor_TestClass() :
	mTestTag("tc::crypto::Tdes112CbcEncryptor"),
	mTestResults()
{
}

void crypto_Tdes112CbcEncryptor_TestClass::runAllTests(void)
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

const std::string& crypto_Tdes112CbcEncryptor_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Tdes112CbcEncryptor_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Tdes112CbcEncryptor_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 8;
		if (tc::crypto::Tdes112CbcEncryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Tdes112CbcEncryptor::kBlockSize, kExpectedBlockSize));
		}

		// check key size
		static const size_t kExpectedKeySize = 16;
		size_t kKeySize = tc::crypto::Tdes112CbcEncryptor::kKeySize;
		if (kKeySize != kExpectedKeySize)
		{
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", kKeySize, kExpectedKeySize));
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

void crypto_Tdes112CbcEncryptor_TestClass::test_UseClassEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112CbcEncryptor cryptor;

		// The repeated iteration test for CBC needs extra steps because encryption XORs the IV with the input block, and since after the first iteration, the IV and input block are the same, some alternation needs to be added
		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);
			tc::ByteData iv   = tc::ByteData(test->iv);
			tc::ByteData prv  = tc::ByteData(test->iv);
			tc::ByteData tmp  = tc::ByteData(prv.size());

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size(), test->iv.data(), test->iv.size());

			// encrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				cryptor.encrypt(data.data(), data.data(), data.size());

				// alternate data
				// save the old prv
                memcpy( tmp.data(), prv.data(), 8 );

                // new prv = enc'd data
                memcpy( prv.data(), data.data(), 8 );

                // data = old prv
                memcpy( data.data(), tmp.data(), 8 );
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

void crypto_Tdes112CbcEncryptor_TestClass::test_UseClassDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112CbcEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);
			
			// initialize key
			cryptor.initialize(test->key.data(), test->key.size(), test->iv.data(), test->iv.size());

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

void crypto_Tdes112CbcEncryptor_TestClass::test_UseUtilFuncEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		// The repeated iteration test for CBC needs extra steps because encryption XORs the IV with the input block, and since after the first iteration, the IV and input block are the same, some alternation needs to be added
		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);
			tc::ByteData iv   = tc::ByteData(test->iv);
			tc::ByteData prv  = tc::ByteData(test->iv);
			tc::ByteData tmp  = tc::ByteData(prv.size());
			
			// encrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				tc::crypto::EncryptTdes112Cbc(data.data(), data.data(), data.size(), test->key.data(), test->key.size(), iv.data(), iv.size());

				// update iv with encrypted block
				memcpy(iv.data(), data.data(), 8);

				// alternate data
				// save the old prv
                memcpy( tmp.data(), prv.data(), 8 );

                // new prv = enc'd data
                memcpy( prv.data(), data.data(), 8 );

                // data = old prv
                memcpy( data.data(), tmp.data(), 8 );
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

void crypto_Tdes112CbcEncryptor_TestClass::test_UseUtilFuncDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112CbcEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->base_data);

			tc::ByteData iv = tc::ByteData(test->iv);
			tc::ByteData next_iv = tc::ByteData(iv.size());

			// decrypt data
			for (size_t itr = 0; itr < test->iteration_count; itr++)
			{
				memcpy(next_iv.data(), data.data(), 8);

				tc::crypto::DecryptTdes112Cbc(data.data(), data.data(), data.size(), test->key.data(), test->key.size(), iv.data(), iv.size());

				memcpy(iv.data(), next_iv.data(), 8);
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

void crypto_Tdes112CbcEncryptor_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		tc::crypto::Tdes112CbcEncryptor cryptor;

		// create data
		tc::ByteData control_data = tc::io::PaddingSource(0xee, tc::crypto::Tdes112CbcEncryptor::kBlockSize).pullData(0, tc::crypto::Tdes112CbcEncryptor::kBlockSize);
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

void crypto_Tdes112CbcEncryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112CbcEncryptor cryptor;

		try
		{
			cryptor.initialize(nullptr, tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentNullException where key==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key==nullptr");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), 0, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tc::crypto::Tdes112CbcEncryptor::kKeySize-1, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tc::crypto::Tdes112CbcEncryptor::kKeySize+1, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize+1");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), nullptr, tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentNullException where iv==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv==nullptr");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv_size==0");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv_size==kBlockSize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv_size==kBlockSize+1");
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

void crypto_Tdes112CbcEncryptor_TestClass::test_EncryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_EncryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}


		tc::crypto::Tdes112CbcEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

		tc::ByteData data = tc::ByteData(tests[0].base_data.size());

		// reference encrypt call
		//cryptor.encrypt(data.data(), tests[0].base_data.data(), data.size());

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
			cryptor.encrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize-1");
		}

		try
		{
			cryptor.encrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize+1");
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

void crypto_Tdes112CbcEncryptor_TestClass::test_DecryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_DecryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<TdesDesCbcEncryptorUtil::TestVector> tests;
		TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(tests, 112);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Tdes112CbcEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

		tc::ByteData data = tc::ByteData(tests[0].base_data.size());

		// reference decrypt call
		//cryptor.decrypt(data.data(), tests[0].base_data.data(), data.size());

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
			cryptor.decrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize-1");
		}

		try
		{
			cryptor.decrypt(data.data(), tests[0].base_data.data(), tc::crypto::Tdes112CbcEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==kBlockSize+1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==kBlockSize+1");
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