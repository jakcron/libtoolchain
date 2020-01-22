	/**
	 * @file		tc.h
	 * @brief       Declaration of the libtoolchain namespace
	 */
#pragma once
#include <tc/types.h>

	/**
	 * @namespace   tc
	 * @brief       Root namespace for libtoolchain
	 */
// classes
#include <tc/Optional.h>

// sub namespaces
#include <tc/string.h>
#include <tc/io.h>

// exceptions
#include <tc/Exception.h>
#include <tc/ArgumentException.h>
#include <tc/NotImplementedException.h>
#include <tc/NotSupportedException.h>
#include <tc/UnauthorisedAccessException.h>