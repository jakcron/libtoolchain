#include <tc.h>
#include <iostream>

#include "bn_endian_TestClass.h"

void bn_endian_TestClass::runAllTests()
{
	std::cout << "[tc::bn endian_types] START" << std::endl;
	testLocalBSwap16();
	testLocalBSwap32();
	testLocalBSwap64();
	testBeUint64Inline();
	testBeUint32Inline();
	testBeUint16Inline();
	testLeUint64Inline();
	testLeUint32Inline();
	testLeUint16Inline();
	testBe64TemplateClass();
	testBe32TemplateClass();
	testBe16TemplateClass();
	testLe64TemplateClass();
	testLe32TemplateClass();
	testLe16TemplateClass();
	std::cout << "[tc::bn endian_types] END" << std::endl;
}

void bn_endian_TestClass::testLocalBSwap16()
{
	std::cout << "[tc::bn::detail::__local_bswap16] testLocalBSwap16 : " << std::flush;
	try 
	{
		uint16_t x = 0xabcd;
		uint16_t x_inv = 0xcdab;

		if (tc::bn::detail::__local_bswap16(x) != x_inv)
		{
			throw tc::Exception("tc::bn::detail::__local_bswap16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLocalBSwap32()
{
	std::cout << "[tc::bn::detail::__local_bswap32] testLocalBSwap32 : " << std::flush;
	try 
	{
		uint32_t x = 0xabcd1234;
		uint32_t x_inv = 0x3412cdab;

		if (tc::bn::detail::__local_bswap32(x) != x_inv)
		{
			throw tc::Exception("tc::bn::detail::__local_bswap32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLocalBSwap64()
{
	std::cout << "[tc::bn::detail::__local_bswap64] testLocalBSwap64 : " << std::flush;
	try 
	{
		uint64_t x = 0x0123456789abcdef;
		uint64_t x_inv = 0xefcdab8967452301;

		if (tc::bn::detail::__local_bswap64(x) != x_inv)
		{
			throw tc::Exception("tc::bn::detail::__local_bswap64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBeUint64Inline()
{
	std::cout << "[tc::bn::detail::__be_uint64] testBeUint64Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint64_t* x_raw_ptr = (uint64_t*)&x_raw;
		uint64_t x_expected = 0x0123456789abcdef;

		if (tc::bn::detail::__be_uint64(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__be_uint64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBeUint32Inline()
{
	std::cout << "[tc::bn::detail::__be_uint32] testBeUint32Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[4] = { 0x01, 0x23, 0x45, 0x67 };
		uint32_t* x_raw_ptr = (uint32_t*)&x_raw;
		uint32_t x_expected = 0x01234567;

		if (tc::bn::detail::__be_uint32(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__be_uint32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBeUint16Inline()
{
	std::cout << "[tc::bn::detail::__be_uint16] testBeUint16Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[2] = { 0x01, 0x23 };
		uint16_t* x_raw_ptr = (uint16_t*)&x_raw;
		uint16_t x_expected = 0x0123;

		if (tc::bn::detail::__be_uint16(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__be_uint16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLeUint64Inline()
{
	std::cout << "[tc::bn::detail::__le_uint64] testLeUint64Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint64_t* x_raw_ptr = (uint64_t*)&x_raw;
		uint64_t x_expected = 0xefcdab8967452301;

		if (tc::bn::detail::__le_uint64(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__le_uint64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLeUint32Inline()
{
	std::cout << "[tc::bn::detail::__le_uint32] testLeUint32Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[4] = { 0x01, 0x23, 0x45, 0x67 };
		uint32_t* x_raw_ptr = (uint32_t*)&x_raw;
		uint32_t x_expected = 0x67452301;

		if (tc::bn::detail::__le_uint32(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__le_uint32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLeUint16Inline()
{
	std::cout << "[tc::bn::detail::__le_uint16] testLeUint16Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[2] = { 0x01, 0x23 };
		uint16_t* x_raw_ptr = (uint16_t*)&x_raw;
		uint16_t x_expected = 0x2301;

		if (tc::bn::detail::__le_uint16(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::detail::__le_uint16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBe64TemplateClass()
{
	std::cout << "[tc::bn::be64<uint64_t>] testBe64TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint8_t x_raw_expected[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		tc::bn::be64<uint64_t>* x_raw_ptr = (tc::bn::be64<uint64_t>*)&x_raw;
		uint64_t x_expected = 0x0123456789abcdef;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be64<uint64_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::be64<uint64_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be64<uint64_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::be64<uint64_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be64<uint64_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::be64<uint64_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be64<uint64_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBe32TemplateClass()
{
	std::cout << "[tc::bn::be32<uint32_t>] testBe32TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		uint8_t x_raw_expected[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		tc::bn::be32<uint32_t>* x_raw_ptr = (tc::bn::be32<uint32_t>*)&x_raw;
		uint32_t x_expected = 0x01234567;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be32<uint32_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::be32<uint32_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be32<uint32_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::be32<uint32_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be32<uint32_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::be32<uint32_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be32<uint32_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testBe16TemplateClass()
{
	std::cout << "[tc::bn::be16<uint16_t>] testBe16TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint16_t)] = { 0x01, 0x23 };
		uint8_t x_raw_expected[sizeof(uint16_t)] = { 0x01, 0x23 };
		tc::bn::be16<uint16_t>* x_raw_ptr = (tc::bn::be16<uint16_t>*)&x_raw;
		uint16_t x_expected = 0x0123;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be16<uint16_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::be16<uint16_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::be16<uint16_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::be16<uint16_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be16<uint16_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::be16<uint16_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::be16<uint16_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLe64TemplateClass()
{
	std::cout << "[tc::bn::le64<uint64_t>] testLe64TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint8_t x_raw_expected[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		tc::bn::le64<uint64_t>* x_raw_ptr = (tc::bn::le64<uint64_t>*)&x_raw;
		uint64_t x_expected = 0xefcdab8967452301;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le64<uint64_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::le64<uint64_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le64<uint64_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::le64<uint64_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le64<uint64_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::le64<uint64_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le64<uint64_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLe32TemplateClass()
{
	std::cout << "[tc::bn::le32<uint32_t>] testLe32TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		uint8_t x_raw_expected[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		tc::bn::le32<uint32_t>* x_raw_ptr = (tc::bn::le32<uint32_t>*)&x_raw;
		uint32_t x_expected = 0x67452301;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le32<uint32_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::le32<uint32_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le32<uint32_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::le32<uint32_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le32<uint32_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::le32<uint32_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le32<uint32_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void bn_endian_TestClass::testLe16TemplateClass()
{
	std::cout << "[tc::bn::le16<uint16_t>] testLe16TemplateClass : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint16_t)] = { 0x01, 0x23 };
		uint8_t x_raw_expected[sizeof(uint16_t)] = { 0x01, 0x23 };
		tc::bn::le16<uint16_t>* x_raw_ptr = (tc::bn::le16<uint16_t>*)&x_raw;
		uint16_t x_expected = 0x2301;

		// explicit unwrap/wrap
		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le16<uint16_t>::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("tc::bn::le16<uint16_t>::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("tc::bn::le16<uint16_t>::wrap() did not wrap test value correectly");
		}

		// implicit unwrap/wrap
		x_raw_ptr = (tc::bn::le16<uint16_t>*)&x_raw;

		if ((*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le16<uint16_t> implicit unwrap did not return expected result");
		}

		(*x_raw_ptr) = 0;
		if ((*x_raw_ptr) != 0)
		{
			throw tc::Exception("tc::bn::le16<uint16_t> implicit wrap did not wrap value 0x0 correctly");
		}

		(*x_raw_ptr) = x_expected;
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || (*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("tc::bn::le16<uint16_t> implicit wrap did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}