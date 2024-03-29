#include "crypto_Rsa2048OaepSha2512Encryptor_TestClass.h"
#include "RsaOaepUtil.h"

#include <fmt/format.h>

#include <tc/crypto/RsaOaepSha2512Encryptor.h>
#include <tc/cli/FormatUtil.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

crypto_Rsa2048OaepSha2512Encryptor_TestClass::crypto_Rsa2048OaepSha2512Encryptor_TestClass() :
	mTestTag("tc::crypto::Rsa2048OaepSha2512Encryptor"),
	mTestResults()
{
}

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::runAllTests(void)
{
	test_Constants();
	test_UseClassDec();
	test_UseClassEnc();
	test_UseUtilFuncDec();
	test_UseUtilFuncEnc();
	test_UnspecifiedSeedProducesDifferentBlock();

	test_DoesNothingWhenNotInit();
	test_InitializeThrowsExceptionOnBadInput();
	test_EncryptReturnsFalseOnBadInput();
	test_DecryptReturnsFalseOnBadInput();
}

const std::string& crypto_Rsa2048OaepSha2512Encryptor_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Rsa2048OaepSha2512Encryptor_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_Constants()
{
	TestResult test_result;
	test_result.test_name = "test_Constants";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 2048 >> 3;
		if (tc::crypto::Rsa2048OaepSha2512Encryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::TestException(fmt::format("kBlockSize had value {:d} (expected {:d}", tc::crypto::Rsa2048OaepSha2512Encryptor::kBlockSize, kExpectedBlockSize));
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_UseClassDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->dec_message.size());
			
			// initialize
			cryptor.initialize(tc::crypto::RsaPrivateKey(test->key_modulus.data(), test->key_modulus.size(), test->key_private_exponent.data(), test->key_private_exponent.size()), test->label.data(), test->label.size(), test->label_is_digested);
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// test decryption
			size_t message_size = 0;
			cryptor.decrypt(data.data(), message_size, data.size(), test->enc_message.data());
			if (message_size != test->dec_message.size())
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: message_size = {:d} (expected {:d})", test->test_name, message_size, test->dec_message.size()));
			}
			if (memcmp(data.data(), test->dec_message.data(), data.size()) != 0)
			{				
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->dec_message, true, "")));
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_UseClassEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseClassEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->enc_message.size());
			
			// initialize
			cryptor.initialize(tc::crypto::RsaPublicKey(test->key_modulus.data(), test->key_modulus.size()), test->label.data(), test->label.size(), test->label_is_digested);
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// test encryption
			cryptor.encrypt(data.data(), test->dec_message.data(), test->dec_message.size(), test->enc_seed.data(), test->enc_seed.size());
			if (memcmp(data.data(), test->enc_message.data(), data.size()) != 0)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->enc_message, true, "")));
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_UseUtilFuncDec()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncDec";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData data = tc::ByteData(test->dec_message.size());
			
			// clear data
			memset(data.data(), 0xff, data.size());

			// test decryption
			size_t message_size = 0;
			bool res = tc::crypto::DecryptRsa2048OaepSha2512(data.data(), message_size, data.size(), test->enc_message.data(), tc::crypto::RsaPrivateKey(test->key_modulus.data(), test->key_modulus.size(), test->key_private_exponent.data(), test->key_private_exponent.size()), test->label.data(), test->label.size(), test->label_is_digested);
			if (res != true)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: DecryptRsa2048OaepSha2512 returned {} (expected {})", test->test_name, res, true));
			}
			if (message_size != test->dec_message.size())
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: message_size = {:d} (expected {:d})", test->test_name, message_size, test->dec_message.size()));
			}
			if (memcmp(data.data(), test->dec_message.data(), data.size()) != 0)
			{				
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->dec_message, true, "")));
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_UseUtilFuncEnc()
{
	TestResult test_result;
	test_result.test_name = "test_UseUtilFuncEnc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		// the utility function doesn't support specifying a seed, so we'll have to do some `lite` validation using the already validated decryption utility.
		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData dec_data = tc::ByteData(test->dec_message.size());
			tc::ByteData enc_data = tc::ByteData(test->enc_message.size());
				
			// clear data
			memset(dec_data.data(), 0xff, dec_data.size());
			memset(enc_data.data(), 0xff, enc_data.size());

			// test encryption
			bool res = tc::crypto::EncryptRsa2048OaepSha2512(enc_data.data(), test->dec_message.data(), test->dec_message.size(), tc::crypto::RsaPublicKey(test->key_modulus.data(), test->key_modulus.size()), test->label.data(), test->label.size(), test->label_is_digested);
			if (res != true)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: EncryptRsa2048OaepSha2512 returned {} (expected {})", test->test_name, res, true));
			}

			// try to decrypt message
			size_t message_size = 0;
			res = tc::crypto::DecryptRsa2048OaepSha2512(dec_data.data(), message_size, dec_data.size(), enc_data.data(), tc::crypto::RsaPrivateKey(test->key_modulus.data(), test->key_modulus.size(), test->key_private_exponent.data(), test->key_private_exponent.size()), test->label.data(), test->label.size(), test->label_is_digested);
			if (res != true)
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: encrypted message could not be decrypted", test->test_name));
			}
			if (message_size != test->dec_message.size())
			{
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: message_size = {:d} (expected {:d})", test->test_name, message_size, test->dec_message.size()));
			}
			if (memcmp(dec_data.data(), test->dec_message.data(), dec_data.size()) != 0)
			{				
				throw tc::TestException(fmt::format("Test \"{:s}\" Failed: decrypted message was not expected {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(dec_data, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->dec_message, true, "")));
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_UnspecifiedSeedProducesDifferentBlock()
{
	TestResult test_result;
	test_result.test_name = "test_UnspecifiedSeedProducesDifferentBlock";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		if (tests.begin() == tests.end())
		{
			throw tc::TestException("No tests");
		}

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		// initialize
		cryptor.initialize(tc::crypto::RsaPublicKey(tests[0].key_modulus.data(), tests[0].key_modulus.size()), tests[0].label.data(), tests[0].label.size(), tests[0].label_is_digested);

		static const size_t kTestNum = 20;
		std::vector<tc::ByteData> enc_messages;

		int difference_score = 0;
		for (size_t i = 0; i < kTestNum; i++)
		{
			// create message buffer
			tc::ByteData msg = tc::ByteData(tests[0].enc_message.size());
			
			// encrypt using auto seed generator
			cryptor.encrypt(msg.data(), tests[0].dec_message.data(), tests[0].dec_message.size());
			
			// add message to vector
			enc_messages.push_back(msg);

			// compare this message to the previous messages
			for (size_t j = 0; j < i; j++)
			{
				difference_score += memcmp(enc_messages[i].data(), enc_messages[j].data(), tests[0].enc_message.size()) == 0;
			}
		}
	
		if (difference_score != 0)
		{
			throw tc::TestException("Failed to generate unique encrypted messages.");
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_DoesNothingWhenNotInit()
{
	TestResult test_result;
	test_result.test_name = "test_DoesNothingWhenNotInit";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{	
		bool res;
		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		// create data
		tc::ByteData control_message = tc::io::PaddingSource(0xee, 0x20).pullData(0, 0x20);
		tc::ByteData message = tc::ByteData(control_message.data(), control_message.size());
		tc::ByteData control_block = tc::io::PaddingSource(0xdd, tc::crypto::Rsa2048OaepSha2512Encryptor::kBlockSize).pullData(0, tc::crypto::Rsa2048OaepSha2512Encryptor::kBlockSize);
		tc::ByteData block = tc::ByteData(control_block);
		size_t control_message_size = 0x1337;
		size_t message_size = control_message_size;

		// try to decrypt without calling initialize()
		res = cryptor.decrypt(message.data(), message_size, message.size(), block.data());

		if (res != false)
		{
			throw tc::TestException("Failed: decrypt() returned true when not initialized");
		}
		if (message_size != control_message_size)
		{
			throw tc::TestException("Failed: decrypt() modified message_size when not initialized");
		}
		if (memcmp(message.data(), control_message.data(), message.size()) != 0)
		{
			throw tc::TestException("Failed: decrypt() operated on message when not initialized");
		}

		// try to encrypt without calling initialize()
		res = cryptor.encrypt(block.data(), message.data(), message.size());

		if (res != false)
		{
			throw tc::TestException("Failed: encrypt() returned true when not initialized");
		}
		if (memcmp(block.data(), control_block.data(), block.size()) != 0)
		{
			throw tc::TestException("Failed: encrypt() operated on block when not initialized");
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_InitializeThrowsExceptionOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		// reference initialize call
		//cryptor.initialize(tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size()), tests[0].label.data(), tests[0].label.size(), false);
		
		auto label = tc::io::PaddingSource(0xab, tc::crypto::Sha2512Generator::kHashSize).pullData(0, tc::crypto::Sha2512Generator::kHashSize-2);
		auto empty_label = tc::ByteData();

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
			cryptor.initialize(empty_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey empty");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey empty");
		}

		try
		{
			cryptor.initialize(bad_modulus_size_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad modulus size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad modulus size");
		}

		try
		{
			cryptor.initialize(no_modulus_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a no modulus");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a no modulus");
		}

		try
		{
			cryptor.initialize(bad_privexp_size_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad private exponent size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad private exponent size");
		}

		try
		{
			cryptor.initialize(bad_pubexp_size_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a bad public exponent size");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a bad public exponent size");
		}

		try
		{
			cryptor.initialize(no_exponent_key, label.data(), label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where RsaKey had a neither public nor private exponents");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where RsaKey had a neither public nor private exponents");
		}

		try
		{
			cryptor.initialize(key, label.data(), label.size(), true);
			throw tc::TestException("Failed to throw ArgumentOutOfRangeException where isLabelDigested==true but the label isn't the correct size");
		}
		catch(const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where isLabelDigested==true but the label isn't the correct size");
		}

		try
		{
			cryptor.initialize(key, label.data(), 0, false);
			throw tc::TestException("Failed to throw ArgumentNullException where label != nullptr but label_size == 0");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where label != nullptr but label_size == 0");
		}

		try
		{
			cryptor.initialize(key, nullptr, label.size(), false);
			throw tc::TestException("Failed to throw ArgumentNullException where label == nullptr but label_size != 0");
		}
		catch(const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Failed to throw correct exception where label == nullptr but label_size != 0");
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_EncryptReturnsFalseOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_EncryptReturnsFalseOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		cryptor.initialize(tc::crypto::RsaPublicKey(tests[0].key_modulus.data(), tests[0].key_modulus.size()), tests[0].label.data(), tests[0].label.size(), false);

		tc::ByteData data = tc::ByteData(tests[0].enc_message.size());

		// reference encrypt call
		//cryptor.encrypt(data.data(), tests[0].dec_message.data(), tests[0].dec_message.size(), tests[0].enc_seed.data(), tests[0].enc_seed.size());

		bool result = false;

		result = cryptor.encrypt(nullptr, tests[0].dec_message.data(), tests[0].dec_message.size(), tests[0].enc_seed.data(), tests[0].enc_seed.size());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where block==nullptr"); // ArgumentNullException
		}

		result = cryptor.encrypt(data.data(), nullptr, tests[0].dec_message.size(), tests[0].enc_seed.data(), tests[0].enc_seed.size());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where message==nullptr"); // ArgumentNullException
		}

		result = cryptor.encrypt(data.data(), tests[0].dec_message.data(), 0, tests[0].enc_seed.data(), tests[0].enc_seed.size());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where message_size==0"); // ArgumentOutOfRangeException
		}

		size_t max_message_size = tc::crypto::Rsa2048OaepSha2512Encryptor::kBlockSize - (2 * tc::crypto::Sha2512Generator::kHashSize) - 2;
		result = cryptor.encrypt(data.data(), tests[0].dec_message.data(), max_message_size+1, tests[0].enc_seed.data(), tests[0].enc_seed.size());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where message_size was too large to be encrypted in one RSA-OAEP block"); // ArgumentOutOfRangeException
		}

		result = cryptor.encrypt(data.data(), tests[0].dec_message.data(), tests[0].dec_message.size(), tests[0].enc_seed.data(), 0);
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where seed_size!=HashCalculator::kHashSize"); // ArgumentOutOfRangeException
		}

		result = cryptor.encrypt(data.data(), tests[0].dec_message.data(), tests[0].dec_message.size(), nullptr, tests[0].enc_seed.size());
		if (result != false)
		{
			throw tc::TestException("encrypt() did not return false where seed==nullptr"); // ArgumentNullException
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

void crypto_Rsa2048OaepSha2512Encryptor_TestClass::test_DecryptReturnsFalseOnBadInput()
{
	TestResult test_result;
	test_result.test_name = "test_DecryptReturnsFalseOnBadInput";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{	
		// create tests
		std::vector<RsaOaepUtil::TestVector> tests;
		RsaOaepUtil::generateRsaOaepTestVectors_Custom(tests, 2048, RsaOaepUtil::SHA512);

		tc::crypto::Rsa2048OaepSha2512Encryptor cryptor;

		cryptor.initialize(tc::crypto::RsaPrivateKey(tests[0].key_modulus.data(), tests[0].key_modulus.size(), tests[0].key_private_exponent.data(), tests[0].key_private_exponent.size()), tests[0].label.data(), tests[0].label.size(), false);

		tc::ByteData data = tc::ByteData(tests[0].dec_message.size());
		size_t message_size = 0;

		// reference encrypt call
		//cryptor.decrypt(data.data(), message_size, data.size(), tests[0].enc_message.data());

		bool result = false;

		result = cryptor.decrypt(nullptr, message_size, data.size(), tests[0].enc_message.data());
		if (result != false)
		{
			throw tc::TestException("decrypt() did not return false where message==nullptr"); // ArgumentNullException
		}

		result = cryptor.decrypt(data.data(), message_size, 0, tests[0].enc_message.data());
		if (result != false)
		{
			throw tc::TestException("decrypt() did not return false where message_capacity==0"); // ArgumentOutOfRangeException
		}

		result = cryptor.decrypt(data.data(), message_size, data.size(), nullptr);
		if (result != false)
		{
			throw tc::TestException("decrypt() did not return false where block==nullptr"); // ArgumentNullException
		}

		result = cryptor.decrypt(data.data(), message_size, tests[0].dec_message.size()-1, tests[0].enc_message.data());
		if (result != false)
		{
			throw tc::TestException("decrypt() did not return false where message_capacity was not large enough"); // ArgumentOutOfRangeException
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