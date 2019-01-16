#include <tc/fs/DirectoryInfo.h>

tc::fs::DirectoryInfo::DirectoryInfo() :
	mPath(),
	mDirList(),
	mFileList()
{
}

tc::fs::DirectoryInfo::DirectoryInfo(const tc::fs::Path& path, const std::vector<std::string>& dir_child_list, const std::vector<std::string>& file_child_list) :
	mPath(path),
	mDirList(dir_child_list),
	mFileList(file_child_list)
{
}

tc::fs::DirectoryInfo::DirectoryInfo(const DirectoryInfo& other) :
	mPath(other.mPath),
	mDirList(other.mDirList),
	mFileList(other.mFileList)
{
}

tc::fs::DirectoryInfo::DirectoryInfo(const DirectoryInfo&& other) :
	mPath(std::move(other.mPath)),
	mDirList(std::move(other.mDirList)),
	mFileList(std::move(other.mFileList))
{
}

tc::fs::DirectoryInfo& tc::fs::DirectoryInfo::operator=(const DirectoryInfo& other)
{
	mPath = other.mPath;
	mDirList = other.mDirList;
	mFileList = other.mFileList;

	return *this;
}

tc::fs::DirectoryInfo& tc::fs::DirectoryInfo::operator=(const DirectoryInfo&& other)
{
	mPath = std::move(other.mPath);
	mDirList = std::move(other.mDirList);
	mFileList = std::move(other.mFileList);

	return *this;
}

const tc::fs::Path& tc::fs::DirectoryInfo::getPath() const
{
	return mPath;
}

void tc::fs::DirectoryInfo::setPath(const tc::fs::Path& path)
{
	mPath = path;
}

const std::vector<std::string>& tc::fs::DirectoryInfo::getDirectoryList() const
{
	return mDirList;
}

void tc::fs::DirectoryInfo::setDirectoryList(const std::vector<std::string>& list)
{
	mDirList = list;
}

const std::vector<std::string>& tc::fs::DirectoryInfo::getFileList() const
{
	return mFileList;
}

void tc::fs::DirectoryInfo::setFileList(const std::vector<std::string>& list)
{
	mFileList = list;
}