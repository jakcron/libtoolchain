	/**
	 * @file LocalFileHandle.h
	 * @brief Declaration of tc::fs::LocalFileHandle
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/05/21
	 * @note Private Class
	 */
#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdio>
#endif

namespace tc { namespace fs {

	/**
	 * @typedef fs_handle_t
	 * @brief Typedef windows/unix file handle as something generic
	 */
#ifdef _WIN32
		typedef HANDLE fs_handle_t;
#else
		typedef int fs_handle_t;
#endif

	/**
	 * @class LocalFileHandle
	 * @brief A wrapper to the native file handle
	 */
class LocalFileHandle
{
public:
		/** 
		 * @brief Default constuctor
		 * @param[in] file_handle Native file handle 
		 */
	LocalFileHandle(tc::fs::fs_handle_t file_handle);

		/// Destructor
	~LocalFileHandle();

	tc::fs::fs_handle_t getHandle();
private:
	LocalFileHandle();
	LocalFileHandle(const LocalFileHandle& other);
	LocalFileHandle(LocalFileHandle&& other);
	LocalFileHandle& operator=(const LocalFileHandle& other) const;
	LocalFileHandle& operator=(LocalFileHandle&& other);

	tc::fs::fs_handle_t mFileHandle;
};

}} // namespace tc::fs