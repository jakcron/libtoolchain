	/**
	 * @file IStorage.h
	 * @brief Declaration of tc::io::IStorage
	 * @author Jack (jakcron)
	 * @version 0.6
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/types.h>
#include <tc/ResourceStatus.h>
#include <tc/io/IStream.h>
#include <tc/io/Path.h>
#include <tc/io/FileMode.h>
#include <tc/io/FileAccess.h>

namespace tc { namespace io {

	/**
	 * @struct sDirectoryListing
	 * @brief Contains basic info about a directory with-in a FileSystem
	 * 
	 * The includes the absolute path of the directory, and lists of child directory and file names.
	 * 
	 * @note All strings are UTF-8
	 */
struct sDirectoryListing
{
		/// Absolute Path
	tc::io::Path abs_path;
		/// List of child directory names
	std::vector<std::string> dir_list;
		/// List of child file names
	std::vector<std::string> file_list;
};

	/**
	 * @class IStorage
	 * 
	 * @brief An interface for implementing a basic FileSystem handler.
	 *
	 * Defines expected functionality including:
	 * - File access (open)
	 * - File management (create, remove)
	 * - Directory traversal (get current directory, change current directory)
	 * - Directory management (create, remove)
	 * - Directory listing
	 * 
	 * @note IStorage uses the tc::io::Path class to represent a path, not as a literal string.
	 * @note It is up to the implementation of IStorage to validate and process tc::io::Path objects.
	 * @note It is up to the implementation to enforce tc::io::FileMode & tc::io::FileAccess.
	 */
class IStorage
{
public:
		/**
		 * @brief Destructor
		 */
	virtual ~IStorage() = default;

		/**
		 * @brief Get state of IStorage
		 * @return ResourceStatus
		 */
	virtual tc::ResourceStatus state() = 0;

		/**
		 * @brief Close the filesystem
		 */
	virtual void dispose() = 0;

		/** 
		 * @brief Create a new file
		 * @param[in] path Path to file
		 * 
		 * @throws tc::Exception If the file cannot be created (invalid path, or access rights)
		 */
	virtual void createFile(const tc::io::Path& path) = 0;

		/** 
		 * @brief Remove a file
		 * @param[in] path Path to file
		 * 
		 * @throws tc::Exception If the file cannot be removed (invalid path, or access rights)
		 */
	virtual void removeFile(const tc::io::Path& path) = 0;

		/** 
		 * @brief Open a file
		 * @param[in] path A relative or absolute path for the file that the current IStorage object will a IStream for.
		 * @param[in] mode One of the enumeration values that determines how to open or create the file.
		 * @param[in] access One of the enumeration values that determines how the file can be accessed by the FileStream object. This also determines the values returned by the @ref canRead and @ref canWrite methods of the FileStream object. @ref canSeek is true if path specifies a disk file.
		 * @param[out] stream Pointer to IStream object to be instantiated
		 *	
		 * @throws tc::Exception If the file cannot be opened (invalid path, or access rights)
		 */
	virtual void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream) = 0;
	
		/** 
		 * @brief Create a new directory
		 * @param[in] path Path to directory
		 * 
		 * @post If the directory already exists, this does nothing if the directory cannot be created (invalid path, or access rights)
		 * 
		 * @throws tc::Exception If the directory cannot be created (invalid path, or access rights)
		 */
	virtual void createDirectory(const tc::io::Path& path) = 0;

		/** 
		 * @brief Remove a directory
		 * @param[in] path Path to directory
		 * 
		 * @throws tc::Exception If the directory cannot be removed (invalid path, or access rights)
		 */
	virtual void removeDirectory(const tc::io::Path& path) = 0;

		/** 
		 * @brief Get the full path of the working directory
		 * @param[out] path Path object to populate
		 */
	virtual void getWorkingDirectory(tc::io::Path& path) = 0;

		/** 
		 * @brief Change the working directory
		 * @param[in] path Path to directory
		 */
	virtual void setWorkingDirectory(const tc::io::Path& path) = 0;

		/** 
		 * @brief Get directory listing a directory
		 * @param[in] path Path to directory
		 * @param[out] info sDirectoryListing object to populate
		 * 
		 * @throws tc::Exception If the directory cannot be accessed (invalid path, or access rights)
		 */
	virtual void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info) = 0;
};

}} // namespace tc::io