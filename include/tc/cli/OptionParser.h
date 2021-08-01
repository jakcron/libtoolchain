	/**
	 * @file    OptionParser.h
	 * @brief   Declaration of tc::cli::OptionParser
	 * @date    2021/07/13
	 * @authors Jack (jakcron)
	 */
#pragma once
#include <vector>
#include <map>
#include <string>
#include <tc/Optional.h>
#include <tc/ArgumentException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace cli {

	/**
	 * @class OptionParser
	 * @brief Class for parsing commandline arguments
	 * 
	 * This class uses call-backs to handle processing of command-line arguments.
	 * 
	 * For example, say we have some state struct like this
	 * @code
	 * struct UserOpt
	 * {
	 *    std::string sku_code;
	 * };
	 * 
	 * UserOpt user_opt;
	 * @endcode 
	 * 
	 * And the command-line should be formatted like this:
	 * @code
	 * someprogram -sku <your SKU code here>
	 * @endcode
	 * 
	 * Then a possible IOptionHandler could be implemented as follows
	 * @code
	 * class SkuOptionHandler : public tc::cli::OptionParserNew::IOptionHandler
	 * {
	 * public:
	 * 	SkuOptionHandler(UserOpt& user_opt) : 
	 * 		mUserOpt(user_opt),
	 * 		mOptStrings({"-sku"})
	 * 	{}
	 * 
	 * 	const std::vector<std::string>& getOptionStrings() const
	 * 	{
	 * 		return mOptStrings;
	 * 	}
	 * 
	 * 	void processOption(const std::string& option, const std::vector<std::string>& params)
	 * 	{
	 * 		// validate number of paramaters (in this case you we only want 1 parameter)
	 * 		if (params.size() != 1)
	 * 		{
	 * 			throw tc::ArgumentOutOfRangeException(fmt::format("Option \"{:s}\" requires a parameter.", option));
	 * 		}
	 * 
	 * 		mUserOpt.sku_code = params[0];
	 * 	}
	 * private:
	 * 	UserOpt& mUserOpt;
	 * 	std::vector<std::string> mOptStrings;
	 * };
	 * 
	 * @endcode
	 * 
	 * A @ref OptionParser::IOptionHandler class must be implemented and registered with the OptionParser instance
	 */
class OptionParser
{
public:
	class IOptionHandler
	{
	public:
		virtual ~IOptionHandler() = default;

		virtual const std::vector<std::string>& getOptionStrings() const = 0;

		virtual void processOption(const std::string& option, const std::vector<std::string>& params) = 0;
	};

	OptionParser();

	void registerOptionHandler(const std::shared_ptr<IOptionHandler>& handler);
	void registerUnrecognisedOptionHandler(const std::shared_ptr<IOptionHandler>& handler);

	void processOptions(const std::vector<std::string>& args);
	void processOptions(const std::vector<std::string>& args, size_t pos, size_t num);

private:
	std::string mModuleLabel;

	void handleOption(const std::string& opt, const std::vector<std::string>& params);
	std::map<std::string, std::shared_ptr<IOptionHandler>> mOptions;
	std::shared_ptr<IOptionHandler> mUnkOptHandler;
};

}} // namespace tc::cli