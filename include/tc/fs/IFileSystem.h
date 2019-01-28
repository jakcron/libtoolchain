/**
 * @file IFileSystem.h
 * @brief Declaration of tc::fs::IFileSystem
 * @author Jack (jakcron)
 * @version 0.3
 * @date 2019/01/15
 */
#pragma once
#include <tc/types.h>
#include <tc/fs/IFile.h>
#include <tc/fs/DirectoryInfo.h>

namespace tc { namespace fs {

	/** FileAccessMode
	 *  This enum is used with openFile() to determine the access mode
	 */
	enum FileAccessMode
	{
		FAM_READ, /**< Access file with READ-ONLY permissions */
		FAM_EDIT, /**< Access file with READ-WRITE permissions */
		FAM_CREATE /**< Create a new file or overwrite an existing file (READ-WRITE permissions) */
	};

	/**
	 * @class IFileSystem
	 * 
	 * @brief An interface for implementing a basic FileSystem handler.
	 *
	 * Defines expected functionality including:
	 * - File access (open,delete)
	 * - Directory traversal (get current directory, change current directory)
	 * - Directory management (create,remove)
	 * - Directory listing
	 * 
	 * @note IFileSystem uses the tc::fs::Path class to represent a path, not as a literal string.
	 * @note It is up to the implementation of IFileSystem to validate and process tc::fs::Path objects.
	 * @note It is up to the implementation to enforce tc::fs::FileAccessMode.
	 */
	class IFileSystem
	{
	public:
		virtual ~IFileSystem() = default;

		/** 
		 * @brief Open a file
		 * @param[in] path Path to file
		 * @param[in] mode Access mode
		 * @return Pointer to IFile object
		 *	
		 * @throws tc::Exception If the file cannot be accessed (invalid path, or access rights)
		 */
		virtual tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode) = 0;

		/** 
		 * @brief Delete a file
		 * @param[in] path Path to file
		 * 
		 * @throws tc::Exception If the file cannot be removed (invalid path, or access rights)
		 */
		virtual void deleteFile(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Get the full path of the current directory
		 * @param[out] path Path object to populate
		 */
		virtual void getCurrentDirectory(tc::fs::Path& path) = 0;

		/** 
		 * @brief Change the current directory
		 * @param[in] path Path to directory
		 */
		virtual void setCurrentDirectory(const tc::fs::Path& path) = 0;
		
		/** 
		 * @brief Create a new directory
		 * @param[in] path Path to directory
		 * 
		 * @post If the directory already exists, this does nothing
		 * @throws tc::Exception If the directory cannot be created (invalid path, or access rights)
		 */
		virtual void createDirectory(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Delete a directory
		 * @param[in] path Path to directory
		 * 
		 * @throws tc::Exception If the directory cannot be deleted (invalid path, or access rights)
		 */
		virtual void deleteDirectory(const tc::fs::Path& path) = 0;

		/** 
		 * @brief Get directory listing a directory
		 * @param[in] path Path to directory
		 * @param[out] info DirectoryInfo object to populate
		 * 
		 * @throws tc::Exception If the directory cannot be accessed (invalid path, or access rights)
		 */
		virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& info) = 0;
	};

}} // namespace tc::fs