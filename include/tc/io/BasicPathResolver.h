	/**
	 * @file BasicPathResolver.h
	 * @brief Declaration of tc::io::BasicPathResolver
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2022/02/22
	 **/
#pragma once
#include <tc/io/IPortablePathResolver.h>

#include <tc/ArgumentOutOfRangeException.h>

namespace tc { namespace io {

	    /**
		 * @class BasicPathResolver
		 * @brief This implementation of IPortablePathResolver resolves a path and current directory to canonical path, resolving only '`.`', '`..`' and empty path elements.
		 * @details This does not consider the local file-system/environment, so links or '`~`' will not be resolved properly. It is intended for processing archived/portable filesystems.
		 */
	class BasicPathResolver : public tc::io::IPortablePathResolver
	{
	public:
			/**
			 * @brief Default Constructor
			 * 
			 * @post The current directory will be "/" and the list of allowed root path names will be { "" }.
			 */
		BasicPathResolver();

			/**
			 * @brief Create BasicPathResolver
			 * 
			 * @param[in] current_directory_path Canonical path for the current directory.
			 * 
			 * @post The current directory will be @p current_directory_path and the list of allowed root path names will be { @p current_directory_path.front() }.
			 */
		BasicPathResolver(const tc::io::Path& current_directory_path);

			/**
			 * @brief Create BasicPathResolver
			 * 
			 * @param[in] current_directory_path Canonical path for the current directory.
			 * @param[in] root_names Vector of valid root path names for this path resolver.
			 * 
			 * @post The current directory will be @p current_directory_path and the list of allowed root path names will be the merge of @p current_directory_path.front() and @p root_names .
			 */
		BasicPathResolver(const tc::io::Path& current_directory_path, const std::vector<std::string>& root_names);

			/**
			 * @brief Set the current directory path
			 * 
			 * @param path Canonical current directory path.
			 * 
			 * @throws tc::ArgumentOutOfRangeException @p path was an empty path.
			 */
		void setCurrentDirectory(const tc::io::Path& path);

			/**
			 * @brief Get the current directory path
			 * 
			 * @return tc::io::Path Canonical current directory path.
			 */
		const tc::io::Path& getCurrentDirectory() const;

			/**
			 * @brief Set valid root labels
			 * @details 
			 * The first element of a canonical path is the root label, for POSIX this is empty "" as in "/some/path", for Windows this is a drive letter e.g. "C:" as in "C:\some\path".
			 * By setting a full list, when resolving paths to canonical paths, the first element can be checked to determine if the path is relative or absolute.
			 * 
			 * @param root_label Vector of root labels
			 */
		void setValidRootLabels(const std::vector<std::string>& root_label);

			/// Get valid root labels
		const std::vector<std::string>& getValidRootLabels() const;

			/**
			 * @brief Resolve path to its canonical path
			 * 
			 * @param path Input path.
			 * @param canonical_path Output path to write resolved canonical path.
			 */
		void resolveCanonicalPath(const tc::io::Path& path, tc::io::Path& canonical_path) const;

			/**
			 * @brief Resolve path to its canonical path
			 * 
			 * @param path Input path.
			 * 
			 * @return Resolved canonical path.
			 */
		tc::io::Path resolveCanonicalPath(const tc::io::Path& path) const;
	private:
		static const std::string kClassName;

		tc::io::Path mCurrentDirPath;
		std::vector<std::string> mValidRootLabels;
	};

}} // namespace tc::io