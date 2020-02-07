	/**
	 * @file ISource.h
	 * @brief Declaration of tc::io::ISource
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
	 * @class ISource
	 * @brief An interface defining a byte data source.
	 **/
class ISource
{
public:
		/// Destructor
	virtual ~ISource() = default;

		/// Get size of source
	virtual int64_t size() = 0;

		/// Get status of source
	virtual tc::ResourceStatus status() = 0;

		/**
		 * @brief Pull data from source
		 * 
		 * @param[in] offset Zero-based offset in source to pull data.
		 * @param[in] size Length in bytes of data to pull.
		 *
		 * @return ByteData containing data pulled from source
		 **/
	virtual tc::ByteData& pullData(int64_t offset, size_t size) = 0;
};


}} // namespace tc::io