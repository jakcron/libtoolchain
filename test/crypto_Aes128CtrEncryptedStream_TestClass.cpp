#include "crypto_Aes128CtrEncryptedStream_TestClass.h"
#include "StreamTestUtil.h"

#include <fmt/format.h>

#include <tc/crypto/Aes128CtrEncryptedStream.h>
#include <tc/io.h>
#include <tc/cli.h>

//---------------------------------------------------------

crypto_Aes128CtrEncryptedStream_TestClass::crypto_Aes128CtrEncryptedStream_TestClass() :
	mTestTag("tc::crypto::Aes128CtrEncryptedStream"),
	mTestResults()
{
}

void crypto_Aes128CtrEncryptedStream_TestClass::runAllTests(void)
{
	test_CreateEmptyStream_DefaultConstructor();
	test_CreateValidStream_CreateConstructor();
	test_RunTestCases();
}

const std::string& crypto_Aes128CtrEncryptedStream_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_Aes128CtrEncryptedStream_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_Aes128CtrEncryptedStream_TestClass::test_CreateEmptyStream_DefaultConstructor()
{
	TestResult test_result;
	test_result.test_name = "test_CreateEmptyStream_DefaultConstructor";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		auto stream = tc::crypto::Aes128CtrEncryptedStream();

		StreamTestUtil::constructor_TestHelper(stream, 0, 0, false, false, false);

		try
		{
			stream.read(nullptr, 0);
			throw tc::TestException(".read() did not throw tc::ObjectDisposedException for uninitialized Aes128CtrEncryptedStream");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".read() did not throw correct exception for uninitialized Aes128CtrEncryptedStream");
		}

		try
		{
			stream.write(nullptr, 0);
			throw tc::TestException(".write() did not throw tc::ObjectDisposedException for uninitialized Aes128CtrEncryptedStream");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".write() did not throw correct exception for uninitialized Aes128CtrEncryptedStream");
		}

		try
		{
			stream.seek(0, tc::io::SeekOrigin::Begin);
			throw tc::TestException(".seek() did not throw tc::ObjectDisposedException for uninitialized Aes128CtrEncryptedStream");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".seek() did not throw correct exception for uninitialized Aes128CtrEncryptedStream");
		}

		try
		{
			stream.setLength(0);
			throw tc::TestException(".setLength() did not throw tc::ObjectDisposedException for uninitialized Aes128CtrEncryptedStream");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".setLength() did not throw correct exception for uninitialized Aes128CtrEncryptedStream");
		}

		try
		{
			stream.flush();
			throw tc::TestException(".flush() did not throw tc::ObjectDisposedException for uninitialized Aes128CtrEncryptedStream");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".flush() did not throw correct exception for uninitialized Aes128CtrEncryptedStream");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_Aes128CtrEncryptedStream_TestClass::test_CreateValidStream_CreateConstructor()
{
	TestResult test_result;
	test_result.test_name = "test_CreateValidStream_CreateConstructor";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		tc::crypto::Aes128CtrEncryptedStream::key_t key;
		tc::crypto::Aes128CtrEncryptedStream::counter_t counter;

		std::shared_ptr<tc::io::IStream> base_stream;
		base_stream = std::shared_ptr<tc::io::MemoryStream>(new tc::io::MemoryStream(tc::ByteData(0x100)));

		auto stream = tc::crypto::Aes128CtrEncryptedStream(base_stream, key, counter);

		try
		{
			stream.write(nullptr, 0);
			throw tc::TestException(".write() did not throw tc::NotImplementedException for initialized Aes128CtrEncryptedStream");
		}
		catch (tc::NotImplementedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".write() did not throw correct exception for initialized Aes128CtrEncryptedStream");
		}

		try
		{
			stream.setLength(0);
			throw tc::TestException(".setLength() did not throw tc::NotImplementedException for initialized Aes128CtrEncryptedStream");
		}
		catch (tc::NotImplementedException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException(".setLength() did not throw correct exception for initialized Aes128CtrEncryptedStream");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_Aes128CtrEncryptedStream_TestClass::test_RunTestCases()
{
	TestResult test_result;
	test_result.test_name = "test_RunTestCases";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// get test cases
		std::vector<crypto_Aes128CtrEncryptedStream_TestClass::TestCase> test_cases;
		util_Setup_TestCases(test_cases);

		for (auto itr = test_cases.begin(); itr != test_cases.end(); itr++)
		{
			tc::crypto::Aes128CtrEncryptedStream::key_t key;
			memcpy(key.data(), itr->key.data(), itr->key.size());

			tc::crypto::Aes128CtrEncryptedStream::counter_t counter;
			memcpy(counter.data(), itr->counter.data(), itr->counter.size());
 
			std::shared_ptr<tc::io::IStream> base_stream;
			base_stream = std::shared_ptr<tc::io::MemoryStream>(new tc::io::MemoryStream(itr->ciphertext));


			auto stream = tc::crypto::Aes128CtrEncryptedStream(base_stream, key, counter);

			try 
			{
				StreamTestUtil::constructor_TestHelper(stream, itr->ciphertext.size(), 0, true, false, true);
				StreamTestUtil::read_TestHelper(stream, itr->read_offset, tc::io::SeekOrigin::Begin, itr->read_size, itr->read_size, itr->read_plaintext.size(), itr->read_offset + int64_t(itr->read_size), itr->read_plaintext.data());
			}
			catch (const tc::Exception& e)
			{
				throw tc::TestException(fmt::format("{} Failed: {}", itr->test_name, e.error()));
			}
			
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_Aes128CtrEncryptedStream_TestClass::util_Setup_TestCases(std::vector<crypto_Aes128CtrEncryptedStream_TestClass::TestCase>& test_cases)
{
	TestCase tmp;

	test_cases.clear();

	// Test vectors taken from NIST SP 800-38A
	tmp.key = tc::cli::FormatUtil::hexStringToBytes("2b7e151628aed2a6abf7158809cf4f3c");
	tmp.counter  = tc::cli::FormatUtil::hexStringToBytes("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff");

	tc::ByteData plaintext =  tc::cli::FormatUtil::hexStringToBytes("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710");
	tc::ByteData ciphertext = tc::cli::FormatUtil::hexStringToBytes("874d6191b620e3261bef6864990db6ce9806f66b7970fdff8617187bb9fffdff5ae4df3edbd5d35e5b4f09020db03eab1e031dda2fbe03d1792170a0f3009cee");

	tmp.test_name  = "Test 1";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x00;
	tmp.read_size = 0x10;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 2";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x10;
	tmp.read_size = 0x10;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 3";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x20;
	tmp.read_size = 0x10;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test 4";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x30;
	tmp.read_size = 0x10;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test read all blocks";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x0;
	tmp.read_size = 0x40;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test un-aligned read over blocks 1-2";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x17;
	tmp.read_size = 0x11;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test un-aligned read over blocks 0-3";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x07;
	tmp.read_size = 0x31;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test partial block 0 read";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x2;
	tmp.read_size = 0x8;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test partial block 1 read";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x12;
	tmp.read_size = 0x8;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);

	tmp.test_name  = "Test partial block 3 read";
	tmp.ciphertext = ciphertext;
	tmp.read_offset = 0x32;
	tmp.read_size = 0x8;
	tmp.read_plaintext = tc::ByteData(plaintext.data() + tmp.read_offset, tmp.read_size);
	test_cases.push_back(tmp);
}