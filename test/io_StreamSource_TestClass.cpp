#include "io_StreamSource_TestClass.h"
#include "SourceTestUtil.h"
#include "StreamTestUtil.h"

#include <tc/io/StreamSource.h>
#include <tc/io/MemoryStream.h>

//---------------------------------------------------------

io_StreamSource_TestClass::io_StreamSource_TestClass() :
	mTestTag("tc::io::StreamSource"),
	mTestResults()
{
}

void io_StreamSource_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testCreateConstructor();
	testCreateFromStreamWithoutSeek();
	testCreateFromStreamWithoutRead();
	testCreateFromStreamWithoutWrite();
	testNegativeOffset();
	testTooLargeOffset();
}

const std::string& io_StreamSource_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_StreamSource_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_StreamSource_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::StreamSource source;

		SourceTestUtil::testSourceLength(source, 0);
		SourceTestUtil::pullTestHelper(source, 0, 0xdead, 0, nullptr);

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

void io_StreamSource_TestClass::testCreateConstructor()
{
	TestResult test;
	test.test_name = "testCreateConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		size_t expected_len = 0x1000;
		tc::ByteData expected_data(expected_len);
		memset(expected_data.data(), 0x5A, expected_data.size());
		tc::io::MemoryStream base_stream = tc::io::MemoryStream(expected_data);
		tc::io::StreamSource source = tc::io::StreamSource(std::make_shared<tc::io::MemoryStream>(base_stream));

		// test
		SourceTestUtil::testSourceLength(source, expected_len);
		SourceTestUtil::pullTestHelper(source, 0, expected_data.size(), expected_data.size(), expected_data.data());
		SourceTestUtil::pullTestHelper(source, 0, expected_data.size()*2, expected_data.size(), expected_data.data());

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

void io_StreamSource_TestClass::testCreateFromStreamWithoutSeek()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutSeek";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create source
			tc::io::StreamSource source = tc::io::StreamSource(std::shared_ptr<StreamTestUtil::DummyStreamBase>(new StreamTestUtil::DummyStreamBase(0x1000, true, true, false, true, true)));

			throw tc::TestException("Create Constructor failed to throw tc::NotSupportedException where base stream did not support seeking");
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

void io_StreamSource_TestClass::testCreateFromStreamWithoutRead()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutRead";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			// create source
			tc::io::StreamSource source = tc::io::StreamSource(std::shared_ptr<StreamTestUtil::DummyStreamBase>(new StreamTestUtil::DummyStreamBase(0x1000, false, true, true, false, true)));

			throw tc::TestException("Create Constructor failed to throw tc::NotSupportedException where base stream did not support reading");
		}
		catch (tc::NotSupportedException&) { /* do nothing */ }
		catch (const tc::Exception&)
		{
			throw tc::TestException("Create Constructor threw the wrong exception where base stream did not support reading");
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

void io_StreamSource_TestClass::testCreateFromStreamWithoutWrite()
{
	TestResult test;
	test.test_name = "testCreateFromStreamWithoutWrite";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		tc::io::StreamSource source = tc::io::StreamSource(std::shared_ptr<StreamTestUtil::DummyStreamBase>(new StreamTestUtil::DummyStreamBase(0x1000, true, false, true, false, true)));

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

void io_StreamSource_TestClass::testNegativeOffset()
{
	TestResult test;
	test.test_name = "testNegativeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		size_t expected_len = 0x1000;
		tc::ByteData expected_data(expected_len);
		memset(expected_data.data(), 0x5A, expected_data.size());
		tc::io::MemoryStream base_stream = tc::io::MemoryStream(expected_data);
		tc::io::StreamSource source = tc::io::StreamSource(std::make_shared<tc::io::MemoryStream>(base_stream));

		// test
		SourceTestUtil::testSourceLength(source, expected_len);
		SourceTestUtil::pullTestHelper(source, -10, 20, 0, nullptr);

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

void io_StreamSource_TestClass::testTooLargeOffset()
{
	TestResult test;
	test.test_name = "testTooLargeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		size_t expected_len = 0x1000;
		tc::ByteData expected_data(expected_len);
		memset(expected_data.data(), 0x5A, expected_data.size());
		tc::io::MemoryStream base_stream = tc::io::MemoryStream(expected_data);
		tc::io::StreamSource source = tc::io::StreamSource(std::make_shared<tc::io::MemoryStream>(base_stream));

		// test
		SourceTestUtil::testSourceLength(source, expected_len);
		SourceTestUtil::pullTestHelper(source, expected_len * 2, 20, 0, nullptr);
		
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