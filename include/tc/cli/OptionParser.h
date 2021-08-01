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
	 * @brief Class for parsing command-line options
	 * 
	 * This class processes command-line options according to user defined implementations of @ref tc::cli::OptionParser::IOptionHandler that are registered with this class.
	 * 
	 * The format of command-line arguments varies by system and convention. This class supports the following styles of command-line options:
	 * * "--opt": Option name prefixed by "--" with no parameters,
	 * * "--opt=var": Option name prefixed by "--" with only one parameter delimetered by "=",
	 * * "--opt var1 var2": Option name prefixed by "--" with one or more parameters delimited by white space,
	 * * "-opt": Option name prefixed by "-" with no parameters,
	 * * "-opt=var": Option name prefixed by "-" with one parameter delimetered by "=",
	 * * "-opt var1 var2": Option name prefixed by "-" with one or more parameters delimited by white space,
	 * 
	 * Command-line options take the form of an option name prefixed with one or two dash characters (e.g. "-i" or "--infile-path") followed by zero or more option values.
	 * Some conventions will allow multiple aliases for a given option (e.g. "-r", "-R", "--recursive"). 
	 * 
	 * Option values can be considered as parameters to the option. Examples include:
	 * 1) Toggling a flag withing program logic: e.g. enabling read-only mode for a forensics tool may used "--read-only" or "-r" as options with no parameters, since the name implies the state.
	 * 2) Passing a variable into the program: e.g. setting the file path for an input file, may use "--infile path/to/file" or "-i path/to/file", an option with one parameter.
	 * 
	 * 
	 * 
	 * 
	 * For example, say we have some state struct like this:
	 * @code
	 * struct UserOpt
	 * {
	 *    std::string sku_code;
	 * };
	 * @endcode 
	 * 
	 * And the command-line is intended be formatted as follows:
	 * @code
	 * someprogram -sku <your SKU code here>
	 * @endcode
	 * 
	 * Then a possible IOptionHandler could be implemented as follows:
	 * @code
	 * class SkuOptionHandler : public tc::cli::OptionParser::IOptionHandler
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
	 * 			throw tc::ArgumentOutOfRangeException("Option \"" + option + "\" requires a parameter.");
	 * 		}
	 * 
	 * 		mUserOpt.sku_code = params[0];
	 * 	}
	 * private:
	 * 	UserOpt& mUserOpt;
	 * 	std::vector<std::string> mOptStrings;
	 * };
	 * @endcode
	 * 
	 * Then register SkuOptionHandler with the OptionParser using OptionParser::registerOptionHandler():
	 * @code
	 * 
	 * UserOpt user_opt;
	 * 
	 * tc::cli::OptionParser opt_parser;
	 * 
	 * opt_parser.registerOptionHandler(std::shared_ptr<SkuOptionHandler>(new SkuOptionHandler(user_opt)))
	 * 
	 * @endcode
	 * 
	 * Then process the command-line arguments with OptionParser::processOptions():
	 * @code
	 * // In this example processOptions
	 * int umain(const std::vector<std::string>& args, const std::vector<std::string>& env)
	 * {
	 * 	UserOpt user_opt;
	 * 	tc::cli::OptionParser opt_parser;
	 * 
	 * 	// register the option handler for "-sku"
	 * 	opt_parser.registerOptionHandler(std::shared_ptr<SkuOptionHandler>(new SkuOptionHandler(user_opt)))
	 * 
	 * 	// since args will include at args[0], the program executable path, use the overload of processOptions that selects a sub vector of args.
	 * 	opt_parser.processOptions(args, 1, args.size()-1);
	 * 
	 * 	// user_opt.sku_type will now be populated if it was set via command-line with "-sku"
	 * 
	 * 	std::cout << "SKUCODE: \"" << user_opt.sku_code << "\"" << std::endl;
	 * 
	 * 	// finish program
	 * 	return 0;
	 * }
	 * @endcode
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