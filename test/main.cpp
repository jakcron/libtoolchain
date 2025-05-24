#include "Optional_TestClass.h"
#include "ByteData_TestClass.h"
#include "string_TranscodeUtil_TestClass.h"
#include "cli_FormatUtil_TestClass.h"
#include "cli_OptionParser_TestClass.h"
#include "encode_Base64Util_TestClass.h"
#include "bn_binaryutils_TestClass.h"
#include "bn_pad_TestClass.h"
#include "bn_string_TestClass.h"
#include "bn_endian_TestClass.h"
#include "bn_bitarrayByteBEBitBE_TestClass.h"
#include "bn_bitarrayByteBEBitLE_TestClass.h"
#include "bn_bitarrayByteLEBitBE_TestClass.h"
#include "bn_bitarrayByteLEBitLE_TestClass.h"
#include "io_Path_TestClass.h"
#include "io_BasicPathResolver_TestClass.h"
#include "io_LocalFileSystem_TestClass.h"
#include "io_FileStream_TestClass.h"
#include "io_MemoryStream_TestClass.h"
#include "io_SubStream_TestClass.h"
#include "io_ConcatenatedStream_TestClass.h"
#include "io_EmptyStream_TestClass.h"
#include "io_SubFileSystem_TestClass.h"
#include "io_VirtualFileSystem_TestClass.h"
#include "io_PaddingSource_TestClass.h"
#include "io_MemorySource_TestClass.h"
#include "io_OverlayedSource_TestClass.h"
#include "io_SubSource_TestClass.h"
#include "io_SubSink_TestClass.h"
#include "io_StreamSource_TestClass.h"
#include "io_StreamSink_TestClass.h"
#include "crypto_Md5Generator_TestClass.h"
#include "crypto_Sha1Generator_TestClass.h"
#include "crypto_Sha2256Generator_TestClass.h"
#include "crypto_Sha2512Generator_TestClass.h"
#include "crypto_HmacMd5Generator_TestClass.h"
#include "crypto_HmacSha1Generator_TestClass.h"
#include "crypto_HmacSha2256Generator_TestClass.h"
#include "crypto_HmacSha2512Generator_TestClass.h"
#include "crypto_Pbkdf1Md5KeyDeriver_TestClass.h"
#include "crypto_Pbkdf1Sha1KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha1KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha2256KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha2512KeyDeriver_TestClass.h"
#include "crypto_PseudoRandomByteGenerator_TestClass.h"
#include "crypto_Aes128Encryptor_TestClass.h"
#include "crypto_Aes192Encryptor_TestClass.h"
#include "crypto_Aes256Encryptor_TestClass.h"
#include "crypto_Aes128EcbEncryptor_TestClass.h"
#include "crypto_Aes192EcbEncryptor_TestClass.h"
#include "crypto_Aes256EcbEncryptor_TestClass.h"
#include "crypto_Aes128CbcEncryptor_TestClass.h"
#include "crypto_Aes192CbcEncryptor_TestClass.h"
#include "crypto_Aes256CbcEncryptor_TestClass.h"
#include "crypto_Aes128CbcEncryptedStream_TestClass.h"
#include "crypto_Aes128CtrEncryptor_TestClass.h"
#include "crypto_Aes192CtrEncryptor_TestClass.h"
#include "crypto_Aes256CtrEncryptor_TestClass.h"
#include "crypto_Aes128CtrEncryptedStream_TestClass.h"
#include "crypto_Aes128XtsEncryptor_TestClass.h"
#include "crypto_Aes256XtsEncryptor_TestClass.h"
#include "crypto_Aes128CcmEncryptor_TestClass.h"
#include "crypto_CmacAes128Generator_TestClass.h"
#include "crypto_CmacAes192Generator_TestClass.h"
#include "crypto_CmacAes256Generator_TestClass.h"
#include "crypto_CmacTdes112Generator_TestClass.h"
#include "crypto_CmacTdes168Generator_TestClass.h"
#include "crypto_Des56EcbEncryptor_TestClass.h"
#include "crypto_Des56CbcEncryptor_TestClass.h"
#include "crypto_Tdes112EcbEncryptor_TestClass.h"
#include "crypto_Tdes112CbcEncryptor_TestClass.h"
#include "crypto_Tdes168EcbEncryptor_TestClass.h"
#include "crypto_Tdes168CbcEncryptor_TestClass.h"
#include "crypto_Rsa1024OaepSha2256Encryptor_TestClass.h"
#include "crypto_Rsa2048OaepSha2256Encryptor_TestClass.h"
#include "crypto_Rsa4096OaepSha2256Encryptor_TestClass.h"
#include "crypto_Rsa2048OaepSha2512Encryptor_TestClass.h"
#include "crypto_Rsa4096OaepSha2512Encryptor_TestClass.h"
#include "crypto_Rsa1024Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha2256Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha2256Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha2256Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha2512Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha2512Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha2512Signer_TestClass.h"
#include "crypto_Rsa1024PssSha2256Signer_TestClass.h"
#include "crypto_Rsa2048PssSha2256Signer_TestClass.h"
#include "crypto_Rsa4096PssSha2256Signer_TestClass.h"
#include "crypto_Rsa1024PssSha2512Signer_TestClass.h"
#include "crypto_Rsa2048PssSha2512Signer_TestClass.h"
#include "crypto_Rsa4096PssSha2512Signer_TestClass.h"

#include "ITestClass.h"

#include <algorithm>
#include <fmt/core.h>

struct TestClassResult
{
	std::string tag;
	std::vector<ITestClass::TestResult> test_results;
};

template <class T>
void runTest(std::vector<TestClassResult>& global_test_results, const std::regex& include_test_regex, const std::regex& exclude_test_regex, bool run_slow_tests)
{
	TestClassResult local_test_results;

	T test_class;

	if (!std::regex_match(test_class.getTestTag(), include_test_regex) || std::regex_match(test_class.getTestTag(), exclude_test_regex))
	{
		return;
	}
	if (test_class.isSlowTest() == true && run_slow_tests == false)
	{
		return;
	}

	test_class.runAllTests();

	local_test_results.tag = test_class.getTestTag();
	local_test_results.test_results.assign(test_class.getTestResults().begin(), test_class.getTestResults().end());

	global_test_results.push_back(std::move(local_test_results));
}

void outputResultsToStdout(const std::vector<TestClassResult>& global_test_results, const std::regex& include_result_regex, const std::regex& exclude_result_regex)
{
	for (auto test_class_itr = global_test_results.begin(); test_class_itr != global_test_results.end(); test_class_itr++)
	{
		size_t total_tests = 0, total_passed_tests = 0;
		fmt::print("[{:s}] START\n", test_class_itr->tag);
		for (auto test_itr = test_class_itr->test_results.begin(); test_itr != test_class_itr->test_results.end(); test_itr++)
		{
			total_tests += 1;
			total_passed_tests += (test_itr->result == "PASS") ? 1 : 0;

			if (!std::regex_match(test_itr->result, include_result_regex) || std::regex_match(test_itr->result, exclude_result_regex))
			{
				continue;
			}

			fmt::print("[{:s}] {:s} : {:s}", test_class_itr->tag, test_itr->test_name, test_itr->result);
			if (test_itr->comments.empty() == false)
			{
				fmt::print(" ({:s})", test_itr->comments);
			}
			fmt::print("\n");
		}
		fmt::print("[{:s}] END ({:d}/{:d} passed)\n", test_class_itr->tag, total_passed_tests, total_tests);
	}
}

int main(int argc, char** argv)
{
	bool include_slow_tests = false;
	std::regex include_test_regex = std::regex("(.)*");
	std::regex exclude_test_regex = std::regex("");
	std::regex include_result_regex = std::regex("^.*((\\W|^)PASS(\\W|$)){0}.*$");
	std::regex exclude_result_regex = std::regex("");
	if (argc > 1)
	{
		static const std::string kNoSlowTestFlag = "--slow";
		static const std::string kIncludeTestRegex = "--intest";
		static const std::string kExcludeTestRegex = "--extest";
		static const std::string kIncludeResultRegex = "--inres";
		static const std::string kExcludeResultRegex = "--exres";
		
		for (int i = 1; i < argc;)
		{
			try {
				if (std::string(argv[i]) == kNoSlowTestFlag)
				{
					include_slow_tests = true;
					i += 1;
				}
				else if (std::string(argv[i]) == kIncludeTestRegex && i+1 < argc)
				{
					include_test_regex = std::regex(std::string(argv[i+1]));
					i += 2;
				}
				else if (std::string(argv[i]) == kExcludeTestRegex && i+1 < argc)
				{
					exclude_test_regex = std::regex(std::string(argv[i+1]));
					i += 2;
				}
				else if (std::string(argv[i]) == kIncludeResultRegex && i+1 < argc)
				{
					include_result_regex = std::regex(std::string(argv[i+1]));
					i += 2;
				}
				else if (std::string(argv[i]) == kExcludeResultRegex && i+1 < argc)
				{
					exclude_result_regex = std::regex(std::string(argv[i+1]));
					i += 2;
				}
				else
				{
					throw tc::Exception(fmt::format("Argument \"{}\" is unrecognised", std::string(argv[i]) ));
				}
			}
			catch (std::exception& e) 
			{
				fmt::print("error: {}\n\n", e.what());
				fmt::print("usage: {} [{slowtest:s}] [{incltestregex:s} <regex>] [{excltestregex:s} <regex>] [{inclresultregex:s} <regex>] [{exclresultregex:s} <regex>]\n", std::string(argv[0]), 
					fmt::arg("slowtest", kNoSlowTestFlag), 
					fmt::arg("incltestregex", kIncludeTestRegex), 
					fmt::arg("excltestregex", kExcludeTestRegex), 
					fmt::arg("inclresultregex", kIncludeResultRegex), 
					fmt::arg("exclresultregex", kExcludeResultRegex));
				fmt::print("\n\nTest Regex Examples:\n");
				fmt::print(" > \"(.*)Aes128(.*)\" - Select tests that include Aes128 in the name\n");
				fmt::print(" > \"tc::io(.*)\" - Select tests that exist in the tc::io namespace\n");
				fmt::print(" > \"tc::io::StreamSource\" - Select a specific test\n");
				fmt::print("\nResult Regex Examples:\n");
				fmt::print(" > \"PASS\" - Select results that passed\n");
				fmt::print(" > \"FAIL\" - Select results that failed\n");
				return 1;
			}
		}
	}

	std::vector<TestClassResult> global_test_results;

	// do tests

	// namespace tc
	runTest<Optional_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<ByteData_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::string
	runTest<string_TranscodeUtil_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::cli
	runTest<cli_FormatUtil_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<cli_OptionParser_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::encode
	runTest<encode_Base64Util_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::bn
	runTest<bn_binaryutils_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_pad_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_string_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_endian_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_bitarrayByteBEBitBE_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_bitarrayByteBEBitLE_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_bitarrayByteLEBitBE_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<bn_bitarrayByteLEBitLE_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::io
	runTest<io_Path_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_BasicPathResolver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	// IS THERE A CORRECT ORDER TO LocalFileSystem and FileStream (since LocalFileSystem uses FileStream internally?)
	runTest<io_LocalFileSystem_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_FileStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_MemoryStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_SubStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_ConcatenatedStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_EmptyStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_SubFileSystem_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_VirtualFileSystem_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_PaddingSource_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_MemorySource_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_OverlayedSource_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_SubSource_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_SubSink_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_StreamSource_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<io_StreamSink_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// namespace tc::crypto
	runTest<crypto_Md5Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Sha1Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Sha2256Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Sha2512Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_HmacMd5Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_HmacSha1Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_HmacSha2256Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_HmacSha2512Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Pbkdf1Md5KeyDeriver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Pbkdf1Sha1KeyDeriver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Pbkdf2Sha1KeyDeriver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Pbkdf2Sha2256KeyDeriver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Pbkdf2Sha2512KeyDeriver_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_PseudoRandomByteGenerator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes192Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes256Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes192EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes256EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes192CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes256CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128CbcEncryptedStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128CtrEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes192CtrEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes256CtrEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128CtrEncryptedStream_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128XtsEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes256XtsEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Aes128CcmEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_CmacAes128Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_CmacAes192Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_CmacAes256Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_CmacTdes112Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_CmacTdes168Generator_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Des56EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Des56CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Tdes112EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Tdes112CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Tdes168EcbEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Tdes168CbcEncryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024OaepSha2256Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048OaepSha2256Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096OaepSha2256Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048OaepSha2512Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096OaepSha2512Encryptor_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024Pkcs1Md5Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048Pkcs1Md5Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096Pkcs1Md5Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024Pkcs1Sha1Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048Pkcs1Sha1Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096Pkcs1Sha1Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024Pkcs1Sha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048Pkcs1Sha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096Pkcs1Sha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024Pkcs1Sha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048Pkcs1Sha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096Pkcs1Sha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024PssSha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048PssSha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096PssSha2256Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa1024PssSha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa2048PssSha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);
	runTest<crypto_Rsa4096PssSha2512Signer_TestClass>(global_test_results, include_test_regex, exclude_test_regex, include_slow_tests);

	// output results
	outputResultsToStdout(global_test_results, include_result_regex, exclude_result_regex);
}