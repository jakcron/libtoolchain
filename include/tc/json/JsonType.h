	/**
	 * @file JsonType.h
	 * @brief Declaration of tc::json::JsonType
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/06/25
	 */
#pragma once

namespace tc { namespace json {

	/**
	 * @enum JsonType
	 * @brief JSON Value Types
	 */
enum class JsonType
{
	JSON_STRING, /**< A sequence of zero or more Unicode characters, wrapped in double quotes, using backslash escapes */
	JSON_NUMBER, /**< Similar to C double (floating point number) */
	JSON_OBJECT, /**< An unordered set of name/value pairs */
	JSON_ARRAY, /**< An ordered collection of values */
	JSON_BOOLEAN, /**< A boolean state represented by 'true' or 'false' */
	JSON_NULL /**< An empty value represented by 'null' */
};

}} // namespace tc::json