	/**
	 * @file ByteData.h
	 * @brief Declaration of tc::ByteData
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2020/04/08
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
		/// Create empty ByteData
	ByteData();

		/**
		 * @brief Create linear memory block
		 * 
		 * @param[in] size Size in bytes of the memory block.
		 * @param[in] clear_memory Clear memory after allocation. Default is true.
		 * 
		 * @throw tc::OutOfMemoryException Insuffient memory available.
		 **/
	ByteData(size_t size, bool clear_memory = true);

		/**
		 * @brief Create ByteData from existing memory.
		 * 
		 * @param[in] data Pointer to memory to copy.
		 * @param[in] size Size of memory to copy.
		 * 
		 * @throw tc::OutOfMemoryException Insuffient memory available.
		 **/
	ByteData(const byte_t* data, size_t size);
		
		/**
		 * @brief Get data pointer
		 **/
	byte_t* get() const;

		/**
		 * @brief Get data size
		 **/
	size_t size() const;
private:
	static const std::string kClassName;

	size_t mSize;
	std::shared_ptr<byte_t> mPtr;
}; 

} // namespace tc