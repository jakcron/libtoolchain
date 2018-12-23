/**
 * \class SandboxFileSystem
 *
 * \ingroup LibToolChain
 *
 * \brief A wrapper around an existing IFileSystem object that exposes a subset of the wrapped IFileSystem directory tree.
 * 
 * 
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/12/23
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/filesystem/IFileSystem.h>
#include <tc/SharedPtr.h>

namespace tc
{
namespace filesystem
{
	class SandboxFileSystem : public IFileSystem
	{
	public:
		/** \brief Default constuctor
		 *  \param fs_ptr const tc::SharedPtr<tc::filesystem::IFileSystem>& Pointer to IFileSystem object to be sandboxed
		 *  \param root_path const tc::filesystem::Path& The path to the subdirectory used as the sandboxed root directory.
		 */
		SandboxFileSystem(const tc::SharedPtr<tc::filesystem::IFileSystem>& fs_ptr, const tc::filesystem::Path& root_path);

		/** \brief Open a file
		 *  \param path const tc::filesystem::Path& Path to file
		 *  \param mode tc::filesystem::FileAccessMode 
		 *  \return tc::filesystem::IFile* pointer to IFile object
		 * 
		 *  IFile object will auto-close the file when destructor is called (when deleted)
		 * 
		 *  If the file cannot be accessed (invalid path, or access rights) an exception will be thrown
		 */
		tc::filesystem::IFile* openFile(const tc::filesystem::Path& path, tc::filesystem::FileAccessMode mode);

		/** \brief Delete a file
		 *  \param path const tc::filesystem::Path& Path to file
		 * 
		 *  If the file cannot be removed (invalid path, or access rights) an exception will be thrown
		 */
		void deleteFile(const tc::filesystem::Path& path);

		/** \brief Get the full path of the current directory
		 *  \param path tc::filesystem::Path& Path object to be populated with current directory path
		 */
		void getCurrentDirectory(tc::filesystem::Path& path);

		/** \brief Change the current directory
		 *  \param path const tc::filesystem::Path& Path to directory
		 */
		void setCurrentDirectory(const tc::filesystem::Path& path);
		
		/** \brief Create a new directory
		 *  \param path const tc::filesystem::Path& Path to directory
		 * 
		 * 	If the directory already exists, this does nothing
		 *  If the directory cannot be created (invalid path, or access rights) an exception will be thrown
		 */
		void createDirectory(const tc::filesystem::Path& path);

		/** \brief Remove a directory
		 *  \param path const tc::filesystem::Path& Path to directory
		 * 
		 *  If the directory cannot be removed (invalid path, or access rights) an exception will be thrown
		 */
		void removeDirectory(const tc::filesystem::Path& path);

		/** \brief Populate a DirectoryInfo object for a specified path
		 *  \param path const tc::filesystem::Path& Path to directory
		 *  \param info DirectoryInfo& reference to DirectoryInfo object to be populated
		 *  \return const DirectoryInfo& 
		 * 
		 *  If the directory cannot be accessed (invalid path, or access rights) an exception will be thrown
		 */
		void getDirectoryInfo(const tc::filesystem::Path& path, DirectoryInfo& info);

	private:
		const std::string kClassName = "tc::filesystem::SandboxFileSystem";

		tc::SharedPtr<tc::filesystem::IFileSystem> mFileSystem;
		tc::filesystem::Path mRootPath;
		tc::filesystem::Path mCurrentDirectory;

		void sandboxPathToRealPath(const tc::filesystem::Path& sandbox_path, tc::filesystem::Path& real_path);
		void realPathToSandboxPath(const tc::filesystem::Path& real_path, tc::filesystem::Path& sandbox_path);
		void sanitiseInputPath(const tc::filesystem::Path& unsafe_path, tc::filesystem::Path& safe_path) const;
	};
}
}