#include "TdesDesEcbEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void TdesDesEcbEncryptorUtil::generateDesEcbTestVectors_Nist(std::vector<TdesDesEcbEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	TdesDesEcbEncryptorUtil::TestVector tmp;

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
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("CDD64F2F9427C15D");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("6A2A19F41ECA854B");
		
		test_list.push_back(tmp);
	}
	else if (key_size == 112)
	{
		test_list.clear();

		tmp.test_name  = "Monte Carlo test";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0123456789ABCDEF23456789ABCDEF01");
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("6996C8FA47A2ABEB");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("03E69F5BFA58EB42");
		
		test_list.push_back(tmp);
	}
	else if (key_size == 168)
	{
		test_list.clear();

		tmp.test_name  = "Monte Carlo test";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0123456789ABCDEF23456789ABCDEF01456789ABCDEF0123");
		tmp.base_data = tc::cli::FormatUtil::hexStringToBytes("4E6F772069732074");
		tmp.iteration_count = 10000;
		tmp.dec_data = tc::cli::FormatUtil::hexStringToBytes("8325397644091A0A");
		tmp.enc_data = tc::cli::FormatUtil::hexStringToBytes("DD17E8B8B437D232");
		
		test_list.push_back(tmp);
	}
}