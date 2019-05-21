/**
 * @file Path.h
 * @brief Declaration of tc::fs::Path
 * @author Jack (jakcron)
 * @version 0.3
 * @date 2019/05/10
 */
#pragma once
#include <list>
#include <tc/types.h>

namespace tc { namespace fs {

	/**
	 * @class Path
	 * @brief Represents a unicode path for a filesystem
	 *
	 * This stores a path as a list of path elements.
	 */
class Path
{
public:
	static const char kWindowsPathDelimiter = '\\'; /**< Path delimiter used on Microsoft Windows based systems */
	static const char kUnixPathDelimiter = '/'; /**< Path delimiter used on Linux/Unix based systems */

		/// Type of const_iterator for Path
	using const_iterator = typename std::list<std::string>::const_iterator;

		/// Type of iterator for Path
	using iterator = typename std::list<std::string>::iterator;

		/// Default Constructor
	Path();

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

		/// Addition operator
	Path operator+(const Path& other) const;

		/// Append operator
	void operator+=(const Path& other);

		/// Equality operator
	bool operator==(const Path& other) const;

		/// Inequality operator
	bool operator!=(const Path& other) const;

		/// Const Begin Iterator, points to front element
	const_iterator begin() const;

		/// Begin Iterator, points to front element
	iterator begin();

		/// Const End Iterator, points to after the last element
	const_iterator end() const;

		/// End Iterator, points to after the last element
	iterator end();

		/// Remove element at the front of the path
	void pop_front();

		/// Remove element at the back of the path
	void pop_back();

		/// Insert path element at the front of the path
	void push_front(const std::string& str);

		/// Insert path element at the back of the path
	void push_back(const std::string& str);

		/// Get number of path elements
	size_t size() const;	
private:
	static const std::string kClassName;

	std::list<std::string> mUnicodePath;

	void initialisePath(const std::string& src);
	void appendPath(const std::list<std::string>& other);
};

}} // namespace tc::fs