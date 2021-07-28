	/**
	 * @file    OptionParserNew.h
	 * @brief   Declaration of tc::cli::OptionParserNew
	 * @date    2021/07/13
	 * @authors Jack (jakcron)
	 */
#pragma once
#include <vector>
#include <map>
#include <string>
#include <tc/Optional.h>
#include <tc/ArgumentException.h>

namespace tc { namespace cli {

	/**
	 * @class OptionParserNew
	 * @brief Class for parsing commandline arguments
	 */
class OptionParserNew
{
public:
	class IOptionHandler
	{
	public:
		virtual ~IOptionHandler() = default;

		virtual const std::vector<std::string>& getOptionStrings() const = 0;

		virtual void processOption(const std::string& option, const std::vector<std::string>& params) = 0;
	};

	OptionParserNew();

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