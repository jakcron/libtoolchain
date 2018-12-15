/**
 * \class LocalFile
 *
 * \ingroup LibToolChain
 *
 * \brief An implementation of IFile as a wrapper to local OS file access functions.
 * 
 * \author Jack (jakcron)
 * \version 0.1
 * \date 2018/11/10
 *
 * Contact: jakcron.dev@gmail.com
 *
 */
#pragma once
#include <tc/filesystem/LocalFileSystem.h>

namespace tc
{
namespace filesystem
{
	class LocalFile : public IFile
	{
	public:
		LocalFile(FileAccessMode mode, LocalFileSystem::fs_handle_t file_handle);
		~LocalFile();

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
		const std::string kClassName = "tc::filesystem::LocalFile";

		FileAccessMode mMode;
		LocalFileSystem::fs_handle_t mFileHandle;
	};
}
}