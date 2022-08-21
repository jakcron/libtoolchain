#include "AesCtrEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void AesCtrEncryptorUtil::generateAesCtrTestVectors_Nist(std::vector<AesCtrEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	AesCtrEncryptorUtil::TestVector tmp;

	if (key_size == 128)
	{
		test_list.clear();

		// Test vectors taken from NIST SP 800-38A
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
		tmp.iv  = tc::cli::FormatUtil::hexStringToBytes("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff");

		tmp.test_name  = "Test 1";
		tmp.block_number = 0;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("874d6191b620e3261bef6864990db6ce");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.block_number = 1;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9806f66b7970fdff8617187bb9fffdff");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.block_number = 2;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5ae4df3edbd5d35e5b4f09020db03eab");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.block_number = 3;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1e031dda2fbe03d1792170a0f3009cee");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.block_number = 0;
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
		tmp.iv  = tc::cli::FormatUtil::hexStringToBytes("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff");

		tmp.test_name  = "Test 1";
		tmp.block_number = 0;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1abc932417521ca24f2b0459fe7e6e0b");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.block_number = 1;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("090339ec0aa6faefd5ccc2c6f4ce8e94");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.block_number = 2;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1e36b26bd1ebc670d1bd1d665620abf7");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.block_number = 3;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4f78a7f6d29809585a97daec58c6b050");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.block_number = 0;
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
		tmp.iv  = tc::cli::FormatUtil::hexStringToBytes("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff");

		tmp.test_name  = "Test 1";
		tmp.block_number = 0;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172a");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("601ec313775789a5b7a7f504bbf3d228");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 2";
		tmp.block_number = 1;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("ae2d8a571e03ac9c9eb76fac45af8e51");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("f443e3ca4d62b59aca84e990cacaf5c5");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 3";
		tmp.block_number = 2;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("30c81c46a35ce411e5fbc1191a0a52ef");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2b0930daa23de94ce87017ba2d84988d");
		test_list.push_back(tmp);

		tmp.test_name  = "Test 4";
		tmp.block_number = 3;
		tmp.plaintext  = tc::cli::FormatUtil::hexStringToBytes("f69f2445df4f9b17ad2b417be66c3710");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("dfc9c58db67aada613c2dd08457941a6");
		test_list.push_back(tmp);

		tmp.test_name  = "Tests 1-4";
		tmp.block_number = 0;
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