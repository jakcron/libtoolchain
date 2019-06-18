	/**
	 * @file ResourceState.h
	 * @brief Declaration of tc::ResourceState
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/01/16
	 */
#pragma once
#include <bitset>

namespace tc {

	/**
	 * @enum ResourceStateFlag
	 * @brief Flags for ResourceState
	 */
enum ResourceStateFlag
{
	RESFLAG_READY, /**< Resource is ready for use */
	RESFLAG_ERROR, /**< Resource encountered an error */
	RESFLAG_NOINIT, /**< Resource is not initialised */
};

	/**
	 * @brief Bitset indicating resource state information (see @ref ResourceStateFlag)
	 */
using ResourceState = std::bitset<32>; 

} // namespace tc