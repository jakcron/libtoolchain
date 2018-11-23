/**
 * \class Path
 *
 * \ingroup LibToolChain
 *
 * \brief Represents a unicode path for a filesystem
 *
 * This stores a path as a vector of path elements.
 * Constructors exist for std::string, std::u16string and std::u32string which transcode and split the string on the path delimeter character ('/' or '\').
 * 
 * Due to differences in FileSystem character restrictions, no filtering is done by this class.
 * 
 * However when using the constructor for std::[u16|u32]string, the path delimeter character ('/' or '\') is detected automatically, and there cannot be mix of both backward and forward slashes.
 * 
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/11/22
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/types.h>

namespace tc
{
namespace filesystem
{
	class Path
	{
	public:
		static const char kWindowsPathDelimiter = '\\'; /**< Path delimiter used on Microsoft Windows based systems */
		static const char kUnixPathDelimiter = '/'; /**< Path delimiter used on Linux/Unix based systems */
#ifdef _WIN32
		static const char kNativePathDelimiter = kWindowsPathDelimiter; /**< Path delimiter for the native OS */
#else
		static const char kNativePathDelimiter = kUnixPathDelimiter; /**< Path delimiter for the native OS */
#endif

		/// Empty Constructor: Create an empty Path
		Path();

		/// Copy constructor: Copy Path from another Path
		Path(const Path& other);

		/// Create path from UTF-8
		Path(const std::string& path);

		/// Create path from UTF-16
		Path(const std::u16string& path);

		/// Create path from UTF-32
		Path(const std::u32string& path);

		/// Copy operator
		void operator=(const Path& other);

		/// Addition operator
		Path operator+(const Path& other);

		/// Append operator
		void operator+=(const Path& other);

		/// Equality operator
		bool operator==(const Path& other) const;

		/// Inequality operator
		bool operator!=(const Path& other) const;

		/** \brief Get the path as a vector of path elements
		 *  \return const std::vector<std::string>&
		 */
		const std::vector<std::string>& getPathElementList() const;
	private:
		const std::string kClassName = "tc::filesystem::Path";

		std::vector<std::string> mUnicodePath;

		void initialisePath(const std::string& src);
		void appendPath(const std::vector<std::string>& other);
	};
}
}