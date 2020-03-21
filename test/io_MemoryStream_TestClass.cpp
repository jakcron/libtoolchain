#include <iostream>
#include <sstream>

#include "io_MemoryStream_TestClass.h"

#include <tc.h>

void io_MemoryStream_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::MemoryStream] START" << std::endl;
	testCreateEmptyStream_DefaultConstructor();
	testCreateEmptyStream_SizedConstructor();
	testCreatePopulatedStream();
	testCreateFromByteData();
	testCreateFromMemoryPointer();
	testSeekBeginToZero();
	testSeekBeginToMiddle();
	testSeekBeginToEnd();
	testSeekBeginPastEnd();
	testSeekBeginNegative();
	testSeekCurrentByZero();
	testSeekCurrentToMiddle();
	testSeekCurrentToEnd();
	testSeekCurrentPastEnd();
	testSeekCurrentNegative();
	testSeekEndByZero();
	testSeekEndPastEnd();
	testSeekEndNegative();
	testSeekEndTooNegative();
	testReadAllDataAvailable();
	testReadRequestsSubsetOfAvailableData();
	testReadSomeDataAvailable();
	testReadNoDataAvailable();
	testWriteAllDataWritable();
	testWriteToSomeOfDataAvailable();
	testWriteSomeDataWritable();
	testWriteNoDataWritable();
	testWriteReadDataPersistence();
	testResizeStreamLarger();
	testResizeStreamSmaller();
	testDispose();
	std::cout << "[tc::io::MemoryStream] END" << std::endl;
}

void io_MemoryStream_TestClass::testCreateEmptyStream_DefaultConstructor()
{
	std::cout << "[tc::io::MemoryStream] testCreateEmptyStream_DefaultConstructor : " << std::flush;
	try
	{
		try
		{
			tc::io::MemoryStream stream;

			constructor_TestHelper(stream, 0, 0, true, true, true);

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

void io_MemoryStream_TestClass::testCreateEmptyStream_SizedConstructor()
{
	std::cout << "[tc::io::MemoryStream] testCreateEmptyStream_SizedConstructor : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0;
			tc::io::MemoryStream stream(length);

			constructor_TestHelper(stream, 0, 0, true, true, true);

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

void io_MemoryStream_TestClass::testCreatePopulatedStream()
{
	std::cout << "[tc::io::MemoryStream] testCreatePopulatedStream : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

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

void io_MemoryStream_TestClass::testCreateFromByteData()
{
	std::cout << "[tc::io::MemoryStream] testCreateFromByteData : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream = tc::io::MemoryStream(tc::ByteData(length));

			constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

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

void io_MemoryStream_TestClass::testCreateFromMemoryPointer()
{
	std::cout << "[tc::io::MemoryStream] testCreateFromMemoryPointer : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::ByteData data(length);
			tc::io::MemoryStream stream(data.buffer(), data.size());

			constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

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

void io_MemoryStream_TestClass::testSeekBeginToZero()
{
	std::cout << "[tc::io::MemoryStream] testSeekBeginToZero : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, 0);

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

void io_MemoryStream_TestClass::testSeekBeginToMiddle()
{
	std::cout << "[tc::io::MemoryStream] testSeekBeginToMiddle : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, 0xbabe, tc::io::SeekOrigin::Begin, 0xbabe, 0xbabe);

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

void io_MemoryStream_TestClass::testSeekBeginToEnd()
{
	std::cout << "[tc::io::MemoryStream] testSeekBeginToEnd : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, length, tc::io::SeekOrigin::Begin, length, length);

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

void io_MemoryStream_TestClass::testSeekBeginPastEnd()
{
	std::cout << "[tc::io::MemoryStream] testSeekBeginPastEnd : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, length+0x10, tc::io::SeekOrigin::Begin, length+0x10, length+0x10);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testSeekBeginNegative()
{
	std::cout << "[tc::io::MemoryStream] testSeekBeginNegative : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, -23, tc::io::SeekOrigin::Begin, 0, 0);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testSeekCurrentByZero()
{
	std::cout << "[tc::io::MemoryStream] testSeekCurrentByZero : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0xbabe;
			tc::io::MemoryStream stream(length);

			stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

			seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, seek_pos, seek_pos);

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

void io_MemoryStream_TestClass::testSeekCurrentToMiddle()
{
	std::cout << "[tc::io::MemoryStream] testSeekCurrentToMiddle : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0xbabe;
			tc::io::MemoryStream stream(length);

			stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

			seek_TestHelper(stream, 0x20, tc::io::SeekOrigin::Current, seek_pos+0x20, seek_pos+0x20);

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

void io_MemoryStream_TestClass::testSeekCurrentToEnd()
{
	std::cout << "[tc::io::MemoryStream] testSeekCurrentToEnd : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0xbabe;
			tc::io::MemoryStream stream(length);

			stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

			seek_TestHelper(stream, length - seek_pos, tc::io::SeekOrigin::Current, length, length);

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

void io_MemoryStream_TestClass::testSeekCurrentPastEnd()
{
	std::cout << "[tc::io::MemoryStream] testSeekCurrentPastEnd : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0xbabe;
			tc::io::MemoryStream stream(length);

			stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

			seek_TestHelper(stream, length, tc::io::SeekOrigin::Current, length, length);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testSeekCurrentNegative()
{
	std::cout << "[tc::io::MemoryStream] testSeekCurrentNegative : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0xbabe;
			tc::io::MemoryStream stream(length);

			stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

			seek_TestHelper(stream, 0 - seek_pos + 1, tc::io::SeekOrigin::Current, 1, 1);

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

void io_MemoryStream_TestClass::testSeekEndByZero()
{
	std::cout << "[tc::io::MemoryStream] testSeekEndByZero : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 0;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, seek_pos, tc::io::SeekOrigin::End, length, length);

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

void io_MemoryStream_TestClass::testSeekEndPastEnd()
{
	std::cout << "[tc::io::MemoryStream] testSeekEndPastEnd : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			int64_t seek_pos = 1;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, seek_pos, tc::io::SeekOrigin::End, length+1, length+1);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testSeekEndNegative()
{
	std::cout << "[tc::io::MemoryStream] testSeekEndNegative : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, 0 - length, tc::io::SeekOrigin::End, 0, 0);

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

void io_MemoryStream_TestClass::testSeekEndTooNegative()
{
	std::cout << "[tc::io::MemoryStream] testSeekEndTooNegative : " << std::flush;
	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			seek_TestHelper(stream, 0 - length - length, tc::io::SeekOrigin::End, 0, 0);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testReadAllDataAvailable()
{
	std::cout << "[tc::io::MemoryStream] testReadAllDataAvailable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0;
			size_t read_len = size_t(stream_length);

			tc::io::MemoryStream stream(stream_length);

			read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len, stream_length);

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

void io_MemoryStream_TestClass::testReadRequestsSubsetOfAvailableData()
{
	std::cout << "[tc::io::MemoryStream] testReadRequestsSubsetOfAvailableData : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0;
			size_t read_len = 0xbabe;

			tc::io::MemoryStream stream(stream_length);

			read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len, int64_t(read_len));

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

void io_MemoryStream_TestClass::testReadSomeDataAvailable()
{
	std::cout << "[tc::io::MemoryStream] testReadSomeDataAvailable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0xbabe;
			size_t read_len = size_t(stream_length);

			tc::io::MemoryStream stream(stream_length);

			read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len - size_t(stream_offset), stream_length);

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

void io_MemoryStream_TestClass::testReadNoDataAvailable()
{
	std::cout << "[tc::io::MemoryStream] testReadNoDataAvailable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			size_t read_len = size_t(stream_length);
			tc::io::MemoryStream stream(stream_length);

			read_TestHelper(stream, 0, tc::io::SeekOrigin::End, read_len, read_len, 0, stream_length);

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

void io_MemoryStream_TestClass::testWriteAllDataWritable()
{
	std::cout << "[tc::io::MemoryStream] testWriteAllDataWritable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0;
			size_t data_len = size_t(stream_length);

			tc::ByteData data = tc::ByteData(data_len);
			tc::io::MemoryStream stream(stream_length);

			int64_t stream_expected_position = int64_t(data_len) + stream_offset;

			write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

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

void io_MemoryStream_TestClass::testWriteToSomeOfDataAvailable()
{
	std::cout << "[tc::io::MemoryStream] testWriteToSomeOfDataAvailable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0x10;
			size_t data_len = size_t(0xbabe);

			tc::ByteData data = tc::ByteData(data_len);
			tc::io::MemoryStream stream(stream_length);

			int64_t stream_expected_position = int64_t(data_len) + stream_offset;

			write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

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

void io_MemoryStream_TestClass::testWriteSomeDataWritable()
{
	std::cout << "[tc::io::MemoryStream] testWriteSomeDataWritable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = 0;
			size_t data_len = size_t(0xdead);

			tc::ByteData data = tc::ByteData(data_len);
			tc::io::MemoryStream stream(stream_length);

			int64_t stream_expected_position = int64_t(data_len) + stream_offset;

			write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testWriteNoDataWritable()
{
	std::cout << "[tc::io::MemoryStream] testWriteNoDataWritable : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xcafe;
			int64_t stream_offset = stream_length;
			size_t data_len = size_t(0xcafe);

			tc::ByteData data = tc::ByteData(data_len);
			tc::io::MemoryStream stream(stream_length);

			int64_t stream_expected_position = int64_t(data_len) + stream_offset;

			write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

			std::cout << "FAIL" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_MemoryStream_TestClass::testWriteReadDataPersistence()
{
	std::cout << "[tc::io::MemoryStream] testWriteReadDataPersistence : " << std::flush;
	try
	{
		try
		{
			size_t data_size = 0x100;
			tc::ByteData source(data_size), dst(data_size);

			memset(source.buffer(), 0xab, source.size());

			tc::io::MemoryStream stream(data_size);

			stream.write(source.buffer(), source.size());
			stream.seek(0, tc::io::SeekOrigin::Begin);
			stream.read(dst.buffer(), dst.size());

			if (memcmp(source.buffer(), dst.buffer(), data_size) != 0)
			{
				throw tc::Exception("Stream did not read back data written to it");
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

void io_MemoryStream_TestClass::testResizeStreamLarger()
{
	std::cout << "[tc::io::MemoryStream] testResizeStreamLarger : " << std::flush;
	try
	{
		try
		{
			int64_t initial_len = 0xbabe;
			int64_t new_len = 0xcafe;

			tc::io::MemoryStream stream(initial_len);
			
			// write data to stream
			tc::ByteData initial_data = tc::ByteData(size_t(initial_len));
			memset(initial_data.buffer(), 0xdf, initial_data.size());
			stream.write(initial_data.buffer(), initial_data.size());

			// resize stream larger
			stream.setLength(new_len);

			// check stream length
			int64_t len_res = stream.length();

			if (len_res != new_len)
			{
				throw tc::Exception("Stream length was not correct after resizing stream");
			}

			// check stream position
			int64_t pos_res = stream.position();

			if (pos_res != initial_len)
			{
				throw tc::Exception("Stream position was not correct after resizing stream");
			}

			// read data from stream
			tc::ByteData new_data = tc::ByteData(size_t(stream.length()));
			stream.seek(0, tc::io::SeekOrigin::Begin);
			stream.read(new_data.buffer(), new_data.size());

			// check data was correct
			size_t cmp_size = std::min<size_t>(initial_data.size(), new_data.size());
			if (memcmp(initial_data.buffer(), new_data.buffer(), cmp_size) != 0)
			{
				throw tc::Exception("After resizing data was not correct");
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

void io_MemoryStream_TestClass::testResizeStreamSmaller()
{
	std::cout << "[tc::io::MemoryStream] testResizeStreamSmaller : " << std::flush;
	try
	{
		try
		{
			int64_t initial_len = 0xdead;
			int64_t new_len = 0xcafe;

			tc::io::MemoryStream stream(initial_len);
			
			// write data to stream
			tc::ByteData initial_data = tc::ByteData(size_t(initial_len));
			memset(initial_data.buffer(), 0xdf, initial_data.size());
			stream.write(initial_data.buffer(), initial_data.size());

			// resize stream larger
			stream.setLength(new_len);

			// check stream length
			int64_t len_res = stream.length();

			if (len_res != new_len)
			{
				throw tc::Exception("Stream length was not correct after resizing stream");
			}

			// check stream position
			int64_t pos_res = stream.position();

			if (pos_res != new_len)
			{
				throw tc::Exception("Stream position was not correct after resizing stream");
			}

			// read data from stream
			tc::ByteData new_data = tc::ByteData(size_t(stream.length()));
			stream.seek(0, tc::io::SeekOrigin::Begin);
			stream.read(new_data.buffer(), new_data.size());

			// check data was correct
			size_t cmp_size = std::min<size_t>(initial_data.size(), new_data.size());
			if (memcmp(initial_data.buffer(), new_data.buffer(), cmp_size) != 0)
			{
				throw tc::Exception("After resizing data was not correct");
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

void io_MemoryStream_TestClass::testDispose()
{
	std::cout << "[tc::io::MemoryStream] testDispose : " << std::flush;
	try
	{
		try
		{
			int64_t stream_length = 0xdead;
			tc::io::MemoryStream stream(stream_length);

			// test stream has a valid length pre-disposal
			if (stream.length() != stream_length)
			{
				throw tc::Exception("Stream did not have expected length pre-disposal");
			}

			// dispose stream
			stream.dispose();

			// test stream has a no length post-disposal
			if (stream.length() != 0)
			{
				throw tc::Exception("Stream did not have no length post-disposal");
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

void io_MemoryStream_TestClass::constructor_TestHelper(tc::io::IStream& stream, int64_t stream_length, int64_t exp_pos_res, bool exp_canread_res, bool exp_canwrite_res, bool exp_canseek_res)
{
	std::stringstream error_ss;

	int64_t length_res = stream.length();
	int64_t pos_res = stream.position();
	bool can_read = stream.canRead();
	bool can_write = stream.canWrite();
	bool can_seek = stream.canSeek();

	if (length_res != stream_length)
	{
		error_ss << "Stream did not have length " << stream_length << " (actual " << length_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_read != exp_canread_res)
	{
		error_ss << "Stream property canRead() was not " << std::boolalpha << exp_canread_res << " (actual " << std::boolalpha << can_read << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_write != exp_canwrite_res)
	{
		error_ss << "Stream property canWrite() was not " << std::boolalpha << exp_canwrite_res << " (actual " << std::boolalpha << can_write << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_seek != exp_canseek_res)
	{
		error_ss << "Stream property canSeek() was not " << std::boolalpha << exp_canseek_res << " (actual " << std::boolalpha << can_seek << ")";
		throw tc::Exception(error_ss.str());
	}
}

void io_MemoryStream_TestClass::seek_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, int64_t exp_seek_res, int64_t exp_pos_res)
{
	std::stringstream error_ss;

	int64_t seek_res = stream.seek(seek_offset, seek_origin);
	int64_t pos_res = stream.position();

	if (seek_res != exp_seek_res)
	{
		error_ss << "Stream did not return position from seek " << exp_seek_res << " (actual " << seek_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}

void io_MemoryStream_TestClass::read_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, size_t dst_size, size_t read_count, size_t exp_read_res, int64_t exp_pos_res)
{
	std::stringstream error_ss;

	tc::ByteData data(dst_size);

	// offset the position
	stream.seek(seek_offset, seek_origin);

	// read data
	size_t read_res = stream.read(data.buffer(), data.size());

	// check position
	int64_t pos_res = stream.position();

	// validate read result
	if (read_res != exp_read_res)
	{
		error_ss << "Stream did not read expected number of bytes " << exp_read_res << " (actual " << read_res << ")";
		throw tc::Exception(error_ss.str());
	}

	// validate pos result
	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}

void io_MemoryStream_TestClass::write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, tc::ByteData& data, int64_t exp_pos_res)
{
	std::stringstream error_ss;

	// offset the position
	stream.seek(seek_offset, seek_origin);

	stream.write(data.buffer(), data.size());

	int64_t pos_res = stream.position();

	// validate pos result
	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}