#include <tc/fs/DirectoryInfo.h>

tc::filesystem::DirectoryInfo::DirectoryInfo() :
	mDirPath(),
	mDirChildList(),
	mFileChildList()
{
}

tc::filesystem::DirectoryInfo::DirectoryInfo(const tc::filesystem::Path& path, const std::vector<std::string>& dir_child_list, const std::vector<std::string>& file_child_list) :
	mDirPath(path),
	mDirChildList(dir_child_list),
	mFileChildList(file_child_list)
{
}

tc::filesystem::DirectoryInfo::DirectoryInfo(const DirectoryInfo& other) :
	mDirPath(other.mDirPath),
	mDirChildList(other.mDirChildList),
	mFileChildList(other.mFileChildList)
{
}

void tc::filesystem::DirectoryInfo::operator=(const DirectoryInfo& other)
{
	mDirPath = other.mDirPath;
	mDirChildList = other.mDirChildList;
	mFileChildList = other.mFileChildList;
}

const tc::filesystem::Path& tc::filesystem::DirectoryInfo::getDirectoryPath() const
{
	return mDirPath;
}

void tc::filesystem::DirectoryInfo::setDirectoryPath(const tc::filesystem::Path& path)
{
	mDirPath = path;
}

const std::vector<std::string>& tc::filesystem::DirectoryInfo::getChildDirectoryList() const
{
	return mDirChildList;
}

void tc::filesystem::DirectoryInfo::setChildDirectoryList(const std::vector<std::string>& list)
{
	mDirChildList = list;
}

const std::vector<std::string>& tc::filesystem::DirectoryInfo::getChildFileList() const
{
	return mFileChildList;
}

void tc::filesystem::DirectoryInfo::setChildFileList(const std::vector<std::string>& list)
{
	mFileChildList = list;
}