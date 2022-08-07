#include "io_SubSink_TestClass.h"

#include <fmt/format.h>

#include <tc/io/SubSink.h>
#include <tc/io/IOUtil.h>

//---------------------------------------------------------

io_SubSink_TestClass::io_SubSink_TestClass() :
	mTestTag("tc::io::SubSink"),
	mTestResults()
{
}

void io_SubSink_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testCreateConstructor();
	testCreateFromNullBase();
	testCreateWithNegativeSubSinkOffset();
	testCreateWithNegativeSubSinkLength();
	testCreateWithExcessiveSubSink();
	testCreateThenSetLength();
	testSetLengthOnDisposedBase();
	testPushDataOnDisposedBase();
	testPushDataOutsideOfBaseRange();
}

const std::string& io_SubSink_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_SubSink_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_SubSink_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::SubSink sink;

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

void io_SubSink_TestClass::testCreateConstructor()
{
	TestResult test;
	test.test_name = "testCreateConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create data to push
		auto data = tc::ByteData(0x100);

		// create base sink
		auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
		base_sink->setLength(0x10000);

		// create sub sink
		int64_t sub_sink_offset = 0xcafe;
		int64_t sub_sink_size = 0x1000;
		auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

		// test
		SinkTestUtil::testSinkLength(sub_sink, sub_sink_size);

		memset(data.data(), 0x33, data.size());
		pushDataTestHelper(sub_sink, base_sink, sub_sink_offset, 0, data, data);
		
		memset(data.data(), 0xea, data.size());
		pushDataTestHelper(sub_sink, base_sink, sub_sink_offset, 0x200, data, data);

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

void io_SubSink_TestClass::testCreateFromNullBase()
{
	TestResult test;
	test.test_name = "testCreateFromNullBase";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create sink
			auto sub_sink = tc::io::SubSink(nullptr, 0, 0);

			throw tc::TestException("Create Constructor did not throw tc::ArgumentNullException where base sink was null");
		}
		catch (tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where base sink was null");
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

void io_SubSink_TestClass::testCreateWithNegativeSubSinkOffset()
{
	TestResult test;
	test.test_name = "testCreateWithNegativeSubSinkOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create data to push
			auto data = tc::ByteData(0x100);

			// create base sink
			auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
			base_sink->setLength(0x10000);

			// create sub sink
			int64_t sub_sink_offset = -1;
			int64_t sub_sink_size = 0x1000;
			auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

			throw tc::TestException("Create Constructor did not throw tc::ArgumentOutOfRangeException sub sink offset was negative");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException("Create Constructor threw the wrong exception sub sink offset was negative");
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

void io_SubSink_TestClass::testCreateWithNegativeSubSinkLength()
{
	TestResult test;
	test.test_name = "testCreateWithNegativeSubSinkLength";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create data to push
			auto data = tc::ByteData(0x100);

			// create base sink
			auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
			base_sink->setLength(0x10000);

			// create sub sink
			int64_t sub_sink_offset = 0x200;
			int64_t sub_sink_size = -1;
			auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

			throw tc::TestException("Create Constructor did not throw tc::ArgumentOutOfRangeException where sub sink size was negative");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where sub sink size was negative");
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

void io_SubSink_TestClass::testCreateWithExcessiveSubSink()
{
	TestResult test;
	test.test_name = "testCreateWithExcessiveSubSink";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create data to push
			auto data = tc::ByteData(0x100);

			// create base sink
			auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
			base_sink->setLength(0x10000);

			// create sub sink
			int64_t sub_sink_offset = base_sink->length() - 1;
			int64_t sub_sink_size = 2;
			auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

			throw tc::TestException("Create Constructor did not throw tc::ArgumentOutOfRangeException where sub sink partially past the end of the base sink");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where sub sink partially past the end of the base sink");
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

void io_SubSink_TestClass::testCreateThenSetLength()
{
	TestResult test;
	test.test_name = "testCreateThenSetLength";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create data to push
			auto data = tc::ByteData(0x100);

			// create base sink
			auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
			base_sink->setLength(0x10000);

			// create sub sink
			int64_t sub_sink_offset = 0xcafe;
			int64_t sub_sink_size = 0x1000;
			auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

			// test
			int64_t new_length = 0xdeadcafe;
			sub_sink.setLength(new_length);

			SinkTestUtil::testSinkLength(sub_sink, new_length);
			
			throw tc::TestException(".setLength() did not throw tc::NotImplementedException where SubSink was initialised");
		}
		catch (tc::NotImplementedException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".setLength() threw the wrong exception where SubSink was initialised");
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

void io_SubSink_TestClass::testSetLengthOnDisposedBase()
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
			tc::io::SubSink sink;

			sink.setLength(0xdeadcafe);

			throw tc::TestException(".setLength() did not throw tc::ObjectDisposedException where SubSink was disposed");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".setLength() threw the wrong exception where SubSink was disposed");
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

void io_SubSink_TestClass::testPushDataOnDisposedBase()
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
			tc::io::SubSink sink;

			sink.pushData(tc::ByteData(0xff), 0);

			throw tc::TestException(".pushData() did not throw tc::ObjectDisposedException where SubSink was disposed");
		}
		catch (tc::ObjectDisposedException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".pushData() threw the wrong exception where SubSink was disposed");
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

void io_SubSink_TestClass::testPushDataOutsideOfBaseRange()
{
	TestResult test;
	test.test_name = "testPushDataOutsideOfBaseRange";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create base sink
		auto base_sink = std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>(new SinkTestUtil::DummySinkTestablePushData());
		base_sink->setLength(0x10000);

		// create sub sink
		int64_t sub_sink_offset = 0xcafe;
		int64_t sub_sink_size = 0x1000;
		auto sub_sink = tc::io::SubSink(base_sink, sub_sink_offset, sub_sink_size);

		// test
		SinkTestUtil::testSinkLength(sub_sink, sub_sink_size);

		// create data to push
		auto push_data = tc::ByteData(0x100);
		memset(push_data.data(), 0x08, push_data.size());

		// create data to expect
		int64_t push_offset = sub_sink_size - 0x20;
		auto expected_data = tc::ByteData(push_data.data(), tc::io::IOUtil::getWritableCount(sub_sink_size, push_offset, push_data.size()));

		pushDataTestHelper(sub_sink, base_sink, sub_sink_offset, push_offset, push_data, expected_data);

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

void io_SubSink_TestClass::pushDataTestHelper(tc::io::ISink& sub_sink, const std::shared_ptr<SinkTestUtil::DummySinkTestablePushData>& base_sink, int64_t sub_base_offset, int64_t sub_push_offset, tc::ByteData& push_data, tc::ByteData& expected_data)
{
	base_sink->setExpectedPushDataCfg(expected_data, sub_base_offset + sub_push_offset);
	size_t push_ret = sub_sink.pushData(push_data, sub_push_offset);
	if (push_ret != expected_data.size())
	{
		throw tc::Exception(fmt::format("pushData(offset: {:d}) returned: {:d}, when it should have been {:d}", sub_push_offset, push_ret, expected_data.size()));
	}
}