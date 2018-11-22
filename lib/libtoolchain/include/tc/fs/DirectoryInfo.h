/**
 * \class DirectoryInfo
 *
 * \ingroup LibToolChain
 *
 * \brief Provides basic info about a directory with-in a FileSystem
 *
 * The includes the absolute path of the directory, and lists of child directory and file names.
 * 
 * 
 * \note All strings are UTF-8
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/11/10
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/types.h>
#include <tc/fs/Path.h>

namespace tc
{
namespace filesystem
{
	class DirectoryInfo
	{
	public:
		/// Create an empty DirectoryInfo
		DirectoryInfo();

		/// Create and initialise a DirectoryInfo
		DirectoryInfo(const tc::filesystem::Path& path, const std::vector<std::string>& dir_child_list, const std::vector<std::string>& file_child_list);

		/// Copy DirectoryInfo from another DirectoryInfo
		DirectoryInfo(const DirectoryInfo& other);

		/// Copy operator
		void operator=(const DirectoryInfo& other);

		/** \brief Get the native path of the directory
		 *  \return const tc::filesystem::Path&
		 */
		const tc::filesystem::Path& getDirectoryPath() const;

		/** \brief Set the native path of the directory
		 *  \param path cosnt tc::filesystem::Path&
		 */
		void setDirectoryPath(const tc::filesystem::Path& path);

		/** \brief Returns a list of child directory names
		 *  \return const std::vector& List of child directory names
		 */
		const std::vector<std::string>& getChildDirectoryList() const;

		/** \brief Set the list of child directory names
		 *  \param list const std::vector& List of child directory names
		 */
		void setChildDirectoryList(const std::vector<std::string>& list);

		/** \brief Returns a list of child file names
		 *  \return const std::vector& List of child file names
		 */
		const std::vector<std::string>& getChildFileList() const;

		/** \brief Set the list of child file names
		 *  \param list const std::vector& List of child file names
		 */
		void setChildFileList(const std::vector<std::string>& list);
	private:
		tc::filesystem::Path mDirPath;
		std::vector<std::string> mDirChildList;
		std::vector<std::string> mFileChildList;
	};
}
}