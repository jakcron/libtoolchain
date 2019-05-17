	/**
	 * @file SandboxedFileSystem.h
	 * @brief Declaration of tc::fs::SandboxedFileSystem
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2019/05/17
	 */
#pragma once
#include <tc/fs/IFileSystem.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class SandboxedFileSystem
	 * @brief A wrapper around an existing IFileSystem object that exposes a subset of the wrapped IFileSystem directory tree.
	 */
class SandboxedFileSystem : public IFileSystem
{
public:
		/** 
		 * @brief Default constuctor
		 * @param[in] fs_ptr Pointer to IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	SandboxedFileSystem(const tc::SharedPtr<tc::fs::IFileSystem>& fs_ptr, const tc::fs::Path& root_path);

	
	void createFile(const tc::fs::Path& path);
	void removeFile(const tc::fs::Path& path);
	void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::FileStream& file);
	void createDirectory(const tc::fs::Path& path);
	void removeDirectory(const tc::fs::Path& path);
	void getWorkingDirectory(tc::fs::Path& path);
	void setWorkingDirectory(const tc::fs::Path& path);
	void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);

private:
	const std::string kClassName = "tc::fs::SandboxedFileSystem";

	tc::SharedPtr<tc::fs::IFileSystem> mFileSystem;
	tc::fs::Path mRootPath;
	tc::fs::Path mWorkingDirectory;

	void sandboxPathToRealPath(const tc::fs::Path& sandbox_path, tc::fs::Path& real_path);
	void realPathToSandboxPath(const tc::fs::Path& real_path, tc::fs::Path& sandbox_path);
	void sanitiseInputPath(const tc::fs::Path& unsafe_path, tc::fs::Path& safe_path) const;
};

}} // namespace tc::fs