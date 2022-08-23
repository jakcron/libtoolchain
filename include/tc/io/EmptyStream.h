	/**
	 * @file EmptyStream.h
	 * @brief Declaration of tc::io::EmptyStream
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2022/08/23
	 **/
#pragma once
#include <tc/io/IStream.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotSupportedException.h>

namespace tc { namespace io {

	/**
	 * @class EmptyStream
	 * @brief A read-only zero length IStream object, used in operations where a valid but empty stream must be returned. 
	 **/
class EmptyStream : public tc::io::IStream
{
public:
		/** 
		 * @brief Default constuctor
		 **/
	EmptyStream();

		/**
		 * @brief Indicates whether the current stream supports reading.
		 **/ 
	bool canRead() const;

		/**
		 * @brief Indicates whether the current stream supports writing.
		 **/
	bool canWrite() const;

		/**
		 * @brief Indicates whether the current stream supports seeking.
		 **/
	bool canSeek() const;

		/**
		 * @brief Gets the length in bytes of the stream.
		 **/
	int64_t length();

		/** 
		 * @brief Gets the position within the current stream.
		 **/
	int64_t position();

		/**
		 * @brief Reads a sequence of bytes from the current stream and advances the position within the stream by the number of bytes read.
		 * 
		 * @param[out] ptr Pointer to an array of bytes. When this method returns, @p ptr contains the specified byte array with the values between 0 and (@p count - 1) replaced by the bytes read from the current source.
		 * @param[in] count The maximum number of bytes to be read from the current stream.
		 * 
		 * @return The total number of bytes read into @p ptr. This can be less than the number of bytes requested if that many bytes are not currently available, or zero (0) if the end of the stream has been reached.
		 * 
		 * @throw tc::ArgumentNullException @p ptr is @a nullptr.
		 **/
	size_t read(byte_t* ptr, size_t count);

		/**
		 * @brief Writes a sequence of bytes to the current stream and advances the current position within this stream by the number of bytes written.
		 * 
		 * @param[in] ptr Pointer to an array of bytes. This method copies @p count bytes from @p ptr to the current stream.
		 * @param[in] count The number of bytes to be written to the current stream.
		 * 
		 * @return The total number of bytes written to the stream. This can be less than the number of bytes requested if that many bytes are not currently available, or zero (0) if the end of the stream has been reached.
		 * 
		 * @throw tc::NotSupportedException @ref write is not supported for @ref EmptyStream
		 **/
	size_t write(const byte_t* ptr, size_t count);

		/**
		 * @brief Sets the position within the current stream.
		 * 
		 * @param[in] offset A byte offset relative to the origin parameter.
		 * @param[in] origin A value of type @ref tc::io::SeekOrigin indicating the reference point used to obtain the new position.
		 * 
		 * @return The new position within the current stream.
		 * 
		 * @throw tc::ArgumentOutOfRangeException @p origin contains an invalid value.
		 **/
	int64_t seek(int64_t offset, SeekOrigin origin);


		/**
		 * @brief Sets the length of the current stream.
		 * 
		 * @param[in] length The desired length of the current stream in bytes.
		 * 
		 * @post If the new length is smaller than the current length, the data will be truncated.
		 * 
		 * @throw tc::NotSupportedException @ref setLength is not supported for @ref EmptyStream
		 **/
	void setLength(int64_t length);

		/**
		 * @brief This does nothing for tc::io::EmptyStream
		 **/
	void flush();

		/**
		 * @brief This does nothing for tc::io::EmptyStream
		 **/
	void dispose();
private:
	static const std::string kClassName;
};

}} // namespace tc::io