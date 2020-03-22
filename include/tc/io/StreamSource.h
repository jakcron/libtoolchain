	/**
	 * @file StreamSource.h
	 * @brief Declaration of tc::io::StreamSource
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/02/13
	 **/
#pragma once
#include <tc/io/ISource.h>
#include <tc/io/IStream.h>

#include <tc/ArgumentNullException.h>
#include <tc/NotSupportedException.h>
#include <tc/ObjectDisposedException.h>

namespace tc { namespace io {

	/**
	 * @class StreamSource
	 * @brief An IStream wrapped in an ISource.
	 **/
class StreamSource : tc::io::ISource
{
public:
		/**
		 * @brief Default constructor
		 **/ 
	StreamSource();

		/** 
		 * @brief Create StreamSource
		 * 
		 * @param[in] stream The base IStream object which this sub source will derive from.
		 * 
		 * @pre The base stream must support reading.
		 * 
		 * @throw tc::ArgumentNullException @p stream is a @p nullptr.
		 * @throw tc::NotSupportedException @p stream does not support reading.
		 **/
	StreamSource(const std::shared_ptr<tc::io::IStream>& stream);

		/**
		 * @brief Gets the length of the source.
		 * 
		 * @throw tc::ObjectDisposedException The base stream was not initialised.
		 **/
	int64_t length();

		/**
		 * @brief Pull data from source
		 * 
		 * @param[in] offset Zero-based offset in source to pull data.
		 * @param[in] count The maximum number of bytes to be pull from the source.
		 *
		 * @return ByteData containing data pulled from source
		 * 
		 * @throw tc::ObjectDisposedException The base stream was not initialised.
		 **/
	tc::ByteData pullData(int64_t offset, size_t count);
private:
	static const std::string kClassName;

	std::shared_ptr<tc::io::IStream> mBaseStream;
	int64_t mBaseSourceOffset;

	int64_t mStreamSourceLength;
};

}} // namespace tc::io