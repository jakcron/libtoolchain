	/**
	 * @file LocalFileSystem.h
	 * @brief Declaration of tc::fs::LocalFileSystem
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/05/17
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

	void createFile(const tc::fs::Path& path);
	void removeFile(const tc::fs::Path& path);
	void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, tc::fs::FileObject& file);
	void createDirectory(const tc::fs::Path& path);
	void removeDirectory(const tc::fs::Path& path);
	void getWorkingDirectory(tc::fs::Path& path);
	void setWorkingDirectory(const tc::fs::Path& path);
	void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);

private:
	const std::string kClassName = "tc::fs::LocalFileSystem";

	bool validateFileAccessMode(tc::fs::FileAccessMode mode) const;
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