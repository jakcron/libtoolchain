#include <tc/fs/SandboxedFileSystem.h>
#include <tc/Exception.h>

tc::fs::SandboxedFileSystem::SandboxedFileSystem(const tc::SharedPtr<tc::fs::IFileSystem>& fs_ptr, const tc::fs::Path& root_path) :
	mFileSystem(fs_ptr),
	mRootPath(root_path),
	mWorkingDirectory("/")
{
	// get full path of root
	mFileSystem->setWorkingDirectory(root_path);
	mFileSystem->getWorkingDirectory(mRootPath);
}

void tc::fs::SandboxedFileSystem::createFile(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->createFile(real_path);
}

void tc::fs::SandboxedFileSystem::removeFile(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// delete file
	mFileSystem->removeFile(real_path);
}

void tc::fs::SandboxedFileSystem::openFile(const tc::fs::Path& path, FileAccessMode mode, tc::fs::FileObject& file)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// open file
	return mFileSystem->openFile(real_path, mode, file);
}

void tc::fs::SandboxedFileSystem::createDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// create directory
	mFileSystem->createDirectory(real_path);
}

void tc::fs::SandboxedFileSystem::removeDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// remove directory
	mFileSystem->removeDirectory(real_path);
}

void tc::fs::SandboxedFileSystem::getWorkingDirectory(tc::fs::Path& path)
{
	path = mWorkingDirectory;
}

void tc::fs::SandboxedFileSystem::setWorkingDirectory(const tc::fs::Path& path)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// set current directory
	mFileSystem->setWorkingDirectory(real_path);

	// save current directory
	realPathToSandboxPath(real_path, mWorkingDirectory);
}

void tc::fs::SandboxedFileSystem::getDirectoryListing(const tc::fs::Path& path, sDirectoryListing& info)
{
	// convert sandbox path to real path
	tc::fs::Path real_path;
	sandboxPathToRealPath(path, real_path);

	// get real directory info
	tc::fs::sDirectoryListing real_info;
	mFileSystem->getDirectoryListing(real_path, real_info);

	// convert directory absolute path
	tc::fs::Path sandbox_dir_path;
	realPathToSandboxPath(real_info.abs_path, sandbox_dir_path);
	
	// update info with sandbox path
	real_info.abs_path = sandbox_dir_path;

	// write object to output
	info = real_info;
}

void tc::fs::SandboxedFileSystem::sandboxPathToRealPath(const tc::fs::Path& sandbox_path, tc::fs::Path& real_path)
{
	tc::fs::Path sandbox_current_dir;
	tc::fs::Path sandbox_path_;

	// test if the sandbox path is an absolute path (begins with the root element)
	if (sandbox_path.size() > 0 && *sandbox_path.begin() == "")
	{
		sandbox_current_dir = sandbox_path;
	}
	// otherwise this is a relative directory and the working directory (which includes the root element) must be obtained
	else
	{
		sandbox_path_ = sandbox_path;
		getWorkingDirectory(sandbox_current_dir);
	}

	// get santized path (removes elements that could be used to escape the sandbox)
	tc::fs::Path safe_sandbox_path;
	sanitiseInputPath(sandbox_current_dir + sandbox_path_, safe_sandbox_path);
	
	// the real path is the sandbox root path + sandbox path
	real_path = mRootPath + safe_sandbox_path;
}

void tc::fs::SandboxedFileSystem::realPathToSandboxPath(const tc::fs::Path& real_path, tc::fs::Path& sandbox_path)
{
	// get iterator for real path
	tc::fs::Path::const_iterator real_path_itr = real_path.begin();

	// determine if the path is large enough to preclude the root path
	if (real_path.size() < mRootPath.size())
	{
		throw tc::Exception(kClassName, "Sandbox security exception (sandbox escape detected)");
	}

	// confirm the real path includes the root path
	for (tc::fs::Path::const_iterator root_path_itr = mRootPath.begin(); root_path_itr != mRootPath.end(); root_path_itr++, real_path_itr++)
	{
		if (*real_path_itr != *root_path_itr)
		{
			throw tc::Exception(kClassName, "Sandbox security exception (sandbox escape detected)");
		}
	}

	// Put root char
	sandbox_path.push_back("");

	// save all path elements after the root sandbox path
	for (; real_path_itr != real_path.end(); real_path_itr++)
	{
		sandbox_path.push_back(*real_path_itr);
	}
}

void tc::fs::SandboxedFileSystem::sanitiseInputPath(const tc::fs::Path& unsafe_path, tc::fs::Path& safe_path) const
{
	//for (size_t i = 0; i < unsafe_path.getPathElementList().size(); i++)
	for (tc::fs::Path::const_iterator itr = unsafe_path.begin(); itr != unsafe_path.end(); itr++)
	{
		// root directory
		if (*itr == "" && itr == unsafe_path.begin())
		{
			continue;
		}
		// skip the working directory "."
		else if (*itr == ".")
		{
			continue;
		}
		// skip empty directories
		else if (*itr == "")
		{
			continue;
		}
		// directory navigate up element
		else if (*itr == "..")
		{
			if (safe_path.size() > 0)
				safe_path.pop_back();
		}
		// normal elements
		else
		{
			safe_path.push_back(*itr);
		}
	}
}