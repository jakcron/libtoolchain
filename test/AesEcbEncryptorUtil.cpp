#include "AesEcbEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void AesEcbEncryptorUtil::generateAesEcbTestVectors_Nist(std::vector<AesEcbEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	AesEcbEncryptorUtil::TestVector tmp;

	if (key_size == 128)
	{
		test_list.clear();

		// Test vectors taken from NIST SP 800-38A
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");

		tmp.test_name  = "Test 1";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3ad77bb40d7a3660a89ecaf32466ef97");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("f5d3d58503b9699de785895a96fdbaaf");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("43b1cd7f598ece23881b00e3ed030688");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7b0c785e27e8ad3f8223207104725dd4");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.plaintext = tc::ByteData(test_list[0].plaintext.size() * 4, false);
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
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("bd334f1d6e45f25ff712a214571fa5cc");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("974104846d0ad3ad7734ecb3ecee4eef");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ef7afd2270e2e60adce0ba2face6444e");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9a4b41ba738d6c72fb16691603c18e0e");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.plaintext = tc::ByteData(test_list[0].plaintext.size() * 4, false);
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
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("f3eed1bdb5d2a03c064b5a7e3db181f8");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("591ccb10d410ed26dc5ba74a31362870");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("b6ed21b99ca6f4f9f153e7b1beafed1d");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("23304b7a39f9f3ff067d8d8f9e24ecc7");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.plaintext = tc::ByteData(test_list[0].plaintext.size() * 4, false);
		tmp.ciphertext = tc::ByteData(tmp.plaintext.size(), false);
		for (size_t i = 0; i < 4; i++)
		{
			memcpy(tmp.plaintext.data() + (i * 0x10), test_list[i].plaintext.data(), test_list[i].plaintext.size());
			memcpy(tmp.ciphertext.data() + (i * 0x10), test_list[i].ciphertext.data(), test_list[i].ciphertext.size());
		}
		test_list.push_back(tmp);
	}
}