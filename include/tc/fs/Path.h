/**
 * @file Path.h
 * @brief Declaration of tc::fs::Path
 * @author Jack (jakcron)
 * @version 0.2
 * @date 2018/12/14
 */
#pragma once
#include <tc/types.h>

namespace tc { namespace fs {

	/**
	 * @class Path
	 * @brief Represents a unicode path for a filesystem
	 *
	 * This stores a path as a vector of path elements.
	 */
	class Path
	{
	public:
		static const char kWindowsPathDelimiter = '\\'; /**< Path delimiter used on Microsoft Windows based systems */
		static const char kUnixPathDelimiter = '/'; /**< Path delimiter used on Linux/Unix based systems */

		/// Default Constructor
		Path();

		/// Parameterized Constructor
		Path(const std::vector<std::string>& path_elements);

		/// Copy constructor
		Path(const Path& other);

		/// Move constructor
		Path(Path&& other);

		/**
		 * @brief Create Path from a literal UTF-8 encoded string
		 * 
		 * @param[in] path UTF-8 encoded path
		 * 
		 * @pre
		 * - path can have either forward or backward slash path delimiters ('/' or '\') but not both
		 * 
		 * @note No filtering or processing of special characters is done (e.g. '.', '~')
		 */
		Path(const std::string& path);

		/**
		 * @brief Create Path from a literal UTF-16 encoded string
		 *
		 * @param[in] path UTF-16 encoded path
		 * 
		 * @pre
		 * - path can have either forward or backward slash path delimiters ('/' or '\') but not both
		 * 
		 * @note 
		 * No filtering or processing of special characters is done (e.g. '.', '~')
		 */
		Path(const std::u16string& path);

		/**
		 * @brief Create Path from a literal UTF-32 encoded string
		 *
		 * @param[in] path UTF-32 encoded path
		 * 
		 * @pre
		 * - path can have either forward or backward slash path delimiters ('/' or '\') but not both
		 * 
		 * @note 
		 * No filtering or processing of special characters is done (e.g. '.', '~')
		 */
		Path(const std::u32string& path);

		/// Copy operator
		Path& operator=(const Path& other);

		/// Move operator
		Path& operator=(Path&& other);

		/// Addition operator
		Path operator+(const Path& other) const;

		/// Append operator
		void operator+=(const Path& other);

		/// Equality operator
		bool operator==(const Path& other) const;

		/// Inequality operator
		bool operator!=(const Path& other) const;

		/** 
		 * @brief Get the path as a list of path elements
		 * @return path element list
		 */
		const std::vector<std::string>& getPathElementList() const;

		/**
		 * @brief Set the list of path elements
		 * @param[in] list path element list
		 */
		void setPathElementList(const std::vector<std::string>& list);
	private:
		const std::string kClassName = "tc::fs::Path";

		std::vector<std::string> mUnicodePath;

		void initialisePath(const std::string& src);
		void appendPath(const std::vector<std::string>& other);
	};

}} // namespace tc::fs