#include "io_SubSource_TestClass.h"
#include "SourceTestUtil.h"

#include <tc/io/SubSource.h>
#include <tc/io/PaddingSource.h>
#include <tc/io/OverlayedSource.h>

//---------------------------------------------------------

io_SubSource_TestClass::io_SubSource_TestClass() :
	mTestTag("tc::io::SubSource"),
	mTestResults()
{
}

void io_SubSource_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testCreateConstructor();
	testNegativeOffset();
	testTooLargeOffset();
}

const std::string& io_SubSource_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_SubSource_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_SubSource_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::SubSource source;

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

void io_SubSource_TestClass::testCreateConstructor()
{
	TestResult test;
	test.test_name = "testCreateConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		int64_t sub_offset = 0xc000;
		int64_t sub_length = 0x1000;
		tc::io::PaddingSource expected_subsource = tc::io::PaddingSource(0xff, 0x1000);
		
		tc::io::OverlayedSource base_source = tc::io::OverlayedSource(std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0, 0x10000)), std::make_shared<tc::io::PaddingSource>(expected_subsource), sub_offset, sub_length);
		tc::io::SubSource source = tc::io::SubSource(std::make_shared<tc::io::OverlayedSource>(base_source), sub_offset, sub_length);

		// create expected data
		tc::ByteData expected_data = expected_subsource.pullData(0, expected_subsource.length());

		// test source
		SourceTestUtil::testSourceLength(source, sub_length);
		SourceTestUtil::pullTestHelper(source, 0, sub_length, sub_length, expected_data.data());
		SourceTestUtil::pullTestHelper(source, 0, sub_length*2, sub_length, expected_data.data());

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

void io_SubSource_TestClass::testNegativeOffset()
{
	TestResult test;
	test.test_name = "testNegativeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		int64_t sub_offset = 0xc000;
		int64_t sub_length = 0x1000;
		tc::io::PaddingSource expected_subsource = tc::io::PaddingSource(0xff, 0x1000);
		
		tc::io::OverlayedSource base_source = tc::io::OverlayedSource(std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0, 0x10000)), std::make_shared<tc::io::PaddingSource>(expected_subsource), sub_offset, sub_length);
		tc::io::SubSource source = tc::io::SubSource(std::make_shared<tc::io::OverlayedSource>(base_source), sub_offset, sub_length);

		// test
		SourceTestUtil::testSourceLength(source, sub_length);
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

void io_SubSource_TestClass::testTooLargeOffset()
{
	TestResult test;
	test.test_name = "testTooLargeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		int64_t sub_offset = 0xc000;
		int64_t sub_length = 0x1000;
		tc::io::PaddingSource expected_subsource = tc::io::PaddingSource(0xff, 0x1000);
		
		tc::io::OverlayedSource base_source = tc::io::OverlayedSource(std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0, 0x10000)), std::make_shared<tc::io::PaddingSource>(expected_subsource), sub_offset, sub_length);
		tc::io::SubSource source = tc::io::SubSource(std::make_shared<tc::io::OverlayedSource>(base_source), sub_offset, sub_length);

		// test
		SourceTestUtil::testSourceLength(source, sub_length);
		SourceTestUtil::pullTestHelper(source, sub_length * 2, 20, 0, nullptr);
		
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