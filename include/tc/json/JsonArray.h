	/**
	 * @file JsonArray.h
	 * @brief Declaration of tc::json::JsonArray
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/17
	 */
#pragma once
#include <tc/json/Value.h>

namespace tc { namespace json {

	/**
	 * @class JsonArray
	 * @brief Extends @ref tc::json::Value to construct a Value of type @ref tc::json::ValueType::kArray
	 */
class JsonArray : public tc::json::Value
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonArray();

		/**
		 * @brief Construct by copy
		 * @param[in] val Array object
		 * @note See @ref tc::json::Value::array_t
		 */
	JsonArray(const tc::json::Value::array_t& val);

		/**
		 * @brief Construct by move
		 * @param[in] val Array object
		 * @note See @ref tc::json::Value::array_t
		 */
	JsonArray(tc::json::Value::array_t&& val);
private:
	static const std::string kClassName;
};

}} // namespace tc::json