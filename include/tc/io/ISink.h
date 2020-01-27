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

		/// Get size of source
	virtual size_t size() = 0;

		/// Get status of source
	virtual tc::ResourceStatus status() = 0;

		/**
		 * @brief Push data to sink
		 * 
		 * @param[in] offset Zero-based offset in sink to push data.
		 **/
	virtual void pushData(const tc::ByteData& x, size_t offset) = 0;
};


}} // namespace tc::io