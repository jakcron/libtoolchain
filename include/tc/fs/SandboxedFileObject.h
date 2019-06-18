	/**
	 * @file SandboxedFileObject.h
	 * @brief Declaration of tc::fs::SandboxedFileObject
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2019/06/18
	 */
#pragma once
#include <tc/fs/GenericFileObject.h>
#include <tc/SharedPtr.h>

namespace tc { namespace fs {

	/**
	 * @class SandboxedFileObject
	 * @brief A wrapper around an existing IFileObject object that exposes a carve out (user specified offset & size) of the IFileObject object.
	 */
class SandboxedFileObject : public IFileObject
{
public:
		/**
		 * @brief Default constructor
		 */
	SandboxedFileObject();

		/** 
		 * @brief Wrap (by copy) constuctor
		 * @param[in] file IFileObject object to be sandboxed
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the sandbox file
		 * @param[in] virtual_size Artificial size of the sandbox file
		 * 
		 * @pre The carve out presented by the sandbox should exist in the base file.
		 */
	SandboxedFileObject(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) constuctor
		 * @param[in] file IFileObject object to be sandboxed
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the sandbox file
		 * @param[in] virtual_size Artificial size of the sandbox file
		 * 
		 * @pre The carve out presented by the sandbox should exist in the base file.
		 */
	SandboxedFileObject(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual tc::fs::IFileObject* copyInstance() const;
	virtual tc::fs::IFileObject* moveInstance();

	virtual tc::ResourceState state();

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] file IFileObject object to be sandboxed
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the sandbox file
		 * @param[in] virtual_size Artificial size of the sandbox file
		 * 
		 * @pre The carve out presented by the sandbox should exist in the base file.
		 */
	void initialise(const tc::fs::IFileObject& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] file IFileObject object to be sandboxed
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the sandbox file
		 * @param[in] virtual_size Artificial size of the sandbox file
		 * 
		 * @pre The carve out presented by the sandbox should exist in the base file.
		 */
	void initialise(tc::fs::IFileObject&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual void close();
	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);

private:
	static const std::string kClassName;

	tc::fs::GenericFileObject mFile;
	uint64_t mFileBaseOffset;
	uint64_t mVirtualSize;

	uint64_t mVirtualOffset;
};

}} // namespace tc::fs