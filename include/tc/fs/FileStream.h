	/**
	 * @file FileStream.h
	 * @brief Declaration of tc::fs::FileStream
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/05/17
	 */
#pragma once
#include <tc/fs/IFile.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class FileStream
	 * @brief A wrapper around an IFile pointer
	 */
class FileStream : public IFile
{
public:
		/** 
		 * @brief Default constuctor
		 */
	FileStream();

		/**
		 * @brief Copy Constructor
		 * @param[in] other FileStream object to copy
		 */
	FileStream(const tc::fs::FileStream& other);

		/** 
		 * @brief Direct Wrap Constructor
		 * @param[in] file_ptr Pointer to IFile object to be wrapped
		 */
	FileStream(tc::fs::IFile* file_ptr);

		/**
		 * @brief Copy Assignment Operator
		 * @param[in] other FileStream object to copy
		 * 
		 * @return this object
		 */
	FileStream& operator=(const tc::fs::FileStream& other);

	uint64_t size();
	void seek(uint64_t offset);
	uint64_t pos();
	void read(byte_t* data, size_t len);
	void write(const byte_t* data, size_t len);

private:
	const std::string kClassName = "tc::fs::FileStream";

	tc::SharedPtr<tc::fs::IFile> mFile;
};

}} // namespace tc::fs