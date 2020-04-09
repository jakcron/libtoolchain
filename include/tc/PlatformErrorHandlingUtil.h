	/**
	 * @file PlatformErrorHandlingUtil.h
	 * @brief Declaration of tc::PlatformErrorHandlingUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/09
	 **/
#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

namespace tc
{
	/**
	 * @class PlatformErrorHandlingUtil
	 * @brief Platform specific error handling utilities.
	 **/
class PlatformErrorHandlingUtil
{
public:
#ifdef _WIN32
		/**
		 * @brief Create a string with last error message
		 * 
		 * @param[in] error Error code, returned from GetLastError().
		 * 
		 * @return Error string localised.
		 **/
	static std::string GetLastErrorString(DWORD error)
#endif
};

} // namespace tc