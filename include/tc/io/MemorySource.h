	/**
	 * @file MemorySource.h
	 * @brief Declaration of tc::io::MemorySource
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/03/20
	 **/
#pragma once
#include <tc/io/ISource.h>

namespace tc { namespace io {

	/**
	 * @class MemorySource
	 * @brief A block of run-time memory wrapped as an ISource object. 
	 **/
class MemorySource : tc::io::ISource
{
public:
		/**
		 * @brief Default constructor
		 * @post This will create a MemorySource with length() == 0.
		 **/ 
	MemorySource();

		/** 
		 * @brief Create MemorySource from a tc::ByteData object.
		 * 
		 * @param[in] byte_data The base data to create the MemorySource from.
		 **/
	MemorySource(const tc::ByteData& byte_data);

		/** 
		 * @brief Create MemorySource from a memory pointer.
		 * 
		 * @param[in] data Pointer to memory which will populate this MemorySource.
		 * @param[in] len Length of data to copy int this MemorySource.
		 **/
	MemorySource(const byte_t* data, size_t len);

		/**
		 * @brief Gets the length of the source.
		 **/
	int64_t length();

		/**
		 * @brief Pull data from source
		 * 
		 * @param[in] offset Zero-based offset in source to pull data.
		 * @param[in] count The maximum number of bytes to be pull from the source.
		 *
		 * @return ByteData containing data pulled from source
		 **/
	tc::ByteData pullData(int64_t offset, size_t count);
private:
	static const std::string kClassName;

	tc::ByteData mData;
};

}} // namespace tc::io