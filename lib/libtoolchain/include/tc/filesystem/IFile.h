/**
 * \class IFile
 *
 * \ingroup LibToolChain
 *
 * \brief An interface for implementing a basic File handler.
 *
 * Defines expcted functionality required to process/access a file.
 * 
 * The usage of size_t in read()/write() reflects the intention that size_t can represent 
 * sizes relevant to the run-time of a program. Whereas the usage of uint64_t in size()/seek()/pos() 
 * reflects the realty that files exist independent of the operating system which 
 * the programs run under. To that end it is important to accept this and preserve the 
 * true sizes of the files, while also working with-in the limitations of the operating system
 * by using size_t where memory is processed.
 * 
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/11/10
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/types.h>

namespace tc
{
namespace filesystem
{
	class IFile
	{
	public:
		virtual ~IFile() = default;

		/** \brief Get size of the file
		 *  \return uint64_t size of the file
		 */
		virtual uint64_t size() = 0;

		/** \brief Move the file position
		 *  \param offset uint64_t new file position
		 * 
		 *  If the offset is beyond the file size, the position will be at the end of file.
		 */
		virtual void seek(uint64_t offset) = 0;

		/** \brief Get the position within the file
		 *  \return uint64_t current postion within the file
		 */
		virtual uint64_t pos() = 0;

		/** \brief Read data from the file
		 *  \param data byte_t* Pointer to memory where data will be written to
		 *  \param len size_t Length of data to read
		 * 
		 *  If the length of data exceeds the capacity of the file, an exception will be thrown
		 */
		virtual void read(byte_t* data, size_t len) = 0;

		/** \brief Write data to the file
		 *  \param data const byte_t* Pointer to memory where data will be sourced from
		 *  \param len size_t Length of data to write
		 */
		virtual void write(const byte_t* data, size_t len) = 0;
	};
}
}