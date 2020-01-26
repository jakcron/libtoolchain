	/**
	 * @file SubStorage.h
	 * @brief Declaration of tc::io::SubStorage
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/18
	 **/
#pragma once
#include <tc/io/IStorage.h>

#include <tc/ArgumentNullException.h>
#include <tc/InvalidOperationException.h>
#include <tc/ObjectDisposedException.h>
#include <tc/UnauthorisedAccessException.h>

namespace tc { namespace io {

	/**
	 * @class SubStorage
	 * @brief A wrapper around an existing IStorage object that exposes a subset of the base IStorage directory tree.
	 **/
class SubStorage : public IStorage
{
public:

		/**
		 * @brief Default constructor
		 **/
	SubStorage();

		/** 
		 * @brief Wrap (by copy) constuctor
		 * 
		 * @note Refer to @ref initialise (by copy) for usage documentation
		 **/
	SubStorage(const std::shared_ptr<tc::io::IStorage>& storage, const tc::io::Path& base_path);

		/** 
		 * @brief Wrap (by move) constuctor
		 * 
		 * @note Refer to @ref initialise (by move) for usage documentation
		 **/
	SubStorage(std::shared_ptr<tc::io::IStorage>&& storage, const tc::io::Path& base_path);

		/** 
		 * @brief Wrap (by copy) initialiser
		 * 
		 * @param[in] storage The base IStorage object which this sub storage will derive from.
		 * @param[in] base_path The path to the subdirectory used as the substream root directory.
		 * 
		 * @throw tc::ArgumentNullException @p storage is @a nullptr.
		 * @throw tc::InvalidOperationException @p storage was not in a ready state
		 **/
	void initialise(const std::shared_ptr<tc::io::IStorage>& storage, const tc::io::Path& base_path);

		/** 
		 * @brief Wrap (by move) initialiser
		 * 
		 * @param[in] storage The base IStorage object which this sub storage will derive from.
		 * @param[in] base_path The path to the subdirectory used as the substream root directory.
		 * 
		 * @throw tc::ArgumentNullException @p storage is @a nullptr.
		 * @throw tc::InvalidOperationException @p storage was not in a ready state
		 **/
	void initialise(std::shared_ptr<tc::io::IStorage>&& storage, const tc::io::Path& base_path);

	virtual tc::ResourceStatus state();
	virtual void dispose();
	virtual void createFile(const tc::io::Path& path);
	virtual void removeFile(const tc::io::Path& path);
	virtual void openFile(const tc::io::Path& path, tc::io::FileMode mode, tc::io::FileAccess access, std::shared_ptr<tc::io::IStream>& stream);
	virtual void createDirectory(const tc::io::Path& path);
	virtual void removeDirectory(const tc::io::Path& path);
	virtual void getWorkingDirectory(tc::io::Path& path);
	virtual void setWorkingDirectory(const tc::io::Path& path);
	virtual void getDirectoryListing(const tc::io::Path& path, tc::io::sDirectoryListing& info);
private:
	static const std::string kClassName;
	
	std::shared_ptr<tc::io::IStorage> mBaseStorage;
	tc::io::Path mBaseStoragePath;
	tc::io::Path mSubStoragePath;

	void subPathToRealPath(const tc::io::Path& substorage_path, tc::io::Path& real_path);
	void realPathToSubPath(const tc::io::Path& real_path, tc::io::Path& substorage_path);
	void sanitiseInputPath(const tc::io::Path& unsafe_path, tc::io::Path& safe_path) const;
};

}} // namespace tc::io