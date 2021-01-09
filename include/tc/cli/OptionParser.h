	/**
	 * @file    OptionParser.h
	 * @brief   Declaration of tc::cli::OptionParser
	 * @date    2020/11/10
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
	 * @class OptionParser
	 * @brief Class for parsing commandline arguments
	 */
class OptionParser
{
public:
	OptionParser(const std::vector<std::string>& args);
	OptionParser(const std::vector<std::string>& args, size_t pos, size_t num);

	bool getUnrecognisedOptions(const std::vector<std::string>& known_opts, std::vector<std::string>& unrecognised_opts);

	bool getOption(const std::string& opt) const;
	bool getOption(const std::vector<std::string>& opts) const;
	bool getOption(const std::initializer_list<std::string>& opts) const;

	bool getOption(const std::string& opt, std::string& param) const;
	bool getOption(const std::vector<std::string>& opts, std::string& param) const;
	bool getOption(const std::initializer_list<std::string>& opts, std::string& param) const;

	bool getOption(const std::string& opt, std::vector<std::string>& params) const;
	bool getOption(const std::vector<std::string>& opts, std::vector<std::string>& params) const;
	bool getOption(const std::initializer_list<std::string>& opts, std::vector<std::string>& params) const;

	bool getOption(const std::string& opt, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const;
	bool getOption(const std::vector<std::string>& opts, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const;
	bool getOption(const std::initializer_list<std::string>& opts, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const;
private:
	OptionParser();
	std::string mModuleLabel;

	void addOption(const std::string& opt);
	void addOptionParameter(const std::string& opt, const std::string& param);
	std::map<std::string, std::vector<std::string>> mOptions;
};

}} // namespace tc::cli