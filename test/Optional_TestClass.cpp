#include "Optional_TestClass.h"

#include <tc/Optional.h>

//---------------------------------------------------------

Optional_TestClass::Optional_TestClass() :
	mTestTag("tc::Optional"),
	mTestResults()
{
}

void Optional_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testWrapConstructor();
	testCopyConstructorFromNullOptional();
	testCopyConstructorFromExistingOptional();
	testWrapOperator();
	testCopyOperatorFromNullOptional();
	testCopyOperatorFromExistingOptional();
	testMakeNullOnNullOptional();
	testMakeNullOnExistingOptional();
}

const std::string& Optional_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& Optional_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void Optional_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::Optional<int> foo;

		if (foo.isNull() == false)
		{
			throw tc::TestException("Default constructor created an object with null state, but isNull() returned false");
		}

		if (foo.isSet() == true)
		{
			throw tc::TestException("Default constructor created an object with null state, but isSet() returned true");
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

void Optional_TestClass::testWrapConstructor()
{
	TestResult test;
	test.test_name = "testWrapConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int testInt = 42;

		tc::Optional<int> foo(testInt);

		if (foo.isNull() == true)
		{
			throw tc::TestException("Wrapping constructor created an object with a valid state, but isNull() returned true");
		}

		if (foo.isSet() == false)
		{
			throw tc::TestException("Wrapping constructor created an object with a valid state, but isSet() returned false");
		}

		if (foo.get() != testInt)
		{
			throw tc::TestException("Wrapping constructor created an object with an incorrect value");
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

void Optional_TestClass::testCopyConstructorFromNullOptional()
{
	TestResult test;
	test.test_name = "testCopyConstructorFromNullOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::Optional<int> foo;
		tc::Optional<int> bar(foo);

		if (bar.isNull() == false)
		{
			throw tc::TestException("Copy constructor created an object with a null state, but isNull() returned false");
		}

		if (bar.isSet() == true)
		{
			throw tc::TestException("Copy constructor created an object with a null state, but isSet() returned true");
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

void Optional_TestClass::testCopyConstructorFromExistingOptional()
{
	TestResult test;
	test.test_name = "testCopyConstructorFromExistingOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int testInt = 42;

		tc::Optional<int> foo(testInt);
		tc::Optional<int> bar(foo);

		if (bar.isNull() == true)
		{
			throw tc::TestException("Copy constructor created an object with a set state, but isNull() returned true");
		}
		if (bar.isSet() == false)
		{
			throw tc::TestException("Copy constructor created an object with a set state, but isSet() returned true");
		}

		if (bar.get() != testInt)
		{
			throw tc::TestException("Copy constructor created an object where the wrapped value was unexpected");
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

void Optional_TestClass::testWrapOperator()
{
	TestResult test;
	test.test_name = "testWrapOperator";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int testInt = 42;

		tc::Optional<int> foo;

		foo = testInt;

		if (foo.isNull() == true)
		{
			throw tc::TestException("Wrap operator created an object with a set state, but isNull() returned true");
		}
		if (foo.isSet() == false)
		{
			throw tc::TestException("Wrap operator created an object with a set state, but isSet() returned false");
		}

		if (foo.get() != testInt)
		{
			throw tc::TestException("Wrap operator created an object where the wrapped value was unexpected");
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

void Optional_TestClass::testCopyOperatorFromNullOptional()
{
	TestResult test;
	test.test_name = "testCopyOperatorFromNullOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::Optional<int> foo;
		tc::Optional<int> bar  = foo;

		if (bar.isNull() == false)
		{
			throw tc::TestException("Copy operator created an object with a null state, but isNull() returned false");
		}

		if (bar.isSet() == true)
		{
			throw tc::TestException("Copy operator created an object with a null state, but isSet() returned false");
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

void Optional_TestClass::testCopyOperatorFromExistingOptional()
{
	TestResult test;
	test.test_name = "testCopyOperatorFromExistingOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int testInt = 42;

		tc::Optional<int> foo(testInt);
		tc::Optional<int> bar = foo;

		if (bar.isNull() == true)
		{
			throw tc::TestException("Copy operator created an object with a set state, but isNull() returned true");
		}
		if (bar.isSet() == false)
		{
			throw tc::TestException("Copy operator created an object with a set state, but isSet() returned false");
		}

		if (bar.get() != testInt)
		{
			throw tc::TestException("Copy operator created an object where the wrapped value was unexpected");
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

void Optional_TestClass::testMakeNullOnNullOptional()
{
	TestResult test;
	test.test_name = "testMakeNullOnNullOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::Optional<int> foo;

		foo.makeNull();

		if (foo.isNull() == false)
		{
			throw tc::TestException("A null Object was nulled by makeNull(), but isNull() returned false");
		}

		if (foo.isSet() == true)
		{
			throw tc::TestException("A null Object was nulled by makeNull() but isSet() returned true");
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

void Optional_TestClass::testMakeNullOnExistingOptional()
{
	TestResult test;
	test.test_name = "testMakeNullOnExistingOptional";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		int testInt = 42;

		tc::Optional<int> foo(testInt);

		foo.makeNull();

		if (foo.isNull() == false)
		{
			throw tc::TestException("A set Object was nulled by makeNull(), but isNull() returned false");
		}

		if (foo.isSet() == true)
		{
			throw tc::TestException("A set Object was nulled by makeNull(), but isSet() returned true");
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