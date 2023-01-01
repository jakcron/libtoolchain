#include "io_PaddingSource_TestClass.h"
#include "SourceTestUtil.h"

#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

io_PaddingSource_TestClass::io_PaddingSource_TestClass() :
	mTestTag("tc::io::PaddingSource"),
	mTestResults()
{
}

void io_PaddingSource_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testCreateConstructor();
	testNegativeOffset();
	testTooLargeOffset();
}

const std::string& io_PaddingSource_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_PaddingSource_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_PaddingSource_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::PaddingSource source;

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

void io_PaddingSource_TestClass::testCreateConstructor()
{
	TestResult test;
	test.test_name = "testCreateConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		byte_t padding_byte = 0xef;
		int64_t source_len = 0x21432;
		tc::io::PaddingSource source(padding_byte, source_len);

		// create expected data
		tc::ByteData expected_data(source_len);
		memset(expected_data.data(), padding_byte, expected_data.size());

		// test source
		SourceTestUtil::testSourceLength(source, source_len);
		SourceTestUtil::pullTestHelper(source, 0, source_len, source_len, expected_data.data());
		SourceTestUtil::pullTestHelper(source, 0, source_len/2, source_len/2, expected_data.data());
		SourceTestUtil::pullTestHelper(source, 0, source_len*2, source_len, expected_data.data());

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

void io_PaddingSource_TestClass::testNegativeOffset()
{
	TestResult test;
	test.test_name = "testNegativeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		byte_t padding_byte = 0xef;
		int64_t source_len = 0x21432;
		tc::io::PaddingSource source(padding_byte, source_len);

		// test
		SourceTestUtil::testSourceLength(source, source_len);
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

void io_PaddingSource_TestClass::testTooLargeOffset()
{
	TestResult test;
	test.test_name = "testTooLargeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		byte_t padding_byte = 0xef;
		int64_t source_len = 0x21432;
		tc::io::PaddingSource source(padding_byte, source_len);

		// test
		SourceTestUtil::testSourceLength(source, source_len);
		SourceTestUtil::pullTestHelper(source, source_len * 2, 20, 0, nullptr);
		
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