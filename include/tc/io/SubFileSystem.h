	/**
	 * @file SubFileSystem.h
	 * @brief Declaration of tc::io::SubFileSystem
	 * @author Jack (jakcron)
	 * @version 0.4
	 * @date 2020/01/26
	 **/
#pragma once
#include <tc/io/IFileSystem.h>

#include <tc/ArgumentNullException.h>
#include <tc/InvalidOperationException.h>
#include <tc/ObjectDisposedException.h>
#include <tc/UnauthorisedAccessException.h>

namespace tc { namespace io {

	/**
	 * @class SubFileSystem
	 * @brief A wrapper around an existing IFileSystem object that exposes a subset of the base IFileSystem directory tree.
	 **/
class SubFileSystem : public tc::io::IFileSystem
{
public:

		/**
		 * @brief Default constructor
		 * @post This will create an unusable SubFileSystem, it will have to be assigned from a valid SubFileSystem object to be usable.
		 **/
	SubFileSystem();

		/** 
		 * @brief Create SubFileSystem
		 * 
		 * @param[in] storage The base IFileSystem object which this sub storage will derive from.
		 * @param[in] base_path The path to the subdirectory used as the substream root directory.
		 * 
		 * @throw tc::ArgumentNullException @p storage is @a nullptr.
		 * @throw tc::InvalidOperationException @p storage was not in a ready state
		 **/
	SubFileSystem(const std::shared_ptr<tc::io::IFileSystem>& storage, const tc::io::Path& base_path);

	tc::ResourceStatus state();
	void dispose();

		/** 
		 * @brief Create a new file
		 * 
		 * @param[in] path A relative or absolute path to file.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void createFile(const tc::io::Path& path);

		/** 
		 * @brief Remove a file
		 * 
		 * @param[in] path A relative or absolute path to file.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void removeFile(const tc::io::Path& path);

		/** 
		 * @brief Open a file
		 * 
		 * @param[in] path A relative or absolute path to file.
		 * @param[in] mode One of the enumeration values that determines how to open or create the file.
		 * @param[in] access One of the enumeration values that determines how the file can be accessed by the @ref IStream object. This also determines the values returned by the @ref IStream::canRead and @ref IStream::canWrite methods of the IStream object. @ref IStream::canSeek is true if path specifies a disk file.
		 * @param[out] stream Pointer to IStream object to be instantiated
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream);
	
		/** 
		 * @brief Create a new directory
		 * 
		 * @param[in] path A relative or absolute path to directory.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void createDirectory(const tc::io::Path& path);

		/** 
		 * @brief Remove a directory
		 * @param[in] path A relative or absolute path to directory.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void removeDirectory(const tc::io::Path& path);

		/** 
		 * @brief Get the full path of the working directory
		 * @param[out] path Path object to populate
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	void getWorkingDirectory(tc::io::Path& path);

		/** 
		 * @brief Change the working directory
		 * @param[in] path A relative or absolute path to directory.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 * @throw tc::UnauthorisedAccessException Substorage escape detected.
		 **/
	void setWorkingDirectory(const tc::io::Path& path);

		/** 
		 * @brief Get directory listing a directory
		 * @param[in] path A relative or absolute path to directory.
		 * @param[out] info The sDirectoryListing object to populate
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 * @throw tc::UnauthorisedAccessException Substorage escape detected.
		 **/
	void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info);
private:
	static const std::string kClassName;
	
	std::shared_ptr<tc::io::IFileSystem> mBaseStorage;
	tc::io::Path mBaseStoragePath;
	tc::io::Path mSubStoragePath;

	void subPathToRealPath(const tc::io::Path& substorage_path, tc::io::Path& real_path);
	void realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& substorage_path);
	void sanitiseInputPath(const tc::io::Path& unsafe_path, tc::io::Path& safe_path) const;
};

}} // namespace tc::io