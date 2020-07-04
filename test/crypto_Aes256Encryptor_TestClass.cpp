#include <iostream>
#include <sstream>
#include <fstream>

#include <mbedtls/aes.h>

#include "crypto_Aes256Encryptor_TestClass.h"

#include <tc/Exception.h>
#include <tc/crypto/AesEncryptor.h>
#include <tc/cli/FormatUtil.h>

void crypto_Aes256Encryptor_TestClass::runAllTests(void)
{
	std::cout << "[tc::crypto::Aes256Encryptor] START" << std::endl;
	test_Constants();
	test_UseClassEnc();
	test_UseClassDec();
	std::cout << "[tc::crypto::Aes256Encryptor] END" << std::endl;
}

void crypto_Aes256Encryptor_TestClass::test_Constants()
{
	std::cout << "[tc::crypto::Aes256Encryptor] test_Constants : " << std::flush;
	try
	{
		try 
		{
			std::stringstream ss;

			// check block size
			static const size_t kExpectedBlockSize = 16;
			if (tc::crypto::Aes256Encryptor::kBlockSize != kExpectedBlockSize)
			{
				ss << "kBlockSize had value " << std::dec << tc::crypto::Aes256Encryptor::kBlockSize << " (expected " << kExpectedBlockSize << ")";
				throw tc::Exception(ss.str());
			}

			// check key size
			static const size_t kExpectedKeySize = 32;
			if (tc::crypto::Aes256Encryptor::kKeySize != kExpectedKeySize)
			{
				ss << "kKeySize had value " << std::dec << tc::crypto::Aes256Encryptor::kKeySize << " (expected " << kExpectedKeySize << ")";
				throw tc::Exception(ss.str());
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void crypto_Aes256Encryptor_TestClass::test_UseClassEnc()
{
	std::cout << "[tc::crypto::Aes256Encryptor] test_UseClassEnc : " << std::flush;
	try
	{
		try 
		{
			std::stringstream ss;

			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes256Encryptor cryptor;

			for (auto test = tests.begin(); test != tests.end(); test++)
			{
				tc::ByteData data = tc::ByteData(test->plaintext.size());	

				// initialize key
				cryptor.initialize(test->key.data(), test->key.size());
				
				// clear data
				memset(data.data(), 0xff, data.size());

				// encrypt data
				cryptor.encrypt(data.data(), test->plaintext.data());
				
				// validate cipher text
				if (memcmp(data.data(), test->ciphertext.data(), data.size()) != 0)
				{
					ss << "Test \"" << test->test_name << "\" Failed: " << tc::cli::FormatUtil::formatBytesAsString(data, true, "") << " (expected " << tc::cli::FormatUtil::formatBytesAsString(test->ciphertext, true, "");
					throw tc::Exception(ss.str());
				}
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void crypto_Aes256Encryptor_TestClass::test_UseClassDec()
{
	std::cout << "[tc::crypto::Aes256Encryptor] test_UseClassDec : " << std::flush;
	try
	{
		try 
		{
			std::stringstream ss;

			// create tests
			std::vector<TestCase> tests;
			util_Setup_TestCases(tests);

			tc::crypto::Aes256Encryptor cryptor;

			for (auto test = tests.begin(); test != tests.end(); test++)
			{
				tc::ByteData data = tc::ByteData(test->plaintext.size());
				
				// initialize key
				cryptor.initialize(test->key.data(), test->key.size());
				
				// clear data
				memset(data.data(), 0xff, data.size());

				// decrypt data
				cryptor.decrypt(data.data(), test->ciphertext.data());

				// test plain text			
				if (memcmp(data.data(), test->plaintext.data(), data.size()) != 0)
				{
					ss << "Test \"" << test->test_name << "\" Failed: " << tc::cli::FormatUtil::formatBytesAsString(data, true, "") << " (expected " << tc::cli::FormatUtil::formatBytesAsString(test->plaintext, true, "");
					throw tc::Exception(ss.str());
				}
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void crypto_Aes256Encryptor_TestClass::util_Setup_TestCases(std::vector<crypto_Aes256Encryptor_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// Variable Key Known Answer Tests
	// taken from "ecb_vk.txt" from https://csrc.nist.gov/archive/aes/rijndael/rijndael-vals.zip
	tmp.plaintext = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000000");

	tmp.test_name = "Variable Key Known Answer Test 1";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("8000000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E35A6DCB19B201A01EBCFA8AA22B5759");

	tmp.test_name = "Variable Key Known Answer Test 2";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("4000000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5075C2405B76F22F553488CAE47CE90B");

	tmp.test_name = "Variable Key Known Answer Test 3";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("2000000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("49DF95D844A0145A7DE01C91793302D3");

	tmp.test_name = "Variable Key Known Answer Test 4";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("1000000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7396D778E940B8418A86120E5F421FE");

	tmp.test_name = "Variable Key Known Answer Test 5";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0800000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("05F535C36FCEDE4657BE37F4087DB1EF");

	tmp.test_name = "Variable Key Known Answer Test 6";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0400000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D0C1DDDD10DA777C68AB36AF51F2C204");

	tmp.test_name = "Variable Key Known Answer Test 7";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0200000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1C55FB811B5C6464C4E5DE1535A75514");

	tmp.test_name = "Variable Key Known Answer Test 8";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0100000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("52917F3AE957D5230D3A2AF57C7B5A71");

	tmp.test_name = "Variable Key Known Answer Test 9";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0080000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C6E3D5501752DD5E9AEF086D6B45D705");

	tmp.test_name = "Variable Key Known Answer Test 10";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0040000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A24A9C7AF1D9B1E17E1C9A3E711B3FA7");

	tmp.test_name = "Variable Key Known Answer Test 11";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0020000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B881ECA724A6D43DBC6B96F6F59A0D20");

	tmp.test_name = "Variable Key Known Answer Test 12";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0010000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EC524D9A24DFFF2A9639879B83B8E137");

	tmp.test_name = "Variable Key Known Answer Test 13";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0008000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("34C4F345F5466215A037F443635D6F75");

	tmp.test_name = "Variable Key Known Answer Test 14";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0004000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5BA5055BEDB8895F672E29F2EB5A355D");

	tmp.test_name = "Variable Key Known Answer Test 15";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0002000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B3F692AA3A435259EBBEF9B51AD1E08D");

	tmp.test_name = "Variable Key Known Answer Test 16";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0001000000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("414FEB4376F2C64A5D2FBB2ED531BA7D");

	tmp.test_name = "Variable Key Known Answer Test 17";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000800000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A20D519E3BCA3303F07E81719F61605E");

	tmp.test_name = "Variable Key Known Answer Test 18";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000400000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A08D10E520AF811F45BD60A2DC0DC4B1");

	tmp.test_name = "Variable Key Known Answer Test 19";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000200000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B06893A8C563C430E6F3858826EFBBE4");

	tmp.test_name = "Variable Key Known Answer Test 20";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000100000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FFEE26AE2D3929C6BD9C6BEDFF84409");

	tmp.test_name = "Variable Key Known Answer Test 21";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000080000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D0F5E906ED77801FC0EF53EDC5F9E2B");

	tmp.test_name = "Variable Key Known Answer Test 22";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000040000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8B6EC00119AD8B026DCE56EA7DEFE930");

	tmp.test_name = "Variable Key Known Answer Test 23";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000020000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("69026591D43363EE9D83B5007F0B484E");

	tmp.test_name = "Variable Key Known Answer Test 24";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000010000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("27135D86950C6A2F86872706279A4761");

	tmp.test_name = "Variable Key Known Answer Test 25";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000008000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("35E6DB8723F281DA410C3AC8535ED77C");

	tmp.test_name = "Variable Key Known Answer Test 26";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000004000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("57427CF214B8C28E4BBF487CCB8D0E09");

	tmp.test_name = "Variable Key Known Answer Test 27";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000002000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6DF01BF56E5131AC87F96E99CAB86367");

	tmp.test_name = "Variable Key Known Answer Test 28";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000001000000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3856C5B55790B768BBF7D43031579BCF");

	tmp.test_name = "Variable Key Known Answer Test 29";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000800000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1E6ED8FB7C15BC4D2F63BA7037ED44D0");

	tmp.test_name = "Variable Key Known Answer Test 30";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000400000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E1B2ED6CD8D93D455534E401156D4BCF");

	tmp.test_name = "Variable Key Known Answer Test 31";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000200000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EFBCCA5BDFDAD10E875F02336212CE36");

	tmp.test_name = "Variable Key Known Answer Test 32";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000100000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0B777F02FD18DCE2646DCFE868DFAFAD");

	tmp.test_name = "Variable Key Known Answer Test 33";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000080000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C8A104B5693D1B14F5BF1F10100BF508");

	tmp.test_name = "Variable Key Known Answer Test 34";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000040000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4CCE6615244AFCB38408FECE219962EA");

	tmp.test_name = "Variable Key Known Answer Test 35";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000020000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F99E7845D3A255B394C9C050CBA258B1");

	tmp.test_name = "Variable Key Known Answer Test 36";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000010000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B4AFBB787F9BCFB7B55FDF447F611295");

	tmp.test_name = "Variable Key Known Answer Test 37";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000008000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AE1C426A697FAF2808B7EF6ADDB5C020");

	tmp.test_name = "Variable Key Known Answer Test 38";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000004000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7572F92811A85B9BDD38DEAD9945BCAE");

	tmp.test_name = "Variable Key Known Answer Test 39";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000002000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("71BC7AA46E43FB95A181527D9F6A360F");

	tmp.test_name = "Variable Key Known Answer Test 40";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000001000000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5542EF2923066F1EC8F546DD0D8E7CA8");

	tmp.test_name = "Variable Key Known Answer Test 41";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000800000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B92317C7D623790B748FDD7EFC42422");

	tmp.test_name = "Variable Key Known Answer Test 42";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000400000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FE7C097E899C71EF045360F8D6C25CF");

	tmp.test_name = "Variable Key Known Answer Test 43";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000200000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4ECE7EE107D0264D04693151C25B9DF6");

	tmp.test_name = "Variable Key Known Answer Test 44";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000100000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FD6AE687CBFCA9E301045888D3BB9605");

	tmp.test_name = "Variable Key Known Answer Test 45";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000080000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("476B579C8556C7254424902CC1D6D36E");

	tmp.test_name = "Variable Key Known Answer Test 46";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000040000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4133CBCDFDD6B8860A1FC18665D6D71B");

	tmp.test_name = "Variable Key Known Answer Test 47";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000020000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3B36EC2664798C108B816812C65DFDC7");

	tmp.test_name = "Variable Key Known Answer Test 48";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000010000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("364E20A234FEA385D48DC5A09C9E70CF");

	tmp.test_name = "Variable Key Known Answer Test 49";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000008000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4A4BA25969DE3F5EE5642C71AAD0EFD1");

	tmp.test_name = "Variable Key Known Answer Test 50";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000004000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E42CBAAE43297F67A76C1C501BB79E36");

	tmp.test_name = "Variable Key Known Answer Test 51";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000002000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("23CEDEDA4C15B4C037E8C61492217937");

	tmp.test_name = "Variable Key Known Answer Test 52";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000001000000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A1719147A1F4A1A1180BD16E8593DCDE");

	tmp.test_name = "Variable Key Known Answer Test 53";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000800000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AB82337E9FB0EC60D1F25A1D0014192C");

	tmp.test_name = "Variable Key Known Answer Test 54";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000400000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74BF2D8FC5A8388DF1A3A4D7D33FC164");

	tmp.test_name = "Variable Key Known Answer Test 55";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000200000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D5B493317E6FBC6FFFD664B3C491368A");

	tmp.test_name = "Variable Key Known Answer Test 56";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000100000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BA767381586DA56A2A8D503D5F7ADA0B");

	tmp.test_name = "Variable Key Known Answer Test 57";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000080000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E8E6BC57DFE9CCADB0DECABF4E5CF91F");

	tmp.test_name = "Variable Key Known Answer Test 58";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000040000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3C8E5A5CDC9CEED90815D1F84BB2998C");

	tmp.test_name = "Variable Key Known Answer Test 59";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000020000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("283843020BA38F056001B2FD585F7CC9");

	tmp.test_name = "Variable Key Known Answer Test 60";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000010000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D8ADC7426F623ECE8741A70621D28870");

	tmp.test_name = "Variable Key Known Answer Test 61";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000008000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D7C5C215592D06F00E6A80DA69A28EA9");

	tmp.test_name = "Variable Key Known Answer Test 62";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000004000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("52CF6FA433C3C870CAC70190358F7F16");

	tmp.test_name = "Variable Key Known Answer Test 63";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000002000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F63D442A584DA71786ADEC9F3346DF75");

	tmp.test_name = "Variable Key Known Answer Test 64";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000001000000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("549078F4B0CA7079B45F9A5ADAFAFD99");

	tmp.test_name = "Variable Key Known Answer Test 65";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000800000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F2A5986EE4E9984BE2BAFB79EA8152FA");

	tmp.test_name = "Variable Key Known Answer Test 66";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000400000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8A74535017B4DB2776668A1FAE64384C");

	tmp.test_name = "Variable Key Known Answer Test 67";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000200000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E613342F57A97FD95DC088711A5D0ECD");

	tmp.test_name = "Variable Key Known Answer Test 68";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000100000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3FFAEBF6B22CF1DC82AE17CD48175B01");

	tmp.test_name = "Variable Key Known Answer Test 69";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000080000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BAFD52EFA15C248CCBF9757735E6B1CE");

	tmp.test_name = "Variable Key Known Answer Test 70";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000040000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7AF94BC018D9DDD4539D2DD1C6F4000F");

	tmp.test_name = "Variable Key Known Answer Test 71";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000020000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FE177AD61CA0FDB281086FBA8FE76803");

	tmp.test_name = "Variable Key Known Answer Test 72";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000010000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74DBEA15E2E9285BAD163D7D534251B6");

	tmp.test_name = "Variable Key Known Answer Test 73";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000008000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("23DD21331B3A92F200FE56FF050FFE74");

	tmp.test_name = "Variable Key Known Answer Test 74";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000004000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A69C5AA34AB20A858CAFA766EACED6D8");

	tmp.test_name = "Variable Key Known Answer Test 75";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000002000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3F72BB4DF2A4F941A4A09CB78F04B97A");

	tmp.test_name = "Variable Key Known Answer Test 76";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000001000000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("72CC43577E1FD5FD14622D24D97FCDCC");

	tmp.test_name = "Variable Key Known Answer Test 77";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000800000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D83AF8EBE93E0B6B99CAFADE224937D1");

	tmp.test_name = "Variable Key Known Answer Test 78";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000400000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("44042329128D56CAA8D084C8BD769D1E");

	tmp.test_name = "Variable Key Known Answer Test 79";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000200000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("14102D72290DE4F2C430ADD1ED64BA1D");

	tmp.test_name = "Variable Key Known Answer Test 80";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000100000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("449124097B1ECD0AE7065206DF06F03C");

	tmp.test_name = "Variable Key Known Answer Test 81";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000080000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D060A99F8CC153A42E11E5F97BD7584A");

	tmp.test_name = "Variable Key Known Answer Test 82";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000040000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("65605B3EA9261488D53E48602ADEA299");

	tmp.test_name = "Variable Key Known Answer Test 83";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000020000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C5E5CAD7A208DE8EA6BE049EFE5C7346");

	tmp.test_name = "Variable Key Known Answer Test 84";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000010000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4C280C46D2181646048DD5BC0C0831A5");

	tmp.test_name = "Variable Key Known Answer Test 85";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000008000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5DD65CF37F2A0929559AABAFDA08E730");

	tmp.test_name = "Variable Key Known Answer Test 86";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000004000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("31F2335CAAF264172F69A693225E6D22");

	tmp.test_name = "Variable Key Known Answer Test 87";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000002000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3E28B35F99A72662590DA96426DD377F");

	tmp.test_name = "Variable Key Known Answer Test 88";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000001000000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("570F40F5D7B20441486578ED344343BE");

	tmp.test_name = "Variable Key Known Answer Test 89";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000800000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C54308AD1C9E3B19F8B7417873045A8C");

	tmp.test_name = "Variable Key Known Answer Test 90";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000400000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CBF335E39CE13ADE2B696179E8FD0CE1");

	tmp.test_name = "Variable Key Known Answer Test 91";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000200000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9C2FBF422355D8293083D51F4A3C18A9");

	tmp.test_name = "Variable Key Known Answer Test 92";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000100000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5ED8B5A31ECEFAB16C9AA6986DA67BCE");

	tmp.test_name = "Variable Key Known Answer Test 93";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000080000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("627815DCFC814ABC75900041B1DD7B59");

	tmp.test_name = "Variable Key Known Answer Test 94";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000040000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9EF3E82A50A59F166260494F7A7F2CC3");

	tmp.test_name = "Variable Key Known Answer Test 95";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000020000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("878CD0D8D920888B5935D6C351128737");

	tmp.test_name = "Variable Key Known Answer Test 96";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000010000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E44429474D6FC3084EB2A6B8B46AF754");

	tmp.test_name = "Variable Key Known Answer Test 97";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000008000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EBAACF9641D54E1FB18D0A2BE4F19BE5");

	tmp.test_name = "Variable Key Known Answer Test 98";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000004000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("13B3BF497CEE780E123C7E193DEA3A01");

	tmp.test_name = "Variable Key Known Answer Test 99";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000002000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E8F381DE00A41161F0DF03B4155BFD4");

	tmp.test_name = "Variable Key Known Answer Test 100";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000001000000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("35E4F29BBA2BAE01144910783C3FEF49");

	tmp.test_name = "Variable Key Known Answer Test 101";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000800000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("55B17BD66788CEAC366398A31F289FFB");

	tmp.test_name = "Variable Key Known Answer Test 102";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000400000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("11341F56C0D6D1008D28741DAA7679CE");

	tmp.test_name = "Variable Key Known Answer Test 103";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000200000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4DF7253DF421D83358BDBE924745D98C");

	tmp.test_name = "Variable Key Known Answer Test 104";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000100000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BAE2EE651116D93EDC8E83B5F3347BE1");

	tmp.test_name = "Variable Key Known Answer Test 105";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000080000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F9721ABD06709157183AF3965A659D9D");

	tmp.test_name = "Variable Key Known Answer Test 106";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000040000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("19A1C252A613FE2860A4AE6D75CE6FA3");

	tmp.test_name = "Variable Key Known Answer Test 107";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000020000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B5DDB2F5D9752C949FBDE3FFF5556C6E");

	tmp.test_name = "Variable Key Known Answer Test 108";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000010000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("81B044FCFFC78ECCFCD171AAD0405C66");

	tmp.test_name = "Variable Key Known Answer Test 109";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000008000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C640566D3C06020EB2C42F1D62E56A9B");

	tmp.test_name = "Variable Key Known Answer Test 110";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000004000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EA6C4BCF425291679FDFFD26A424FBCC");

	tmp.test_name = "Variable Key Known Answer Test 111";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000002000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("57F6901465D9440D9F15EE2CBA5A4090");

	tmp.test_name = "Variable Key Known Answer Test 112";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000001000000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FBCFA74CADC7406260F63D96C8AAB6B1");

	tmp.test_name = "Variable Key Known Answer Test 113";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000800000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DFF4F096CEA211D4BBDACA033D0EC7D1");

	tmp.test_name = "Variable Key Known Answer Test 114";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000400000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1EE5190D551F0F42F675227A381296A9");

	tmp.test_name = "Variable Key Known Answer Test 115";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000200000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F98E1905012E580F097623C10B93054F");

	tmp.test_name = "Variable Key Known Answer Test 116";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000100000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7D43743D21DD3C9F168C86856558B9A");

	tmp.test_name = "Variable Key Known Answer Test 117";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000080000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("632A9DDA730DAB67593C5D08D8AC1059");

	tmp.test_name = "Variable Key Known Answer Test 118";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000040000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E084317000715B9057BC9DE9F3AB6124");

	tmp.test_name = "Variable Key Known Answer Test 119";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000020000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("61F9EF33A0BB4E666C2ED99101919FAB");

	tmp.test_name = "Variable Key Known Answer Test 120";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000010000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6DC1D68A11834657D46703C22578D59A");

	tmp.test_name = "Variable Key Known Answer Test 121";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000008000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("53AC1548863D3D16F1D4DC7242E05F2C");

	tmp.test_name = "Variable Key Known Answer Test 122";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000004000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E82CD587A408306AD78CEAE0916B9F8C");

	tmp.test_name = "Variable Key Known Answer Test 123";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000002000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FD2D40EA6AD17A3A767F0A8600D6295");

	tmp.test_name = "Variable Key Known Answer Test 124";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000001000000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AD84CC8255ADB39DFCA23F92761AE7E9");

	tmp.test_name = "Variable Key Known Answer Test 125";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000800000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F4F20CF7D51BEE7DA024A2B11A7ECA0B");

	tmp.test_name = "Variable Key Known Answer Test 126";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000400000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5057691B85D9CE93A193214DB0A016B6");

	tmp.test_name = "Variable Key Known Answer Test 127";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000200000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0F58C960876390BDEF4BB6BE95CAA1EE");

	tmp.test_name = "Variable Key Known Answer Test 128";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000100000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9A3E66EEBC21BC0BD9430B341EF465FA");

	tmp.test_name = "Variable Key Known Answer Test 129";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000080000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("20415035F34B8BCBCB28ABF07F78F0D4");

	tmp.test_name = "Variable Key Known Answer Test 130";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000040000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AC89FC7BA10479EBF10DE65BCEF89B3C");

	tmp.test_name = "Variable Key Known Answer Test 131";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000020000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("068FA75A30BE443171AF3F6FEB1A20D2");

	tmp.test_name = "Variable Key Known Answer Test 132";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000010000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("50E02F213246C525A8C27700CA34B502");

	tmp.test_name = "Variable Key Known Answer Test 133";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000008000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("227DA47D5A0906DB3AB042BB0A695FB6");

	tmp.test_name = "Variable Key Known Answer Test 134";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000004000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8663AC30ED12514F1DE46777F4514BFC");

	tmp.test_name = "Variable Key Known Answer Test 135";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000002000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A987D4BC12E1DE9F4B6DF43567C34A8B");

	tmp.test_name = "Variable Key Known Answer Test 136";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000001000000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6D5A0370F599ACA605F63B04E5143D0C");

	tmp.test_name = "Variable Key Known Answer Test 137";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000800000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9809266E378B07B7AFDB3BAA97B7E442");

	tmp.test_name = "Variable Key Known Answer Test 138";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000400000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8F753252B30CCCACE12D9A301F4D5090");

	tmp.test_name = "Variable Key Known Answer Test 139";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000200000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("032465F6C0CE34D41962F561692A1AFF");

	tmp.test_name = "Variable Key Known Answer Test 140";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000100000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C50E9AD5BEB8F3B00821DD47FF8AC093");

	tmp.test_name = "Variable Key Known Answer Test 141";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000080000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9C6FEA3D46268D54A6829B2AD25BB276");

	tmp.test_name = "Variable Key Known Answer Test 142";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000040000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FD8575E87706F561343D7B3A41E044A");

	tmp.test_name = "Variable Key Known Answer Test 143";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000020000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BEE9BEB3739540D88CBCE77925F0A114");

	tmp.test_name = "Variable Key Known Answer Test 144";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000010000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D24EAEE7FFFBAC3D6F26C2DCE0DCDE28");

	tmp.test_name = "Variable Key Known Answer Test 145";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000008000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("47771A90398FF0F7FA821C2F8F5E1398");

	tmp.test_name = "Variable Key Known Answer Test 146";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000004000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4639741B6F84B135AD118C8249B64ED0");

	tmp.test_name = "Variable Key Known Answer Test 147";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000002000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8EE5505EC85567697A3306F250A27720");

	tmp.test_name = "Variable Key Known Answer Test 148";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000001000000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7C8A19AC1AEFBC5E0119D91A5F05D4C2");

	tmp.test_name = "Variable Key Known Answer Test 149";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000800000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5141B9B672E54773B672E3A6C424887B");

	tmp.test_name = "Variable Key Known Answer Test 150";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000400000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B5A2D3CD206653C6402F34FB0AE3613D");

	tmp.test_name = "Variable Key Known Answer Test 151";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000200000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0F5BD9408738231D114B0A82753279A3");

	tmp.test_name = "Variable Key Known Answer Test 152";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000100000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FEF033FF4268EA487FC74C5E43A45338");

	tmp.test_name = "Variable Key Known Answer Test 153";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000080000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A3EDC09DCD529B113910D904AD855581");

	tmp.test_name = "Variable Key Known Answer Test 154";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000040000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AB8FBB6F27A0AC7C55B59FDD36B72F1C");

	tmp.test_name = "Variable Key Known Answer Test 155";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000020000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EEA44D5ED4D769CC930CD83D8999EC46");

	tmp.test_name = "Variable Key Known Answer Test 156";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000010000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6972276803AE9AA7C6F431AB10979C34");

	tmp.test_name = "Variable Key Known Answer Test 157";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000008000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("86DEAA9F39244101818178474D7DBDE9");

	tmp.test_name = "Variable Key Known Answer Test 158";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000004000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("88C6B466EA361D662D8D08CBF181F4FE");

	tmp.test_name = "Variable Key Known Answer Test 159";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000002000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("91AB2C6B7C63FF59F7CBEEBF91B20B95");

	tmp.test_name = "Variable Key Known Answer Test 160";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000001000000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2DFE6C146AD5B3D8C3C1718F13B48E01");

	tmp.test_name = "Variable Key Known Answer Test 161";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000800000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C7CFF1623451711391A302EEC3584AAA");

	tmp.test_name = "Variable Key Known Answer Test 162";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000400000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("089FE845CC05011686C66019D18BE050");

	tmp.test_name = "Variable Key Known Answer Test 163";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000200000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("08C8410B9B427211A67124B0DCCEAD48");

	tmp.test_name = "Variable Key Known Answer Test 164";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000100000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8D91592F5566085254784606334D7629");

	tmp.test_name = "Variable Key Known Answer Test 165";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000080000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3298FEAAF2E1201D6299FF8846639C97");

	tmp.test_name = "Variable Key Known Answer Test 166";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000040000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C497CB9F0BDFE0EFC8C2F3F90760AA72");

	tmp.test_name = "Variable Key Known Answer Test 167";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000020000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2788AFD046E0309CBE4424690DA2AB89");

	tmp.test_name = "Variable Key Known Answer Test 168";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000010000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E9891707F25EF29FEE372890D4258982");

	tmp.test_name = "Variable Key Known Answer Test 169";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000008000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DB041D94A23D45D4D4DCED5A030CAF61");

	tmp.test_name = "Variable Key Known Answer Test 170";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000004000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FFAFDBF0ECB18DF9EA02C27077448E6D");

	tmp.test_name = "Variable Key Known Answer Test 171";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000002000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2DAAA42A7D0A1D3B0E4761D99CF2150A");

	tmp.test_name = "Variable Key Known Answer Test 172";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000001000000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3B7A54CB7CF30ABE263DD6ED5BFE8D63");

	tmp.test_name = "Variable Key Known Answer Test 173";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000800000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EEFA090174C590C448A55D43648F534A");

	tmp.test_name = "Variable Key Known Answer Test 174";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000400000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9E15798731ED42F43EA2740A691DA872");

	tmp.test_name = "Variable Key Known Answer Test 175";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000200000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("31FBD661540A5DEAAD1017CFD3909EC8");

	tmp.test_name = "Variable Key Known Answer Test 176";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000100000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CDA9AE05F224140E28CB951721B44D6A");

	tmp.test_name = "Variable Key Known Answer Test 177";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000080000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0C5BC512C60A1EAC3434EFB1A8FBB182");

	tmp.test_name = "Variable Key Known Answer Test 178";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000040000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AA863610DEEEEB62D045E87EA30B59B5");

	tmp.test_name = "Variable Key Known Answer Test 179";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000020000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6AC2448DE568D279C7EEBE1DF403920C");

	tmp.test_name = "Variable Key Known Answer Test 180";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000010000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E2011E3D292B26888AE801215FD0CB40");

	tmp.test_name = "Variable Key Known Answer Test 181";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000008000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E06F3E15EE3A61672D1C99BADE5B9DBE");

	tmp.test_name = "Variable Key Known Answer Test 182";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000004000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BB7027F0548CF6712CEB4C7A4B28E178");

	tmp.test_name = "Variable Key Known Answer Test 183";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000002000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("061EC21FB70FADBDF87C3BD2AE23825B");

	tmp.test_name = "Variable Key Known Answer Test 184";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000001000000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4C21F26FE94ABBAC381352375314C3EB");

	tmp.test_name = "Variable Key Known Answer Test 185";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000800000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F7CEE6DD99909C2B569EEDA61ED8942E");

	tmp.test_name = "Variable Key Known Answer Test 186";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000400000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CE98C4A876C65E4CCB261EBB1D9DF7F5");

	tmp.test_name = "Variable Key Known Answer Test 187";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000200000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A5491881CF833C3604ABC08044F402AC");

	tmp.test_name = "Variable Key Known Answer Test 188";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000100000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A1BA16E64CCCB3087D57A768507B0BFC");

	tmp.test_name = "Variable Key Known Answer Test 189";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000080000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D55951E202D2949EBD3BE43120C738BF");

	tmp.test_name = "Variable Key Known Answer Test 190";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000040000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EBB8E43069E69F450EFEC65DCD52B7FD");

	tmp.test_name = "Variable Key Known Answer Test 191";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000020000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2B292135663B4AA5ABFE9423D57E7EE9");

	tmp.test_name = "Variable Key Known Answer Test 192";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000010000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E91BF974B3BE3AD966249D8655292A85");

	tmp.test_name = "Variable Key Known Answer Test 193";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000008000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("384365998EAA9562236CC58F6ADF9610");

	tmp.test_name = "Variable Key Known Answer Test 194";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000004000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C2E997012AA3D4D8D359C9A947CBE69F");

	tmp.test_name = "Variable Key Known Answer Test 195";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000002000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F49421204148BA213BE87E2D5C22B0BF");

	tmp.test_name = "Variable Key Known Answer Test 196";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000001000000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("82ED0ED9953AA92E4DF30929CA65C00F");

	tmp.test_name = "Variable Key Known Answer Test 197";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000800000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("291EB1D11653C8479437C74A977F5106");

	tmp.test_name = "Variable Key Known Answer Test 198";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000400000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BCB997B1939B8983ABD550D6025683E3");

	tmp.test_name = "Variable Key Known Answer Test 199";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000200000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1FBA2592C6F489775CAADA71F9B983E9");

	tmp.test_name = "Variable Key Known Answer Test 200";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000100000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("969F66F217AF1A3DB9E41C1B29039824");

	tmp.test_name = "Variable Key Known Answer Test 201";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000080000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A54BB7D6B17E423AC0A7744C19073CB8");

	tmp.test_name = "Variable Key Known Answer Test 202";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000040000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B0AC6E6578D1021F47DCF9748A32EAD5");

	tmp.test_name = "Variable Key Known Answer Test 203";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000020000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B87B361C3B7B194C77A4358D4669153E");

	tmp.test_name = "Variable Key Known Answer Test 204";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000010000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("46A133847F96EAA8282A799DC8899D58");

	tmp.test_name = "Variable Key Known Answer Test 205";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000008000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2265EC3A9F2D5C9547A091CC8CFB18EA");

	tmp.test_name = "Variable Key Known Answer Test 206";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000004000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("54CBF3A6FC4FE56D426117AA1FFD1DDE");

	tmp.test_name = "Variable Key Known Answer Test 207";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000002000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5312877CCEAB6CFB0905394A370A8003");

	tmp.test_name = "Variable Key Known Answer Test 208";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000001000000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7190BD6EC613FE38B84ECFE28F702FE4");

	tmp.test_name = "Variable Key Known Answer Test 209";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000800000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1FA5B9CA89A43B04C05F0EF29EF68CD");

	tmp.test_name = "Variable Key Known Answer Test 210";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000400000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("808285751548ED934FD1056D2D9AE8BA");

	tmp.test_name = "Variable Key Known Answer Test 211";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000200000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2758DEF3E7B95A9AE89777BE64D5A6CF");

	tmp.test_name = "Variable Key Known Answer Test 212";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000100000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("07D81F87DB3E0ACC82B01E08FB22F3C1");

	tmp.test_name = "Variable Key Known Answer Test 213";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000080000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8DA250E5553D650711A75EE1CB4FD1C7");

	tmp.test_name = "Variable Key Known Answer Test 214";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000040000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A93D946BD0E87F32719DF5F158CEE669");

	tmp.test_name = "Variable Key Known Answer Test 215";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000020000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("03945236EC2A4D4EAF30B8ABEB54330D");

	tmp.test_name = "Variable Key Known Answer Test 216";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000010000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("11CC35301F24B79DDE31AEA2D1354F88");

	tmp.test_name = "Variable Key Known Answer Test 217";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000008000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E73715B3E8D9A290F44AE6FFBF247E5D");

	tmp.test_name = "Variable Key Known Answer Test 218";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000004000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7345E07732B71CB158BBF64CCA5C5B96");

	tmp.test_name = "Variable Key Known Answer Test 219";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000002000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E128F296D24705A1924FD9B70C4ED04");

	tmp.test_name = "Variable Key Known Answer Test 220";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000001000000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("95A789776F036783FBD330947083F54F");

	tmp.test_name = "Variable Key Known Answer Test 221";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000800000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("360DEC2533EA4AA2E3E54FD3DE2906EB");

	tmp.test_name = "Variable Key Known Answer Test 222";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000400000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E68EFD7FECF4D601EA22727BD764965B");

	tmp.test_name = "Variable Key Known Answer Test 223";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000200000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9065C64A8BFF44AC33EDBB611CF83D7B");

	tmp.test_name = "Variable Key Known Answer Test 224";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000100000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8F33C8DF2A7A51CE8090E8F123BC3723");

	tmp.test_name = "Variable Key Known Answer Test 225";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000080000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("807F391FFBA8291BA625623210F99018");

	tmp.test_name = "Variable Key Known Answer Test 226";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000040000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5E8B3F3A701522CE5CAA761C929D6292");

	tmp.test_name = "Variable Key Known Answer Test 227";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000020000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3BA404DC38735A78289E3809E8364835");

	tmp.test_name = "Variable Key Known Answer Test 228";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000010000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D23BEDBAD229F8305DC425B6B759DCC9");

	tmp.test_name = "Variable Key Known Answer Test 229";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000008000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("44880F21CF5913040AE376AEE2A10AD8");

	tmp.test_name = "Variable Key Known Answer Test 230";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000004000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9BC98E29D057C0E828C3B5CCE69256C1");

	tmp.test_name = "Variable Key Known Answer Test 231";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000002000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B293CC7A975DA141A68279368057CC41");

	tmp.test_name = "Variable Key Known Answer Test 232";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000001000000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8D60FB87ACD91385B313BE5F1D7BD30F");

	tmp.test_name = "Variable Key Known Answer Test 233";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000800000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2C8E56132D70291B303C48FDF75543CD");

	tmp.test_name = "Variable Key Known Answer Test 234";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000400000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1F80035B826791F6CE4E59B7DB1BB0D");

	tmp.test_name = "Variable Key Known Answer Test 235";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000200000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("42CE6224FC36469339A133DD08173BD4");

	tmp.test_name = "Variable Key Known Answer Test 236";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000100000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("61817155EA41BCBA2AF7F06AE7CBF585");

	tmp.test_name = "Variable Key Known Answer Test 237";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000080000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1923A9866068D2EF5FB77D57C3315B6");

	tmp.test_name = "Variable Key Known Answer Test 238";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000040000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B37CBDB5D719F49691CA968EF2E84140");

	tmp.test_name = "Variable Key Known Answer Test 239";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000020000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EC974E653A055D7F8F22171030F68E1D");

	tmp.test_name = "Variable Key Known Answer Test 240";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000010000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DDE5D3B9AAD9C32213BB3675A822499C");

	tmp.test_name = "Variable Key Known Answer Test 241";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000008000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D3B6E9216EA1AE57EB1C628A3C38AB78");

	tmp.test_name = "Variable Key Known Answer Test 242";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000004000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("82C99ECC69472B7E96324B042AE8B87A");

	tmp.test_name = "Variable Key Known Answer Test 243";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000002000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("97144DC5338C43600F84439C0AA0D147");

	tmp.test_name = "Variable Key Known Answer Test 244";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000001000");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("400AC4A0BBADA1DB2121EB144C7E5209");

	tmp.test_name = "Variable Key Known Answer Test 245";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000800");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EFD9D550EB419ED278F4885A490AB54C");

	tmp.test_name = "Variable Key Known Answer Test 246";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000400");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2AB7816E149B7C0404C88A8857793670");

	tmp.test_name = "Variable Key Known Answer Test 247";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000200");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5B591DFF9E8DEE15BAD24C025DBCA481");

	tmp.test_name = "Variable Key Known Answer Test 248";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000100");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0C06633E30721C3749F49AD8CBF2B754");

	tmp.test_name = "Variable Key Known Answer Test 249";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000080");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("96D6D31A41B5123B2035FD91A921D4CA");

	tmp.test_name = "Variable Key Known Answer Test 250";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000040");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7F6C34D86668BC2805CA7793C5E86AD");

	tmp.test_name = "Variable Key Known Answer Test 251";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000020");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F46DFF5FF500D6879C4D3E45CF0CF0F3");

	tmp.test_name = "Variable Key Known Answer Test 252";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000010");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("60D842D9C61DA7495C116197B7CECBBE");

	tmp.test_name = "Variable Key Known Answer Test 253";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000008");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D45B24EDB673353EBDF248B8FA06B67A");

	tmp.test_name = "Variable Key Known Answer Test 254";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000004");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("119EAEBCC165D0BD02C0D35DC82EF992");

	tmp.test_name = "Variable Key Known Answer Test 255";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000002");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E673143680414ADA301D0ED34626B9FE");

	tmp.test_name = "Variable Key Known Answer Test 256";
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000001");
	tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B6CFE160A6263631B292F879EEFF926");
}