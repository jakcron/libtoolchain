	/**
	 * @file		io.h
	 * @brief       Declaration of the input/output library
	 */
#pragma once
#include <tc/types.h>
#include <tc/Exception.h>

	/**
	 * @namespace   tc::io
	 * @brief       Namespace of the input/output library
	 */
#include <tc/io/Path.h>
#include <tc/io/PathUtils.h>

#include <tc/io/IFileObject.h>
#include <tc/io/IFileSystem.h>

#include <tc/io/LocalFileObject.h>
#include <tc/io/LocalFileSystem.h>

#include <tc/io/PartitionedFileObject.h>
#include <tc/io/SandboxedFileSystem.h>