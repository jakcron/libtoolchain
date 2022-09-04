#include "io_EmptyStream_TestClass.h"
#include "StreamTestUtil.h"

#include <fmt/format.h>

#include <tc/io/EmptyStream.h>

//---------------------------------------------------------

io_EmptyStream_TestClass::io_EmptyStream_TestClass() :
	mTestTag("tc::io::EmptyStream"),
	mTestResults()
{
}

void io_EmptyStream_TestClass::runAllTests(void)
{
	// test constructor sets properties properly
	testCreateEmptyStream_DefaultConstructor();

	// test seek() throws exceptions where it should, but ultimately return 0
	testSeekBeginToZero();
	testSeekBeginPastEnd();
	testSeekBeginNegative();
	testSeekCurrentByZero();
	testSeekCurrentPastEnd();
	testSeekCurrentNegative();
	testSeekEndByZero();
	testSeekEndPastEnd();
	testSeekEndNegative();
	testSeekThrowsOnBadOriginValue();

	// test read() ultimately reads no data into buffer
	testReadDataIsAlwaysZero();
	testReadThrowsOnNullptr();

	// test that write()/setLength() throw not support exception
	testWriteThrowsUnsupported();
	testSetLengthThrowsUnsupported();

	// test that flush/dispose does nothing
	testFlushDoesNothing();
	testDisposeDoesNothing();
}

const std::string& io_EmptyStream_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_EmptyStream_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_EmptyStream_TestClass::testCreateEmptyStream_DefaultConstructor()
{
	TestResult test;
	test.test_name = "testCreateEmptyStream_DefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);

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

void io_EmptyStream_TestClass::testSeekBeginToZero()
{
	TestResult test;
	test.test_name = "testSeekBeginToZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

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

void io_EmptyStream_TestClass::testSeekBeginPastEnd()
{
	TestResult test;
	test.test_name = "testSeekBeginPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0x0;
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, length+0x10, tc::io::SeekOrigin::Begin, 0, 0);

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

void io_EmptyStream_TestClass::testSeekBeginNegative()
{
	TestResult test;
	test.test_name = "testSeekBeginNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, -23, tc::io::SeekOrigin::Begin, 0, 0);

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

void io_EmptyStream_TestClass::testSeekCurrentByZero()
{
	TestResult test;
	test.test_name = "testSeekCurrentByZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::Current, 0, 0);

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

void io_EmptyStream_TestClass::testSeekCurrentPastEnd()
{
	TestResult test;
	test.test_name = "testSeekCurrentPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0x0;
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, length+0x10, tc::io::SeekOrigin::Current, 0, 0);

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

void io_EmptyStream_TestClass::testSeekCurrentNegative()
{
	TestResult test;
	test.test_name = "testSeekCurrentNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, -23, tc::io::SeekOrigin::Current, 0, 0);

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

void io_EmptyStream_TestClass::testSeekEndByZero()
{
	TestResult test;
	test.test_name = "testSeekEndByZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, 0, tc::io::SeekOrigin::End, 0, 0);

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

void io_EmptyStream_TestClass::testSeekEndPastEnd()
{
	TestResult test;
	test.test_name = "testSeekEndPastEnd";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0x0;
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, length+0x10, tc::io::SeekOrigin::End, 0, 0);

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

void io_EmptyStream_TestClass::testSeekEndNegative()
{
	TestResult test;
	test.test_name = "testSeekEndNegative";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::seek_TestHelper(stream, -23, tc::io::SeekOrigin::End, 0, 0);

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

void io_EmptyStream_TestClass::testSeekThrowsOnBadOriginValue()
{
	TestResult test;
	test.test_name = "testSeekThrowsOnBadOriginValue";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::EmptyStream stream;

			StreamTestUtil::seek_TestHelper(stream, -23, (tc::io::SeekOrigin)99, 0, 0);
			throw tc::TestException(".seek() with invalid SeekOrigin did not throw tc::ArgumentOutOfRangeException");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".seek() with invalid SeekOrigin threw the wrong exception ({:s})", e.what()));
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

void io_EmptyStream_TestClass::testReadDataIsAlwaysZero()
{
	TestResult test;
	test.test_name = "testReadDataIsAlwaysZero";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::EmptyStream stream;

		StreamTestUtil::read_TestHelper(stream, 0x0, tc::io::SeekOrigin::Begin, 0x0, 0x0, 0x0, 0x0);
		StreamTestUtil::read_TestHelper(stream, 0x0, tc::io::SeekOrigin::Begin, 0x100, 0x0, 0x0, 0x0);
		StreamTestUtil::read_TestHelper(stream, 0x0, tc::io::SeekOrigin::Begin, 0x1000, 0x0, 0x0, 0x0);

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

void io_EmptyStream_TestClass::testReadThrowsOnNullptr()
{
	TestResult test;
	test.test_name = "testReadThrowsOnNullptr";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::EmptyStream stream;

			stream.read(nullptr, 0x10);

			throw tc::TestException(".read() with dst=nullptr did not throw tc::ArgumentNullException");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".read() with dst=nullptr threw the wrong exception ({:s})", e.what()));
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

void io_EmptyStream_TestClass::testWriteThrowsUnsupported()
{
	TestResult test;
	test.test_name = "testWriteThrowsUnsupported";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::EmptyStream stream;

			tc::ByteData test_bytes = tc::ByteData(0x10);
			stream.write(test_bytes.data(), test_bytes.size());

			throw tc::TestException(".write() did not throw tc::NotSupportedException");
		}
		catch (const tc::NotSupportedException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".write() threw the wrong exception ({:s})", e.what()));
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

void io_EmptyStream_TestClass::testSetLengthThrowsUnsupported()
{
	TestResult test;
	test.test_name = "testSetLengthThrowsUnsupported";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::EmptyStream stream;

			stream.setLength(0x10);

			throw tc::TestException(".setLength() did not throw tc::NotSupportedException");
		}
		catch (const tc::NotSupportedException&) { /* do nothing */ }
		catch (const tc::Exception& e) 
		{
			throw tc::TestException(fmt::format(".setLength() threw the wrong exception ({:s})", e.what()));
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

void io_EmptyStream_TestClass::testFlushDoesNothing()
{
	TestResult test;
	test.test_name = "testFlushDoesNothing";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		
		tc::io::EmptyStream stream;

		// call .flush()
		stream.flush();

		// ensure the stream properties haven't changed
		StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);

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

void io_EmptyStream_TestClass::testDisposeDoesNothing()
{
	TestResult test;
	test.test_name = "testDisposeDoesNothing";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		
		tc::io::EmptyStream stream;

		// call .flush()
		stream.flush();

		// ensure the stream properties haven't changed
		StreamTestUtil::constructor_TestHelper(stream, 0, 0, true, false, true);

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