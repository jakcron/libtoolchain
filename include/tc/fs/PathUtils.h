/**
 * @file PathUtils.h
 * @brief Declaration of utilities related to tc::fs::Path
 * @author Jack (jakcron)
 * @version 0.1
 * @date 2019/06/18
 */
#pragma once
#include <list>
#include <tc/types.h>
#include <tc/fs/Path.h>

namespace tc { namespace fs {

	/**
	 * @brief Format a Path as a Windows style UTF-16 string
	 * @param[in] path Source Path
	 * @param[out] dst Destination UTF-16 string
	 * @note See @ref tc::fs::Path
	 */
void pathToWindowsUTF16(const tc::fs::Path& path, std::u16string& out);

	/**
	 * @brief Format a Path as a Unix/Linux style UTF-8 string
	 * @param[in] path Source Path
	 * @param[out] dst Destination UTF-8 string
	 * @note See @ref tc::fs::Path
	 */
void pathToUnixUTF8(const tc::fs::Path& path, std::string& out);

}} // namespace tc::fs