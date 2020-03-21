#include <iostream>
#include <sstream>

#include "io_PaddingSource_TestClass.h"

#include <tc.h>

void io_PaddingSource_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::PaddingSource] START" << std::endl;
	testDefaultConstructor();
	testCreateConstructor();
	testNegativeOffset();
	testTooLargeOffset();
	std::cout << "[tc::io::PaddingSource] END" << std::endl;
}

void io_PaddingSource_TestClass::testDefaultConstructor()
{
	std::cout << "[tc::io::PaddingSource] testDefaultConstructor : " << std::flush;
	try
	{
		try
		{
			std::stringstream error_ss;

			tc::io::PaddingSource source;

			if (source.length() != 0)
			{
				error_ss << "Source did not have length: " << 0;
				throw tc::Exception(error_ss.str());
			}

			size_t pull_len = 0xdead;
			size_t expected_pull_len = 0x0;
			tc::ByteData data = source.pullData(0, pull_len);

			if (data.size() != expected_pull_len)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << expected_pull_len;
				throw tc::Exception(error_ss.str());
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

void io_PaddingSource_TestClass::testCreateConstructor()
{
	std::cout << "[tc::io::PaddingSource] testCreateConstructor : " << std::flush;
	try
	{
		try
		{
			std::stringstream error_ss;

			byte_t padding_byte = 0xef;
			int64_t source_len = 0x21432;
			tc::io::PaddingSource source(padding_byte, source_len);

			// test source length
			if (source.length() != source_len)
			{
				error_ss << "Source did not have length: " << source_len;
				throw tc::Exception(error_ss.str());
			}

			tc::ByteData data;
			size_t pull_len;

			// test reading full size
			data = source.pullData(0, pull_len = source_len);
			if (data.size() != pull_len)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << pull_len;
				throw tc::Exception(error_ss.str());
			}

			// test reading half size
			data = source.pullData(0, pull_len = source_len/2);
			if (data.size() != pull_len)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << pull_len;
				throw tc::Exception(error_ss.str());
			}

			// test reading double size
			data = source.pullData(0, pull_len = source_len*2);
			if (data.size() != source_len)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << source_len;
				throw tc::Exception(error_ss.str());
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

void io_PaddingSource_TestClass::testNegativeOffset()
{
	std::cout << "[tc::io::PaddingSource] testNegativeOffset : " << std::flush;
	try
	{
		try
		{
			std::stringstream error_ss;

			byte_t padding_byte = 0xef;
			int64_t source_len = 0x21432;
			tc::io::PaddingSource source(padding_byte, source_len);

			// test source length
			if (source.length() != source_len)
			{
				error_ss << "Source did not have length: " << source_len;
				throw tc::Exception(error_ss.str());
			}

			tc::ByteData data = source.pullData(-10, 20);

			if (data.size() != 0)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << 0;
				throw tc::Exception(error_ss.str());
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

void io_PaddingSource_TestClass::testTooLargeOffset()
{
	std::cout << "[tc::io::PaddingSource] testTooLargeOffset : " << std::flush;
	try
	{
		try
		{
			std::stringstream error_ss;

			byte_t padding_byte = 0xef;
			int64_t source_len = 0x21432;
			tc::io::PaddingSource source(padding_byte, source_len);

			// test source length
			if (source.length() != source_len)
			{
				error_ss << "Source did not have length: " << source_len;
				throw tc::Exception(error_ss.str());
			}

			tc::ByteData data = source.pullData(source_len * 2, 20);

			if (data.size() != 0)
			{
				error_ss << "pullData() returned ByteData with size(): " << data.size() << ", when it should have been " << 0;
				throw tc::Exception(error_ss.str());
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