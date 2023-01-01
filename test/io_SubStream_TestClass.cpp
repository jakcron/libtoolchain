#include "io_SubStream_TestClass.h"
#include "StreamTestUtil.h"

#include <tc/io/SubStream.h>

//---------------------------------------------------------

io_SubStream_TestClass::io_SubStream_TestClass() :
	mTestTag("tc::io::SubStream"),
	mTestResults()
{
}

void io_SubStream_TestClass::runAllTests(void)
{
	testProperties();
	testSize();
	testSeekPos();
	testRead();
	testWrite();
}

const std::string& io_SubStream_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_SubStream_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_SubStream_TestClass::testProperties()
{
	TestResult test;
	test.test_name = "testProperties";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{
			}
		};

		int64_t substream_offset = 0x56;
		int64_t substream_length = 0x1000;

		auto dummy_stream = std::shared_ptr<DummyStream>(new DummyStream());
		dummy_stream->init(0x10000, true, true, true, false, true);

		// create null substream
		auto substream = std::shared_ptr<tc::io::SubStream>(new tc::io::SubStream());
		if (substream->canSeek() != false)
		{
			throw tc::TestException("canSeek() returned true when base stream was null.");
		}
		if (substream->canRead() != false)
		{
			throw tc::TestException("canRead() returned true when base stream was null.");
		}
		if (substream->canWrite() != false)
		{
			throw tc::TestException("canWrite() returned true when base stream was null.");
		}

		// create proper substream
		substream = std::shared_ptr<tc::io::SubStream>(new tc::io::SubStream(dummy_stream, substream_offset, substream_length));
		if (substream->canSeek() != true)
		{
			throw tc::TestException("canSeek() returned false when base stream was valid.");
		}
		if (substream->canRead() != true)
		{
			throw tc::TestException("canRead() returned false when base stream was valid.");
		}
		if (substream->canWrite() != true)
		{
			throw tc::TestException("canWrite() returned false when base stream was valid.");
		}

		// basestream has canRead==false
		dummy_stream->init(0x10000, false, true, true, false, true);
		if (substream->canSeek() != true)
		{
			throw tc::TestException("canSeek() returned false when base stream was valid.");
		}
		if (substream->canRead() != false)
		{
			throw tc::TestException("canRead() returned true when base stream was valid, but basestream->canRead() was false.");
		}
		if (substream->canWrite() != true)
		{
			throw tc::TestException("canWrite() returned false when base stream was valid.");
		}

		// basestream has canWrite==false
		dummy_stream->init(0x10000, true, false, true, false, true);
		if (substream->canSeek() != true)
		{
			throw tc::TestException("canSeek() returned false when base stream was valid.");
		}
		if (substream->canRead() != true)
		{
			throw tc::TestException("canRead() returned false when base stream was valid.");
		}
		if (substream->canWrite() != false)
		{
			throw tc::TestException("canWrite() returned true when base stream was valid, but basestream->canWrite() was false.");
		}

		// basestream has canSeek==false
		dummy_stream->init(0x10000, true, true, false, false, true);
		if (substream->canSeek() != false)
		{
			throw tc::TestException("canSeek() returned true when base stream was valid, but basestream->canSeek() was false.");
		}
		if (substream->canRead() != true)
		{
			throw tc::TestException("canRead() returned false when base stream was valid.");
		}
		if (substream->canWrite() != true)
		{
			throw tc::TestException("canWrite() returned false when base stream was valid.");
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

void io_SubStream_TestClass::testSize()
{
	TestResult test;
	test.test_name = "testSize";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		class DummyStream : public StreamTestUtil::DummyStreamBase
		{
		public:
			DummyStream()
			{
			}
		};

		int64_t substream_offset = 0x56;
		int64_t substream_length = 0x1000;

		// get substream file
		tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_length);

		if (substream.length() != substream_length)
		{
			throw tc::TestException("Unexpected substream length");
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

void io_SubStream_TestClass::testSeekPos()
{
	TestResult test;
	test.test_name = "testSeekPos";
	test.result = "NOT RUN";
	test.comments = "";

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
					throw tc::TestException("The base stream position was not as expected.");
				}

				return count;
			}
		};

		int64_t substream_offset = 0x56;
		int64_t substream_size = 0x1000;

		DummyStream stream;

		// get sandbox file
		tc::io::SubStream substream(std::make_shared<DummyStream>(stream), substream_offset, substream_size);

		int64_t offset_to_seek = 0x337;
		substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

		if (substream.position() != offset_to_seek)
		{
			throw tc::TestException("Was not able to seek as expected");
		}

		substream.read(nullptr, 0x20);

		if (substream.position() != offset_to_seek + 0x20)
		{
			throw tc::TestException("Was not able to seek as expected");
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

void io_SubStream_TestClass::testRead()
{
	TestResult test;
	test.test_name = "testRead";
	test.result = "NOT RUN";
	test.comments = "";

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
					throw tc::TestException("'ptr' pointer was passed to base IStream object not as expected");
				}

				if (count != 0xbabe)
				{
					throw tc::TestException("'count' parameter was passed to base IStream object not as expected");
				}

				return count;
			}
		};

		uint64_t substream_offset = 0x56;
		uint64_t substream_size = 0x100000;

		// get sandbox file
		tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_size);

		uint64_t offset_to_seek = 0x337;
		substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

		byte_t* dummy_ptr = (byte_t*)0xcafe;
		size_t dummy_read_len = 0xbabe;

		substream.read(dummy_ptr, dummy_read_len);

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

void io_SubStream_TestClass::testWrite()
{
	TestResult test;
	test.test_name = "testWrite";
	test.result = "NOT RUN";
	test.comments = "";

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
					throw tc::TestException("'data' pointer was passed to base IStream object not as expected");
				}

				if (count != 0xbabe)
				{
					throw tc::TestException("'count' parameter was passed to base IStream object not as expected");
				}

				return count;
			}
		};

		uint64_t substream_offset = 0x56;
		uint64_t substream_size = 0x100000;

		// get sandbox file
		tc::io::SubStream substream(std::shared_ptr<DummyStream>(new DummyStream()), substream_offset, substream_size);

		uint64_t offset_to_seek = 0x337;
		substream.seek(offset_to_seek, tc::io::SeekOrigin::Begin);

		byte_t* dummy_ptr = (byte_t*)0xcafe;
		size_t dummy_read_len = 0xbabe;

		substream.write(dummy_ptr, dummy_read_len);

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