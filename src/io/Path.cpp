#include <sstream>
#include <tc/io/Path.h>
#include <tc/string.h>
#include <tc/Exception.h>

#include <iostream>

#ifdef _WIN32
static const char kNativePathDelimiter = tc::io::Path::kWindowsPathDelimiter; /**< Path delimiter for the native OS */
#else
static const char kNativePathDelimiter = tc::io::Path::kUnixPathDelimiter; /**< Path delimiter for the native OS */
#endif

const std::string tc::io::Path::kClassName = "tc::io::Path";

tc::io::Path::Path()
{}

tc::io::Path::Path(const std::string& path)
{
	initialisePath(path);
}

tc::io::Path::Path(const std::u16string& path)
{
	std::string utf8_path;
	string::TranscodeUtil::UTF16ToUTF8(path, utf8_path);
	initialisePath(utf8_path);
}

tc::io::Path::Path(const std::u32string& path)
{
	std::string utf8_path;
	string::TranscodeUtil::UTF32ToUTF8(path, utf8_path);
	initialisePath(utf8_path);
}

tc::io::Path tc::io::Path::operator+(const Path& other) const
{
	Path new_path = *this;
	new_path.appendPath(other.mUnicodePath);
	return new_path;
}

void tc::io::Path::operator+=(const Path& other)
{
	appendPath(other.mUnicodePath);
}

bool tc::io::Path::operator==(const Path& other) const
{
	return mUnicodePath == other.mUnicodePath;
}

bool tc::io::Path::operator!=(const Path& other) const
{
	return !(this->operator==(other));
}

bool tc::io::Path::operator<(const Path& other) const
{
	int cmp_score = 0;

	auto self_itr = this->begin();
	auto other_itr = other.begin();

	// in this loop for as long as both path has an itr, it'll compare them
	for (; self_itr != this->end() && other_itr != other.end(); self_itr++, other_itr++)
	{
		cmp_score = self_itr->compare(*other_itr);
		if (cmp_score != 0)
			break;
	}

	// if one of the itrs isn't the end, then that one is "larger"
	// it can't be both or the prior loop won't have ended
	if (cmp_score == 0 && (self_itr != this->end() || other_itr != other.end()))
	{
		cmp_score = self_itr == this->end() ? -1 : 1;
	}

	return cmp_score < 0;
}

tc::io::Path::iterator tc::io::Path::begin()
{
	return mUnicodePath.begin();
}

std::string& tc::io::Path::front()
{
	return mUnicodePath.front();
}

const std::string& tc::io::Path::front() const
{
	return mUnicodePath.front();
}

std::string& tc::io::Path::back()
{
	return mUnicodePath.back();
}

const std::string& tc::io::Path::back() const
{
	return mUnicodePath.back();
}

tc::io::Path::const_iterator tc::io::Path::begin() const
{
	return mUnicodePath.begin();
}

tc::io::Path::iterator tc::io::Path::end()
{
	return mUnicodePath.end();
}

tc::io::Path::const_iterator tc::io::Path::end() const
{
	return mUnicodePath.end();
}

void tc::io::Path::pop_front()
{
	mUnicodePath.pop_front();
}

void tc::io::Path::pop_back()
{
	mUnicodePath.pop_back();
}

void tc::io::Path::push_front(const std::string& str)
{
	mUnicodePath.push_front(str);
}

void tc::io::Path::push_back(const std::string& str)
{
	mUnicodePath.push_back(str);
}

void tc::io::Path::clear()
{
	mUnicodePath.clear();
}

size_t tc::io::Path::size() const
{
	return mUnicodePath.size();
}

void tc::io::Path::initialisePath(const std::string& src)
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

void tc::io::Path::appendPath(const std::list<std::string>& other)
{
	for (std::list<std::string>::const_iterator itr = other.begin(); itr != other.end(); itr++)
	{
		mUnicodePath.push_back(*itr);
	}
}