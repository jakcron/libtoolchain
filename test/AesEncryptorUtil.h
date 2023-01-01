#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

class AesEncryptorUtil
{
public:
    struct TestVector
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData plaintext;
		tc::ByteData ciphertext;
	};

        // taken from "ecb_vk.txt" from https://csrc.nist.gov/archive/aes/rijndael/rijndael-vals.zip
	static void generateAesTestVectors_Nist(std::vector<AesEncryptorUtil::TestVector>& test_list, size_t key_size);
};