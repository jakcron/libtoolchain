#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

class TdesDesEcbEncryptorUtil
{
public:
	struct TestVector
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData base_data;
		size_t iteration_count;
		tc::ByteData dec_data;
		tc::ByteData enc_data;
	};

	static void generateDesEcbTestVectors_Nist(std::vector<TdesDesEcbEncryptorUtil::TestVector>& test_list, size_t key_size);
};