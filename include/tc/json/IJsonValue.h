	/**
	 * @file IJsonValue.h
	 * @brief Declaration of tc::json::IJsonValue
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/06/24
	 */
#pragma once
#include <tc/types.h>
#include <tc/json/Number.h>
#include <tc/json/GenericJsonValue.h>
#include <string>
#include <map>
#include <vector>

namespace tc { namespace json {

	/**
	 * @enum JsonType
	 * @brief JSON Value Types
	 */
enum JsonType
{
	JSON_STRING,
	JSON_NUMBER,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_BOOLEAN,
	JSON_NULL
};

	/**
	 * @class IJsonValue
	 * @brief Interface for implementing a JSON value
	 */
class IJsonValue
{
public:
		/**
		 * @brief Destructor
		 */
	virtual ~IJsonValue() = default;

		/**
		 * @brief Create a new instance of this object as a copy. This allows this instance to be copied even when the type isn't known.
		 * This is required by @ref tc::json::GenericJsonValue
		 * @return new instance of IJsonValue (dynamically allocated)
		 */
	virtual IJsonValue* copyInstance() const = 0;

		/**
		 * @brief Create a new instance of this object and move elements to the new instance. This allows this instance to be moved even when the type isn't known.
		 * This is required by @ref tc::json::GenericJsonValue
		 * @return new instance of IJsonValue (dynamically allocated)
		 */
	virtual IJsonValue* moveInstance() = 0;

	virtual JsonType type() const = 0;

	virtual std::map<std::string, tc::json::GenericJsonValue>& asObject() = 0;
	virtual std::vector<tc::json::GenericJsonValue>& asArray() = 0;
	virtual std::string& asString() = 0;
	virtual tc::json::Number& asNumber() = 0;
	virtual bool& asBoolean() = 0;
	virtual void asNull() = 0;
};

}} // namespace tc::json

