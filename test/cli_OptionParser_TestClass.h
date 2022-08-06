#pragma once
#include "ITestClass.h"
#include <tc/cli/OptionParser.h>

class cli_OptionParser_TestClass : public ITestClass
{
public:
	cli_OptionParser_TestClass();

		// this will run the tests
	void runAllTests();

		// this is the label for this test (for filtering purposes)
	const std::string& getTestTag() const;

		// this is where the test results are written
	const std::vector<ITestClass::TestResult>& getTestResults() const;
private:
	std::string mTestTag;
	std::vector<TestResult> mTestResults;

	void test_Constructor_DefaultConstructor();
	void test_ProcessNoOptionsWithNoHandlers();
	void test_ProcessOptionsWithNoHandlers();
	void test_ProcessOptionsWithOnlyUnkHandler();
	void test_ProcessOptionsWithLiteralHandlers();
	void test_ProcessOptionsWithRegexHandlers();
	void test_ProcessOptionsWithLiteralAndRegexHandlers();
	void test_NullHandlerSupplied();
	void test_RegularHandlerProvidesNoOptionLiteralOrRegex();
	void test_ProcessMalformedOptions();

	class UnkOptionHandler : public tc::cli::OptionParser::IOptionHandler
	{
	public:
		enum class ResultCode
		{
			Success,
			DidNotUseUnkOptionHandler,
			DidNotPassOptionsAndParameters
		};

		UnkOptionHandler(ResultCode& external_result) :
			external_result(external_result)
		{}

		// this throws an exception as it should not be called
		const std::vector<std::string>& getOptionStrings() const
		{
			throw tc::Exception("getOptionStrings() not defined for UnkOptionHandler.");
		}

		// this throws an exception as it should not be called
		const std::vector<std::string>& getOptionRegexPatterns() const
		{
			throw tc::Exception("getOptionRegexPatterns() not defined for UnkOptionHandler.");
		}

		void processOption(const std::string& option, const std::vector<std::string>& params)
		{
			if (option == "-someopt" && params.size() == 1 && params[0] == "someparameter")
			{
				external_result = ResultCode::Success;
			}
			else
			{
				external_result = ResultCode::DidNotPassOptionsAndParameters;
			}
			
		}
	private:
		ResultCode& external_result;
	};

	class TestOptionHandler : public tc::cli::OptionParser::IOptionHandler
	{
	public:
		enum class ResultCode
		{
			Success,
			DidNotUseOptionHandler,
			DidNotPassOptionsAndParameters
		};

		TestOptionHandler(ResultCode& external_result, const std::string& opt_literal, const std::string& opt_regex, const std::string& expected_option, const std::vector<std::string>& expected_params) : 
			mExternalResult(external_result),
			mOptStrings(opt_literal.empty() ? std::vector<std::string>({}) : std::vector<std::string>({opt_literal})),
			mOptRegex(opt_regex.empty() ? std::vector<std::string>({}) : std::vector<std::string>({opt_regex})),
			mExpectedOption(expected_option),
			mExpectedParams(expected_params)
		{}
	
		const std::vector<std::string>& getOptionStrings() const
		{
			return mOptStrings;
		}
	
		const std::vector<std::string>& getOptionRegexPatterns() const
		{
			return mOptRegex;
		}
	
		void processOption(const std::string& option, const std::vector<std::string>& params)
		{
			if (option == mExpectedOption && params == mExpectedParams)
			{
				mExternalResult = ResultCode::Success;
			}
			else
			{
				mExternalResult = ResultCode::DidNotPassOptionsAndParameters;
			}
		}
	private:
		ResultCode& mExternalResult;
		std::vector<std::string> mOptStrings;
		std::vector<std::string> mOptRegex;

		std::string mExpectedOption;
		std::vector<std::string> mExpectedParams;
	};

	class DummyOptionHandler : public tc::cli::OptionParser::IOptionHandler
	{
	public:
		// The constructor is where you link the object to the state you want to modify in the call-back
		DummyOptionHandler(const std::string& opt_literal, const std::string& opt_regex) : 
			mOptStrings(opt_literal.empty() ? std::vector<std::string>({}) : std::vector<std::string>({opt_literal})),
			mOptRegex(opt_regex.empty() ? std::vector<std::string>({}) : std::vector<std::string>({opt_regex}))
		{}
	
		const std::vector<std::string>& getOptionStrings() const
		{
			return mOptStrings;
		}
	
		const std::vector<std::string>& getOptionRegexPatterns() const
		{
			return mOptRegex;
		}
	
		void processOption(const std::string& option, const std::vector<std::string>& params)
		{
			// do nothing
		}
	private:
		std::vector<std::string> mOptStrings;
		std::vector<std::string> mOptRegex;
	};
};