	/**
	 * @file LocalStorage.h
	 * @brief Declaration of tc::io::LocalStorage
	 * @author Jack (jakcron)
	 * @version 0.5
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/io/IStorage.h>

#ifdef _WIN32
	#include <windows.h>
#endif

namespace tc { namespace io {

	/**
	 * @class LocalStorage
	 * @brief An IStorage wrapper around the existing OS FileSystem API.
	 */
class LocalStorage : public IStorage
{
public:
		/// Default Constructor
	LocalStorage();

		/// Open Local Storage
	void openStorage();

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

	tc::ResourceStatus mState;
};

}} // namespace tc::io