/**
 * @file LocalFileSystem.h
 * @brief Declaration of tc::fs::LocalFileSystem
 * @author Jack (jakcron)
 * @version 0.2
 * @date 2018/12/23
 */
#pragma once
#include <tc/fs/IFileSystem.h>

#ifdef _WIN32
	#include <windows.h>
#endif

namespace tc { namespace fs {

	/**
	 * @class LocalFileSystem
	 * @brief An IFileSystem wrapper around the existing OS FileSystem API.
	 */
	class LocalFileSystem : public IFileSystem
	{
	public:
		/** 
		 * @brief Default Constructor
		 */
		LocalFileSystem();

		tc::fs::IFile* openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode);
		void deleteFile(const tc::fs::Path& path);
		void getCurrentDirectory(tc::fs::Path& path);
		void setCurrentDirectory(const tc::fs::Path& path);
		void createDirectory(const tc::fs::Path& path);
		void deleteDirectory(const tc::fs::Path& path);
		void getDirectoryListing(const tc::fs::Path& path, tc::fs::DirectoryInfo& info);

	private:
		const std::string kClassName = "tc::fs::LocalFileSystem";
#ifdef _WIN32
		DWORD getOpenModeFlag(tc::fs::FileAccessMode mode) const;
		DWORD getShareModeFlag(tc::fs::FileAccessMode mode) const;
		DWORD getCreationModeFlag(tc::fs::FileAccessMode mode) const;

		void pathToWindowsUTF16(const tc::fs::Path& path, std::u16string& out);
#else
		int getOpenModeFlag(tc::fs::FileAccessMode mode) const;

		void pathToUnixUTF8(const tc::fs::Path& path, std::string& out);
#endif
	};

}} // namespace tc::fs