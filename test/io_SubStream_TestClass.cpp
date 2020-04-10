#include <tc/Exception.h>
#include <iostream>

#include "io_SubStream_TestClass.h"
#include "StreamTestUtil.h"

void io_SubStream_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::SubStream] START" << std::endl;
	testSize();
	testSeekPos();
	testRead();
	testWrite();
	std::cout << "[tc::io::SubStream] END" << std::endl;
}

void io_SubStream_TestClass::testSize()
{
	std::cout << "[tc::io::SubStream] testSize : " << std::flush;
	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{
			}
		};

		try
		{
			int64_t substream_offset = 0x56;
			int64_t substream_length = 0x1000;

			// get substream file
			tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_length);

			if (substream.length() != substream_length)
			{
				throw tc::Exception("Unexpected substream length");
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

void io_SubStream_TestClass::testSeekPos()
{
	std::cout << "[tc::io::SubStream] testSeekPos : " << std::flush;
	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{

			}

			virtual size_t read(byte_t* ptr, size_t count)
			{
				if (this->position() != (0x56 + 0x337))
				{
					throw tc::Exception("The base stream position was not as expected.");
				}

				return count;
			}
		};

		try
		{
			int64_t substream_offset = 0x56;
			int64_t substream_size = 0x1000;

			DummyStream stream;

			// get sandbox file
			tc::io::SubStream substream(std::make_shared<DummyStream>(stream), substream_offset, substream_size);

			int64_t offset_to_seek = 0x337;
			substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

			if (substream.position() != offset_to_seek)
			{
				throw tc::Exception("Was not able to seek as expected");
			}

			substream.read(nullptr, 0x20);

			if (substream.position() != offset_to_seek + 0x20)
			{
				throw tc::Exception("Was not able to seek as expected");
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

void io_SubStream_TestClass::testRead()
{
	std::cout << "[tc::io::SubStream] testRead : " << std::flush;
	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{

			}

			virtual size_t read(byte_t* ptr, size_t count)
			{
				if (ptr != (byte_t*)0xcafe)
				{
					throw tc::Exception("'ptr' pointer was passed to base IStream object not as expected");
				}

				if (count != 0xbabe)
				{
					throw tc::Exception("'count' parameter was passed to base IStream object not as expected");
				}

				return count;
			}
		};

		try
		{
			uint64_t substream_offset = 0x56;
			uint64_t substream_size = 0x100000;

			// get sandbox file
			tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_size);

			uint64_t offset_to_seek = 0x337;
			substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xbabe;

			substream.read(dummy_ptr, dummy_read_len);

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

void io_SubStream_TestClass::testWrite()
{
	std::cout << "[tc::io::SubStream] testWrite : " << std::flush;
	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{

			}

			virtual size_t write(const byte_t* data, size_t count)
			{
				if (data != (const byte_t*)0xcafe)
				{
					throw tc::Exception("'data' pointer was passed to base IStream object not as expected");
				}

				if (count != 0xbabe)
				{
					throw tc::Exception("'count' parameter was passed to base IStream object not as expected");
				}

				return count;
			}
		};

		try
		{
			uint64_t substream_offset = 0x56;
			uint64_t substream_size = 0x100000;

			// get sandbox file
			tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_size);

			uint64_t offset_to_seek = 0x337;
			substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xbabe;

			substream.write(dummy_ptr, dummy_read_len);

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