	/**
	 * @file JsonString.h
	 * @brief Declaration of tc::json::JsonString
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/17
	 */
#pragma once
#include <tc/json/Value.h>

namespace tc { namespace json {

	/**
	 * @class JsonString
	 * @brief Extends @ref tc::json::Value to construct a Value of type @ref tc::json::ValueType::kString
	 */
class JsonString : public tc::json::Value
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonString();

		/**
		 * @brief Construct by copy
		 * @param[in] val String object
		 * @note See @ref tc::json::Value::string_t
		 */
	JsonString(const tc::json::Value::string_t& val);

		/**
		 * @brief Construct by move
		 * @param[in] val String object
		 * @note See @ref tc::json::Value::string_t
		 */
	JsonString(tc::json::Value::string_t&& val);
private:
	static const std::string kClassName;
};

}} // namespace tc::json