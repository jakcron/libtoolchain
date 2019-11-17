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
#include <tc/json/ValueType.h>
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

		/// Alias for string type
	using string_t = std::string;

		/// Alias for number container type
	using number_t = tc::json::Number;

		/// Alias for boolean type
	using boolean_t = bool;

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
		 * @note See @ref tc::json::ValueType
		 */
	tc::json::ValueType type() const;

		/**
		 * @brief `Cast` this value as a JSON Object.
		 * @return Reference to a @ref tc::json::Value::object_t containing the object members
		 * @post This modifies the JSON value type: type() = ValueType::kObject
		 */
	tc::json::Value::object_t& asObject();

		/**
		 * @brief Get the value from a JSON Object.
		 * @return Reference (const) to a @ref tc::json::Value::object_t containing the object members
		 * @pre type() == ValueType::kObject
		 */
	const tc::json::Value::object_t& asObject() const;

		/**
		 * @brief `Cast` this value as a JSON Array.
		 * @return Reference to a @ref tc::json::Value::array_t containing the array elements
		 * @post This modifies the JSON value type: type() = ValueType::kArray
		 */
	tc::json::Value::array_t& asArray();

		/**
		 * @brief Get the value from a JSON Array.
		 * @return Reference (const) to a @ref tc::json::Value::array_t containing the array elements
		 * @pre type() == ValueType::kArray
		 */
	const tc::json::Value::array_t& asArray() const;

		/**
		 * @brief `Cast` this value as a JSON String.
		 * @return Reference to a @ref tc::json::Value::string_t containing the JSON string value
		 * @post This modifies the JSON value type: type() = ValueType::kString
		 */
	tc::json::Value::string_t& asString();

		/**
		 * @brief Get the value from a JSON String.
		 * @return Reference (const) to a @ref tc::json::Value::string_t containing the JSON string value
		 * @pre type() == ValueType::kString
		 */
	const tc::json::Value::string_t& asString() const;

		/**
		 * @brief `Cast` this value as a JSON Number.
		 * @return Reference to a @ref tc::json::Value::number_t containing the JSON number value
		 * @post This modifies the JSON value type: type() = ValueType::kNumber
		 */
	tc::json::Value::number_t& asNumber();

		/**
		 * @brief Get the value from a JSON Number.
		 * @return Reference (const) to a @ref tc::json::Value::number_t containing the JSON number value
		 * @pre type() == ValueType::kNumber
		 */
	const tc::json::Value::number_t& asNumber() const;

		/**
		 * @brief `Cast` this value as a JSON Boolean.
		 * @return Reference to a @ref tc::json::Value::boolean_t containing the JSON boolean value
		 * @post This modifies the JSON value type: type() = ValueType::kBoolean
		 */
	tc::json::Value::boolean_t& asBoolean();

		/**
		 * @brief Get the value from a JSON Boolean.
		 * @return Reference (const) to a @ref tc::json::Value::boolean_t containing the JSON boolean value
		 * @pre type() == ValueType::kBoolean
		 */
	const tc::json::Value::boolean_t& asBoolean() const;

		/**
		 * @brief `Cast` this value as a null JSON value.
		 * @post This modifies the JSON value type: type() == kNull
		 * @post Calling asNull() will clear data stored as other JSON value types
		 */
	void asNull();

private:
	static const std::string kClassName;

	tc::json::ValueType mType;
	object_t mObject;
	array_t mArray;
	string_t mString;
	number_t mNumber;
	boolean_t mBoolean;

	void parseJson(tc::json::Value& val, const std::string& literal_json, const tc::json::JsonParser& p, size_t event_index);

	void castAsType(tc::json::ValueType type);
};

}} // namespace tc::json