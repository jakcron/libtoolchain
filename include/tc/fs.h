	/**
	 * @file		fs.h
	 * @brief       Declaration of the filesystem library
	 */
#pragma once
#include <tc/types.h>
#include <tc/Exception.h>

	/**
	 * @namespace   tc::fs
	 * @brief       Namespace of the filesystem library
	 */
#include <tc/fs/Path.h>
#include <tc/fs/IFile.h>
#include <tc/fs/IFileSystem.h>
#include <tc/fs/SandboxedFileObject.h>
#include <tc/fs/SandboxedFileSystem.h>
#include <tc/fs/LocalFileSystem.h>
