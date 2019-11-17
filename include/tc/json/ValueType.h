	/**
	 * @file ValueType.h
	 * @brief Declaration of tc::json::ValueType
	 * @author Jack (jakcron)
	 * @version	0.2
	 * @date 2019/11/17
	 */
#pragma once

namespace tc { namespace json {

	/**
	 * @enum ValueType
	 * @brief JSON Value Types
	 */
enum class ValueType
{
	kString, /**< A sequence of zero or more Unicode characters, wrapped in double quotes, using backslash escapes */
	kNumber, /**< Similar to C double (floating point number) */
	kObject, /**< An unordered set of name/value pairs */
	kArray, /**< An ordered collection of values */
	kBoolean, /**< A boolean state represented by 'true' or 'false' */
	kNull /**< An empty value represented by 'null' */
};

}} // namespace tc::json