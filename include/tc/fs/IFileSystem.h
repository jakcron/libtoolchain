	/**
	 * @file IFileSystem.h
	 * @brief Declaration of tc::fs::IFileSystem
	 * @author Jack (jakcron)
	 * @version 0.6
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/types.h>
#include <tc/ResourceState.h>
#include <tc/fs/GenericFileObject.h>
#include <tc/SharedPtr.h>
#include <tc/fs/Path.h>

namespace tc { namespace fs {

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
	tc::fs::Path abs_path;
		/// List of child directory names
	std::vector<std::string> dir_list;
		/// List of child file names
	std::vector<std::string> file_list;
};

	/**
	 * @class IFileSystem
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
	 * @note IFileSystem uses the tc::fs::Path class to represent a path, not as a literal string.
	 * @note It is up to the implementation of IFileSystem to validate and process tc::fs::Path objects.
	 * @note It is up to the implementation to enforce tc::fs::FileAccessMode.
	 */
class IFileSystem
{
public:
		/**
		 * @brief Destructor
		 */
	virtual ~IFileSystem() = default;

		/**
		 * @brief Create a new instance of this object as a copy
		 * This is required by @ref tc::fs::GenericFileSystem
		 * @return new instance of IFileSystem (dynamically allocated)
		 */
	virtual IFileSystem* copyInstance() const = 0;

		/**
		 * @brief Create a new instance of this object and move elements to the new instance
		 * This is required by @ref tc::fs::GenericFileSystem
		 * @return new instance of IFileSystem (dynamically allocated)
		 */
	virtual IFileSystem* moveInstance() = 0;

		/**
		 * @brief Get state of IFileSystem
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
	virtual void createFile(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Remove a file
		 * @param[in] path Path to file
		 * 
		 * @throws tc::Exception If the file cannot be removed (invalid path, or access rights)
		 */
	virtual void removeFile(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Open a file
		 * @param[in] path Path to file
		 * @param[in] mode Access mode
		 * @param[out] file Pointer to IFileObject object to be instantiated
		 *	
		 * @throws tc::Exception If the file cannot be opened (invalid path, or access rights)
		 */
	virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::GenericFileObject& file) = 0;
	
		/** 
		 * @brief Create a new directory
		 * @param[in] path Path to directory
		 * 
		 * @post If the directory already exists, this does nothing if the directory cannot be created (invalid path, or access rights)
		 * 
		 * @throws tc::Exception If the directory cannot be created (invalid path, or access rights)
		 */
	virtual void createDirectory(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Remove a directory
		 * @param[in] path Path to directory
		 * 
		 * @throws tc::Exception If the directory cannot be removed (invalid path, or access rights)
		 * 
		 * @post tc::Result::isSuccess() on success
		 */
	virtual void removeDirectory(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Get the full path of the working directory
		 * @param[out] path Path object to populate
		 */
	virtual void getWorkingDirectory(tc::fs::Path& path) = 0;

		/** 
		 * @brief Change the working directory
		 * @param[in] path Path to directory
		 */
	virtual void setWorkingDirectory(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Get directory listing a directory
		 * @param[in] path Path to directory
		 * @param[out] info sDirectoryListing object to populate
		 * 
		 * @throws tc::Exception If the directory cannot be accessed (invalid path, or access rights)
		 * 
		 * @post tc::Result::isSuccess() on success
		 */
	virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info) = 0;
};

}} // namespace tc::fs