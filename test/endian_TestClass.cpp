#include <tc.h>
#include <iostream>

#include "endian_TestClass.h"

void endian_TestClass::runAllTests()
{
	std::cout << "[:: endian] START" << std::endl;
	testLocalBSwap16();
	testLocalBSwap32();
	testLocalBSwap64();
	testBeUint64Inline();
	testBeUint32Inline();
	testBeUint16Inline();
	testLeUint64Inline();
	testLeUint32Inline();
	testLeUint16Inline();
	testBeUint64Class();
	testBeUint32Class();
	testBeUint16Class();
	testLeUint64Class();
	testLeUint32Class();
	testLeUint16Class();
	std::cout << "[:: endian] END" << std::endl;
}

void endian_TestClass::testLocalBSwap16()
{
	std::cout << "[::__local_bswap16] testLocalBSwap16 : " << std::flush;
	try 
	{
		uint16_t x = 0xabcd;
		uint16_t x_inv = 0xcdab;

		if (__local_bswap16(x) != x_inv)
		{
			throw tc::Exception("__local_bswap16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLocalBSwap32()
{
	std::cout << "[::__local_bswap32] testLocalBSwap32 : " << std::flush;
	try 
	{
		uint32_t x = 0xabcd1234;
		uint32_t x_inv = 0x3412cdab;

		if (__local_bswap32(x) != x_inv)
		{
			throw tc::Exception("__local_bswap32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLocalBSwap64()
{
	std::cout << "[::__local_bswap64] testLocalBSwap64 : " << std::flush;
	try 
	{
		uint64_t x = 0x0123456789abcdef;
		uint64_t x_inv = 0xefcdab8967452301;

		if (__local_bswap64(x) != x_inv)
		{
			throw tc::Exception("__local_bswap64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint64Inline()
{
	std::cout << "[::__be_uint64] testBeUint64Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint64_t* x_raw_ptr = (uint64_t*)&x_raw;
		uint64_t x_expected = 0x0123456789abcdef;

		if (__be_uint64(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__be_uint64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint32Inline()
{
	std::cout << "[::__be_uint32] testBeUint32Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[4] = { 0x01, 0x23, 0x45, 0x67 };
		uint32_t* x_raw_ptr = (uint32_t*)&x_raw;
		uint32_t x_expected = 0x01234567;

		if (__be_uint32(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__be_uint32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint16Inline()
{
	std::cout << "[::__be_uint16] testBeUint16Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[2] = { 0x01, 0x23 };
		uint16_t* x_raw_ptr = (uint16_t*)&x_raw;
		uint16_t x_expected = 0x0123;

		if (__be_uint16(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__be_uint16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint64Inline()
{
	std::cout << "[::__le_uint64] testLeUint64Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint64_t* x_raw_ptr = (uint64_t*)&x_raw;
		uint64_t x_expected = 0xefcdab8967452301;

		if (__le_uint64(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__le_uint64() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint32Inline()
{
	std::cout << "[::__le_uint32] testLeUint32Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[4] = { 0x01, 0x23, 0x45, 0x67 };
		uint32_t* x_raw_ptr = (uint32_t*)&x_raw;
		uint32_t x_expected = 0x67452301;

		if (__le_uint32(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__le_uint32() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint16Inline()
{
	std::cout << "[::__le_uint16] testLeUint16Inline : " << std::flush;
	try 
	{
		uint8_t x_raw[2] = { 0x01, 0x23 };
		uint16_t* x_raw_ptr = (uint16_t*)&x_raw;
		uint16_t x_expected = 0x2301;

		if (__le_uint16(*x_raw_ptr) != x_expected)
		{
			throw tc::Exception("__le_uint16() did not swap as expected");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint64Class()
{
	std::cout << "[::be_uint64_t] testBeUint64Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint8_t x_raw_expected[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		be_uint64_t* x_raw_ptr = (be_uint64_t*)&x_raw;
		uint64_t x_expected = 0x0123456789abcdef;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint64_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("be_uint64_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint64_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint32Class()
{
	std::cout << "[::be_uint32_t] testBeUint32Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		uint8_t x_raw_expected[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		be_uint32_t* x_raw_ptr = (be_uint32_t*)&x_raw;
		uint32_t x_expected = 0x01234567;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint32_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("be_uint32_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint32_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testBeUint16Class()
{
	std::cout << "[::be_uint16_t] testBeUint16Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint16_t)] = { 0x01, 0x23 };
		uint8_t x_raw_expected[sizeof(uint16_t)] = { 0x01, 0x23 };
		be_uint16_t* x_raw_ptr = (be_uint16_t*)&x_raw;
		uint16_t x_expected = 0x0123;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint16_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("be_uint16_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("be_uint16_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint64Class()
{
	std::cout << "[::le_uint64_t] testLeUint64Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		uint8_t x_raw_expected[sizeof(uint64_t)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		le_uint64_t* x_raw_ptr = (le_uint64_t*)&x_raw;
		uint64_t x_expected = 0xefcdab8967452301;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint64_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("le_uint64_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint64_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint64_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint32Class()
{
	std::cout << "[::le_uint32_t] testLeUint32Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		uint8_t x_raw_expected[sizeof(uint32_t)] = { 0x01, 0x23, 0x45, 0x67 };
		le_uint32_t* x_raw_ptr = (le_uint32_t*)&x_raw;
		uint32_t x_expected = 0x67452301;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint32_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("le_uint32_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint32_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint32_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void endian_TestClass::testLeUint16Class()
{
	std::cout << "[::le_uint16_t] testLeUint16Class : " << std::flush;
	try 
	{
		uint8_t x_raw[sizeof(uint16_t)] = { 0x01, 0x23 };
		uint8_t x_raw_expected[sizeof(uint16_t)] = { 0x01, 0x23 };
		le_uint16_t* x_raw_ptr = (le_uint16_t*)&x_raw;
		uint16_t x_expected = 0x2301;

		if (x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint16_t::unwrap() did not return expected result");
		}

		x_raw_ptr->wrap(0);
		if (x_raw_ptr->unwrap() != 0)
		{
			throw tc::Exception("le_uint16_t::wrap() did not wrap value 0x0 correctly");
		}

		x_raw_ptr->wrap(x_expected);
		if (memcmp(x_raw, x_raw_expected, sizeof(uint16_t)) != 0 || x_raw_ptr->unwrap() != x_expected)
		{
			throw tc::Exception("le_uint16_t::wrap() did not wrap test value correectly");
		}
		
		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}
