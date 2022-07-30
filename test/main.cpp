#include "string_TranscodeUtil_TestClass.h"
#include "ByteData_TestClass.h"
#include "bn_binaryutils_TestClass.h"
#include "bn_pad_TestClass.h"
#include "bn_string_TestClass.h"
#include "bn_endian_TestClass.h"
#include "bn_bitarrayByteBEBitBE_TestClass.h"
#include "bn_bitarrayByteBEBitLE_TestClass.h"
#include "bn_bitarrayByteLEBitBE_TestClass.h"
#include "bn_bitarrayByteLEBitLE_TestClass.h"
#include "Optional_TestClass.h"
#include "io_Path_TestClass.h"
#include "io_BasicPathResolver_TestClass.h"
#include "io_LocalFileSystem_TestClass.h"
#include "io_FileStream_TestClass.h"
#include "io_MemoryStream_TestClass.h"
#include "io_SubStream_TestClass.h"
#include "io_ConcatenatedStream_TestClass.h"
#include "io_SubFileSystem_TestClass.h"
#include "io_VirtualFileSystem_TestClass.h"
#include "io_PaddingSource_TestClass.h"
#include "io_MemorySource_TestClass.h"
#include "io_OverlayedSource_TestClass.h"
#include "io_SubSource_TestClass.h"
#include "io_SubSink_TestClass.h"
#include "io_StreamSource_TestClass.h"
#include "io_StreamSink_TestClass.h"
#include "cli_FormatUtil_TestClass.h"
#include "cli_OptionParser_TestClass.h"
#include "crypto_Md5Generator_TestClass.h"
#include "crypto_Sha1Generator_TestClass.h"
#include "crypto_Sha256Generator_TestClass.h"
#include "crypto_Sha512Generator_TestClass.h"
#include "crypto_HmacMd5Generator_TestClass.h"
#include "crypto_HmacSha1Generator_TestClass.h"
#include "crypto_HmacSha256Generator_TestClass.h"
#include "crypto_HmacSha512Generator_TestClass.h"
#include "crypto_Pbkdf1Md5KeyDeriver_TestClass.h"
#include "crypto_Pbkdf1Sha1KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha1KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha256KeyDeriver_TestClass.h"
#include "crypto_Pbkdf2Sha512KeyDeriver_TestClass.h"
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
#include "crypto_Rsa1024OaepSha256Encryptor_TestClass.h"
#include "crypto_Rsa2048OaepSha256Encryptor_TestClass.h"
#include "crypto_Rsa4096OaepSha256Encryptor_TestClass.h"
#include "crypto_Rsa2048OaepSha512Encryptor_TestClass.h"
#include "crypto_Rsa4096OaepSha512Encryptor_TestClass.h"
#include "crypto_Rsa1024Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Md5Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha1Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha256Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha256Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha256Signer_TestClass.h"
#include "crypto_Rsa1024Pkcs1Sha512Signer_TestClass.h"
#include "crypto_Rsa2048Pkcs1Sha512Signer_TestClass.h"
#include "crypto_Rsa4096Pkcs1Sha512Signer_TestClass.h"
#include "crypto_Rsa1024PssSha256Signer_TestClass.h"
#include "crypto_Rsa1024PssSha512Signer_TestClass.h"
#include "crypto_Rsa2048PssSha256Signer_TestClass.h"
#include "crypto_Rsa2048PssSha512Signer_TestClass.h"
#include "crypto_Rsa4096PssSha256Signer_TestClass.h"
#include "crypto_Rsa4096PssSha512Signer_TestClass.h"

#include <fmt/core.h>

template <class T>
void runTest()
{
	T test_class;
	test_class.runAllTests();
}


int main(int argc, char** argv)
{
	bool includeSlowTests = false;
	if (argc > 1)
	{
		static const std::string kNoSlowTestFlag = "--slow";
		if (strncmp(argv[1], kNoSlowTestFlag.c_str(), kNoSlowTestFlag.size()) == 0)
		{
			includeSlowTests = true;
		}
		else
		{
			fmt::print("usage: {} [--slow]\n", std::string(argv[0]));
			return 1;
		}
		
	}
	
	runTest<string_TranscodeUtil_TestClass>();
	runTest<ByteData_TestClass>();
	runTest<bn_binaryutils_TestClass>();
	runTest<bn_pad_TestClass>();
	runTest<bn_string_TestClass>();
	runTest<bn_endian_TestClass>();
	runTest<bn_bitarrayByteBEBitBE_TestClass>();
	runTest<bn_bitarrayByteBEBitLE_TestClass>();
	runTest<bn_bitarrayByteLEBitBE_TestClass>();
	runTest<bn_bitarrayByteLEBitLE_TestClass>();
	runTest<Optional_TestClass>();
	runTest<io_Path_TestClass>();
	runTest<io_BasicPathResolver_TestClass>();
	runTest<io_LocalFileSystem_TestClass>();
	runTest<io_FileStream_TestClass>();
	runTest<io_MemoryStream_TestClass>();
	runTest<io_SubStream_TestClass>();
	runTest<io_ConcatenatedStream_TestClass>();
	runTest<io_SubFileSystem_TestClass>();
	runTest<io_VirtualFileSystem_TestClass>();
	runTest<io_PaddingSource_TestClass>();
	runTest<io_MemorySource_TestClass>();
	runTest<io_OverlayedSource_TestClass>();
	runTest<io_SubSource_TestClass>();
	runTest<io_SubSink_TestClass>();
	runTest<io_StreamSource_TestClass>();
	runTest<io_StreamSink_TestClass>();
	runTest<cli_FormatUtil_TestClass>();
	runTest<cli_OptionParser_TestClass>();
	runTest<crypto_Md5Generator_TestClass>();
	runTest<crypto_Sha1Generator_TestClass>();
	runTest<crypto_Sha256Generator_TestClass>();
	runTest<crypto_Sha512Generator_TestClass>();
	runTest<crypto_HmacMd5Generator_TestClass>();
	runTest<crypto_HmacSha1Generator_TestClass>();
	runTest<crypto_HmacSha256Generator_TestClass>();
	runTest<crypto_HmacSha512Generator_TestClass>();
	if (includeSlowTests)
	{
		runTest<crypto_Pbkdf1Md5KeyDeriver_TestClass>();
		runTest<crypto_Pbkdf1Sha1KeyDeriver_TestClass>();
		runTest<crypto_Pbkdf2Sha1KeyDeriver_TestClass>();
		runTest<crypto_Pbkdf2Sha256KeyDeriver_TestClass>();
		runTest<crypto_Pbkdf2Sha512KeyDeriver_TestClass>();
	}
	runTest<crypto_PseudoRandomByteGenerator_TestClass>();
	runTest<crypto_Aes128Encryptor_TestClass>();
	runTest<crypto_Aes192Encryptor_TestClass>();
	runTest<crypto_Aes256Encryptor_TestClass>();
	runTest<crypto_Aes128EcbEncryptor_TestClass>();
	runTest<crypto_Aes192EcbEncryptor_TestClass>();
	runTest<crypto_Aes256EcbEncryptor_TestClass>();
	runTest<crypto_Aes128CbcEncryptor_TestClass>();
	runTest<crypto_Aes192CbcEncryptor_TestClass>();
	runTest<crypto_Aes256CbcEncryptor_TestClass>();
	runTest<crypto_Aes128CbcEncryptedStream_TestClass>();
	runTest<crypto_Aes128CtrEncryptor_TestClass>();
	runTest<crypto_Aes192CtrEncryptor_TestClass>();
	runTest<crypto_Aes256CtrEncryptor_TestClass>();
	runTest<crypto_Aes128CtrEncryptedStream_TestClass>();
	runTest<crypto_Aes128XtsEncryptor_TestClass>();
	runTest<crypto_Aes256XtsEncryptor_TestClass>();
	runTest<crypto_Aes128CcmEncryptor_TestClass>();
	runTest<crypto_Rsa1024OaepSha256Encryptor_TestClass>();
	runTest<crypto_Rsa2048OaepSha256Encryptor_TestClass>();
	runTest<crypto_Rsa4096OaepSha256Encryptor_TestClass>();
	runTest<crypto_Rsa2048OaepSha512Encryptor_TestClass>();
	runTest<crypto_Rsa4096OaepSha512Encryptor_TestClass>();
	runTest<crypto_Rsa1024Pkcs1Md5Signer_TestClass>();
	runTest<crypto_Rsa2048Pkcs1Md5Signer_TestClass>();
	runTest<crypto_Rsa4096Pkcs1Md5Signer_TestClass>();
	runTest<crypto_Rsa1024Pkcs1Sha1Signer_TestClass>();
	runTest<crypto_Rsa2048Pkcs1Sha1Signer_TestClass>();
	runTest<crypto_Rsa4096Pkcs1Sha1Signer_TestClass>();
	runTest<crypto_Rsa1024Pkcs1Sha256Signer_TestClass>();
	runTest<crypto_Rsa2048Pkcs1Sha256Signer_TestClass>();
	runTest<crypto_Rsa4096Pkcs1Sha256Signer_TestClass>();
	runTest<crypto_Rsa1024Pkcs1Sha512Signer_TestClass>();
	runTest<crypto_Rsa2048Pkcs1Sha512Signer_TestClass>();
	runTest<crypto_Rsa4096Pkcs1Sha512Signer_TestClass>();
	runTest<crypto_Rsa1024PssSha256Signer_TestClass>();
	runTest<crypto_Rsa1024PssSha512Signer_TestClass>();
	runTest<crypto_Rsa2048PssSha256Signer_TestClass>();
	runTest<crypto_Rsa2048PssSha512Signer_TestClass>();
	runTest<crypto_Rsa4096PssSha256Signer_TestClass>();
	runTest<crypto_Rsa4096PssSha512Signer_TestClass>();
}