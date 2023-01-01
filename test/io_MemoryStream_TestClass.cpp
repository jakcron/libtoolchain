#include "io_MemoryStream_TestClass.h"
#include "StreamTestUtil.h"

#include <fmt/format.h>

#include <tc/io/MemoryStream.h>

//---------------------------------------------------------

io_MemoryStream_TestClass::io_MemoryStream_TestClass() :
	mTestTag("tc::io::MemoryStream"),
	mTestResults()
{
}

void io_MemoryStream_TestClass::runAllTests(void)
{
	testCreateEmptyStream_DefaultConstructor();
	testCreateEmptyStream_SizedConstructor();
	testCreatePopulatedStream();
	testInitializeByCopyWithByteData();
	testInitializeByMoveWithByteData();
	testInitializeByCopyWithMemoryPointer();
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
}

const std::string& io_MemoryStream_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_MemoryStream_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_MemoryStream_TestClass::testCreateEmptyStream_DefaultConstructor()
{
	TestResult test;
	test.test_name = "testCreateEmptyStream_DefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::MemoryStream stream;

		StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testCreateEmptyStream_SizedConstructor()
{
	TestResult test;
	test.test_name = "testCreateEmptyStream_SizedConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, true, true);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testCreatePopulatedStream()
{
	TestResult test;
	test.test_name = "testCreatePopulatedStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testInitializeByCopyWithByteData()
{
	TestResult test;
	test.test_name = "testInitializeByCopyWithByteData";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;

		tc::ByteData data(length);
		memset(data.data(), 0xff, data.size());

		tc::io::MemoryStream stream = tc::io::MemoryStream(data);

		StreamTestUtil::constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

		tc::ByteData output_data(stream.length());
		stream.read(output_data.data(), output_data.size());

		if (memcmp(output_data.data(), data.data(), length) != 0)
		{
			throw tc::TestException("Data in memory stream was not correct after being constructed from a ByteData object");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testInitializeByMoveWithByteData()
{
	TestResult test;
	test.test_name = "testInitializeByMoveWithByteData";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;

		tc::ByteData control_data(length);
		memset(control_data.data(), 0xff, control_data.size());

		tc::ByteData experiment_data = control_data;

		tc::io::MemoryStream stream = tc::io::MemoryStream(std::move(experiment_data));

		if (experiment_data.size() != 0)
		{
			throw tc::TestException("experiment_data.size() != 0 after being moved from.");
		}
		if (experiment_data.data() != nullptr)
		{
			throw tc::TestException("experiment_data.data() != nullptr after being moved from.");
		}

		StreamTestUtil::constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

		tc::ByteData output_data(stream.length());
		stream.read(output_data.data(), output_data.size());

		if (memcmp(output_data.data(), control_data.data(), length) != 0)
		{
			throw tc::TestException("Data in memory stream was not correct after being constructed from a ByteData object");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testInitializeByCopyWithMemoryPointer()
{
	TestResult test;
	test.test_name = "testInitializeByCopyWithMemoryPointer";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::ByteData data(length);
		tc::io::MemoryStream stream(data.data(), data.size());

		StreamTestUtil::constructor_TestHelper(stream, 0xcafe, 0, true, true, true);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekBeginToZero()
{
	TestResult test;
	test.test_name = "testSeekBeginToZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Begin, 0, 0);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekBeginToMiddle()
{
	TestResult test;
	test.test_name = "testSeekBeginToMiddle";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, 0xbabe, tc::io::SeekOrigin::Begin, 0xbabe, 0xbabe);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekBeginToEnd()
{
	TestResult test;
	test.test_name = "testSeekBeginToEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, length, tc::io::SeekOrigin::Begin, length, length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekBeginPastEnd()
{
	TestResult test;
	test.test_name = "testSeekBeginPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, length+0x10, tc::io::SeekOrigin::Begin, length+0x10, length+0x10);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekBeginNegative()
{
	TestResult test;
	test.test_name = "testSeekBeginNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			StreamTestUtil::seek_TestHelper(stream, -23, tc::io::SeekOrigin::Begin, 0, 0);

			throw tc::TestException(".seek() with position that was negative did not throw tc::ArgumentOutOfRangeException");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".seek() with position that was negative threw the wrong exception ({:s})", e.what()));
		}
			

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekCurrentByZero()
{
	TestResult test;
	test.test_name = "testSeekCurrentByZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0xbabe;
		tc::io::MemoryStream stream(length);

		stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

		StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, seek_pos, seek_pos);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekCurrentToMiddle()
{
	TestResult test;
	test.test_name = "testSeekCurrentToMiddle";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0xbabe;
		tc::io::MemoryStream stream(length);

		stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

		StreamTestUtil::seek_TestHelper(stream, 0x20, tc::io::SeekOrigin::Current, seek_pos+0x20, seek_pos+0x20);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekCurrentToEnd()
{
	TestResult test;
	test.test_name = "testSeekCurrentToEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0xbabe;
		tc::io::MemoryStream stream(length);

		stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

		StreamTestUtil::seek_TestHelper(stream, length - seek_pos, tc::io::SeekOrigin::Current, length, length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekCurrentPastEnd()
{
	TestResult test;
	test.test_name = "testSeekCurrentPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0xbabe;
		tc::io::MemoryStream stream(length);

		// pick a spot within the stream so there is a none-zero Current position to seek from
		stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

		// if we seek "length" from Current (which is seek_pos), then the position should be seek_pos+length
		StreamTestUtil::seek_TestHelper(stream, length, tc::io::SeekOrigin::Current, seek_pos + length, seek_pos + length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekCurrentNegative()
{
	TestResult test;
	test.test_name = "testSeekCurrentNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0xbabe;
		tc::io::MemoryStream stream(length);

		stream.seek(seek_pos, tc::io::SeekOrigin::Begin);

		StreamTestUtil::seek_TestHelper(stream, 0 - seek_pos + 1, tc::io::SeekOrigin::Current, 1, 1);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekEndByZero()
{
	TestResult test;
	test.test_name = "testSeekEndByZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 0;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, seek_pos, tc::io::SeekOrigin::End, length, length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekEndPastEnd()
{
	TestResult test;
	test.test_name = "testSeekEndPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		int64_t seek_pos = 1;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, seek_pos, tc::io::SeekOrigin::End, length + seek_pos, length + seek_pos);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekEndNegative()
{
	TestResult test;
	test.test_name = "testSeekEndNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::io::MemoryStream stream(length);

		StreamTestUtil::seek_TestHelper(stream, 0 - length, tc::io::SeekOrigin::End, 0, 0);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testSeekEndTooNegative()
{
	TestResult test;
	test.test_name = "testSeekEndTooNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			int64_t length = 0xcafe;
			tc::io::MemoryStream stream(length);

			StreamTestUtil::seek_TestHelper(stream, 0 - length - length, tc::io::SeekOrigin::End, 0, 0);

			throw tc::TestException(".seek(SeekOrigin::End) with negative offset greater in magnitude than the stream length did not throw tc::ArgumentOutOfRangeException");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".seek(SeekOrigin::End) with negative offset greater in magnitude than the stream length threw the wrong exception ({:s})", e.what()));
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testReadAllDataAvailable()
{
	TestResult test;
	test.test_name = "testReadAllDataAvailable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0;
		size_t read_len = size_t(stream_length);

		tc::io::MemoryStream stream(stream_length);

		StreamTestUtil::read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len, stream_length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testReadRequestsSubsetOfAvailableData()
{
	TestResult test;
	test.test_name = "testReadRequestsSubsetOfAvailableData";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0;
		size_t read_len = 0xbabe;

		tc::io::MemoryStream stream(stream_length);

		StreamTestUtil::read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len, int64_t(read_len));

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testReadSomeDataAvailable()
{
	TestResult test;
	test.test_name = "testReadSomeDataAvailable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0xbabe;
		size_t read_len = size_t(stream_length);

		tc::io::MemoryStream stream(stream_length);

		StreamTestUtil::read_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, read_len, read_len, read_len - size_t(stream_offset), stream_length);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testReadNoDataAvailable()
{
	TestResult test;
	test.test_name = "testReadNoDataAvailable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		size_t read_len = size_t(stream_length);
		tc::io::MemoryStream stream(stream_length);

		StreamTestUtil::read_TestHelper(stream, 0, tc::io::SeekOrigin::End, read_len, read_len, 0, stream_length);
		StreamTestUtil::read_TestHelper(stream, 20, tc::io::SeekOrigin::End, read_len, read_len, 0, stream_length + 20);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testWriteAllDataWritable()
{
	TestResult test;
	test.test_name = "testWriteAllDataWritable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0;
		size_t data_len = size_t(stream_length);

		tc::ByteData data = tc::ByteData(data_len);
		tc::io::MemoryStream stream(stream_length);

		int64_t stream_expected_position = int64_t(data_len) + stream_offset;

		StreamTestUtil::write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testWriteToSomeOfDataAvailable()
{
	TestResult test;
	test.test_name = "testWriteToSomeOfDataAvailable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0x10;
		size_t data_len = size_t(0xbabe);

		tc::ByteData data = tc::ByteData(data_len);
		tc::io::MemoryStream stream(stream_length);

		int64_t stream_expected_position = int64_t(data_len) + stream_offset;

		StreamTestUtil::write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testWriteSomeDataWritable()
{
	TestResult test;
	test.test_name = "testWriteSomeDataWritable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = 0;
		size_t data_len = size_t(0xdead);

		tc::ByteData data = tc::ByteData(data_len);
		tc::io::MemoryStream stream(stream_length);

		int64_t stream_expected_position = int64_t(data_len) + stream_offset;

		StreamTestUtil::write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position, stream_expected_position);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testWriteNoDataWritable()
{
	TestResult test;
	test.test_name = "testWriteNoDataWritable";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xcafe;
		int64_t stream_offset = stream_length;
		size_t data_len = size_t(0xcafe);

		tc::ByteData data = tc::ByteData(data_len);
		tc::io::MemoryStream stream(stream_length);

		int64_t stream_expected_position = int64_t(data_len) + stream_offset;

		StreamTestUtil::write_TestHelper(stream, stream_offset, tc::io::SeekOrigin::Begin, data, stream_expected_position, stream_expected_position);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testWriteReadDataPersistence()
{
	TestResult test;
	test.test_name = "testWriteReadDataPersistence";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		size_t data_size = 0x100;
		tc::ByteData source(data_size), dst(data_size);

		memset(source.data(), 0xab, source.size());

		tc::io::MemoryStream stream(data_size);

		stream.write(source.data(), source.size());
		stream.seek(0, tc::io::SeekOrigin::Begin);
		stream.read(dst.data(), dst.size());

		if (memcmp(source.data(), dst.data(), data_size) != 0)
		{
			throw tc::TestException("Stream did not read back data written to it");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testResizeStreamLarger()
{
	TestResult test;
	test.test_name = "testResizeStreamLarger";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t initial_len = 0xbabe;
		int64_t new_len = 0xcafe;

		tc::io::MemoryStream stream(initial_len);
		
		// write data to stream
		tc::ByteData initial_data = tc::ByteData(size_t(initial_len));
		memset(initial_data.data(), 0xdf, initial_data.size());
		stream.write(initial_data.data(), initial_data.size());

		// resize stream larger
		stream.setLength(new_len);

		// check stream length
		int64_t len_res = stream.length();

		if (len_res != new_len)
		{
			throw tc::TestException("Stream length was not correct after resizing stream");
		}

		// check stream position
		int64_t pos_res = stream.position();

		if (pos_res != initial_len)
		{
			throw tc::TestException("Stream position was not correct after resizing stream");
		}

		// read data from stream
		tc::ByteData new_data = tc::ByteData(size_t(stream.length()));
		stream.seek(0, tc::io::SeekOrigin::Begin);
		stream.read(new_data.data(), new_data.size());

		// check data was correct
		size_t cmp_size = std::min<size_t>(initial_data.size(), new_data.size());
		if (memcmp(initial_data.data(), new_data.data(), cmp_size) != 0)
		{
			throw tc::TestException("After resizing data was not correct");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testResizeStreamSmaller()
{
	TestResult test;
	test.test_name = "testResizeStreamSmaller";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t initial_len = 0xdead;
		int64_t new_len = 0xcafe;

		tc::io::MemoryStream stream(initial_len);
		
		// write data to stream
		tc::ByteData initial_data = tc::ByteData(size_t(initial_len));
		memset(initial_data.data(), 0xdf, initial_data.size());
		stream.write(initial_data.data(), initial_data.size());

		// resize stream larger
		stream.setLength(new_len);

		// check stream length
		int64_t len_res = stream.length();

		if (len_res != new_len)
		{
			throw tc::TestException("Stream length was not correct after resizing stream");
		}

		// check stream position
		int64_t pos_res = stream.position();

		if (pos_res != new_len)
		{
			throw tc::TestException("Stream position was not correct after resizing stream");
		}

		// read data from stream
		tc::ByteData new_data = tc::ByteData(size_t(stream.length()));
		stream.seek(0, tc::io::SeekOrigin::Begin);
		stream.read(new_data.data(), new_data.size());

		// check data was correct
		size_t cmp_size = std::min<size_t>(initial_data.size(), new_data.size());
		if (memcmp(initial_data.data(), new_data.data(), cmp_size) != 0)
		{
			throw tc::TestException("After resizing data was not correct");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void io_MemoryStream_TestClass::testDispose()
{
	TestResult test;
	test.test_name = "testDispose";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t stream_length = 0xdead;
		tc::io::MemoryStream stream(stream_length);

		// test stream has a valid length pre-disposal
		if (stream.length() != stream_length)
		{
			throw tc::TestException("Stream did not have expected length pre-disposal");
		}

		// dispose stream
		stream.dispose();

		// test stream has a no length post-disposal
		if (stream.length() != 0)
		{
			throw tc::TestException("Stream did not have no length post-disposal");
		}

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}