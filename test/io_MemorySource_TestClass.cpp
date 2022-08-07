#include "io_MemorySource_TestClass.h"
#include "SourceTestUtil.h"

#include <tc/io/MemorySource.h>

//---------------------------------------------------------

io_MemorySource_TestClass::io_MemorySource_TestClass() :
	mTestTag("tc::io::MemorySource"),
	mTestResults()
{
}

void io_MemorySource_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testInitializeByCopyWithByteData();
	testInitializeByMoveWithByteData();
	testInitializeByCopyWithMemoryPointer();
	testNegativeOffset();
	testTooLargeOffset();
}

const std::string& io_MemorySource_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_MemorySource_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_MemorySource_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::MemorySource source;

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

void io_MemorySource_TestClass::testInitializeByCopyWithByteData()
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

		tc::io::MemorySource source = tc::io::MemorySource(data);

		SourceTestUtil::testSourceLength(source, length);
		SourceTestUtil::pullTestHelper(source, 0, data.size(), data.size(), data.data());
		SourceTestUtil::pullTestHelper(source, 0, data.size()*2, data.size(), data.data());

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

void io_MemorySource_TestClass::testInitializeByMoveWithByteData()
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

		tc::io::MemorySource source = tc::io::MemorySource(std::move(experiment_data));

		if (experiment_data.size() != 0)
		{
			throw tc::TestException("experiment_data.size() != 0 after being moved from.");
		}
		if (experiment_data.data() != nullptr)
		{
			throw tc::TestException("experiment_data.data() != nullptr after being moved from.");
		}

		SourceTestUtil::testSourceLength(source, length);
		SourceTestUtil::pullTestHelper(source, 0, control_data.size(), control_data.size(), control_data.data());
		SourceTestUtil::pullTestHelper(source, 0, control_data.size()*2, control_data.size(), control_data.data());

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

void io_MemorySource_TestClass::testInitializeByCopyWithMemoryPointer()
{
	TestResult test;
	test.test_name = "testInitializeByCopyWithMemoryPointer";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int64_t length = 0xcafe;
		tc::ByteData data(length);
		memset(data.data(), 0xff, data.size());

		tc::io::MemorySource source = tc::io::MemorySource(data.data(), data.size());

		SourceTestUtil::testSourceLength(source, length);
		SourceTestUtil::pullTestHelper(source, 0, data.size(), data.size(), data.data());
		SourceTestUtil::pullTestHelper(source, 0, data.size()*2, data.size(), data.data());

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

void io_MemorySource_TestClass::testNegativeOffset()
{
	TestResult test;
	test.test_name = "testNegativeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		size_t source_len = 0xbabe;
		tc::io::MemorySource source = tc::io::MemorySource(tc::ByteData(source_len));

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

void io_MemorySource_TestClass::testTooLargeOffset()
{
	TestResult test;
	test.test_name = "testTooLargeOffset";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// create source
		size_t source_len = 0xbabe;
		tc::io::MemorySource source = tc::io::MemorySource(tc::ByteData(source_len));

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