	/**
	 * @file PartitionedFileObject.h
	 * @brief Declaration of tc::fs::PartitionedFileObject
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/19
	 */
#pragma once
#include <tc/fs/IFileObject.h>

namespace tc { namespace fs {

	/**
	 * @class PartitionedFileObject
	 * @brief A wrapper around an existing IFileObject object that exposes are partition (user specified offset & size) of the IFileObject object.
	 */
class PartitionedFileObject : public IFileObject
{
public:
		/**
		 * @brief Default constructor
		 */
	PartitionedFileObject();

		/** 
		 * @brief Wrap (by copy) constuctor
		 * @param[in] file IFileObject object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	PartitionedFileObject(const std::shared_ptr<tc::fs::IFileObject>& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) constuctor
		 * @param[in] file IFileObject object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	PartitionedFileObject(std::shared_ptr<tc::fs::IFileObject>&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual tc::ResourceState state();

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] file IFileObject object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(const std::shared_ptr<tc::fs::IFileObject>& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] file IFileObject object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(std::shared_ptr<tc::fs::IFileObject>&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual void close();
	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);

private:
	static const std::string kClassName;

	std::shared_ptr<tc::fs::IFileObject> mFile;
	uint64_t mFileBaseOffset;
	uint64_t mVirtualSize;

	uint64_t mVirtualOffset;
};

}} // namespace tc::fs