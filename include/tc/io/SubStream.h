	/**
	 * @file SubStream.h
	 * @brief Declaration of tc::io::SubStream
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/19
	 **/
#pragma once
#include <tc/io/IStream.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotSupportedException.h>
#include <tc/NotImplementedException.h>
#include <tc/ObjectDisposedException.h>

namespace tc { namespace io {

	/**
	 * @class SubStream
	 * @brief A wrapper around an existing IStream object that exposes a subset of the base the IStream object.
	 **/
class SubStream : public tc::io::IStream
{
public:
		/**
		 * @brief Default constructor
		 **/
	SubStream();

		/** 
		 * @brief Create SubStream
		 * 
		 * @param[in] stream The base IStream object which this sub stream will derive from.
		 * @param[in] offset The zero-based byte offset in stream at which to begin the sub stream.
		 * @param[in] length Length of the sub stream.
		 * 
		 * @pre The sub stream must be a subset of the base stream.
		 * @pre A stream must support seeking for @ref seek to work. 
		 * 
		 * @throw tc::ArgumentNullException @p stream is a @p nullptr.
		 * @throw tc::NotSupportedException The base stream does not support seeking.
		 * @throw tc::ArgumentOutOfRangeException @p offset or @p length is negative or otherwise invalid given the length of the base stream.
		 **/
	SubStream(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length);

	virtual bool canRead() const;
	virtual bool canWrite() const;
	virtual bool canSeek() const;

		/**
		 * @brief Gets the length in bytes of the stream.
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual int64_t length();

		/** 
		 * @brief Gets the position within the current stream. 
		 * 
		 * @return This is returns the result of seek(0, SeekOrigin::Current);
		 * 
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual int64_t position();

		/**
		 * @brief Reads a sequence of bytes from the current stream and advances the position within the stream by the number of bytes read.
		 * 
		 * @param[out] buffer An array of bytes. When this method returns, the buffer contains the specified byte array with the values between 0 and (@p count - 1) replaced by the bytes read from the current source.
		 * @param[in] count The maximum number of bytes to be read from the current stream.
		 * 
		 * @return The total number of bytes read into the buffer. This can be less than the number of bytes requested if that many bytes are not currently available, or zero (0) if the end of the stream has been reached.
		 * 
		 * @pre A stream must support reading for @ref read to work. 
		 * @note Use @ref canRead to determine if this stream supports reading.
		 * @note Exceptions thrown by the base stream are not altered/intercepted, refer to that module's documentation for those exceptions.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p count exceeds the length of readable data in the sub stream.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual size_t read(byte_t* buffer, size_t count);

		/**
		 * @brief Writes a sequence of bytes to the current stream and advances the current position within this stream by the number of bytes written.
		 * 
		 * @param[in] buffer An array of bytes. This method copies count bytes from buffer to the current stream.
		 * @param[in] count The number of bytes to be written to the current stream.
		 * 
		 * @pre A stream must support writing for @ref write to work. 
		 * @note Use @ref canWrite to determine if this stream supports writing.
		 * @note Exceptions thrown by the base stream are not altered/intercepted, refer to that module's documentation for those exceptions.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p count exceeds the length of writeable data in the sub stream.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual void write(const byte_t* buffer, size_t count);

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
		 * @note Exceptions thrown by the base stream are not altered/intercepted, refer to that module's documentation for those exceptions.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p origin contains an invalid value.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual int64_t seek(int64_t offset, SeekOrigin origin);

		/**
		 * @brief Sets the length of the current stream. THIS IS NOT IMPLEMENTED FOR @ref SubStream.
		 * 
		 * @param[in] length The desired length of the current stream in bytes.
		 * 
		 * @pre A stream must support both writing and seeking for @ref setLength to work. 
		 * @note Use @ref canWrite to determine if this stream supports writing.
		 * @note Use @ref canSeek to determine if this stream supports seeking.
		 * 
		 * @throw tc::NotImplementedException @ref setLength is not implemented for @ref SubStream
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual void setLength(int64_t length);

		/**
		 * @brief Clears all buffers for this and the base steram and causes any buffered data to be written to the underlying device.
		 * 
		 * @throw tc::io::IOException An I/O error occurs.
		 * @throw tc::ObjectDisposedException Methods were called after the stream was closed.
		 **/
	virtual void flush();
	
	virtual void dispose();
private:
	static const std::string kClassName;

	std::shared_ptr<tc::io::IStream> mBaseStream;
	int64_t mBaseStreamOffset;

	int64_t mSubStreamLength;
	int64_t mSubStreamPosition;
};

}} // namespace tc::io