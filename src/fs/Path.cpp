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
	new_path.appendPath(other.mUnicodePath);
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

tc::fs::Path::const_iterator tc::fs::Path::begin() const
{
	return mUnicodePath.begin();
}

tc::fs::Path::iterator tc::fs::Path::begin()
{
	return mUnicodePath.begin();
}

tc::fs::Path::const_iterator tc::fs::Path::end() const
{
	return mUnicodePath.end();
}

tc::fs::Path::iterator tc::fs::Path::end()
{
	return mUnicodePath.end();
}

void tc::fs::Path::pop_front()
{
	mUnicodePath.pop_front();
}

void tc::fs::Path::pop_back()
{
	mUnicodePath.pop_back();
}

void tc::fs::Path::push_front(const std::string& str)
{
	mUnicodePath.push_front(str);
}

void tc::fs::Path::push_back(const std::string& str)
{
	mUnicodePath.push_back(str);
}

size_t tc::fs::Path::size() const
{
	return mUnicodePath.size();
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

void tc::fs::Path::appendPath(const std::list<std::string>& other)
{
	for (std::list<std::string>::const_iterator itr = other.begin(); itr != other.end(); itr++)
	{
		mUnicodePath.push_back(*itr);
	}
}