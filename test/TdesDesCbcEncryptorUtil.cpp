#include "TdesDesCbcEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void TdesDesCbcEncryptorUtil::generateDesCbcTestVectors_Nist(std::vector<TdesDesCbcEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	TdesDesCbcEncryptorUtil::TestVector tmp;

	/*
	 * DES and 3DES test vectors from:
	 *
	 * http://csrc.nist.gov/groups/STM/cavp/documents/des/tripledes-vectors.zip
	 */
	if (key_size == 56)
	{
		test_list.clear();

		tmp.test_name  = "Monte Carlo test";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0123456789ABCDEF");
		tmp.iv = tc::cli::FormatUtil::hexStringToBytes("1234567890ABCDEF");
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("129F40B9D20056B3");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("9452B69F6D1C6AEC");
		
		test_list.push_back(tmp);
	}
	else if (key_size == 112)
	{
		test_list.clear();

		tmp.test_name  = "Monte Carlo test";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0123456789ABCDEF23456789ABCDEF01");
		tmp.iv = tc::cli::FormatUtil::hexStringToBytes("1234567890ABCDEF");
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("470EFC9A6B8EE393");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("332237A1624FC335");
		
		test_list.push_back(tmp);
	}
	else if (key_size == 168)
	{
		test_list.clear();

		tmp.test_name  = "Monte Carlo test";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0123456789ABCDEF23456789ABCDEF01456789ABCDEF0123");
		tmp.iv = tc::cli::FormatUtil::hexStringToBytes("1234567890ABCDEF");
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("C5CECF63ECEC514C");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("22DCF21270A2577C");
		
		test_list.push_back(tmp);
	}
}