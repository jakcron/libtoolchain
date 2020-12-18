#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include <tc/types.h>

#include "bitfield_TestClass.h"

//---------------------------------------------------------

void bitfield_TestClass::runAllTests(void)
{
	std::cout << "[tc::bitfield] START" << std::endl;
	test_BEByteOrderBEBitOrder();
	//test_LEByteOrderBEBitOrder();
	//test_BEByteOrderLEBitOrder();
	//test_LEByteOrderLEBitOrder();
	std::cout << "[tc::bitfield] END" << std::endl;
}

//---------------------------------------------------------

void bitfield_TestClass::test_BEByteOrderBEBitOrder()
{
	std::cout << "[tc::bitfield] test_BEByteOrderBEBitOrder : " << std::flush;
	try
	{
		try 
		{
			std::stringstream ss;

			// check size
			static const size_t kBitFieldSize = sizeof(uint32_t);
			tc::bitfield<kBitFieldSize, false, false> bf;
			if (sizeof(bf) != kBitFieldSize)
			{
				ss << "sizeof(bf) had value " << std::dec << sizeof(bf) << " (expected " << kBitFieldSize << ")";
				throw tc::Exception(ss.str());
			}

			// clear all bits
			*((uint32_t*)&bf) = 0;

			// check bits
			for (size_t i = 0; i < bf.bit_size(); i++)
			{
				if (bf.test(i) != false)
				{
					ss << "bf.test(" << std::dec << i << ") had value " << std::boolalpha << true << " (expected " << std::boolalpha << false << ")";
					throw tc::Exception(ss.str());
				}
			}

			// set all bits
			*((uint32_t*)&bf) = -1;

			// check bits
			for (size_t i = 0; i < bf.bit_size(); i++)
			{
				if (bf.test(i) != true)
				{
					ss << "bf.test(" << std::dec << i << ") had value " << std::boolalpha << false << " (expected " << std::boolalpha << true << ")";
					throw tc::Exception(ss.str());
				}
			}

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}