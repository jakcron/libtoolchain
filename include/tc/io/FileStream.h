	/**
	 * @file FileStream.h
	 * @brief Declaration of tc::io::FileStream
	 * @author Jack (jakcron)
	 * @version	0.4
	 * @date 2020/01/23
	 */
#pragma once
#include <tc/io/IStream.h>
#include <tc/io/Path.h>
#include <tc/io/FileMode.h>
#include <tc/io/FileAccess.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdio>
#endif

namespace tc { namespace io {

	/**
	 * @class FileStream
	 * @brief An implementation of IStream as a wrapper to local OS file access functions.
	 */
class FileStream : public IStream
{
public:
		/** 
		 * @brief Default constuctor
		 */
	FileStream();

		/** 
		 * @brief Initialsing constuctor.
		 * 
		 * @note Refer to @ref open for usage documentation
		 */
	FileStream(const tc::io::Path& path, FileMode mode, FileAccess access);

		/** 
		 * @brief Open file stream
		 * 
		 * @param[in] path A relative or absolute path for the file that the current FileStream object will encapsulate.
		 * @param[in] mode One of the enumeration values that determines how to open or create the file.
		 * @param[in] access One of the enumeration values that determines how the file can be accessed by the FileStream object. This also determines the values returned by the @ref canRead and @ref canWrite methods of the FileStream object. @ref canSeek is true if path specifies a disk file.
		 *
		 * @throw tc::ArgumentException @p path contains invalid characters or is empty.
		 * @throw tc::NotSupportedException @p path refers to an unsupported non-file device.
		 * @throw tc::io::IOException An I/O error, such as specifying @a FileMode.CreateNew when the file specified by @p path already exists, occurred. Or the stream has been closed.
		 * @throw tc::SecurityException The caller does not have the required permission.
		 * @throw tc::io::DirectoryNotFoundException The specified path is invalid, such as being on an unmapped drive.
		 * @throw tc::UnauthorizedAccessException The @p access requested is not permitted by the operating system for the specified @p path, such as when @p access is @a Write or @a ReadWrite and the file or directory is set for read-only access.
		 * @throw tc::io::PathTooLongException The specified @p path, file name, or both exceed the system-defined maximum length.
		 * @throw tc::ArgumentOutOfRangeException @p mode contains an invalid value.
		 */
	void open(const tc::io::Path& path, FileMode mode, FileAccess access);

	virtual bool canRead() const;
	virtual bool canWrite() const;
	virtual bool canSeek() const;
	virtual int64_t length();
	virtual int64_t position();

	virtual size_t read(byte_t* buffer, size_t count);
	virtual void write(const byte_t* buffer, size_t count);
	virtual int64_t seek(int64_t offset, SeekOrigin origin);
	virtual void setLength(int64_t length);
	virtual void flush();

	virtual void dispose();
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


	bool mCanRead;
	bool mCanWrite;
	bool mCanSeek;
	std::shared_ptr<tc::io::FileStream::FileHandle> mFileHandle;

#ifdef _WIN32
	void open_impl(const tc::io::Path& path, FileMode mode, FileAccess access);
	int64_t length_impl();
	size_t read_impl(byte_t* buffer, size_t count);
	void write_impl(const byte_t* buffer, size_t count);
	int64_t seek_impl(int64_t offset, SeekOrigin origin);
	void setLength_impl(int64_t length);
	void flush_impl();
#else
	void open_impl(const tc::io::Path& path, FileMode mode, FileAccess access);
	int64_t length_impl();
	size_t read_impl(byte_t* buffer, size_t count);
	void write_impl(const byte_t* buffer, size_t count);
	int64_t seek_impl(int64_t offset, SeekOrigin origin);
	void setLength_impl(int64_t length);
	void flush_impl();
#endif
};

}} // namespace tc::io