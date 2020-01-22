	/**
	 * @file FileAccessMode.h
	 * @brief Declaration of tc::io::FileAccessMode
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/01/22
	 */
#pragma once

namespace tc { namespace io {

	/** 
	 * @enum FileAccessMode
	 * @brief This enum is used with openFile() to determine the access mode
	 */
enum FileAccessMode
{
	FILEACCESS_READ, /**< Access file with READ-ONLY permissions */
	FILEACCESS_EDIT, /**< Access file with READ-WRITE permissions */
	FILEACCESS_CREATE /**< Create a new file or overwrite an existing file (READ-WRITE permissions) */
};

}} // namespace tc::io