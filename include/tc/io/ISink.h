	/**
	 * @file ISink.h
	 * @brief Declaration of tc::io::ISink
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/01/27
	 **/
#pragma once
#include <tc/types.h>
#include <tc/ResourceStatus.h>
#include <tc/ByteData.h>

namespace tc { namespace io {

	/**
	 * @class ISink
	 * @brief An interface defining a byte data sink.
	 **/
class ISink
{
public:
		/// Destructor
	virtual ~ISink() = default;

		/// Get length of sink
	virtual int64_t length() = 0;

		/// Set length of sink
	virtual void setLength(int64_t length) = 0;

		/**
		 * @brief Push data to sink
		 * 
		 * @param[in] data Data to be pushed to the sink.
		 * @param[in] offset Zero-based offset in sink to push data.
		 **/
	virtual void pushData(const tc::ByteData& data, int64_t offset) = 0;
};

}} // namespace tc::io