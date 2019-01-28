/**
 * @file SandboxedIFileSystem.h
 * @brief Declaration of tc::fs::SandboxedIFileSystem
 * @author Jack (jakcron)
 * @version 0.1
 * @date 2018/12/23
 */
#pragma once
#include <tc/fs/IFileSystem.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class SandboxedIFileSystem
	 * @brief A wrapper around an existing IFileSystem object that exposes a subset of the wrapped IFileSystem directory tree.
	 */
	class SandboxedIFileSystem : public IFileSystem
	{
	public:
		/** 
		 * @brief Default constuctor
		 * @param[in] fs_ptr Pointer to IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
		SandboxedIFileSystem(const tc::SharedPtr<tc::fs::IFileSystem>& fs_ptr, const tc::fs::Path& root_path);

		tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode);
		void deleteFile(const tc::fs::Path& path);
		void getCurrentDirectory(tc::fs::Path& path);
		void setCurrentDirectory(const tc::fs::Path& path);
		void createDirectory(const tc::fs::Path& path);
		void deleteDirectory(const tc::fs::Path& path);
		void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& info);

	private:
		const std::string kClassName = "tc::fs::SandboxedIFileSystem";

		tc::SharedPtr<tc::fs::IFileSystem> mFileSystem;
		tc::fs::Path mRootPath;
		tc::fs::Path mCurrentDirectory;

		void sandboxPathToRealPath(const tc::fs::Path& sandbox_path, tc::fs::Path& real_path);
		void realPathToSandboxPath(const tc::fs::Path& real_path, tc::fs::Path& sandbox_path);
		void sanitiseInputPath(const tc::fs::Path& unsafe_path, tc::fs::Path& safe_path) const;
	};

}} // namespace tc::fs