#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include "cli_OptionParser_TestClass.h"

//---------------------------------------------------------

void cli_OptionParser_TestClass::runAllTests(void)
{
	std::cout << "[tc::cli::OptionParser] START" << std::endl;
	test_Constructor_DefaultConstructor();
	std::cout << "[tc::cli::OptionParser] END" << std::endl;
}

//---------------------------------------------------------

void cli_OptionParser_TestClass::test_Constructor_DefaultConstructor()
{
	std::cout << "[tc::cli::OptionParser] test_Constructor_DefaultConstructor : " << std::flush;
	try
	{
		try 
		{
			tc::cli::OptionParser opt;

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}