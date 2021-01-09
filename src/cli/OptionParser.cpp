#include <tc/cli/OptionParser.h>

#include <iostream>
#include <sstream>

tc::cli::OptionParser::OptionParser(const std::vector<std::string>& args) :
	mModuleLabel("OptionParser"),
	mOptions()
{
	/*
	std::cout << "OptionParser" << std::endl;
	std::cout << "  args:" << std::endl;
	
	for (auto itr = args.begin(); itr != args.end(); itr++)
	{
		std::cout << "  #" << *itr << "#" << std::endl;
	}
	*/

	//std::cout << "Begin parsing options" << std::endl;

	std::string key = std::string();
	for (auto itr = args.begin(); itr != args.end(); itr++)
	{
		//std::cout << "itr=" << *itr << std::endl;

		// determine if this is an option or option parameter
		// starting with "-" indicates it is an option
		if (itr->compare(0,1,"-") == 0)
		{
			//std::cout << "looks like an option" << std::endl;

			// if there is an "=" in this, then this is a compound option & paramter
			size_t equalsign_pos = itr->find('=');
			if (equalsign_pos == std::string::npos)
			{
				//std::cout << "the option looks like a solo option" << std::endl;
				key = *itr;
				addOption(key);
				// create entry or sth
			}
			else
			{
				//std::cout << "the option looks like a compound option=param" << std::endl;
				std::string opt = itr->substr(0, equalsign_pos);
				std::string param = itr->substr(equalsign_pos + 1, itr->length() - (equalsign_pos + 1));
				//std::cout << " > opt :   " << opt << std::endl;
				//std::cout << " > param : " << param << std::endl;
				// --path=here
				// 0123456789a
				// --path : pos=0, size = 6 = equalsign_pos
				// here : pos = 7 = eqialsign_pos + 1, size = 4 = 11 - 7 = itr->length() -(equalsign_pos+1)
				addOption(opt);
				addOptionParameter(opt, param);

				// clear opt key
				key = std::string();
			}
			
		}
		// if this an option parameter, check we have saved the option
		else if (key.empty() == false)
		{
			//std::cout << "looks like a parameter" << std::endl;
			addOptionParameter(key, *itr);
		}
		else
		{
			throw tc::ArgumentException(mModuleLabel, "Option parameter was provided without an option.");
		}	
	}
}

tc::cli::OptionParser::OptionParser(const std::vector<std::string>& args, size_t pos, size_t num) :
	OptionParser({args.begin()+pos, args.begin()+pos+num})
{
}

bool tc::cli::OptionParser::getUnrecognisedOptions(const std::vector<std::string>& known_opts, std::vector<std::string>& unrecognised_opts)
{
	unrecognised_opts.clear();

	for (auto itr = mOptions.begin(); itr != mOptions.end(); itr++)
	{
		if (std::find(known_opts.begin(), known_opts.end(), itr->first) == known_opts.end())
		{
			unrecognised_opts.push_back(itr->first);
		}	 
	}

	return unrecognised_opts.empty() == false;
}

bool tc::cli::OptionParser::getOption(const std::string& opt) const
{
	return getOption(std::vector<std::string>({opt}));
}

bool tc::cli::OptionParser::getOption(const std::vector<std::string>& opts) const
{
	std::vector<std::string> params;
	return getOption(opts, params, true, 0);
}

bool tc::cli::OptionParser::getOption(const std::initializer_list<std::string>& opts) const
{
	return getOption(std::vector<std::string>(opts));
}

bool tc::cli::OptionParser::getOption(const std::string& opt, std::string& param) const
{
	return getOption(std::vector<std::string>({opt}), param);
}

bool tc::cli::OptionParser::getOption(const std::vector<std::string>& opts, std::string& param) const
{
	std::vector<std::string> params;
	bool result = getOption(opts, params, true, 1);
	if (result != false) param = params[0];
	return result;
}

bool tc::cli::OptionParser::getOption(const std::initializer_list<std::string>& opts, std::string& param) const
{
	return getOption(std::vector<std::string>(opts), param);
}

bool tc::cli::OptionParser::getOption(const std::string& opt, std::vector<std::string>& params) const
{
	return getOption(std::vector<std::string>({opt}), params);
}

bool tc::cli::OptionParser::getOption(const std::vector<std::string>& opts, std::vector<std::string>& params) const
{
	return getOption(opts, params, false, 0);
}

bool tc::cli::OptionParser::getOption(const std::initializer_list<std::string>& opts, std::vector<std::string>& params) const
{
	return getOption(std::vector<std::string>(opts), params);
}

bool tc::cli::OptionParser::getOption(const std::string& opt, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const
{
	return getOption(std::vector<std::string>({opt}), params, restrict_param_num, param_num);
}

bool tc::cli::OptionParser::getOption(const std::vector<std::string>& opts, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const
{
	//std::cout << "getOption() BEGIN" << std::endl;

	std::vector<std::string> existing_opts;

	params.clear();
	for (auto itr = opts.begin(); itr != opts.end(); itr++)
	{
		auto map_itr = mOptions.find(*itr);

		if (map_itr != mOptions.end())
		{
			existing_opts.push_back(*itr);
			params.insert(params.end(), map_itr->second.begin(), map_itr->second.end());
		}
	}

	if (existing_opts.empty() == false && restrict_param_num && params.size() != param_num)
	{
		std::stringstream ss;
		ss << (existing_opts.size() > 1 ? "Options " : "Option ");
		for (auto itr = existing_opts.begin(); itr != existing_opts.end(); itr++)
		{
			if (itr != existing_opts.begin())
				ss << ", ";
			ss << *itr;
		}
		switch (param_num)
		{
			case 0:
				ss << " takes no parameters";
				break;
			case 1:
				ss << " requires one parameter";
				break;
			default:
				ss << " requires " << param_num << " parameters";
		}
		throw tc::ArgumentException(mModuleLabel, ss.str());
	}

	//std::cout << "getOption() END" << std::endl;

	return existing_opts.empty() == false;
}

bool tc::cli::OptionParser::getOption(const std::initializer_list<std::string>& opts, std::vector<std::string>& params, bool restrict_param_num, size_t param_num) const
{
	return getOption(std::vector<std::string>(opts), params, restrict_param_num, param_num);
}

void tc::cli::OptionParser::addOption(const std::string& opt)
{
	auto itr = mOptions.find(opt);
	if (itr == mOptions.end())
	{
		mOptions.insert(std::pair<std::string, std::vector<std::string>>(opt, std::vector<std::string>()));
	}
}

void tc::cli::OptionParser::addOptionParameter(const std::string& opt, const std::string& param)
{
	mOptions[opt].push_back(param);
}