	/**
	 * @file SandboxedFileSystem.h
	 * @brief Declaration of tc::fs::SandboxedFileSystem
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/fs/GenericFileSystem.h>
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
		 * @brief Default constructor
		 */
	SandboxedFileSystem();

		/** 
		 * @brief Wrap (by copy) constuctor
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	SandboxedFileSystem(const tc::fs::IFileSystem& fs, const tc::fs::Path& root_path);

		/** 
		 * @brief Wrap (by move) constuctor
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	SandboxedFileSystem(tc::fs::IFileSystem&& fs, const tc::fs::Path& root_path);

	virtual tc::fs::IFileSystem* copyInstance() const;
	virtual tc::fs::IFileSystem* moveInstance();

	virtual tc::ResourceState getFsState();

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	void initialiseFs(const tc::fs::IFileSystem& fs, const tc::fs::Path& root_path);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	void initialiseFs(tc::fs::IFileSystem&& fs, const tc::fs::Path& root_path);

	virtual void closeFs();
	virtual void createFile(const tc::fs::Path& path);
	virtual void removeFile(const tc::fs::Path& path);
	virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file);
	virtual void createDirectory(const tc::fs::Path& path);
	virtual void removeDirectory(const tc::fs::Path& path);
	virtual void getWorkingDirectory(tc::fs::Path& path);
	virtual void setWorkingDirectory(const tc::fs::Path& path);
	virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);
private:
	static const std::string kClassName;
	
	tc::fs::GenericFileSystem mFileSystem;
	tc::fs::Path mRootPath;
	tc::fs::Path mWorkingDirectory;

	void sandboxPathToRealPath(const tc::fs::Path& sandbox_path, tc::fs::Path& real_path);
	void realPathToSandboxPath(const tc::fs::Path& real_path, tc::fs::Path& sandbox_path);
	void sanitiseInputPath(const tc::fs::Path& unsafe_path, tc::fs::Path& safe_path) const;
};

}} // namespace tc::fs