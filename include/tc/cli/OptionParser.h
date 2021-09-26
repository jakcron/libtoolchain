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
#include <memory>
#include <tc/ArgumentException.h>
#include <tc/ArgumentNullException.h>

namespace tc { namespace cli {

	/**
	 * @class OptionParser
	 * @brief Class for parsing command-line options.
	 * 
	 * This class processes command-line options according to user defined implementations of @ref tc::cli::OptionParser::IOptionHandler that are registered with this class.
	 * 
	 * The format of command-line arguments varies by system and convention. This class supports the following styles of command-line options:
	 * * "--opt": Option name prefixed by "--" with no parameters,
	 * * "--opt=var": Option name prefixed by "--" with only one parameter delimited by "=",
	 * * "--opt var1 var2": Option name prefixed by "--" with one or more parameters delimited by white space,
	 * * "-opt": Option name prefixed by "-" with no parameters,
	 * * "-opt=var": Option name prefixed by "-" with one parameter delimited by "=",
	 * * "-opt var1 var2": Option name prefixed by "-" with one or more parameters delimited by white space,
	 * 
	 * When parsing options from command-line arguments, it will (in order of occurence) collect the option name and the parameters that follow in 
	 * accordance to the above rules, and defer to the user defined @ref tc::cli::OptionParser::IOptionHandler for this option. If none is defined 
	 * it will throw a @ref tc::ArgumentException, or alternatively defer to a user defined unknown option handler (also a @ref tc::cli::OptionParser::IOptionHandler).
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
	 * Then a possible IOptionHandler for "-sku <your SKU code here>" could be implemented as follows:
	 * @code
	 * class SkuOptionHandler : public tc::cli::OptionParser::IOptionHandler
	 * {
	 * public:
	 * 	// The constructor is where you link the object to the state you want to modify in the call-back
	 * 	SkuOptionHandler(UserOpt& user_opt) : 
	 * 		mUserOpt(user_opt),
	 * 		mOptStrings({"-sku"})
	 * 	{}
	 * 
	 * 	// OptionParser uses this to determine which IOptionHandler to use, so this should return all aliases of the option
	 * 	const std::vector<std::string>& getOptionStrings() const
	 * 	{
	 * 		return mOptStrings;
	 * 	}
	 * 
	 * 	// This is what is called when OptionParser defers to IOptionHandler to process the option and any arguments
	 * 	// In your implementation this is where you validate the data and modify your linked state data accordingly
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
	 * Defining an unknown option handler is optional, but at a minimum allows customising the exception.
	 * @code
	 * class UnkOptionHandler : public tc::cli::OptionParser::IOptionHandler
	 * {
	 * public:
	 * 	UnkOptionHandler()
	 * 	{}
	 * 
	 * 	// this throws an exception as it should not be called
	 * 	const std::vector<std::string>& getOptionStrings() const
	 * 	{
	 * 		throw tc::InvalidOperationException("getOptionStrings() not defined for UnkOptionHandler.");
	 * 	}
	 * 
	 * 	void processOption(const std::string& option, const std::vector<std::string>& params)
	 * 	{
	 * 		throw tc::Exception("Unrecognized option: \"" + option + "\"");
	 * 	}
	 * private:
	 * };
	 * @endcode
	 * 
	 * Then process the command-line arguments with OptionParser::processOptions():
	 * @code
	 * int umain(const std::vector<std::string>& args, const std::vector<std::string>& env)
	 * {
	 * 	UserOpt user_opt;
	 * 	tc::cli::OptionParser opt_parser;
	 * 
	 * 	// register the option handler for "-sku"
	 * 	opt_parser.registerOptionHandler(std::shared_ptr<SkuOptionHandler>(new SkuOptionHandler(user_opt)));
	 * 
	 * 	// register the unknown option handler
	 * 	opt_parser.registerUnrecognisedOptionHandler(std::shared_ptr<UnkOptionHandler>(new UnkOptionHandler()));
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

		/**
		 * @class IOptionHandler
		 * @brief Interface for handling command-line options and any parameters, to be used with @ref OptionParser.
		 * 
		 * See @ref OptionParser for an example on how to implement this class.
		 */
	class IOptionHandler
	{
	public:
		virtual ~IOptionHandler() = default;

			/**
			 * @brief Returns a vector of aliases for the option this will handle.
			 */
		virtual const std::vector<std::string>& getOptionStrings() const = 0;

			/**
			 * @brief Processes command-line option and any parameters.
			 * 
			 * @param[in] option This is full option name that was used.
			 * @param[in] params This is a vector of parameters that were supplied with the option name, size may be 0 or more.
			 */ 
		virtual void processOption(const std::string& option, const std::vector<std::string>& params) = 0;
	};

	OptionParser();


		/**
		 * @brief Register an IOptionHandler to handle an option.
		 * 
		 * @param[in] handler Shared pointer to the IOptionHandler.
		 */ 
	void registerOptionHandler(const std::shared_ptr<IOptionHandler>& handler);

		/**
		 * @brief Register an IOptionHandler to handle all unrecognised options. Only use this extra processing of unrecognised options is required beyond a generic exception.
		 * 
		 * @param[in] handler Shared pointer to the IOptionHandler.
		 */ 
	void registerUnrecognisedOptionHandler(const std::shared_ptr<IOptionHandler>& handler);

		/**
		 * @brief Process a vector of command-line args in accordance with the registered option handlers.
		 * 
		 * @param[in] args Command-line args to process.
		 */
	void processOptions(const std::vector<std::string>& args);

		/**
		 * @brief Process a vector of command-line args in accordance with the registered option handlers.
		 * 
		 * @param[in] args Command-line args to process.
		 * @param[in] pos Position in args vector to begin with.
		 * @param[in] num Number of elements in the args vector to process.
		 */
	void processOptions(const std::vector<std::string>& args, size_t pos, size_t num);

private:
	std::string mModuleLabel;

	void handleOption(const std::string& opt, const std::vector<std::string>& params);
	std::map<std::string, std::shared_ptr<IOptionHandler>> mOptions;
	std::shared_ptr<IOptionHandler> mUnkOptHandler;
};

}} // namespace tc::cli