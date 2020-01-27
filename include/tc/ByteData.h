	/**
	 * @file ByteData.h
	 * @brief Declaration of tc::ByteData
	 * @author Jack (jakcron)
	 * @version 0.6
	 * @date 2019/06/18
	 **/
#pragma once
#include <tc/types.h>

#include <tc/OutOfMemoryException.h>

namespace tc {

	/**
	 * @class ByteData
	 * @brief A container of linear memory, used to hold raw data.
	 **/
class ByteData
{
public:
		/**
		 * @brief Create linear memory block
		 * 
		 * @param[in] size Size in bytes of the memory block
		 * 
		 * @throw tc::OutOfMemoryException Insuffient memory available.
		 **/
	ByteData(size_t size);
		
		/**
		 * @brief Get buffer pointer
		 **/
	const byte_t* buffer() const { return mPtr.get(); }

		/**
		 * @brief Get buffer size
		 **/
	size_t size() const { return mSize; }
private:
	static const std::string kClassName;

	// deleted default constructor
	ByteData();

	size_t mSize;
	std::shared_ptr<byte_t> mPtr;
}; 

} // namespace tc