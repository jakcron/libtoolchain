/**
 * @file LocalFile.h
 * @brief Declaration of tc::fs::LocalFile
 * @author Jack (jakcron)
 * @version	0.1
 * @date 2018/11/10
 * @note Private Class
 */
#pragma once
#include <tc/fs/IFile.h>
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
	 * @class LocalFile
	 * @brief An implementation of IFile as a wrapper to local OS file access functions.
	 */
	class LocalFile : public IFile
	{
	public:
		/** 
		 * @brief Default constuctor
		 * @param[in] mode Access mode
		 * @param[in] file_handle Native file handle 
		 */
		LocalFile(tc::fs::FileAccessMode mode, fs_handle_t file_handle);
	
		~LocalFile();
		uint64_t size();
		void seek(uint64_t offset);
		uint64_t pos();
		void read(byte_t* data, size_t len);
		void write(const byte_t* data, size_t len);
	
	private:
		const std::string kClassName = "tc::fs::LocalFile";

		tc::fs::FileAccessMode mMode;
		tc::fs::fs_handle_t mFileHandle;
	};

}} // namespace tc::fs