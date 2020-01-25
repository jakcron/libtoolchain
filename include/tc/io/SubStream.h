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
		 * 
		 * @note Refer to @ref initialise (by copy) for usage documentation
		 */
	SubStream(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length);

		/** 
		 * @brief Wrap (by move) constuctor
		 * 
		 * @note Refer to @ref initialise (by move) for usage documentation
		 */
	SubStream(std::shared_ptr<tc::io::IStream>&& stream, int64_t offset, int64_t length);

		/** 
		 * @brief Wrap (by copy) initialiser
		 * @param[in] stream The base IStream object which this sub stream will derive from.
		 * @param[in] offset The zero-based byte offset in stream at which to begin the sub stream.
		 * @param[in] length Length of the sub stream.
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(const std::shared_ptr<tc::io::IStream>& stream, int64_t offset, int64_t length);

		/** 
		 * @brief Wrap (by move) initialiser
		 * @param[in] stream The base IStream object which this sub stream will derive from.
		 * @param[in] offset The zero-based byte offset in stream at which to begin the sub stream.
		 * @param[in] length Length of the sub stream.
		 * 
		 * @pre The carve out presented by the partititon should exist in the base file.
		 */
	void initialise(std::shared_ptr<tc::io::IStream>&& stream, int64_t offset, int64_t length);

	virtual bool canRead() const;
	virtual bool canWrite() const;
	virtual bool canSeek() const;
	virtual int64_t length();
	virtual int64_t position();

	virtual size_t read(byte_t* buffer, size_t count);
	virtual void write(const byte_t* buffer, size_t count);
	virtual int64_t seek(int64_t offset, SeekOrigin origin);
	virtual void setLength(int64_t length);
	virtual void flush();
	
	virtual void dispose();
private:
	static const std::string kClassName;

	std::shared_ptr<tc::io::IStream> mBaseStream;
	int64_t mBaseStreamOffset;

	int64_t mSubStreamLength;
	int64_t mSubStreamPosition;

	void validateInitArgsAgainstBaseStream(int64_t offset, int64_t length);
};

}} // namespace tc::io