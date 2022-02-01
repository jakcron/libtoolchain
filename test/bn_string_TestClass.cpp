#include <tc/Exception.h>
#include <fmt/core.h>

#include "bn_string_TestClass.h"

void bn_string_TestClass::runAllTests(void)
{
	fmt::print("[tc::bn::string] START\n");
	test_CodedSizeEqualsLogicalSize();
	test_CodedSizeGreaterThanLogicalSize();
	fmt::print("[tc::bn::string] END\n");
}

void bn_string_TestClass::test_CodedSizeEqualsLogicalSize()
{
	fmt::print("[tc::bn::string] test_CodedSizeEqualsLogicalSize : ");
	try
	{
		try 
		{
			// create bn::string with encoded size of 16 bytes (and implicit logical size of 16)
			static const size_t kEncodedSize = 16;
			tc::bn::string<kEncodedSize> bn_string;

			if (sizeof(bn_string) != kEncodedSize)
			{
				throw tc::Exception(fmt::format("sizeof(tc::bn::string<{:d}>) did not return ENCODED_SIZE ({:d})", kEncodedSize, kEncodedSize));
			}

			// test string with zeros for data
			memset(bn_string.data(), 0, sizeof(bn_string));
			
			if (bn_string.size() != 0)
			{
				throw tc::Exception(".size() did not return 0 (was cleared before use)");
			}

			if (bn_string.max_size() != kEncodedSize)
			{
				throw tc::Exception(fmt::format("max_size() did not return LOGICAL_SIZE ({:d})", kEncodedSize));
			}

			// test string after "hello" is written to it
			std::string hello_string = "hello";
			std::strncpy(bn_string.data(), hello_string.data(), hello_string.size());
		
			if (bn_string.size() != hello_string.size())
			{
				throw tc::Exception(".size() did not return expected size after \"hello\" was written to it");
			}

			if (bn_string.str() != hello_string)
			{
				throw tc::Exception(".str() did not return expected string after \"hello\" was written to it");
			}

			// test when string data continues past the boundary of bn::string, ensure it doesn't use the data past the boundary
			union {
				std::array<char, 10> raw_data;
				tc::bn::string<5> bn_string;
			} overwrite_test;

			std::string long_string = "abcdefgh";
			strncpy(overwrite_test.raw_data.data(), long_string.data(), long_string.size());

			if (overwrite_test.bn_string.size() != 5)
			{
				throw tc::Exception(".size() did not honour the max_size() when counting the string size.");
			}

			if (overwrite_test.bn_string.str() != long_string.substr(0,5))
			{
				throw tc::Exception(".str() did not honour the max_size() when generating the string.");
			}

			fmt::print("PASS\n");
		}
		catch (const tc::Exception& e)
		{
			fmt::print("FAIL ({:s})\n", e.error());
		}
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}

void bn_string_TestClass::test_CodedSizeGreaterThanLogicalSize()
{
	fmt::print("[tc::bn::string] test_CodedSizeGreaterThanLogicalSize : ");
	try
	{
		try 
		{
			static const size_t kEncodedSize = 64, kLogicalSize = 50;

			// create bn::string with encoded size of 64 bytes and logical size of 50
			tc::bn::string<kEncodedSize, kLogicalSize> bn_string;

			if (sizeof(bn_string) != kEncodedSize)
			{
				throw tc::Exception(fmt::format("sizeof(tc::bn::string<{:d},{:d}>) did not return ENCODED_SIZE ({:d})", kEncodedSize, kLogicalSize, kEncodedSize));
			}

			// test string with zeros for data
			memset(bn_string.data(), 0, sizeof(bn_string));
			
			if (bn_string.size() != 0)
			{
				throw tc::Exception(".size() did not return 0 (was cleared before use)");
			}

			if (bn_string.max_size() != kLogicalSize)
			{
				throw tc::Exception(".max_size() did not return LOGICAL_SIZE (50)");
			}

			// test string after "hello" is written to it
			std::string hello_string = "hello";
			std::strncpy(bn_string.data(), hello_string.data(), hello_string.size());
		
			if (bn_string.size() != hello_string.size())
			{
				throw tc::Exception(".size() did not return expected size after \"hello\" was written to it");
			}

			if (bn_string.str() != hello_string)
			{
				throw tc::Exception(".str() did not return expected string after \"hello\" was written to it");
			}

			// test when string data continues past the boundary of bn::string, ensure it doesn't use the data past the logical boundary
			union {
				std::array<char, 10> raw_data;
				tc::bn::string<10, 5> bn_string;
			} overwrite_test;

			std::string long_string = "abcdefgh";
			strncpy(overwrite_test.raw_data.data(), long_string.data(), long_string.size());

			if (overwrite_test.bn_string.size() != 5)
			{
				throw tc::Exception(".size() did not honour the max_size() when counting the string size.");
			}

			if (overwrite_test.bn_string.str() != long_string.substr(0,5))
			{
				throw tc::Exception(".str() did not honour the max_size() when generating the string.");
			}

			fmt::print("PASS\n");
		}
		catch (const tc::Exception& e)
		{
			fmt::print("FAIL ({:s})\n", e.error());
		}
	}
	catch (const std::exception& e)
	{
		fmt::print("UNHANDLED EXCEPTION ({:s})\n", e.what());
	}
}