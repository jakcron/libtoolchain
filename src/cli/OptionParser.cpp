#include <tc/cli/OptionParser.h>

#include <iostream>
#include <sstream>

tc::cli::OptionParser::OptionParser() :
	mModuleLabel("OptionParser"),
	mOptions(),
	mUnkOptHandler(nullptr)
{
}

void tc::cli::OptionParser::registerOptionHandler(const std::shared_ptr<IOptionHandler>& handler)
{
	if (handler == nullptr)
	{
		// throw exception
		throw tc::ArgumentNullException(mModuleLabel, "OptionHandler was null.");
	}

	for (auto itr = handler->getOptionStrings().begin(); itr != handler->getOptionStrings().end(); itr++)
	{
		mOptions.insert(std::pair<std::string, std::shared_ptr<IOptionHandler>>(*itr, handler));
	}
}

void tc::cli::OptionParser::registerUnrecognisedOptionHandler(const std::shared_ptr<IOptionHandler>& handler)
{
	if (handler == nullptr)
	{
		// throw exception
		throw tc::ArgumentNullException(mModuleLabel, "OptionHandler was null.");
	}

	mUnkOptHandler = handler;
}

void tc::cli::OptionParser::processOptions(const std::vector<std::string>& args)
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

	std::string opt = std::string();
	std::vector<std::string> params = std::vector<std::string>();
	for (auto itr = args.begin(); itr != args.end(); itr++)
	{
		//std::cout << "itr=" << *itr << std::endl;

		// (1) parse the current string
		std::string tmp_opt = std::string();
		std::string tmp_param = std::string();

		// if the string begins with '-' then it is an option (which may be compound)
		if (itr->compare(0,1,"-") == 0)
		{
			//std::cout << "looks like an option" << std::endl;

			// if there is an "=" in this, then this is a compound option & paramter
			size_t equalsign_pos = itr->find('=');
			if (equalsign_pos == std::string::npos)
			{
				//std::cout << "the option looks like a solo option" << std::endl;
				tmp_opt = *itr;				
			}
			else
			{
				//std::cout << "the option looks like a compound opt=param" << std::endl;
				tmp_opt = itr->substr(0, equalsign_pos);
				tmp_param = itr->substr(equalsign_pos + 1, itr->length() - (equalsign_pos + 1));
				//std::cout << " > opt :   " << tmp_opt << std::endl;
				//std::cout << " > param : " << tmp_param << std::endl;
				// --path=here
				// 0123456789a
				// --path : pos=0, size = 6 = equalsign_pos
				// here : pos = 7 = eqialsign_pos + 1, size = 4 = 11 - 7 = itr->length() -(equalsign_pos+1)
				
			}
			
		}
		// otherwise it is a param
		else
		{
			tmp_param = *itr;
		}

		// (2) interprete it in the context of the current state

		// the user has indicated the end of the current option
		// hand off to option handler and clear state
		if (opt.empty() == false && tmp_opt.empty() == false)
		{
			handleOption(opt, params);

			opt = std::string();
			params = std::vector<std::string>();
		}

		// if tmp_opt isn't empty then make it the option
		if (tmp_opt.empty() == false)
		{
			opt = tmp_opt;
		}

		// if tmp_param isn't empty then add it to the param list
		if (tmp_param.empty() == false)
		{
			// if there is no option set, then this is a head-less parameter, throw exception
			if (opt.empty() == true)
			{
				throw tc::ArgumentException(mModuleLabel, "Option parameter was provided without an option.");
			}
			params.push_back(tmp_param);
		}
	}

	// process dangling opt/params
	if (opt.empty() == false)
	{
		handleOption(opt, params);
	}
}

void tc::cli::OptionParser::processOptions(const std::vector<std::string>& args, size_t pos, size_t num)
{
	processOptions({args.begin()+pos, args.begin()+pos+num});
}

void tc::cli::OptionParser::handleOption(const std::string& opt, const std::vector<std::string>& params)
{
	auto itr = mOptions.find(opt);
	if (itr == mOptions.end())
	{
		if (mUnkOptHandler != nullptr)
		{
			mUnkOptHandler->processOption(opt, params);
		}
		else
		{
			//throw tc::ArgumentException(mModuleLabel, fmt::format("Option \"{}\" is not recognised.", (*itr)));
			throw tc::ArgumentException(mModuleLabel, "Option is not recognised.");
		}
	}
	itr->second->processOption(opt, params);
}