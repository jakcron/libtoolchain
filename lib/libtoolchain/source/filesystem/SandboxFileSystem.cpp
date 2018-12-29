#include <tc/filesystem/SandboxFileSystem.h>
#include <tc/Exception.h>

tc::filesystem::SandboxFileSystem::SandboxFileSystem(const tc::SharedPtr<tc::filesystem::IFileSystem>& fs_ptr, const tc::filesystem::Path& root_path) :
	mFileSystem(fs_ptr),
	mRootPath(root_path),
	mCurrentDirectory("/")
{
	// get full path of root
	mFileSystem->setCurrentDirectory(root_path);
	mFileSystem->getCurrentDirectory(mRootPath);
}

tc::filesystem::IFile* tc::filesystem::SandboxFileSystem::openFile(const tc::filesystem::Path& path, FileAccessMode mode)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// open file
	return mFileSystem->openFile(real_path, mode);
}

void tc::filesystem::SandboxFileSystem::deleteFile(const tc::filesystem::Path& path)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->deleteFile(real_path);
}

void tc::filesystem::SandboxFileSystem::getCurrentDirectory(tc::filesystem::Path& path)
{
	path = mCurrentDirectory;
}

void tc::filesystem::SandboxFileSystem::setCurrentDirectory(const tc::filesystem::Path& path)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// set current directory
	mFileSystem->setCurrentDirectory(real_path);

	// save current directory
	realPathToSandboxPath(real_path, mCurrentDirectory);
}

void tc::filesystem::SandboxFileSystem::createDirectory(const tc::filesystem::Path& path)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// create directory
	mFileSystem->createDirectory(real_path);
}

void tc::filesystem::SandboxFileSystem::removeDirectory(const tc::filesystem::Path& path)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// remove directory
	mFileSystem->removeDirectory(real_path);
}

void tc::filesystem::SandboxFileSystem::getDirectoryInfo(const tc::filesystem::Path& path, DirectoryInfo& info)
{
	// convert sandbox path to real path
	tc::filesystem::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// get real directory info
	tc::filesystem::DirectoryInfo real_info;
	mFileSystem->getDirectoryInfo(real_path, real_info);

	// convert directory absolute path
	tc::filesystem::Path sandbox_dir_path;
	realPathToSandboxPath(real_info.getDirectoryPath(), sandbox_dir_path);
	
	// update info with sandbox path
	real_info.setDirectoryPath(sandbox_dir_path);

	// write object to output
	info = real_info;
}

void tc::filesystem::SandboxFileSystem::sandboxPathToRealPath(const tc::filesystem::Path& sandbox_path, tc::filesystem::Path& real_path)
{
	tc::filesystem::Path sandbox_current_dir;
	tc::filesystem::Path sandbox_path_;

	// test path begins with root dir
	if (sandbox_path.getPathElementList().size() > 0 && sandbox_path.getPathElementList()[0] == "")
	{
		sandbox_current_dir = sandbox_path;
	}
	else
	{
		sandbox_path_ = sandbox_path;
		getCurrentDirectory(sandbox_current_dir);
	}

	// get santized path (removes elements that could be used to escape the sandbox)
	tc::filesystem::Path safe_sandbox_path;
	sanitiseInputPath(sandbox_current_dir + sandbox_path_, safe_sandbox_path);
	
	// the real path is the sandbox root path + sandbox path
	real_path = mRootPath + safe_sandbox_path;
}

void tc::filesystem::SandboxFileSystem::realPathToSandboxPath(const tc::filesystem::Path& real_path, tc::filesystem::Path& sandbox_path)
{
	std::vector<std::string> sandbox_path_element_list;

	// root char
	sandbox_path_element_list.push_back("");

	for (size_t i = 0; i < real_path.getPathElementList().size(); i++)
	{
		// verify that the real path matches the sandbox root path
		if (i < mRootPath.getPathElementList().size())
		{
			if (real_path.getPathElementList()[i] != mRootPath.getPathElementList()[i])
			{
				throw tc::Exception(kClassName, "Sandbox security exception (sandbox escape detected)");
			}
		}
		// save the elements that represent the sandboxed portion of the path
		else
		{
			sandbox_path_element_list.push_back(real_path.getPathElementList()[i]);
		}
	}

	// write sandbox path to output
	sandbox_path.setPathElementList(sandbox_path_element_list);
}

void tc::filesystem::SandboxFileSystem::sanitiseInputPath(const tc::filesystem::Path& unsafe_path, tc::filesystem::Path& safe_path) const
{
	std::vector<std::string> safe_list;

	for (size_t i = 0; i < unsafe_path.getPathElementList().size(); i++)
	{
		// root directory
		if (unsafe_path.getPathElementList()[i] == "" && i == 0)
		{
			continue;
		}
		// skip the current directory "."
		else if (unsafe_path.getPathElementList()[i] == ".")
		{
			continue;
		}
		// skip empty directories
		else if (unsafe_path.getPathElementList()[i] == "")
		{
			continue;
		}
		// directory navigate up element
		else if (unsafe_path.getPathElementList()[i] == "..")
		{
			if (safe_list.size() > 0)
				safe_list.pop_back();
		}
		// normal elements
		else
		{
			safe_list.push_back(unsafe_path.getPathElementList()[i]);
		}
	}

	safe_path.setPathElementList(safe_list);
}