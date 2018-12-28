/**
 * \class SandboxFile
 *
 * \ingroup LibToolChain
 *
 * \brief A wrapper around an existing IFile object that exposes a carve out (user specified offset & size) of the IFile object.
 *
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/12/18
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/filesystem/IFile.h>
#include <tc/SharedPtr.h>

namespace tc
{
	namespace filesystem
	{
		class SandboxFile : public IFile
		{
		public:
			/** \brief Default constuctor
			 *  \param file_ptr const tc::SharedPtr<tc::filesystem::IFile>& file_ptr Base IFile object pointer
			 *  \param file_base_offset uint64_t Offset in the base file that serves as offset 0 in the sandbox file
			 *  \param virtual_size uint64_t Artificial size of the sandbox file
			 * 
			 * The carve out presented by the sandbox should exist in the base file.
			 */
			SandboxFile(const tc::SharedPtr<tc::filesystem::IFile>& file_ptr, uint64_t file_base_offset, uint64_t virtual_size);

			/** \brief Get size of the file
			 *  \return uint64_t size of the file
			 */
			uint64_t size();

			/** \brief Move the file position
			 *  \param offset uint64_t new file position
			 *
			 *  If the offset is beyond the file size, the position will be at the end of file.
			 */
			void seek(uint64_t offset);

			/** \brief Get the position within the file
			 *  \return uint64_t current postion within the file
			 */
			uint64_t pos();

			/** \brief Read data from the file
			 *  \param data byte_t* Pointer to memory where data will be written to
			 *  \param len size_t Length of data to read
			 *
			 *  If the length of data exceeds the capacity of the file, an exception will be thrown
			 */
			void read(byte_t* data, size_t len);

			/** \brief Write data to the file
			 *  \param data const byte_t* Pointer to memory where data will be sourced from
			 *  \param len size_t Length of data to write
			 */
			void write(const byte_t* data, size_t len);

		private:
			const std::string kClassName = "tc::filesystem::SandboxFile";

			tc::SharedPtr<tc::filesystem::IFile> mFile;
			uint64_t mFileBaseOffset;
			uint64_t mVirtualSize;

			uint64_t mVirtualOffset;
		};
	}
}