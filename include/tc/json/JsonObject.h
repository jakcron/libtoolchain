	/**
	 * @file JsonObject.h
	 * @brief Declaration of tc::json::JsonObject
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/17
	 */
#pragma once
#include <tc/json/Value.h>

namespace tc { namespace json {

	/**
	 * @class JsonObject
	 * @brief Extends @ref tc::json::Value to construct a Value of type @ref tc::json::ValueType::kObject
	 */
class JsonObject : public tc::json::Value
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonObject();

		/**
		 * @brief Construct by copy
		 * @param[in] val Object object
		 * @note See @ref tc::json::Value::object_t
		 */
	JsonObject(const tc::json::Value::object_t& val);

		/**
		 * @brief Construct by move
		 * @param[in] val Object object
		 * @note See @ref tc::json::Value::object_t
		 */
	JsonObject(tc::json::Value::object_t&& val);
private:
	static const std::string kClassName;
};

}} // namespace tc::json