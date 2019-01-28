#include <tc/Exception.h>
#include <iostream>

#include "Optional_TestClass.h"

void Optional_TestClass::testDefaultConstructor()
{
	std::cout << "[tc::Optional] testDefaultConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::Optional<int> foo;

			if (foo.isNull() == false)
			{
				throw tc::Exception("Default constructor created an object with an incorrect null state");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
	
}

void Optional_TestClass::testWrapConstructor()
{
	std::cout << "[tc::Optional] testWrapConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			int testInt = 42;

			tc::Optional<int> foo(testInt);

			if (foo.isNull() == true)
			{
				throw tc::Exception("Wrapping constructor created an object with an incorrect null state");
			}

			if (foo.get() != testInt)
			{
				throw tc::Exception("Wrapping constructor created an object with an incorrect value");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testCopyConstructorFromNullOptional()
{
	std::cout << "[tc::Optional] testCopyConstructorFromNullOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::Optional<int> foo;
			tc::Optional<int> bar(foo);

			if (bar.isNull() == false)
			{
				throw tc::Exception("Copy constructor created an object with an incorrect null state");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testCopyConstructorFromExistingOptional()
{
	std::cout << "[tc::Optional] testCopyConstructorFromExistingOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			int testInt = 42;

			tc::Optional<int> foo(testInt);
			tc::Optional<int> bar(foo);

			if (bar.isNull() == true)
			{
				throw tc::Exception("Copy constructor created an object with an incorrect null state");
			}

			if (bar.get() != testInt)
			{
				throw tc::Exception("Copy constructor created an object where the wrapped value was unexpected");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testWrapOperator()
{
	std::cout << "[tc::Optional] testWrapOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			int testInt = 42;

			tc::Optional<int> foo;

			foo = testInt;

			if (foo.isNull() == true)
			{
				throw tc::Exception("Wrap operator created an object with an incorrect null state");
			}

			if (foo.get() != testInt)
			{
				throw tc::Exception("Wrap operator created an object where the wrapped value was unexpected");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testCopyOperatorFromNullOptional()
{
	std::cout << "[tc::Optional] testCopyOperatorFromNullOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::Optional<int> foo;
			tc::Optional<int> bar  = foo;

			if (bar.isNull() == false)
			{
				throw tc::Exception("Copy operator created an object with an incorrect null state");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testCopyOperatorFromExistingOptional()
{
	std::cout << "[tc::Optional] testCopyOperatorFromExistingOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			int testInt = 42;

			tc::Optional<int> foo(testInt);
			tc::Optional<int> bar = foo;

			if (bar.isNull() == true)
			{
				throw tc::Exception("Copy operator created an object with an incorrect null state");
			}

			if (bar.get() != testInt)
			{
				throw tc::Exception("Copy operator created an object where the wrapped value was unexpected");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testMakeNullOnNullOptional()
{
	std::cout << "[tc::Optional] testMakeNullOnNullOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::Optional<int> foo;

			foo.makeNull();

			if (foo.isNull() == false)
			{
				throw tc::Exception("Object had incorrect null state");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::testMakeNullOnExistingOptional()
{
	std::cout << "[tc::Optional] testMakeNullOnExistingOptional : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			int testInt = 42;

			tc::Optional<int> foo(testInt);

			foo.makeNull();

			if (foo.isNull() == false)
			{
				throw tc::Exception("Object had incorrect null state");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void Optional_TestClass::runAllTests()
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