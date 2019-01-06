#include <tc/Exception.h>
#include <iostream>
#include <tc/Optional.h>

void testDefaultConstructor()
{
	std::cout << "[Optional-test] testDefaultConstructor : ";
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

void testWrapConstructor()
{
	std::cout << "[Optional-test] testWrapConstructor : ";
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

void testCopyConstructorFromNullOptional()
{
	std::cout << "[Optional-test] testCopyConstructorFromNullOptional : ";
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

void testCopyConstructorFromExistingOptional()
{
	std::cout << "[Optional-test] testCopyConstructorFromExistingOptional : ";
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

void testWrapOperator()
{
	std::cout << "[Optional-test] testWrapOperator : ";
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

void testCopyOperatorFromNullOptional()
{
	std::cout << "[Optional-test] testCopyOperatorFromNullOptional : ";
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

void testCopyOperatorFromExistingOptional()
{
	std::cout << "[Optional-test] testCopyOperatorFromExistingOptional : ";
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

void testMakeNullOnNullOptional()
{
	std::cout << "[Optional-test] testMakeNullOnNullOptional : ";
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

void testMakeNullOnExistingOptional()
{
	std::cout << "[Optional-test] testMakeNullOnExistingOptional : ";
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

int main(int argc, char** argv)
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