	/**
	 * @file LocalFileObject.h
	 * @brief Declaration of tc::fs::LocalFileObject
	 * @author Jack (jakcron)
	 * @version	0.2
	 * @date 2019/05/20
	 * @note Private Class
	 */
#pragma once
#include <tc/fs/IFileObject.h>
#include <tc/fs/IFileSystem.h>
#include "LocalFileHandle.h"

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
		 * @param[in] mode Access mode
		 * @param[in] file_handle Native file handle 
		 */
	LocalFileObject(tc::fs::FileAccessMode mode, tc::fs::fs_handle_t file_handle);

	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);

	virtual tc::fs::IFileObject* copyInstance() const;
	virtual tc::fs::IFileObject* moveInstance();

private:
	static const std::string kClassName;

	// Private so it cannot be used
	LocalFileObject();

	tc::fs::FileAccessMode mMode;
	tc::SharedPtr<tc::fs::LocalFileHandle> mFileHandle;
};

}} // namespace tc::fs