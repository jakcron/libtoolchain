	/**
	 * @file		io.h
	 * @brief       Declaration of the input/output library
	 **/
#pragma once
#include <tc/types.h>
#include <tc/Exception.h>

	/**
	 * @namespace   tc::io
	 * @brief       Namespace of the input/output library
	 **/
#include <tc/io/Path.h>
#include <tc/io/PathUtils.h>

#include <tc/io/IStream.h>
#include <tc/io/IStorage.h>

#include <tc/io/FileStream.h>
#include <tc/io/LocalStorage.h>

#include <tc/io/SubStream.h>
#include <tc/io/SubStorage.h>

// Exceptions
#include <tc/io/IOException.h>
#include <tc/io/DirectoryNotEmptyException.h>
#include <tc/io/DirectoryNotFoundException.h>
#include <tc/io/FileExistsException.h>
#include <tc/io/FileNotFoundException.h>
#include <tc/io/PathTooLongException.h>