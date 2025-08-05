#include <tc/os/Environment.h>
#include <tc/string.h>

#ifdef _WIN32
#include <windows.h>
#else

#endif

bool tc::os::getEnvVar(const std::string& name, std::string& value)
{
	bool did_find_variable = false;
#ifdef _WIN32
	// convert utf-8 to utf-16 for wide char functions
	std::u16string utf16_name;
	tc::string::TranscodeUtil::UTF8ToUTF16(name, utf16_name);

	// get size of environment variable
	size_t required_size = 0;
	_wgetenv_s(&required_size, nullptr, 0, (wchar_t*)utf16_name.c_str());

	// set output if variable was found
	if (required_size != 0)
	{
		// get environment variable
		std::shared_ptr<wchar_t> utf16_value(new wchar_t[required_size]);
		_wgetenv_s(&required_size, utf16_value.get(), required_size, (wchar_t*)utf16_name.c_str());

		// transcode back to utf-8
		tc::string::TranscodeUtil::UTF16ToUTF8((char16_t*)utf16_value.get(), value);

		did_find_variable = true;
	}
#else
	// get ptr to env variable
	char* env_ptr = getenv(name.c_str());

	// set output if variable was found
	if (env_ptr != nullptr)
	{
		value = std::string(env_ptr);
		did_find_variable = true;
	}
#endif
	return did_find_variable;
}

static const std::vector<std::string> kOSTempDirEnvVarList = {"TMPDIR", "TMP", "TEMP", "TEMPDIR"};

void tc::os::getTempDirPath(tc::io::Path& dir_path)
{
#ifdef _WIN32
	DWORD dir_buffer_size = MAX_PATH+1;
	std::shared_ptr<wchar_t> dir_buffer(new wchar_t[dir_buffer_size]);

	DWORD dir_string_size = GetTempPath2W(dir_buffer_size, dir_buffer.get());

	if (dir_string_size == 0)
	{
		throw tc::io::DirectoryNotFoundException("Operating system could not provide temporary directory.");
	}

	dir_path = tc::io::Path(std::u16string(dir_buffer.get()));
#else
	std::string dir_path_str = "";
	for (size_t i = 0; i < kOSTempDirEnvVarList.size(); i++)
	{
		if (tc::os::getEnvVar(kOSTempDirEnvVarList[i], dir_path_str) && dir_path_str != "")
		{
			break;
		}
	}

	if (dir_path_str.size() == 0)
	{
		throw tc::io::DirectoryNotFoundException("Operating system could not provide temporary directory.");
	}

	dir_path = tc::io::Path(dir_path_str);
#endif
}