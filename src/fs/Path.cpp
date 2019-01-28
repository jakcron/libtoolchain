#include <sstream>
#include <tc/fs/Path.h>
#include <tc/string.h>
#include <tc/Exception.h>

#include <iostream>

#ifdef _WIN32
static const char kNativePathDelimiter = tc::fs::Path::kWindowsPathDelimiter; /**< Path delimiter for the native OS */
#else
static const char kNativePathDelimiter = tc::fs::Path::kUnixPathDelimiter; /**< Path delimiter for the native OS */
#endif

tc::fs::Path::Path() :
	mUnicodePath()
{

}

tc::fs::Path::Path(const Path& other) :
	mUnicodePath(other.mUnicodePath)
{
}

tc::fs::Path::Path(Path&& other) :
	mUnicodePath(std::move(other.mUnicodePath))
{
}

tc::fs::Path::Path(const std::vector<std::string>& path_elements) :
	Path()
{
	setPathElementList(path_elements);
}


tc::fs::Path::Path(const std::string& path)
{
	initialisePath(path);
}

tc::fs::Path::Path(const std::u16string& path)
{
	std::string utf8_path;
	string::transcodeUTF16ToUTF8(path, utf8_path);
	initialisePath(utf8_path);
}

tc::fs::Path::Path(const std::u32string& path)
{
	std::string utf8_path;
	string::transcodeUTF32ToUTF8(path, utf8_path);
	initialisePath(utf8_path);
}

tc::fs::Path& tc::fs::Path::operator=(const Path& other)
{
	mUnicodePath = other.mUnicodePath;
	return *this;
}

tc::fs::Path& tc::fs::Path::operator=(Path&& other)
{
	mUnicodePath = std::move(other.mUnicodePath);
	return *this;
}

tc::fs::Path tc::fs::Path::operator+(const Path& other) const
{
	Path new_path = *this;
	new_path.appendPath(other.getPathElementList());
	return new_path;
}

void tc::fs::Path::operator+=(const Path& other)
{
	appendPath(other.mUnicodePath);
}

bool tc::fs::Path::operator==(const Path& other) const
{
	return mUnicodePath == other.mUnicodePath;
}

bool tc::fs::Path::operator!=(const Path& other) const
{
	return !(this->operator==(other));
}

const std::vector<std::string>& tc::fs::Path::getPathElementList() const
{
	return mUnicodePath;
}

void tc::fs::Path::setPathElementList(const std::vector<std::string>& list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		for (size_t j = 0; j < list[i].size(); j++)
		{
			if (list[i].c_str()[j] == '/' || list[i].c_str()[j] == '\\')
				throw tc::Exception(kClassName, "Path delimiter detected in path element list");
		}
	}
	mUnicodePath = list;
}

void tc::fs::Path::initialisePath(const std::string& src)
{
	size_t windows_slash_count = 0;
	size_t unix_slash_count = 0;
	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == kWindowsPathDelimiter)
			windows_slash_count += 1;
		else if (src[i] == kUnixPathDelimiter)
			unix_slash_count += 1;
	}

	if (windows_slash_count != 0 && unix_slash_count != 0)
	{
		throw tc::Exception(kClassName, "Both Windows and Unix path delimiters are present in path");
	}

	char path_delimiter = kNativePathDelimiter;
	if (windows_slash_count > 0)
		path_delimiter = kWindowsPathDelimiter;
	else if (unix_slash_count > 0)
		path_delimiter = kUnixPathDelimiter;


	std::stringstream src_stream(src);

	std::string element;
	while (std::getline(src_stream, element, path_delimiter))
	{
		mUnicodePath.push_back(element);
	}
}

void tc::fs::Path::appendPath(const std::vector<std::string>& other)
{
	for (size_t i = 0; i < other.size(); i++)
	{
		mUnicodePath.push_back(other[i]);
	}
}