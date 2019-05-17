/**
 * @file LocalFileObject.h
 * @brief Declaration of tc::fs::LocalFileObject
 * @author Jack (jakcron)
 * @version	0.1
 * @date 2018/11/10
 * @note Private Class
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

/**	fs_handle_t
 * 
 */
#ifdef _WIN32
		typedef HANDLE fs_handle_t;
#else
		typedef int fs_handle_t;
#endif

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
		LocalFileObject(tc::fs::FileAccessMode mode, fs_handle_t file_handle);
	
		~LocalFileObject();
		uint64_t size();
		void seek(uint64_t offset);
		uint64_t pos();
		void read(byte_t* data, size_t len);
		void write(const byte_t* data, size_t len);
	
	private:
		const std::string kClassName = "tc::fs::LocalFileObject";

		tc::fs::FileAccessMode mMode;
		tc::fs::fs_handle_t mFileHandle;
	};

}} // namespace tc::fs