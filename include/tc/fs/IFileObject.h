	/**
	 * @file IFileObject.h
	 * @brief Declaration of tc::fs::IFileObject
	 * @author Jack (jakcron)
	 * @version	0.3
	 * @date 2019/06/16
	 */
#pragma once
#include <tc/types.h>
#include <tc/ResourceState.h>

namespace tc { namespace fs {

	/**
	 * @class IFileObject
	 * @brief An interface for implementing a basic File handler.
	 *
	 * Defines expcted functionality required to process/access a file.
	 * 
	 * The usage of size_t in read()/write() reflects the intention that size_t can represent 
	 * sizes relevant to the run-time of a program. Whereas the usage of uint64_t in size()/seek()/pos() 
	 * reflects the realty that files exist independent of the operating system which 
	 * the programs run under. To that end it is important to accept this and preserve the 
	 * true sizes of the files, while also working with-in the limitations of the operating system
	 * by using size_t where memory is processed.
	 */
class IFileObject
{
public:
		/**
		 * @brief Destructor
		 */
	virtual ~IFileObject() = default;

		/**
		 * @brief Create a new instance of this object as a copy. This allows this instance to be copied even when the type isn't known.
		 * This is required by @ref tc::fs::GenericFileObject
		 * @return new instance of IFileObject (dynamically allocated)
		 */
	virtual IFileObject* copyInstance() const = 0;

		/**
		 * @brief Create a new instance of this object and move elements to the new instance. This allows this instance to be moved even when the type isn't known.
		 * This is required by @ref tc::fs::GenericFileObject
		 * @return new instance of IFileObject (dynamically allocated)
		 */
	virtual IFileObject* moveInstance() = 0;

		/**
		 * @brief Get state of IFileObject
		 * @return ResourceState
		 */
	virtual tc::ResourceState state() = 0;

		/**
		 * @brief Close the file
		 */
	virtual void close() = 0;

		/**
		 * @brief Get size of the file
		 * @return file size
		 */
	virtual uint64_t size() = 0;

		/** 
		 * @brief Set the file position
		 * @param[in] offset file position
		 * @post If the offset is beyond the file size, the position will be at the end of file.
		 */
	virtual void seek(uint64_t offset) = 0;

		/** 
		 * @brief Get the file position
		 * @return file position
		 */
	virtual uint64_t pos() = 0;

		/** 
		 * @brief Read data from the file
		 * @param[out] data Pointer to memory where data will be written to
		 * @param[in] len Length of data to read
		 * 
		 * @throws tc::Exception If read length exceeds file capacity
		 */
	virtual void read(byte_t* data, size_t len) = 0;

		/** 
		 * @brief Write data to the file
		 * @param[in] data Pointer to memory where data will be sourced from
		 * @param[in] len Length of data to write
		 */
	virtual void write(const byte_t* data, size_t len) = 0;
};

}}