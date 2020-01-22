	/**
	 * @file SubStream.h
	 * @brief Declaration of tc::io::SubStream
	 * @author Jack (jakcron)
	 * @version 0.3
	 * @date 2019/06/19
	 */
#pragma once
#include <tc/io/IStream.h>

namespace tc { namespace io {

	/**
	 * @class SubStream
	 * @brief A wrapper around an existing IStream object that exposes a subset of the base the IStream object.
	 */
class SubStream : public IStream
{
public:
		/**
		 * @brief Default constructor
		 */
	SubStream();

		/** 
		 * @brief Wrap (by copy) constuctor
		 * @param[in] file IStream object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	SubStream(const std::shared_ptr<tc::io::IStream>& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) constuctor
		 * @param[in] file IStream object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	SubStream(std::shared_ptr<tc::io::IStream>&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual tc::ResourceStatus state();

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] file IStream object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(const std::shared_ptr<tc::io::IStream>& file, uint64_t file_base_offset, uint64_t virtual_size);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] file IStream object to be partitioned
		 * @param[in] file_base_offset Offset in the base file that serves as offset 0 in the partition
		 * @param[in] virtual_size Artificial size of the partition
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(std::shared_ptr<tc::io::IStream>&& file, uint64_t file_base_offset, uint64_t virtual_size);

	virtual void close();
	virtual uint64_t size();
	virtual void seek(uint64_t offset);
	virtual uint64_t pos();
	virtual void read(byte_t* data, size_t len);
	virtual void write(const byte_t* data, size_t len);

private:
	static const std::string kClassName;

	std::shared_ptr<tc::io::IStream> mFile;
	uint64_t mFileBaseOffset;
	uint64_t mVirtualSize;

	uint64_t mVirtualOffset;
};

}} // namespace tc::io