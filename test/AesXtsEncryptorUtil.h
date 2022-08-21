#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

class AesXtsEncryptorUtil
{
public:
	struct TestVector
	{
		std::string test_name;
		tc::ByteData key1;
		tc::ByteData key2;
		uint64_t data_unit;
		uint64_t data_unit_sequence_number;
		tc::ByteData plaintext;
		tc::ByteData ciphertext;
	};

	static void generateAesXtsTestVectors_IEEE1619_2007(std::vector<AesXtsEncryptorUtil::TestVector>& test_list, size_t key_size);
};