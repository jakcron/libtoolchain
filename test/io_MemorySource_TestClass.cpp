#include <iostream>
#include <sstream>

#include "io_MemorySource_TestClass.h"
#include "SourceUtil.h"

#include <tc.h>

void io_MemorySource_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::MemorySource] START" << std::endl;
	testDefaultConstructor();
	testCreateFromByteData();
	testCreateFromMemoryPointer();
	testNegativeOffset();
	testTooLargeOffset();
	std::cout << "[tc::io::MemorySource] END" << std::endl;
}

void io_MemorySource_TestClass::testDefaultConstructor()
{
	std::cout << "[tc::io::MemorySource] testDefaultConstructor : " << std::flush;
	try
	{
		try
		{
			tc::io::MemorySource source;

			test::SourceUtil::testSourceLength(source, 0);
			test::SourceUtil::pullTestHelper(source, 0, 0xdead, 0, nullptr);

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

void io_MemorySource_TestClass::testCreateFromByteData()
{
	std::cout << "[tc::io::MemorySource] testCreateFromByteData : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::ByteData data(length);
			memset(data.buffer(), 0xff, data.size());

			tc::io::MemorySource source = tc::io::MemorySource(data);

			test::SourceUtil::testSourceLength(source, length);
			test::SourceUtil::pullTestHelper(source, 0, data.size(), data.size(), data.buffer());
			test::SourceUtil::pullTestHelper(source, 0, data.size()*2, data.size(), data.buffer());

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

void io_MemorySource_TestClass::testCreateFromMemoryPointer()
{
	std::cout << "[tc::io::MemorySource] testCreateFromMemoryPointer : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::ByteData data(length);
			memset(data.buffer(), 0xff, data.size());

			tc::io::MemorySource source = tc::io::MemorySource(data.buffer(), data.size());

			test::SourceUtil::testSourceLength(source, length);
			test::SourceUtil::pullTestHelper(source, 0, data.size(), data.size(), data.buffer());
			test::SourceUtil::pullTestHelper(source, 0, data.size()*2, data.size(), data.buffer());

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

void io_MemorySource_TestClass::testNegativeOffset()
{
	std::cout << "[tc::io::MemorySource] testNegativeOffset : " << std::flush;
	try
	{
		try
		{
			// create source
			size_t source_len = 0xbabe;
			tc::io::MemorySource source = tc::io::MemorySource(tc::ByteData(source_len));

			// test
			test::SourceUtil::testSourceLength(source, source_len);
			test::SourceUtil::pullTestHelper(source, -10, 20, 0, nullptr);

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

void io_MemorySource_TestClass::testTooLargeOffset()
{
	std::cout << "[tc::io::MemorySource] testTooLargeOffset : " << std::flush;
	try
	{
		try
		{
			// create source
			size_t source_len = 0xbabe;
			tc::io::MemorySource source = tc::io::MemorySource(tc::ByteData(source_len));

			// test
			test::SourceUtil::testSourceLength(source, source_len);
			test::SourceUtil::pullTestHelper(source, source_len * 2, 20, 0, nullptr);
			
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