#include "crypto_Rsa1024Pkcs1Sha1Signer_TestClass.h"
#include "RsaPkcs1Util.h"

#include <fmt/format.h>

#include <tc/crypto/RsaPkcs1Sha1Signer.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

crypto_Rsa1024Pkcs1Sha1Signer_TestClass::crypto_Rsa1024Pkcs1Sha1Signer_TestClass() :
	mTestTag("tc::crypto::Rsa1024Pkcs1Sha1Signer"),
	mTestResults()
{
}

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::runAllTests(void)
{
	test_Constants();
	test_UseClassSign();
	test_UseClassVerify();
	test_UseUtilFuncSign();
	test_UseUtilFuncVerify();

	test_DoesNothingWhenNotInit();
	test_InitializeThrowsExceptionOnBadInput();
	test_SignReturnsFalseOnBadInput();
	test_VerifyReturnsFalseOnBadInput();
}

const std::string& crypto_Rsa1024Pkcs1Sha1Signer_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Rsa1024Pkcs1Sha1Signer_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check signature size
		static const size_t kExpectedSignatureSize = 1024 >> 3;
		if (tc::crypto::Rsa1024Pkcs1Sha1Signer::kSignatureSize != kExpectedSignatureSize)
		{
			throw tc::TestException(fmt::format("kSignatureSize had value {:d} (expected {:d}", tc::crypto::Rsa1024Pkcs1Sha1Signer::kSignatureSize, kExpectedSignatureSize));
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_UseClassSign()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassSign";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData signature = tc::ByteData(test->signature.size());
			
			// initialize
			signer.initialize(tc::crypto::RsaPrivateKey(test->key_modulus.data(), test->key_modulus.size(), test->key_private_exponent.data(), test->key_private_exponent.size()));
			
			// clear data
			memset(signature.data(), 0xff, signature.size());

			// test sign
			bool result = signer.sign(signature.data(), test->message_digest.data());
			if (result == false)
			{				
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: sign() returned false",test->test_name));
			}
			if (memcmp(signature.data(), test->signature.data(), signature.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(signature, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->signature, true, "")));
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_UseClassVerify()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassVerify";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{				
			// initialize
			signer.initialize(tc::crypto::RsaPublicKey(test->key_modulus.data(), test->key_modulus.size()));

			// test verify
			bool result = signer.verify(test->signature.data(), test->message_digest.data());
			if (result == false)
			{				
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: verify() returned false", test->test_name));
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_UseUtilFuncSign()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncSign";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData signature = tc::ByteData(test->signature.size());
			
			// clear data
			memset(signature.data(), 0xff, signature.size());

			// test sign
			bool result = tc::crypto::SignRsa1024Pkcs1Sha1(signature.data(), test->message_digest.data(), tc::crypto::RsaPrivateKey(test->key_modulus.data(), test->key_modulus.size(), test->key_private_exponent.data(), test->key_private_exponent.size()));
			if (result == false)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: sign() returned false", test->test_name));
			}
			if (memcmp(signature.data(), test->signature.data(), signature.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(signature, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->signature, true, "")));
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_UseUtilFuncVerify()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncVerify";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{				
			// test verify
			bool result = tc::crypto::VerifyRsa1024Pkcs1Sha1(test->signature.data(), test->message_digest.data(), tc::crypto::RsaPublicKey(test->key_modulus.data(), test->key_modulus.size()));
			if (result == false)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: verify() returned false", test->test_name));
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}
		
		bool res;
		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		// create data
		tc::ByteData hash = tc::ByteData(tests[0].message_digest.size());
		tc::ByteData control_signature = tc::io::PaddingSource(0xee, tests[0].signature.size()).pullData(0, 0x20);
		tc::ByteData signature = tc::ByteData(control_signature.data(), control_signature.size());
		

		// try to sign without calling initialize()
		res = signer.sign(signature.data(), hash.data());
		if (res != false)
		{
			throw tc::TestException("Failed: sign() returned true when not initialized");
		}
		if (memcmp(signature.data(), control_signature.data(), signature.size()) != 0)
		{
			throw tc::TestException("Failed: sign() operated on message when not initialized");
		}

		// try to verify without calling initialize()
		res = signer.verify(signature.data(), hash.data());
		if (res != false)
		{
			throw tc::TestException("Failed: verify() returned true when not initialized");
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		// reference initialize call
		//signer.initialize(tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size()));

		auto key = tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size());
		auto empty_key = tc::crypto::RsaKey();
		auto bad_modulus_size_key = tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size()-2, tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size());
		auto no_modulus_key = key;
		no_modulus_key.n = tc::ByteData();
		auto bad_privexp_size_key = tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size()-2);
		auto bad_pubexp_size_key = key;
		bad_pubexp_size_key.e = tc::ByteData(5);
		auto no_exponent_key = key;
		no_exponent_key.d = tc::ByteData();
		no_exponent_key.e = tc::ByteData();

		try
		{
			signer.initialize(empty_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey empty");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey empty");
		}

		try
		{
			signer.initialize(bad_modulus_size_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad modulus size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad modulus size");
		}

		try
		{
			signer.initialize(no_modulus_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a no modulus");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a no modulus");
		}

		try
		{
			signer.initialize(bad_privexp_size_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad private exponent size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad private exponent size");
		}

		try
		{
			signer.initialize(bad_pubexp_size_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad public exponent size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad public exponent size");
		}

		try
		{
			signer.initialize(no_exponent_key);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a neither public nor private exponents");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a neither public nor private exponents");
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_SignReturnsFalseOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_SignReturnsFalseOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{	
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		signer.initialize(tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size()));

		tc::ByteData signature = tc::ByteData(tests[0].signature.size());

		// reference sign call
		//signer.sign(signature.data(), tests[0].message_digest.data());

		bool result = false;

		result = signer.sign(nullptr, tests[0].message_digest.data());
		if (result != false)
		{
			throw tc::TestException("sign() did not return false where signature==nullptr");
		}

		result = signer.sign(signature.data(), nullptr);
		if (result != false)
		{
			throw tc::TestException("sign() did not return false where message_digest==nullptr");
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

void crypto_Rsa1024Pkcs1Sha1Signer_TestClass::test_VerifyReturnsFalseOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_VerifyReturnsFalseOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaPkcs1Util::TestVector> tests;
		RsaPkcs1Util::generateRsaPkcs1TestVectors_Custom(tests, 1024, RsaPkcs1Util::SHA1);

		tc::crypto::Rsa1024Pkcs1Sha1Signer signer;

		signer.initialize(tc::crypto::RsaPublicKey(tests[0].key_modulus.data(), tests[0].key_modulus.size()));

		// reference verify call
		//signer.verify(tests[0].signature.data(), tests[0].message_digest.data());

		bool result = false;

		result = signer.verify(nullptr, tests[0].message_digest.data());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where signature==nullptr");
		}

		result = signer.verify(tests[0].signature.data(), nullptr);
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where message_digest==nullptr");
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