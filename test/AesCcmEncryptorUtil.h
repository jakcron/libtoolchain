#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

class AesCcmEncryptorUtil
{
public:
	struct TestVector
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData nonce;
		tc::ByteData aad;
		tc::ByteData mac;
		tc::ByteData plaintext;
		tc::ByteData ciphertext;
	};

	static void generateAesCcmTestVectors_Nist(std::vector<AesCcmEncryptorUtil::TestVector>& test_list, size_t key_size);
};