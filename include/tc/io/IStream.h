	/**
	 * @file IStream.h
	 * @brief Declaration of tc::io::IStream
	 * @author Jack (jakcron)
	 * @version	0.4
	 * @date 2020/01/22
	 */
#pragma once
#include <tc/types.h>
#include <tc/io/SeekOrigin.h>

namespace tc { namespace io {

	/**
	 * @class IStream
	 * @brief An interface for implementing a basic data stream handler.
	 *
	 * Defines expcted functionality required to process/access a data stream.
	 * 
	 * Usage of size_t with offsets and lengths reflect run-time memory allocation limits
	 * Usage of int64_t with offsets and lengths reflect more closely the natural size limits of a stream
	 */
class IStream
{
public:
		/**
		 * @brief Destructor
		 */
	virtual ~IStream() = default;

		/**
		 * @brief Indicates whether the current stream supports reading.
		 **/ 
	virtual bool canRead() const = 0;

		/**
		 * @brief Indicates whether the current stream supports writing.
		 **/
	virtual bool canWrite() const = 0;

		/**
		 * @brief Indicates whether the current stream supports seeking.
		 **/
	virtual bool canSeek() const = 0;

		/**
		 * @brief Gets the length in bytes of the stream.
		 **/
	virtual int64_t length() = 0;

		/** 
		 * @brief Gets the position within the current stream.
		 */
	virtual int64_t position() = 0;

		/**
		 * @brief Reads a sequence of bytes from the current stream and advances the position within the stream by the number of bytes read.
		 * 
		 * @param[out] buffer An array of bytes. When this method returns, the buffer contains the specified byte array with the values between offset and (offset + length - 1) replaced by the bytes read from the current source.
		 * @param[in] offset The zero-based byte offset in buffer at which to begin storing the data read from the current stream.
		 * @param[in] count The maximum number of bytes to be read from the current stream.
		 * 
		 * @return The total number of bytes read into the buffer. This can be less than the number of bytes requested if that many bytes are not currently available, or zero (0) if the end of the stream has been reached.
		 * 
		 * @pre A stream must support reading for @ref read to work. 
		 * @note Use @ref canRead to determine if this stream supports reading.
		 * 
		 * @throw tc::ArgumentNullException @p buffer is @a nullptr.
		 * @throw tc::ArgumentOutOfRangeException @p offset or @p count is negative.
		 * @throw tc::io::IOException An I/O error occurred, such as the specified file cannot be found.
		 * @throw tc::NotSupportedException The stream does not support reading.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual size_t read(byte_t* buffer, size_t offset, size_t count) = 0;
	
		/**
		 * @brief Writes a sequence of bytes to the current stream and advances the current position within this stream by the number of bytes written.
		 * 
		 * @param[in] buffer An array of bytes. This method copies count bytes from buffer to the current stream.
		 * @param[in] offset The zero-based byte offset in buffer at which to begin copying bytes to the current stream.
		 * @param[in] count The number of bytes to be written to the current stream.
		 * 
		 * @pre A stream must support writing for @ref write to work. 
		 * @note Use @ref canWrite to determine if this stream supports writing.
		 * 
		 * @throw tc::ArgumentNullException @p buffer is @a nullptr.
		 * @throw tc::ArgumentOutOfRangeException @p offset or @p count is negative.
		 * @throw tc::io::IOException An I/O error occurred, such as the specified file cannot be found.
		 * @throw tc::NotSupportedException The stream does not support writing.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual void write(const byte_t* buffer, size_t offset, size_t count) = 0;
	
		/**
		 * @brief Sets the position within the current stream.
		 * 
		 * @param[in] offset A byte offset relative to the origin parameter.
		 * @param[in] origin A value of type @ref tc::io::SeekOrigin indicating the reference point used to obtain the new position.
		 * 
		 * @return The new position within the current stream.
		 * 
		 * @pre A stream must support seeking for @ref seek to work. 
		 * @note Use @ref canSeek to determine if this stream supports seeking.
		 * 
		 * @throw tc::io::IOException An I/O error occurs.
		 * @throw tc::NotSupportedException The stream does not support seeking, such as if the stream is constructed from a pipe or console output.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual int64_t seek(int64_t offset, SeekOrigin origin) = 0;

		/**
		 * @brief Sets the length of the current stream.
		 * 
		 * @param[in] length The desired length of the current stream in bytes.
		 * 
		 * @pre A stream must support both writing and seeking for @ref setLength to work. 
		 * @note Use @ref canWrite to determine if this stream supports writing.
		 * @note Use @ref canSeek to determine if this stream supports seeking.
		 * 
		 * @throw tc::io::IOException An I/O error occurs.
		 * @throw tc::NotSupportedException The stream does not support both writing and seeking, such as if the stream is constructed from a pipe or console output.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual void setLength(int64_t length) = 0;
	
		/**
		 * @brief Clears all buffers for this stream and causes any buffered data to be written to the underlying device.
		 * 
		 * @throw tc::io::IOException An I/O error occurs.
		 **/
	virtual void flush() = 0;
	
		/**
		 * @brief Releases all resources used by the Stream.
		 **/
	virtual void dispose() = 0;
};

}}