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
#include <tc/fs/SandboxedIFile.h>
#include <tc/fs/SandboxedIFileSystem.h>
#include <tc/fs/LocalFileSystem.h>
