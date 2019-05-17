	/**
	 * @file FileObject.h
	 * @brief Declaration of tc::fs::FileObject
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/05/17
	 */
#pragma once
#include <tc/fs/IFileObject.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class FileObject
	 * @brief A wrapper around an IFileObject pointer
	 */
class FileObject : public IFileObject
{
public:
		/** 
		 * @brief Default constuctor
		 */
	FileObject();

		/**
		 * @brief Copy Constructor
		 * @param[in] other FileObject object to copy
		 */
	FileObject(const tc::fs::FileObject& other);

		/** 
		 * @brief Direct Wrap Constructor
		 * @param[in] file_ptr Pointer to IFileObject object to be wrapped
		 */
	FileObject(tc::fs::IFileObject* file_ptr);

		/**
		 * @brief Copy Assignment Operator
		 * @param[in] other FileObject object to copy
		 * 
		 * @return this object
		 */
	FileObject& operator=(const tc::fs::FileObject& other);

	uint64_t size();
	void seek(uint64_t offset);
	uint64_t pos();
	void read(byte_t* data, size_t len);
	void write(const byte_t* data, size_t len);

private:
	const std::string kClassName = "tc::fs::FileObject";

	tc::SharedPtr<tc::fs::IFileObject> mFile;
};

}} // namespace tc::fs