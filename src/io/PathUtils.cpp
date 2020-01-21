#include <tc/io/PathUtils.h>
#include <tc/string.h>

void tc::io::pathToWindowsUTF16(const tc::io::Path& path, std::u16string& out)
{
	std::u16string utf16_element;

	out.clear();
	for (tc::io::Path::const_iterator itr = path.begin(); itr != path.end(); itr++)
	{
		tc::string::transcodeUTF8ToUTF16(*itr, utf16_element);

		out += utf16_element;
		if (itr != --path.end())
			out += std::u16string(u"\\");
		if (utf16_element == std::u16string(u"") && itr == path.begin())
			out += std::u16string(u"\\");
	}
}

void tc::io::pathToUnixUTF8(const tc::io::Path& path, std::string& out)
{
	out.clear();
	for (tc::io::Path::const_iterator itr = path.begin(); itr != path.end(); itr++)
	{
		out += *itr;
		if (itr != --path.end())
			out += "/";
		else if (*itr == "" && itr == path.begin())
			out += "/";
	}
}
