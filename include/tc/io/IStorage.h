	/**
	 * @file IStorage.h
	 * @brief Declaration of tc::io::IStorage
	 * @author Jack (jakcron)
	 * @version 0.6
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/types.h>
#include <tc/ResourceState.h>
#include <tc/io/IFileObject.h>
#include <tc/io/Path.h>

namespace tc { namespace io {

	/** 
	 * @enum FileAccessMode
	 * @brief This enum is used with openFile() to determine the access mode
	 */
enum FileAccessMode
{
	FILEACCESS_READ, /**< Access file with READ-ONLY permissions */
	FILEACCESS_EDIT, /**< Access file with READ-WRITE permissions */
	FILEACCESS_CREATE /**< Create a new file or overwrite an existing file (READ-WRITE permissions) */
};


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
	 * @note It is up to the implementation to enforce tc::io::FileAccessMode.
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
		 * @return ResourceState
		 */
	virtual tc::ResourceState getFsState() = 0;

		/**
		 * @brief Close the filesystem
		 */
	virtual void closeFs() = 0;

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
		 * @param[in] path Path to file
		 * @param[in] mode Access mode
		 * @param[out] file Pointer to IFileObject object to be instantiated
		 *	
		 * @throws tc::Exception If the file cannot be opened (invalid path, or access rights)
		 */
	virtual void openFile(const tc::io::Path& path, tc::io::FileAccessMode mode, std::shared_ptr<tc::io::IFileObject>& file) = 0;
	
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