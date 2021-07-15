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


		virtual size_t processOption(const std::string& option, const std::vector<std::string>& params);
	};

	OptionParserNew();

	

	void parseOptions(const std::vector<std::string>& args);
	void parseOptions(const std::vector<std::string>& args, size_t pos, size_t num);

	
private:
	OptionParserNew();
	std::string mModuleLabel;

	void addOption(const std::string& opt);
	void addOptionParameter(const std::string& opt, const std::string& param);
	std::map<std::string, std::vector<std::string>> mOptions;
};

}} // namespace tc::cli