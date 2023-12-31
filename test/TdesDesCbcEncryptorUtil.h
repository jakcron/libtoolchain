#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>

class TdesDesCbcEncryptorUtil
{
public:
	struct TestVector
	{
		std::string test_name;
		tc::ByteData key;
		tc::ByteData iv;
		tc::ByteData base_data;
		size_t iteration_count;
		tc::ByteData dec_data;
		tc::ByteData enc_data;
	};

	static void generateDesCbcTestVectors_Nist(std::vector<TdesDesCbcEncryptorUtil::TestVector>& test_list, size_t key_size);
};