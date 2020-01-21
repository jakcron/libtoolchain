	/**
	 * @file LocalFileSystem.h
	 * @brief Declaration of tc::fs::LocalFileSystem
	 * @author Jack (jakcron)
	 * @version 0.5
	 * @date 2019/06/18
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
		/// Default Constructor
	LocalFileSystem();

	virtual tc::ResourceState getFsState();

		/// Open Local Filesystem
	void openFs();

	virtual void closeFs();
	virtual void createFile(const tc::fs::Path& path);
	virtual void removeFile(const tc::fs::Path& path);
	virtual void openFile(const tc::fs::Path& path, tc::fs::FileAccessMode mode, std::shared_ptr<tc::fs::IFileObject>& file);
	virtual void createDirectory(const tc::fs::Path& path);
	virtual void removeDirectory(const tc::fs::Path& path);
	virtual void getWorkingDirectory(tc::fs::Path& path);
	virtual void setWorkingDirectory(const tc::fs::Path& path);
	virtual void getDirectoryListing(const tc::fs::Path& path, tc::fs::sDirectoryListing& info);
private:
	static const std::string kClassName;

	tc::ResourceState mState;
};

}} // namespace tc::fs