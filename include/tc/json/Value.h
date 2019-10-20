	/**
	 * @file Value.h
	 * @brief Declaration of tc::json::Value
	 * @author Jack (jakcron)
	 * @version	0.2
	 * @date 2019/10/20
	 */
#pragma once
#include <string>
#include <map>
#include <vector>
#include <tc/json/JsonType.h>
#include <tc/json/JsonParser.h>
#include <tc/json/Number.h>

namespace tc { namespace json {

	/**
	 * @class Value
	 * @brief Wraps any JSON value.
	 */
class Value
{
public:
		/// Alias for object containter type
	using object_t = std::map<std::string, tc::json::Value>;

		/// Alias for array container type
	using array_t = std::vector<tc::json::Value>;

		/** 
		 * @brief Default constuctor
		 */
	Value();

		/**
		 * @brief Construct from literal JSON
		 * @param[in] str Literal JSON string
		 * @pre str must be a valid JSON string
		 */
	Value(const std::string& str);

		/// Equality Operator
	bool operator==(const Value& other) const;

		/**
		 * @brief Get type of JSON value
		 * @return JSON Type
		 * @note See @ref tc::json::JsonType
		 */
	tc::json::JsonType type() const;

		/**
		 * @brief `Cast` this value as a JSON Object.
		 * @return Reference to a @ref tc::json::Value::object_t containing the object members
		 * @post This modifies the JSON value type: type() = JSON_OBJECT
		 */
	tc::json::Value::object_t& asObject();

		/**
		 * @brief Get the value from a JSON Object.
		 * @return Reference (const) to a @ref tc::json::Value::object_t containing the object members
		 * @pre type() == JSON_OBJECT
		 */
	const tc::json::Value::object_t& asObject() const;

		/**
		 * @brief `Cast` this value as a JSON Array.
		 * @return Reference to a @ref tc::json::Value::array_t containing the array elements
		 * @post This modifies the JSON value type: type() = JSON_ARRAY
		 */
	tc::json::Value::array_t& asArray();

		/**
		 * @brief Get the value from a JSON Array.
		 * @return Reference (const) to a @ref tc::json::Value::array_t containing the array elements
		 * @pre type() == JSON_ARRAY
		 */
	const tc::json::Value::array_t& asArray() const;

		/**
		 * @brief `Cast` this value as a JSON String.
		 * @return Reference to a @ref tc::json::String containing the JSON string value
		 * @post This modifies the JSON value type: type() = JSON_STRING
		 */
	std::string& asString();

		/**
		 * @brief Get the value from a JSON String.
		 * @return Reference (const) to a @ref tc::json::String containing the JSON string value
		 * @pre type() == JSON_STRING
		 */
	const std::string& asString() const;

		/**
		 * @brief `Cast` this value as a JSON Number.
		 * @return Reference to a @ref tc::json::Number containing the JSON number value
		 * @post This modifies the JSON value type: type() = JSON_NUMBER
		 */
	tc::json::Number& asNumber();

		/**
		 * @brief Get the value from a JSON Number.
		 * @return Reference (const) to a @ref tc::json::Number containing the JSON number value
		 * @pre type() == JSON_NUMBER
		 */
	const tc::json::Number& asNumber() const;

		/**
		 * @brief `Cast` this value as a JSON Boolean.
		 * @return Reference to a @ref bool containing the JSON boolean value
		 * @post This modifies the JSON value type: type() = JSON_BOOLEAN
		 */
	bool& asBoolean();

		/**
		 * @brief Get the value from a JSON Boolean.
		 * @return Reference (const) to a @ref bool containing the JSON boolean value
		 * @pre type() == JSON_BOOLEAN
		 */
	bool asBoolean() const;

		/**
		 * @brief `Cast` this value as a null JSON value.
		 * @post This modifies the JSON value type: type() == JSON_NULL
		 * @post Calling asNull() will clear data stored as other JSON value types
		 */
	void asNull();

private:
	static const std::string kClassName;

	tc::json::JsonType mType;
	object_t mObject;
	array_t mArray;
	std::string mString;
	tc::json::Number mNumber;
	bool mBoolean;

	void parseJson(tc::json::Value& val, const std::string& literal_json, const tc::json::JsonParser& p, size_t event_index);

	void castAsType(tc::json::JsonType type);
};

}} // namespace tc::json