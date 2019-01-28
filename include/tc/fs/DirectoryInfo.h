
/**
 * @file DirectoryInfo.h
 * @brief Declaration of tc::fs::DirectoryInfo
 * @author Jack (jakcron)
 * @version	0.2
 * @date 2019/01/15
 */
#pragma once
#include <tc/types.h>
#include <tc/fs/Path.h>

namespace tc { namespace fs {

	/**
	 * @class DirectoryInfo
	 * @brief Provides basic info about a directory with-in a FileSystem
	 * 
	 * The includes the absolute path of the directory, and lists of child directory and file names.
	 * 
	 * @note All strings are UTF-8
	 */
	class DirectoryInfo
	{
	public:
		/// Default Constructor
		DirectoryInfo();

		/// Parametrized Constructor
		DirectoryInfo(const tc::fs::Path& path, const std::vector<std::string>& dir_list, const std::vector<std::string>& file_list);

		/// Copy Constructor
		DirectoryInfo(const DirectoryInfo& other);

		/// Move Constructor
		DirectoryInfo(DirectoryInfo&& other);

		/// Copy Operator
		DirectoryInfo& operator=(const DirectoryInfo& other);

		/// Move Operator
		DirectoryInfo& operator=(DirectoryInfo&& other);

		/**
		 * @brief Get the native path of the directory
		 * @return Path to directory
		 */
		const tc::fs::Path& getPath() const;

		/**
		 * @brief Set the native path of the directory
		 * @param[in] path Path to directory
		 */
		void setPath(const tc::fs::Path& path);

		/**
		 * @brief Get the list of directories
		 * @return List of directories
		 */
		const std::vector<std::string>& getDirectoryList() const;

		/**
		 * @brief Set the list of child directories
		 * @param list List of child directories
		 */
		void setDirectoryList(const std::vector<std::string>& list);

		/**
		 * @brief Get the list of files
		 * @return List of files
		 */
		const std::vector<std::string>& getFileList() const;

		/**
		 * @brief Set the list of files
		 * @param list List of files
		 */
		void setFileList(const std::vector<std::string>& list);
	private:
		tc::fs::Path mPath;
		std::vector<std::string> mDirList;
		std::vector<std::string> mFileList;
	};

}} // namespace tc::fs