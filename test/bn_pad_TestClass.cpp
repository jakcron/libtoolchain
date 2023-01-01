#include "bn_pad_TestClass.h"

#include <fmt/format.h>

#include <tc/bn/pad.h>

//---------------------------------------------------------

bn_pad_TestClass::bn_pad_TestClass() :
	mTestTag("tc::bn::pad"),
	mTestResults()
{
}

void bn_pad_TestClass::runAllTests(void)
{
	test_CorrectSize();
}

const std::string& bn_pad_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& bn_pad_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void bn_pad_TestClass::test_CorrectSize()
{
	TestResult test;
	test.test_name = "test_CorrectSize";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::bn::pad<5> test_pad0;

		if (sizeof(test_pad0) != 5)
		{
			throw tc::TestException("tc::bn::pad<5> had incorrect sizeof()");
		}

		if (test_pad0.size() != 5)
		{
			throw tc::TestException("tc::bn::pad<5> had incorrect pad::size() result");
		}

		tc::bn::pad<0x200> test_pad1;

		if (sizeof(test_pad1) != 0x200)
		{
			throw tc::TestException("tc::bn::pad<0x200> had incorrect sizeof()");
		}

		if (test_pad1.size() != 0x200)
		{
			throw tc::TestException("tc::bn::pad<0x200> had incorrect pad::size() result");
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