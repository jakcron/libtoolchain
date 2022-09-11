#include "crypto_Aes128CcmEncryptor_TestClass.h"
#include "AesCcmEncryptorUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Aes128CcmEncryptor.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

crypto_Aes128CcmEncryptor_TestClass::crypto_Aes128CcmEncryptor_TestClass() :
	mTestTag("tc::crypto::Aes128CcmEncryptor"),
	mTestResults()
{
}

void crypto_Aes128CcmEncryptor_TestClass::runAllTests(void)
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

const std::string& crypto_Aes128CcmEncryptor_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Aes128CcmEncryptor_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Aes128CcmEncryptor_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::Aes128CcmEncryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Aes128CcmEncryptor::kBlockSize, kExpectedBlockSize));
		}

		// check key size
		static const size_t kExpectedKeySize = 128 >> 3;
		if (tc::crypto::Aes128CcmEncryptor::kKeySize != kExpectedKeySize)
		{
			throw tc::TestException(fmt::format("kKeySize had value {:d} (expected {:d})", tc::crypto::Aes128CcmEncryptor::kKeySize, kExpectedKeySize));
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

void crypto_Aes128CcmEncryptor_TestClass::test_UseClassEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes128CcmEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData payload = tc::ByteData(test->plaintext.size());
			tc::ByteData mac = tc::ByteData(test->mac.size());

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size());
			
			// clear data
			memset(payload.data(), 0xff, payload.size());
			memset(mac.data(), 0xff, mac.size());

			// encrypt data
			cryptor.encrypt(payload.data(), test->plaintext.data(), payload.size(), test->nonce.data(), test->nonce.size(), test->aad.data(), test->aad.size(), mac.data(), mac.size());
			
			// validate cipher text
			if (memcmp(payload.data(), test->ciphertext.data(), payload.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: Ciphertext {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(payload, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
			}

			// validate mac
			if (memcmp(mac.data(), test->mac.data(), mac.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: MAC {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->mac, true, "")));
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

void crypto_Aes128CcmEncryptor_TestClass::test_UseClassDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes128CcmEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData payload = tc::ByteData(test->ciphertext.size());
			tc::ByteData mac = tc::ByteData(test->mac.size());

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size());
			
			// clear data
			memset(payload.data(), 0xff, payload.size());
			memset(mac.data(), 0xff, mac.size());

			// decrypt data
			cryptor.decrypt(payload.data(), test->ciphertext.data(), payload.size(), test->nonce.data(), test->nonce.size(), test->aad.data(), test->aad.size(), mac.data(), mac.size());
			
			// validate plain text
			if (memcmp(payload.data(), test->plaintext.data(), payload.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: Plaintext {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(payload, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
			}

			// validate mac
			if (memcmp(mac.data(), test->mac.data(), mac.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: MAC {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->mac, true, "")));
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

void crypto_Aes128CcmEncryptor_TestClass::test_UseUtilFuncEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData payload = tc::ByteData(test->plaintext.size());
			tc::ByteData mac = tc::ByteData(test->mac.size());
			
			// clear data
			memset(payload.data(), 0xff, payload.size());
			memset(mac.data(), 0xff, mac.size());

			// encrypt data
			tc::crypto::EncryptAes128Ccm(payload.data(), test->plaintext.data(), payload.size(), test->key.data(), test->key.size(), test->nonce.data(), test->nonce.size(), test->aad.data(), test->aad.size(), mac.data(), mac.size());
			
			// validate cipher text
			if (memcmp(payload.data(), test->ciphertext.data(), payload.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: Ciphertext {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(payload, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
			}

			// validate mac
			if (memcmp(mac.data(), test->mac.data(), mac.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: MAC {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->mac, true, "")));
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

void crypto_Aes128CcmEncryptor_TestClass::test_UseUtilFuncDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData payload = tc::ByteData(test->ciphertext.size());
			tc::ByteData mac = tc::ByteData(test->mac.size());
			
			// clear data
			memset(payload.data(), 0xff, payload.size());
			memset(mac.data(), 0xff, mac.size());

			// decrypt data			
			tc::crypto::DecryptAes128Ccm(payload.data(), test->ciphertext.data(), payload.size(), test->key.data(), test->key.size(), test->nonce.data(), test->nonce.size(), test->aad.data(), test->aad.size(), mac.data(), mac.size());

			// validate plain text
			if (memcmp(payload.data(), test->plaintext.data(), payload.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: Plaintext {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(payload, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
			}

			// validate mac
			if (memcmp(mac.data(), test->mac.data(), mac.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: MAC {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->mac, true, "")));
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

void crypto_Aes128CcmEncryptor_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		tc::crypto::Aes128CcmEncryptor cryptor;

		// create data
		tc::ByteData control_plaintext = tc::io::PaddingSource(0xaa, 0x20).pullData(0, 0x20);
		tc::ByteData plaintext = tc::ByteData(control_plaintext.data(), control_plaintext.size());

		tc::ByteData control_ciphertext = tc::io::PaddingSource(0xbb, control_plaintext.size()).pullData(0, control_plaintext.size());
		tc::ByteData ciphertext = tc::ByteData(control_ciphertext.data(), control_ciphertext.size());

		tc::ByteData control_nonce = tc::io::PaddingSource(0xcc, 0xC).pullData(0, 0xC);
		tc::ByteData nonce = tc::ByteData(control_nonce.data(), control_nonce.size());

		tc::ByteData control_aad = tc::io::PaddingSource(0xee, 0x20).pullData(0, 0x20);
		tc::ByteData aad = tc::ByteData(control_aad.data(), control_aad.size());

		tc::ByteData control_mac = tc::io::PaddingSource(0xff, 0x10).pullData(0, 0x10);
		tc::ByteData mac = tc::ByteData(control_mac.data(), control_mac.size());

		// try to decrypt without calling initialize()
		cryptor.decrypt(plaintext.data(), ciphertext.data(), plaintext.size(), nonce.data(), nonce.size(), aad.data(), aad.size(), mac.data(), mac.size());

		// test fields
		if (memcmp(plaintext.data(), control_plaintext.data(), plaintext.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on plaintext when not initialized");
		}

		if (memcmp(ciphertext.data(), control_ciphertext.data(), ciphertext.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on ciphertext when not initialized");
		}

		if (memcmp(nonce.data(), control_nonce.data(), nonce.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on nonce when not initialized");
		}

		if (memcmp(aad.data(), control_aad.data(), aad.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on aad when not initialized");
		}

		if (memcmp(mac.data(), control_mac.data(), mac.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on mac when not initialized");
		}

		// try to encrypt without calling initialize()
		cryptor.encrypt(plaintext.data(), ciphertext.data(), plaintext.size(), nonce.data(), nonce.size(), aad.data(), aad.size(), mac.data(), mac.size());

		// test fields
		if (memcmp(plaintext.data(), control_plaintext.data(), plaintext.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on plaintext when not initialized");
		}

		if (memcmp(ciphertext.data(), control_ciphertext.data(), ciphertext.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on ciphertext when not initialized");
		}

		if (memcmp(nonce.data(), control_nonce.data(), nonce.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on nonce when not initialized");
		}

		if (memcmp(aad.data(), control_aad.data(), aad.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on aad when not initialized");
		}

		if (memcmp(mac.data(), control_mac.data(), mac.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on mac when not initialized");
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

void crypto_Aes128CcmEncryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes128CcmEncryptor cryptor;
		// reference call cryptor.initialize(test->key.data(), test->key.size());

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
			cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==kKeySize-1");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where key_size==kKeySize-1");
		}

		try
		{
			cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize+1);
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

void crypto_Aes128CcmEncryptor_TestClass::test_EncryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_EncryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes128CcmEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size());

		tc::ByteData payload = tc::ByteData(tests[0].plaintext.size());
		tc::ByteData mac = tc::ByteData(tests[0].mac.size());
		tc::ByteData aad = tc::ByteData(0x10);

		// reference encrypt call
		//cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

		try
		{
			cryptor.encrypt(nullptr, tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.encrypt(payload.data(), nullptr, payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), 0, tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), nullptr, tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where iv==nullptr but iv_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv==nullptr but iv_size!=0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), 0, tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where iv!=nullptr but iv_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv_size==0 but iv_size==0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), nullptr, aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where add==nullptr but add_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add==nullptr but add_size!=0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), aad.data(), 0, mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where add!=nullptr but add_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add_size==0 but add_size==0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), nullptr, mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where tag==nullptr but tag_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where tag==nullptr but tag_size!=0");
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), 0);

			throw tc::TestException("Failed to throw ArgumentNullException where tag!=nullptr but tag_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where tag_size==0 but tag_size==0");
		}

		std::vector<size_t> invalid_iv_sizes = {1,2,3,4,5,6,14,15,16};

		for (size_t i = 0; i <= invalid_iv_sizes.size(); i++)
		{
			try
			{
				cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), invalid_iv_sizes[i], tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where iv_size=={}", invalid_iv_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where iv_size=={}", invalid_iv_sizes[i]));
			}
		}

		std::vector<size_t> valid_iv_sizes = {7,8,9,10,11,12,13};
		uint64_t native_sizet_max = std::numeric_limits<size_t>::max();

		for (size_t i = 0; i <= valid_iv_sizes.size(); i++)
		{
			uint64_t max_payload_size = (uint64_t)0xffffffffffffffff >> (8 * (valid_iv_sizes[i] - 7));
			
			// skip tests where the native size_t can't exceed the maximum payload size
			if (max_payload_size >= native_sizet_max) continue;

			try
			{
				cryptor.encrypt(payload.data(), tests[0].plaintext.data(), size_t(max_payload_size) + 1, tests[0].nonce.data(), valid_iv_sizes[i], tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where size > 0x{:x} given iv_size == 0x{:x}", max_payload_size, valid_iv_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where size > 0x{:x} given iv_size == 0x{:x}", max_payload_size, valid_iv_sizes[i]));
			}
		}

		try
		{
			cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), aad.data(), 0xff01, mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where add_size > 0xff00");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add_size > 0xff00");
		}

		std::vector<size_t> invalid_mac_sizes = {1,2,3,5,7,9,11,13,15};

		for (size_t i = 0; i <= invalid_mac_sizes.size(); i++)
		{
			try
			{
				cryptor.encrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), invalid_mac_sizes[i]);

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where tag_size=={}", invalid_mac_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where tag_size=={}", invalid_mac_sizes[i]));
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

void crypto_Aes128CcmEncryptor_TestClass::test_DecryptThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_DecryptThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<AesCcmEncryptorUtil::TestVector> tests;
		AesCcmEncryptorUtil::generateAesCcmTestVectors_Nist(tests, 128);
		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No test vectors");
		}

		tc::crypto::Aes128CcmEncryptor cryptor;

		cryptor.initialize(tests[0].key.data(), tests[0].key.size());

		tc::ByteData payload = tc::ByteData(tests[0].plaintext.size());
		tc::ByteData mac = tc::ByteData(tests[0].mac.size());
		tc::ByteData aad = tc::ByteData(0x10);

		// reference decrypt call
		//cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

		try
		{
			cryptor.decrypt(nullptr, tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where dst==nullptr");
		}

		try
		{
			cryptor.decrypt(payload.data(), nullptr, payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where src==nullptr");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), 0, tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where size==0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), nullptr, tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where iv==nullptr but iv_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv==nullptr but iv_size!=0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), 0, tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where iv!=nullptr but iv_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where iv_size==0 but iv_size==0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), nullptr, aad.size(), mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where add==nullptr but add_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add==nullptr but add_size!=0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), aad.data(), 0, mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where add!=nullptr but add_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add_size==0 but add_size==0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), nullptr, mac.size());

			throw tc::TestException("Failed to throw ArgumentNullException where tag==nullptr but tag_size!=0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where tag==nullptr but tag_size!=0");
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), 0);

			throw tc::TestException("Failed to throw ArgumentNullException where tag!=nullptr but tag_size==0");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where tag_size==0 but tag_size==0");
		}

		std::vector<size_t> invalid_iv_sizes = {1,2,3,4,5,6,14,15,16};

		for (size_t i = 0; i <= invalid_iv_sizes.size(); i++)
		{
			try
			{
				cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), invalid_iv_sizes[i], tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where iv_size=={}", invalid_iv_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where iv_size=={}", invalid_iv_sizes[i]));
			}
		}

		std::vector<size_t> valid_iv_sizes = {7,8,9,10,11,12,13};
		uint64_t native_sizet_max = std::numeric_limits<size_t>::max();

		for (size_t i = 0; i <= valid_iv_sizes.size(); i++)
		{
			uint64_t max_payload_size = (uint64_t)0xffffffffffffffff >> (8 * (valid_iv_sizes[i] - 7));
			
			// skip tests where the native size_t can't exceed the maximum payload size
			if (max_payload_size >= native_sizet_max) continue;

			try
			{
				cryptor.decrypt(payload.data(), tests[0].plaintext.data(), size_t(max_payload_size) + 1, tests[0].nonce.data(), valid_iv_sizes[i], tests[0].aad.data(), tests[0].aad.size(), mac.data(), mac.size());

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where size > 0x{:x} given iv_size == 0x{:x}", max_payload_size, valid_iv_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where size > 0x{:x} given iv_size == 0x{:x}", max_payload_size, valid_iv_sizes[i]));
			}
		}

		try
		{
			cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), aad.data(), 0xff01, mac.data(), mac.size());

			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where add_size > 0xff00");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where add_size > 0xff00");
		}

		std::vector<size_t> invalid_mac_sizes = {1,2,3,5,7,9,11,13,15};

		for (size_t i = 0; i <= invalid_mac_sizes.size(); i++)
		{
			try
			{
				cryptor.decrypt(payload.data(), tests[0].plaintext.data(), payload.size(), tests[0].nonce.data(), tests[0].nonce.size(), tests[0].aad.data(), tests[0].aad.size(), mac.data(), invalid_mac_sizes[i]);

				throw tc::TestException(fmt::format("Failed to throw ArgumentOutOfRangeException where tag_size=={}", invalid_mac_sizes[i]));
			}
			catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
			catch (const tc::Exception&)
			{
				throw tc::TestException(fmt::format("Failed to throw correct exception where tag_size=={}", invalid_mac_sizes[i]));
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