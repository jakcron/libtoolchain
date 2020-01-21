	/**
	 * @file SandboxedFileSystem.h
	 * @brief Declaration of tc::io::SandboxedFileSystem
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/io/IFileSystem.h>

namespace tc { namespace io {

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
	SandboxedFileSystem(const std::shared_ptr<tc::io::IFileSystem>& fs, const tc::io::Path& root_path);

		/** 
		 * @brief Wrap (by move) constuctor
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	SandboxedFileSystem(std::shared_ptr<tc::io::IFileSystem>&& fs, const tc::io::Path& root_path);

	virtual tc::ResourceState getFsState();

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	void initialiseFs(const std::shared_ptr<tc::io::IFileSystem>& fs, const tc::io::Path& root_path);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] fs IFileSystem object to be sandboxed
		 * @param[in] root_path The path to the subdirectory used as the sandboxed root directory.
		 */
	void initialiseFs(std::shared_ptr<tc::io::IFileSystem>&& fs, const tc::io::Path& root_path);

	virtual void closeFs();
	virtual void createFile(const tc::io::Path& path);
	virtual void removeFile(const tc::io::Path& path);
	virtual void openFile(const tc::io::Path& path, tc::io::FileAccessMode mode, std::shared_ptr<tc::io::IFileObject>& file);
	virtual void createDirectory(const tc::io::Path& path);
	virtual void removeDirectory(const tc::io::Path& path);
	virtual void getWorkingDirectory(tc::io::Path& path);
	virtual void setWorkingDirectory(const tc::io::Path& path);
	virtual void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info);
private:
	static const std::string kClassName;
	
	std::shared_ptr<tc::io::IFileSystem> mFileSystem;
	tc::io::Path mRootPath;
	tc::io::Path mWorkingDirectory;

	void sandboxPathToRealPath(const tc::io::Path& sandbox_path, tc::io::Path& real_path);
	void realPathToSandboxPath(const tc::io::Path& real_path, tc::io::Path& sandbox_path);
	void sanitiseInputPath(const tc::io::Path& unsafe_path, tc::io::Path& safe_path) const;
};

}} // namespace tc::io