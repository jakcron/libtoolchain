#include "cli_OptionParser_TestClass.h"

#include <fmt/format.h>

//---------------------------------------------------------

cli_OptionParser_TestClass::cli_OptionParser_TestClass() :
	mTestTag("tc::cli::OptionParser"),
	mTestResults()
{
}

void cli_OptionParser_TestClass::runAllTests(void)
{
	test_Constructor_DefaultConstructor();
	test_ProcessNoOptionsWithNoHandlers();
	test_ProcessOptionsWithNoHandlers();
	test_ProcessOptionsWithOnlyUnkHandler();
	test_ProcessOptionsWithLiteralHandlers();
	test_ProcessOptionsWithRegexHandlers();
	test_ProcessOptionsWithLiteralAndRegexHandlers();
	test_NullHandlerSupplied();
	test_RegularHandlerProvidesNoOptionLiteralOrRegex();
	test_ProcessMalformedOptions();
}

const std::string& cli_OptionParser_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& cli_OptionParser_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void cli_OptionParser_TestClass::test_Constructor_DefaultConstructor()
{
	TestResult test;
	test.test_name = "test_Constructor_DefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

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

void cli_OptionParser_TestClass::test_ProcessNoOptionsWithNoHandlers()
{
	TestResult test;
	test.test_name = "test_ProcessNoOptionsWithNoHandlers";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		std::vector<std::string> args;

		opt.processOptions(args);

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

void cli_OptionParser_TestClass::test_ProcessOptionsWithNoHandlers()
{
	TestResult test;
	test.test_name = "test_ProcessOptionsWithNoHandlers";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		std::vector<std::string> args = {"-someopt", "someparameter"};

		try 
		{
			opt.processOptions(args);
			throw tc::TestException("Did not throw an ArgumentException for unhandled option");
		}
		catch (const tc::ArgumentException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".processOptions() threw the wrong exception when an unhandled option was detected");
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

void cli_OptionParser_TestClass::test_ProcessOptionsWithOnlyUnkHandler()
{
	TestResult test;
	test.test_name = "test_ProcessOptionsWithOnlyUnkHandler";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		UnkOptionHandler::ResultCode result = UnkOptionHandler::ResultCode::DidNotUseUnkOptionHandler;

		opt.registerUnrecognisedOptionHandler(std::make_shared<UnkOptionHandler>(UnkOptionHandler(result)));

		std::vector<std::string> args = {"-someopt", "someparameter"};

		opt.processOptions(args);

		if (result == UnkOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (result == UnkOptionHandler::ResultCode::DidNotUseUnkOptionHandler)
		{
			throw tc::TestException("Unrecognised option handler was registered but not used.");
		}
		else if (result == UnkOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Unrecognised option handler was registered but the option & parameter were not passed to it correctly.");
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

void cli_OptionParser_TestClass::test_ProcessOptionsWithLiteralHandlers()
{
	TestResult test;
	test.test_name = "test_ProcessOptionsWithLiteralHandlers";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		TestOptionHandler::ResultCode flag_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(flag_result, "-flagoption", "", "-flagoption", {})));

		TestOptionHandler::ResultCode single_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(single_param_result, "-singleparam", "", "-singleparam", {"my_param"})));

		TestOptionHandler::ResultCode multi_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(multi_param_result, "-multiparam", "", "-multiparam", {"my_param1", "my_param2"})));

		std::vector<std::string> args = {"-flagoption", "-singleparam", "my_param", "-multiparam", "my_param1", "my_param2"};

		opt.processOptions(args);

		if (flag_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for flag option) was registered but not used.");
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for flag option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (single_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for single param option) was registered but not used.");
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for single param option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (multi_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but not used.");
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but the option & parameter were not passed to it correctly.");
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

void cli_OptionParser_TestClass::test_ProcessOptionsWithRegexHandlers()
{
	TestResult test;
	test.test_name = "test_ProcessOptionsWithRegexHandlers";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		TestOptionHandler::ResultCode flag_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(flag_result, "", "(-F.a.+)", "-Flag", {})));

		TestOptionHandler::ResultCode single_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(single_param_result, "", "(-s.+)", "-singleparam", {"my_param"})));

		TestOptionHandler::ResultCode multi_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(multi_param_result, "", "(-multiparam)", "-multiparam", {"my_param1", "my_param2"})));

		std::vector<std::string> args = {"-Flag", "-singleparam", "my_param", "-multiparam", "my_param1", "my_param2"};

		opt.processOptions(args);

		if (flag_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for flag option) was registered but not used.");
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for flag option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (single_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for single param option) was registered but not used.");
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for single param option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (multi_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but not used.");
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but the option & parameter were not passed to it correctly.");
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

void cli_OptionParser_TestClass::test_ProcessOptionsWithLiteralAndRegexHandlers()
{
	TestResult test;
	test.test_name = "test_ProcessOptionsWithLiteralAndRegexHandlers";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		TestOptionHandler::ResultCode regex_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(regex_result, "", "(-D.+)", "-DKEY", {"value"})));

		TestOptionHandler::ResultCode flag_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(flag_result, "-flag", "", "-flag", {})));

		TestOptionHandler::ResultCode single_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(single_param_result, "-singleparam", "", "-singleparam", {"my_param"})));

		TestOptionHandler::ResultCode multi_param_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
		opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(multi_param_result, "-multiparam", "", "-multiparam", {"my_param1", "my_param2"})));

		std::vector<std::string> args = {"-flag", "-DKEY=value", "-singleparam", "my_param", "-multiparam", "my_param1", "my_param2"};

		opt.processOptions(args);

		if (regex_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (regex_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for regex option) was registered but not used.");
		}
		else if (regex_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for regex option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (flag_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for flag option) was registered but not used.");
		}
		else if (flag_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for flag option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (single_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for single param option) was registered but not used.");
		}
		else if (single_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for single param option) was registered but the option & parameter were not passed to it correctly.");
		}

		if (multi_param_result == TestOptionHandler::ResultCode::Success)
		{
			/* do nothing */
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotUseOptionHandler)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but not used.");
		}
		else if (multi_param_result == TestOptionHandler::ResultCode::DidNotPassOptionsAndParameters)
		{
			throw tc::TestException("Option handler (for multi param option) was registered but the option & parameter were not passed to it correctly.");
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

void cli_OptionParser_TestClass::test_NullHandlerSupplied()
{
	TestResult test;
	test.test_name = "test_NullHandlerSupplied";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		try 
		{
			opt.registerOptionHandler(std::shared_ptr<tc::cli::OptionParser::IOptionHandler>());
			throw tc::TestException(".registerOptionHandler() did not throw ArgumentNullException when passed a nullptr.");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".registerOptionHandler() threw the wrong exception when passed a nullptr.");
		}
		
		try 
		{
			opt.registerUnrecognisedOptionHandler(std::shared_ptr<tc::cli::OptionParser::IOptionHandler>());
			throw tc::TestException(".registerUnrecognisedOptionHandler() did not throw ArgumentNullException when passed a nullptr.");
		}
		catch (const tc::ArgumentNullException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".registerUnrecognisedOptionHandler() threw the wrong exception when passed a nullptr.");
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

void cli_OptionParser_TestClass::test_RegularHandlerProvidesNoOptionLiteralOrRegex()
{
	TestResult test;
	test.test_name = "test_RegularHandlerProvidesNoOptionLiteralOrRegex";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::cli::OptionParser opt;

		try
		{
			TestOptionHandler::ResultCode test_result = TestOptionHandler::ResultCode::DidNotUseOptionHandler;
			opt.registerOptionHandler(std::make_shared<TestOptionHandler>(TestOptionHandler(test_result, "", "", "-DKEY", {"value"})));
			throw tc::TestException(".registerOptionHandler() Did not throw tc::ArgumentOutOfRangeException when option handler had no option literals or option regex.");
		}
		catch (const tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".registerOptionHandler() threw the wrong exception when option handler had no option literals or option regex.");
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

void cli_OptionParser_TestClass::test_ProcessMalformedOptions()
{
	TestResult test;
	test.test_name = "test_ProcessMalformedOptions";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try 
		{
			tc::cli::OptionParser opt;
			opt.processOptions({"dangling_parameter"});
			throw tc::TestException(".processOptions() did not throw exception for dangling parameter");
		}
		catch (const tc::ArgumentException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".processOptions() threw the wrong exception for dangling parameter");
		}
		
		try 
		{
			tc::cli::OptionParser opt;

			opt.registerOptionHandler(std::make_shared<DummyOptionHandler>(DummyOptionHandler("-opt","")));
			opt.processOptions({"-opt=param", "dangling_parameter"});
			throw tc::TestException(".processOptions() did not throw exception for dangling parameter located after compound option");
		}
		catch (const tc::ArgumentException&) { /* do nothing */ }
		catch (const tc::Exception& e)
		{
			throw tc::TestException(".processOptions() threw the wrong exception for dangling parameter located after compound option");
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