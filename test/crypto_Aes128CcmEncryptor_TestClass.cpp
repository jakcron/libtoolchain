#include <fmt/core.h>

#include <mbedtls/aes.h>
#include <mbedtls/ccm.h>

#include "crypto_Aes128CcmEncryptor_TestClass.h"

#include <tc/Exception.h>
#include <tc/crypto/Aes128CcmEncryptor.h>
#include <tc/cli/FormatUtil.h>

#include <tc/io/PaddingSource.h>

void crypto_Aes128CcmEncryptor_TestClass::runAllTests(void)
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] START\n");
	test_Constants();
	test_UseClassEnc();
	//test_UseClassDec();
	//test_UseUtilFuncEnc();
	//test_UseUtilFuncDec();

	//test_DoesNothingWhenNotInit();
	//test_InitializeThrowsExceptionOnBadInput();
	//test_EncryptThrowsExceptionOnBadInput();
	//test_DecryptThrowsExceptionOnBadInput();
	fmt::print("[tc::crypto::Aes128CcmEncryptor] END\n");
}

void crypto_Aes128CcmEncryptor_TestClass::test_Constants()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_Constants : ");
	try
	{
		// check block size
		static const size_t kExpectedBlockSize = 16;
		if (tc::crypto::Aes128CcmEncryptor::kBlockSize != kExpectedBlockSize)
		{
			throw tc::Exception(fmt::format("kBlockSize had value {:d} (expected {:d})", tc::crypto::Aes128CcmEncryptor::kBlockSize, kExpectedBlockSize));
		}

		// check key size
		static const size_t kExpectedKeySize = 16;
		if (tc::crypto::Aes128CcmEncryptor::kKeySize != kExpectedKeySize)
		{
			throw tc::Exception(fmt::format("kKeySize had value {:d} (expected {:d})", tc::crypto::Aes128CcmEncryptor::kKeySize, kExpectedKeySize));
		}

		fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_UseClassEnc()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_UseClassEnc : ");
	try
	{
		// create tests
		std::vector<TestCase> tests;
		util_Setup_TestCases(tests);

		tc::crypto::Aes128CcmEncryptor cryptor;

		for (auto test = tests.begin(); test != tests.end(); test++)
		{
			tc::ByteData payload = tc::ByteData(test->plaintext.size());	
			tc::ByteData mac = tc::ByteData(test->mac.size());

			// initialize key
			cryptor.initialize(test->key.data(), test->key.size());
			
			// clear data
			memset(payload.data(), 0xff, payload.size());

			// encrypt data
			cryptor.encrypt(payload.data(), test->plaintext.data(), payload.size(), test->nonce.data(), test->nonce.size(), test->aad.data(), test->aad.size(), mac.data(), mac.size());

			// validate cipher text
			if (memcmp(payload.data(), test->ciphertext.data(), payload.size()) != 0)
			{
				throw tc::Exception(fmt::format("Test \"{:s}\" Failed: Ciphertext {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(payload, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "")));
			}

			// validate mac
			if (memcmp(mac.data(), test->mac.data(), mac.size()) != 0)
			{
				throw tc::Exception(fmt::format("Test \"{:s}\" Failed: MAC {:s} (expected {:s})", test->test_name, tc::cli::FormatUtil::formatBytesAsString(mac, true, ""), tc::cli::FormatUtil::formatBytesAsString(test->mac, true, "")));
			}
		}

		fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}
/*
void crypto_Aes128CcmEncryptor_TestClass::test_UseClassDec()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_UseClassDec : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes128CcmEncryptor cryptor;

			for (auto test = tests.begin(); test != tests.end(); test++)
			{
				tc::ByteData data = tc::ByteData(test->plaintext.size());
				
				// initialize key
				cryptor.initialize(test->key.data(), test->key.size(), test->iv.data(), test->iv.size());
				
				// clear data
				memset(data.data(), 0xff, data.size());

				// decrypt data
				cryptor.decrypt(data.data(), test->ciphertext.data(), data.size());

				// test plain text			
				if (memcmp(data.data(), test->plaintext.data(), data.size()) != 0)
				{
					ss << "Test \"" << test->test_name << "\" Failed: " << tc::cli::FormatUtil::formatBytesAsString(data, true, "") << " (expected " << tc::cli::FormatUtil::formatBytesAsString(test->plaintext, true, "");
					throw tc::Exception(ss.str());
				}
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_UseUtilFuncEnc()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_UseUtilFuncEnc : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			for (auto test = tests.begin(); test != tests.end(); test++)
			{
				tc::ByteData data = tc::ByteData(test->plaintext.size());	

				// clear data
				memset(data.data(), 0xff, data.size());

				// encrypt data
				tc::crypto::EncryptAes128Ccm(data.data(), test->plaintext.data(), data.size(), test->key.data(), test->key.size(), test->iv.data(), test->iv.size());
				
				// validate cipher text
				if (memcmp(data.data(), test->ciphertext.data(), data.size()) != 0)
				{
					ss << "Test \"" << test->test_name << "\" Failed: " << tc::cli::FormatUtil::formatBytesAsString(data, true, "") << " (expected " << tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "");
					throw tc::Exception(ss.str());
				}
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_UseUtilFuncDec()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_UseUtilFuncDec : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			for (auto test = tests.begin(); test != tests.end(); test++)
			{
				tc::ByteData data = tc::ByteData(test->plaintext.size());
				
				// clear data
				memset(data.data(), 0xff, data.size());

				// decrypt data
				tc::crypto::DecryptAes128Ccm(data.data(), test->ciphertext.data(), data.size(), test->key.data(), test->key.size(), test->iv.data(), test->iv.size());

				// test plain text			
				if (memcmp(data.data(), test->plaintext.data(), data.size()) != 0)
				{
					ss << "Test \"" << test->test_name << "\" Failed: " << tc::cli::FormatUtil::formatBytesAsString(data, true, "") << " (expected " << tc::cli::FormatUtil::formatBytesAsString(test->plaintext, true, "");
					throw tc::Exception(ss.str());
				}
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_DoesNothingWhenNotInit()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_DoesNothingWhenNotInit : ");
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
				throw tc::Exception(ss.str());
			}

			// try to encrypt without calling initialize()
			cryptor.encrypt(data.data(), data.data(), data.size());

			// test plain text			
			if (memcmp(data.data(), control_data.data(), data.size()) != 0)
			{
				ss << "Failed: encrypt() operated on data when not initialized";
				throw tc::Exception(ss.str());
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_InitializeThrowsExceptionOnBadInput()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_InitializeThrowsExceptionOnBadInput : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes128CcmEncryptor cryptor;

			try {
				cryptor.initialize(nullptr, tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());
				throw tc::Exception("Failed to throw ArgumentNullException where key==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), 0, tests[0].iv.data(), tests[0].iv.size());
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where key_size==0");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize-1, tests[0].iv.data(), tests[0].iv.size());
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where key_size==tc::crypto::Aes128CcmEncryptor::kKeySize-1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tc::crypto::Aes128CcmEncryptor::kKeySize+1, tests[0].iv.data(), tests[0].iv.size());
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where key_size==tc::crypto::Aes128CcmEncryptor::kKeySize+1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tests[0].key.size(), nullptr, tests[0].iv.size());
				throw tc::Exception("Failed to throw ArgumentNullException where iv==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), 0);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where iv_size==0");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize-1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where iv_size==kBlockSize+1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_EncryptThrowsExceptionOnBadInput()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_EncryptThrowsExceptionOnBadInput : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes128CcmEncryptor cryptor;

			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

			tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

			// reference encrypt call
			//cryptor.encrypt(data.data(), tests[0].plaintext.data(), data.size());

			try {
				cryptor.encrypt(nullptr, tests[0].plaintext.data(), data.size());
				throw tc::Exception("Failed to throw ArgumentNullException where dst==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.encrypt(data.data(), nullptr, data.size());
				throw tc::Exception("Failed to throw ArgumentNullException where src==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.encrypt(data.data(), tests[0].plaintext.data(), 0);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==0");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.encrypt(data.data(), tests[0].plaintext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize-1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.encrypt(data.data(), tests[0].plaintext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize+1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void crypto_Aes128CcmEncryptor_TestClass::test_DecryptThrowsExceptionOnBadInput()
{
	fmt::print("[tc::crypto::Aes128CcmEncryptor] test_DecryptThrowsExceptionOnBadInput : ");
	try
	{
			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes128CcmEncryptor cryptor;

			cryptor.initialize(tests[0].key.data(), tests[0].key.size(), tests[0].iv.data(), tests[0].iv.size());

			tc::ByteData data = tc::ByteData(tests[0].plaintext.size());

			// reference decrypt call
			//cryptor.decrypt(data.data(), tests[0].ciphertext.data(), data.size());

			try {
				cryptor.decrypt(nullptr, tests[0].ciphertext.data(), data.size());
				throw tc::Exception("Failed to throw ArgumentNullException where dst==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.decrypt(data.data(), nullptr, data.size());
				throw tc::Exception("Failed to throw ArgumentNullException where src==nullptr");
			} catch(const tc::ArgumentNullException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.decrypt(data.data(), tests[0].ciphertext.data(), 0);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==0");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.decrypt(data.data(), tests[0].ciphertext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize-1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize-1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			try {
				cryptor.decrypt(data.data(), tests[0].ciphertext.data(), tc::crypto::Aes128CcmEncryptor::kBlockSize+1);
				throw tc::Exception("Failed to throw ArgumentOutOfRangeException where size==tc::crypto::Aes128CcmEncryptor::kBlockSize+1");
			} catch(const tc::ArgumentOutOfRangeException&) {
				// all good if this was thrown.
			}

			fmt::print("PASS\n");
	}	
	catch (const tc::Exception& e)
	{
		fmt::print("FAIL ({:s})\n", e.error());
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}
*/

void crypto_Aes128CcmEncryptor_TestClass::util_Setup_TestCases(std::vector<crypto_Aes128CcmEncryptor_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	tc::ByteData base_key = tc::ByteData({0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f});
	tc::ByteData base_iv = tc::ByteData({0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b});
	tc::ByteData base_add = tc::ByteData({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13});
	tc::ByteData base_msg = tc::ByteData({0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37});

	static const size_t kTestNum = 3;

	static const size_t test_iv_size [kTestNum] = { 7, 8,  12 };
	static const size_t test_add_size[kTestNum] = { 8, 16, 20 };
	static const size_t test_msg_size[kTestNum] = { 4, 16, 24 };

	std::array<tc::ByteData, kTestNum> expected_mac = {
		tc::ByteData({0x4d, 0xac, 0x25, 0x5d}),
		tc::ByteData({0x1f, 0xc6, 0x4f, 0xbf, 0xac, 0xcd}),
		tc::ByteData({0x48, 0x43, 0x92, 0xfb, 0xc1, 0xb0, 0x99, 0x51})
	};
	std::array<tc::ByteData, kTestNum> expected_ciphertext = {
		tc::ByteData({0x71, 0x62, 0x01, 0x5b}),
		tc::ByteData({0xd2, 0xa1, 0xf0, 0xe0, 0x51, 0xea, 0x5f, 0x62, 0x08, 0x1a, 0x77, 0x92, 0x07, 0x3d, 0x59, 0x3d}),
		tc::ByteData({0xe3, 0xb2, 0x01, 0xa9, 0xf5, 0xb7, 0x1a, 0x7a, 0x9b, 0x1c, 0xea, 0xec, 0xcd, 0x97, 0xe7, 0x0b, 0x61, 0x76, 0xaa, 0xd9, 0xa4, 0x42, 0x8a, 0xa5})
	};

	
	tmp.test_name = "DevCciInitialData";
	tmp.key = tc::ByteData(16);
	tmp.nonce = tc::ByteData(12);
	tmp.aad = tc::ByteData();
	tmp.mac = tc::ByteData({0xAD, 0x88, 0xAC, 0x41, 0xA2, 0xB1, 0x5E, 0x8F, 0x66, 0x9C, 0x97, 0xE5, 0xE1, 0x5E, 0xA3, 0xEB});
	tmp.plaintext = tc::ByteData({0x6E, 0xC7, 0x5F, 0xB2, 0xE2, 0xB4, 0x87, 0x46, 0x1E, 0xDD, 0xCB, 0xB8, 0x97, 0x11, 0x92, 0xBA});
	tmp.ciphertext = tc::ByteData(16);
	test_cases.push_back(tmp);


	for (size_t i = 0; i < kTestNum; i++)
	{
		tmp.test_name = fmt::format("Test {:d}", i);

		tmp.key = base_key;
		tmp.nonce = tc::ByteData(base_iv.data(), test_iv_size[i]);
		tmp.aad = tc::ByteData(base_add.data(), test_add_size[i]);
		tmp.mac = expected_mac[i];
		tmp.plaintext = tc::ByteData(base_msg.data(), test_msg_size[i]);
		tmp.ciphertext = expected_ciphertext[i];
		test_cases.push_back(tmp);
	}

	// Test vectors taken from NIST SP 800-38A
	/*
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");

	tmp.test_name  = "Test 1";
	tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
	tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7649abac8119b246cee98e9b12e9197d");
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 2";
	tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("7649ABAC8119B246CEE98E9B12E9197D");
	tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5086cb9b507219ee95db113a917678b2");
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 3";
	tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("5086CB9B507219EE95DB113A917678B2");
	tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("73bed6b8e3c1743b7116e69e22229516");
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 4";
	tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("73BED6B8E3C1743B7116E69E22229516");
	tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3ff1caa1681fac09120eca307586e1a7");
	test_cases.push_back(tmp);

	tmp.test_name  = "Tests 1-4";
	tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
	tmp.plaintext  = tc::ByteData(test_cases[0].plaintext.size() * 4, false);
	tmp.ciphertext = tc::ByteData(tmp.plaintext.size(), false);
	for (size_t i = 0; i < 4; i++)
	{
		memcpy(tmp.plaintext.data() + (i * 0x10), test_cases[i].plaintext.data(), test_cases[i].plaintext.size());
		memcpy(tmp.ciphertext.data() + (i * 0x10), test_cases[i].ciphertext.data(), test_cases[i].ciphertext.size());
	}
	test_cases.push_back(tmp);
	*/
}