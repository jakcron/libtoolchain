	/**
	 * @file Environment.h
	 * @brief Declarations for API resources for accessing run-time environment
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2025/08/05
	 **/
#pragma once
#include <tc/types.h>
#include <tc/ByteData.h>
#include <tc/io/Path.h>

#include <tc/io/DirectoryNotFoundException.h>

namespace tc { namespace os {

	/**
	 * @brief Get environment variable.
	 * 
	 * @details This function supports UTF-8 encoding
	 * 
	 * @param[in] name Name of environment variable.
	 * @param[out] value Reference to string to populate with variable.
	 *
	 * @post @p value will contain the environment variable if it exists.
	 * 
	 * @return true if operation was successful.
	 */
bool getEnvVar(const std::string& name, std::string& value);

	/**
	 * @brief Get OS defined temporary directory path.
	 * 
	 * @details This function returns the temporary directory path, that can be used for storing files during run-time of the application.
	 * 
	 * @param[out] dir_path Refence to path object to populate with temporary directory path.
	 * 
	 * @post @p dir_path will contain the temporary directory path.
	 * 
	 * @throws tc::io::DirectoryNotFoundException Temporary directory could not be determined.
	 */
void getTempDirPath(tc::io::Path& dir_path);

}} // namespace tc::cli