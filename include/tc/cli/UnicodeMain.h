	/**
	 * @file UnicodeMain.h
	 * @brief Declaration of unicode entry point (umain())
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/13
	 **/
#include <string>
#include <vector>
#ifdef _WIN32
#include <wchar.h>
#endif
#include <tc/string/TranscodeUtil.h>

	/// Entry point to define in your program
int umain(const std::vector<std::string>& args);

#ifdef _WIN32
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
	std::vector<std::string> args;
	for (size_t i = 0; i < (size_t)argc; i++)
	{
#ifdef _WIN32
		args.push_back(tc::string::TranscodeUtil::UTF16ToUTF8(std::u16string((char16_t*)argv[i])));
#else
		args.push_back(argv[i]);
#endif
	}

	return umain(args);
}