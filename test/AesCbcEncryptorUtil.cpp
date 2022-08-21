#include "AesCbcEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void AesCbcEncryptorUtil::generateAesCbcTestVectors_Nist(std::vector<AesCbcEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	AesCbcEncryptorUtil::TestVector tmp;

	if (key_size == 128)
	{
		test_list.clear();

		// Test vectors taken from NIST SP 800-38A
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");

		tmp.test_name  = "Test 1";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7649abac8119b246cee98e9b12e9197d");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("7649ABAC8119B246CEE98E9B12E9197D");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5086cb9b507219ee95db113a917678b2");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("5086CB9B507219EE95DB113A917678B2");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("73bed6b8e3c1743b7116e69e22229516");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("73BED6B8E3C1743B7116E69E22229516");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3ff1caa1681fac09120eca307586e1a7");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::ByteData(test_list[0].plaintext.size() * 4, false);
		tmp.ciphertext = tc::ByteData(tmp.plaintext.size(), false);
		for (size_t i = 0; i < 4; i++)
		{
			memcpy(tmp.plaintext.data() + (i * 0x10), test_list[i].plaintext.data(), test_list[i].plaintext.size());
			memcpy(tmp.ciphertext.data() + (i * 0x10), test_list[i].ciphertext.data(), test_list[i].ciphertext.size());
		}
		test_list.push_back(tmp);
	}
	else if (key_size == 192)
	{
		test_list.clear();

		// Test vectors taken from NIST SP 800-38A
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b");

		tmp.test_name  = "Test 1";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4f021db243bc633d7178183a9fa071e8");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("4F021DB243BC633D7178183A9FA071E8");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("b4d9ada9ad7dedf4e5e738763f69145a");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("B4D9ADA9AD7DEDF4E5E738763F69145A");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("571b242012fb7ae07fa9baac3df102e0");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("571B242012FB7AE07FA9BAAC3DF102E0");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("08b0e27988598881d920a9e64f5615cd");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::ByteData(test_list[0].plaintext.size() * 4, false);
		tmp.ciphertext = tc::ByteData(tmp.plaintext.size(), false);
		for (size_t i = 0; i < 4; i++)
		{
			memcpy(tmp.plaintext.data() + (i * 0x10), test_list[i].plaintext.data(), test_list[i].plaintext.size());
			memcpy(tmp.ciphertext.data() + (i * 0x10), test_list[i].ciphertext.data(), test_list[i].ciphertext.size());
		}
		test_list.push_back(tmp);
	}
	else if (key_size == 256)
	{
		test_list.clear();

		// Test vectors taken from NIST SP 800-38A
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4");

		tmp.test_name  = "Test 1";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("f58c4c04d6e5f1ba779eabfb5f7bfbd6");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("F58C4C04D6E5F1BA779EABFB5F7BFBD6");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9cfc4e967edb808d679f777bc6702c7d");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("9CFC4E967EDB808D679F777BC6702C7D");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("39f23369a9d9bacfa530e26304231461");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("39F23369A9D9BACFA530E26304231461");
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("b2eb05e2c39be9fcda6c19078c6a9d1b");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.iv         = tc::cli::FormatUtil::hexStringToBytes("000102030405060708090A0B0C0D0E0F");
		tmp.plaintext  = tc::ByteData(test_list[0].plaintext.size() * 4, false);
		tmp.ciphertext = tc::ByteData(tmp.plaintext.size(), false);
		for (size_t i = 0; i < 4; i++)
		{
			memcpy(tmp.plaintext.data() + (i * 0x10), test_list[i].plaintext.data(), test_list[i].plaintext.size());
			memcpy(tmp.ciphertext.data() + (i * 0x10), test_list[i].ciphertext.data(), test_list[i].ciphertext.size());
		}
		test_list.push_back(tmp);
	}
}