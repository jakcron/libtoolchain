#include <tc/fs/SandboxedIFileSystem.h>
#include <tc/Exception.h>

tc::fs::SandboxedIFileSystem::SandboxedIFileSystem(const tc::SharedPtr<tc::fs::IFileSystem>& fs_ptr, const tc::fs::Path& root_path) :
	mFileSystem(fs_ptr),
	mRootPath(root_path),
	mCurrentDirectory("/")
{
	// get full path of root
	mFileSystem->setCurrentDirectory(root_path);
	mFileSystem->getCurrentDirectory(mRootPath);
}

tc::fs::IFile* tc::fs::SandboxedIFileSystem::openFile(const tc::fs::Path& path, FileAccessMode mode)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// open file
	return mFileSystem->openFile(real_path, mode);
}

void tc::fs::SandboxedIFileSystem::deleteFile(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->deleteFile(real_path);
}

void tc::fs::SandboxedIFileSystem::getCurrentDirectory(tc::fs::Path& path)
{
	path = mCurrentDirectory;
}

void tc::fs::SandboxedIFileSystem::setCurrentDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// set current directory
	mFileSystem->setCurrentDirectory(real_path);

	// save current directory
	realPathToSandboxPath(real_path, mCurrentDirectory);
}

void tc::fs::SandboxedIFileSystem::createDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// create directory
	mFileSystem->createDirectory(real_path);
}

void tc::fs::SandboxedIFileSystem::deleteDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// remove directory
	mFileSystem->deleteDirectory(real_path);
}

void tc::fs::SandboxedIFileSystem::getDirectoryListing(const tc::fs::Path& path, DirectoryInfo& info)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// get real directory info
	tc::fs::DirectoryInfo real_info;
	mFileSystem->getDirectoryListing(real_path, real_info);

	// convert directory absolute path
	tc::fs::Path sandbox_dir_path;
	realPathToSandboxPath(real_info.getPath(), sandbox_dir_path);
	
	// update info with sandbox path
	real_info.setPath(sandbox_dir_path);

	// write object to output
	info = real_info;
}

void tc::fs::SandboxedIFileSystem::sandboxPathToRealPath(const tc::fs::Path& sandbox_path, tc::fs::Path& real_path)
{
	tc::fs::Path sandbox_current_dir;
	tc::fs::Path sandbox_path_;

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
	tc::fs::Path safe_sandbox_path;
	sanitiseInputPath(sandbox_current_dir + sandbox_path_, safe_sandbox_path);
	
	// the real path is the sandbox root path + sandbox path
	real_path = mRootPath + safe_sandbox_path;
}

void tc::fs::SandboxedIFileSystem::realPathToSandboxPath(const tc::fs::Path& real_path, tc::fs::Path& sandbox_path)
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

void tc::fs::SandboxedIFileSystem::sanitiseInputPath(const tc::fs::Path& unsafe_path, tc::fs::Path& safe_path) const
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