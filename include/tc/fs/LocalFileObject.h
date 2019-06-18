	/**
	 * @file LocalFileObject.h
	 * @brief Declaration of tc::fs::LocalFileObject
	 * @author Jack (jakcron)
	 * @version	0.3
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/fs/IFileObject.h>
#include <tc/fs/IFileSystem.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdio>
#endif

namespace tc { namespace fs {

	/**
	 * @class LocalFileObject
	 * @brief An implementation of IFileObject as a wrapper to local OS file access functions.
	 */
class LocalFileObject : public IFileObject
{
public:
		/** 
		 * @brief Default constuctor
		 */
	LocalFileObject();

		/** 
		 * @brief Initialsing constuctor
		 * @param[in] path Path to file
		 * @param[in] mode Access mode
		 */
	LocalFileObject(const tc::fs::Path& path, tc::fs::FileAccessMode mode);

	virtual tc::fs::IFileObject* copyInstance() const;
	virtual tc::fs::IFileObject* moveInstance();
	virtual tc::ResourceState state();

		/** 
		 * @brief Open file
		 * @param[in] path Path to file
		 * @param[in] mode Access mode
		 */
	void open(const tc::fs::Path& path, tc::fs::FileAccessMode mode);

	virtual void close();
	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);
private:
	static const std::string kClassName;

	struct FileHandle
	{
#ifdef _WIN32
		HANDLE handle;
		FileHandle(HANDLE h) :  handle(h) {}
#else
		int handle;
		FileHandle(int h) :  handle(h) {}
#endif
		~FileHandle();		
	};

	tc::ResourceState mState;
	
	tc::fs::FileAccessMode mMode;
	tc::SharedPtr<tc::fs::LocalFileObject::FileHandle> mFileHandle;

#ifdef _WIN32
	DWORD getOpenModeFlag(tc::fs::FileAccessMode mode) const;
	DWORD getShareModeFlag(tc::fs::FileAccessMode mode) const;
	DWORD getCreationModeFlag(tc::fs::FileAccessMode mode) const;
#else
	int getOpenModeFlag(tc::fs::FileAccessMode mode) const;
#endif
};

}} // namespace tc::fs