	/**
	 * @file FileSystem.h
	 * @brief Declaration of tc::fs::FileSystem
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/05/17
	 */
#pragma once
#include <tc/fs/IFileSystem.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class FileSystem
	 * @brief A wrapper around an IFileSystem pointer
	 */
class FileSystem : public IFileSystem
{
public:
		/** 
		 * @brief Default constuctor
		 */
	FileSystem();

		/**
		 * @brief Copy Constructor
		 * @param[in] other FileSystem object to copy
		 */
	FileSystem(const tc::fs::FileSystem& other);

		/** 
		 * @brief Direct Wrap Constructor
		 * @param[in] file_ptr Pointer to IFileSysten object to be wrapped
		 */
	FileSystem(tc::fs::IFileSystem* file_ptr);

		/**
		 * @brief Copy Assignment Operator
		 * @param[in] other FileSystem object to copy
		 * 
		 * @return this object
		 */
	FileSystem& operator=(const tc::fs::FileSystem& other);

	void createFile(const tc::fs::Path& path);
	void removeFile(const tc::fs::Path& path);
	void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::FileObject& file);
	void createDirectory(const tc::fs::Path& path);
	void removeDirectory(const tc::fs::Path& path);
	void getWorkingDirectory(tc::fs::Path& path);
	void setWorkingDirectory(const tc::fs::Path& path);
	void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);

private:
	const std::string kClassName = "tc::fs::FileSystem";

	tc::SharedPtr<tc::fs::IFileSystem> mFileSystem;
};

}} // namespace tc::fs