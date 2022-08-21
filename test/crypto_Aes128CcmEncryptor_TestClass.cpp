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

	//test_DoesNothingWhenNotInit();
	//test_InitializeThrowsExceptionOnBadInput();
	//test_EncryptThrowsExceptionOnBadInput();
	//test_DecryptThrowsExceptionOnBadInput();
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

/*

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
		tc::ByteData control_data = tc::io::PaddingSource(0xee, 0x20).pullData(0, 0x20);
		tc::ByteData data = tc::ByteData(control_data.data(), control_data.size());

		// try to decrypt without calling initialize()
		cryptor.decrypt(data.data(), data.data(), data.size());

		// test plain text			
		if (memcmp(data.data(), control_data.data(), data.size()) != 0)
		{
			ss << "Failed: decrypt() operated on data when not initialized";
			throw tc::TestException(ss.str());
		}

		// try to encrypt without calling initialize()
		cryptor.encrypt(data.data(), data.data(), data.size());

		// test plain text			
		if (memcmp(data.data(), control_data.data(), data.size()) != 0)
		{
			ss << "Failed: encrypt() operated on data when not initialized";
			throw tc::TestException(ss.str());
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

		try {
			cryptor.initialize(nullptr, tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentNullException where key==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), 0, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==0");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize-1, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==tc::crypto::Aes128CcmEncryptor::kKeySize-1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize+1, tests[0].iv.data(), tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where key_size==tc::crypto::Aes128CcmEncryptor::kKeySize+1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), nullptr, tests[0].iv.size());
			throw tc::TestException("Failed to throw ArgumentNullException where iv==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==0");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize-1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize+1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
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

		cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

		tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

		// reference encrypt call
		//cryptor.encrypt(data.data(), tests[0].plaintext.data(), data.size());

		try {
			cryptor.encrypt(nullptr, tests[0].plaintext.data(), data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.encrypt(data.data(), nullptr, data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.encrypt(data.data(), tests[0].plaintext.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.encrypt(data.data(), tests[0].plaintext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize-1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.encrypt(data.data(), tests[0].plaintext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize+1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
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

		cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

		tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

		// reference decrypt call
		//cryptor.decrypt(data.data(), tests[0].ciphertext.data(), data.size());

		try {
			cryptor.decrypt(nullptr, tests[0].ciphertext.data(), data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where dst==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.decrypt(data.data(), nullptr, data.size());
			throw tc::TestException("Failed to throw ArgumentNullException where src==nullptr");
		} catch(const tc::ArgumentNullException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.decrypt(data.data(), tests[0].ciphertext.data(), 0);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==0");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.decrypt(data.data(), tests[0].ciphertext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize-1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
		}

		try {
			cryptor.decrypt(data.data(), tests[0].ciphertext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize+1");
		} catch(const tc::ArgumentOutOfRangeException&) {
			// all good if this was thrown.
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
*/