#include "io_StreamSink_TestClass.h"
#include "SinkTestUtil.h"
#include "StreamTestUtil.h"

#include <fmt/format.h>

#include <tc/io/StreamSink.h>
#include <tc/io/MemoryStream.h>

//---------------------------------------------------------

io_StreamSink_TestClass::io_StreamSink_TestClass() :
	mTestTag("tc::io::StreamSink"),
	mTestResults()
{
}

void io_StreamSink_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testCreateConstructor();
	testCreateFromNullStream();
	testCreateFromStreamWithoutSeek();
	testCreateFromStreamWithoutRead();
	testCreateFromStreamWithoutWrite();
	testSetLengthOnDisposedBase();
	testPushDataOnDisposedBase();
	testPushDataOutsideOfBaseRange();
}

const std::string& io_StreamSink_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_StreamSink_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_StreamSink_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::StreamSink sink;

		SinkTestUtil::testSinkLength(sink, 0);

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

void io_StreamSink_TestClass::testCreateConstructor()
{
	TestResult test;
	test.test_name = "testCreateConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create sink
		size_t expected_data_len = 0x1000;
		tc::ByteData expected_data(expected_data_len);
		int64_t base_stream_len = 0x100000;
		auto base_stream = std::shared_ptr<tc::io::MemoryStream>(new tc::io::MemoryStream(base_stream_len));	
		tc::io::StreamSink sink = tc::io::StreamSink(base_stream);

		// test
		SinkTestUtil::testSinkLength(sink, base_stream->length());

		memset(expected_data.data(), 0x5A, expected_data.size());
		pushTestHelper(sink, base_stream, expected_data, 0);

		memset(expected_data.data(), 0x08, expected_data.size());
		pushTestHelper(sink, base_stream, expected_data, 0xcafe);

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

void io_StreamSink_TestClass::testCreateFromNullStream()
{
	TestResult test;
	test.test_name = "testCreateFromNullStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			tc::io::StreamSink sink = tc::io::StreamSink(nullptr);

			throw tc::TestException("Create Constructor did not throw tc::ArgumentNullException where base stream was null");
		}
		catch (tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where base stream was null");
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

void io_StreamSink_TestClass::testCreateFromStreamWithoutSeek()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutSeek";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			auto base_stream = StreamTestUtil::DummyStreamBase(0x1000, true, true, false, false, true);
			tc::io::StreamSink sink = tc::io::StreamSink(std::make_shared<StreamTestUtil::DummyStreamBase>(base_stream));

			throw tc::TestException("Create Constructor did not throw tc::NotSupportedException where base stream did not support seeking");
		}
		catch (tc::NotSupportedException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where base stream did not support seeking");
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

void io_StreamSink_TestClass::testCreateFromStreamWithoutRead()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutRead";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create sink
		auto base_stream = StreamTestUtil::DummyStreamBase(0x1000, false, true, true, true, true);
		tc::io::StreamSink sink = tc::io::StreamSink(std::make_shared<StreamTestUtil::DummyStreamBase>(base_stream));

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

void io_StreamSink_TestClass::testCreateFromStreamWithoutWrite()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutWrite";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			auto base_stream = StreamTestUtil::DummyStreamBase(0x1000, true, false, true, true, false);
			tc::io::StreamSink sink = tc::io::StreamSink(std::make_shared<StreamTestUtil::DummyStreamBase>(base_stream));

			throw tc::TestException("Create Constructor did not throw tc::NotSupportedException where base stream did not support writing");
		}
		catch (tc::NotSupportedException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where base stream did not support writing");
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

void io_StreamSink_TestClass::testSetLengthOnDisposedBase()
{
	TestResult test;
	test.test_name = "testSetLengthOnDisposedBase";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			tc::io::StreamSink sink;

			sink.setLength(0xdeadcafe);

			throw tc::TestException("setLength() did not throw tc::ObjectDisposedException where StreamSink was disposed");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("setLength() threw the wrong exception where StreamSink was disposed");
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

void io_StreamSink_TestClass::testPushDataOnDisposedBase()
{
	TestResult test;
	test.test_name = "testPushDataOnDisposedBase";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			tc::io::StreamSink sink;

			sink.pushData(tc::ByteData(0xff), 0);

			throw tc::TestException(".pushData() did not throw tc::ObjectDisposedException where StreamSink was disposed");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException(".pushData() threw the wrong exception where StreamSink was disposed");
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

void io_StreamSink_TestClass::testPushDataOutsideOfBaseRange()
{
	TestResult test;
	test.test_name = "testPushDataOutsideOfBaseRange";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create sink
		size_t data_len = 0x1000;
		tc::ByteData data(data_len);
		int64_t base_stream_len = 0x100000;
		auto base_stream = std::shared_ptr<tc::io::MemoryStream>(new tc::io::MemoryStream(base_stream_len));	
		tc::io::StreamSink sink = tc::io::StreamSink(base_stream);

		// test
		SinkTestUtil::testSinkLength(sink, base_stream->length());

		memset(data.data(), 0x08, data.size());
		pushTestHelper(sink, base_stream, data, base_stream_len);

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

void io_StreamSink_TestClass::pushTestHelper(tc::io::ISink& sink, const std::shared_ptr<tc::io::IStream>& base_stream, tc::ByteData& expected_data, int64_t push_offset)
{
	// push data
	size_t push_ret = sink.pushData(expected_data, push_offset);
	if (push_ret != expected_data.size())
	{		
		throw tc::TestException(fmt::format("pushData(offset: {:d}) returned: {:d}, when it should have been {:d}", push_offset, push_ret, expected_data.size()));
	}	

	// setup memory for reading result of push
	tc::ByteData output_data(expected_data.size());

	int64_t position_ret = base_stream->position();
	int64_t expected_position = push_offset + expected_data.size();
	if (position_ret != expected_position)
	{		
		throw tc::TestException(fmt::format("pushData(offset: {:d}) failed to write enough bytes, position(): {:d}, when it should have been {:d}", push_offset, position_ret, expected_position));
	}	

	int64_t seek_ret = base_stream->seek(push_offset, tc::io::SeekOrigin::Begin);
	if (seek_ret != push_offset)
	{		
		throw tc::TestException(fmt::format("internal test method to adjust base_stream position failed. seek(offset: {:d}, origin: Begin): {:d}, when it should have been {:d}", push_offset, seek_ret, push_offset));
	}
	
	size_t read_ret = base_stream->read(output_data.data(), output_data.size());
	if (read_ret != expected_data.size())
	{		
		throw tc::TestException(fmt::format("internal test method to read from base_stream failed. read(size: {:d}): {:d}, when it should have been {:d}", expected_data.size(), read_ret, expected_data.size()));
	}

	if (memcmp(expected_data.data(), output_data.data(), expected_data.size()) != 0)
	{		
		throw tc::TestException(fmt::format("pushData(offset: {:d}) did not write data to base_stream as expected", push_offset));
	}
}