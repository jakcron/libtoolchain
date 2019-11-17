	/**
	 * @file JsonBoolean.h
	 * @brief Declaration of tc::json::JsonBoolean
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/17
	 */
#pragma once
#include <tc/json/Value.h>

namespace tc { namespace json {

	/**
	 * @class JsonBoolean
	 * @brief Extends @ref tc::json::Value to construct a Value of type @ref tc::json::ValueType::kBoolean
	 */
class JsonBoolean : public tc::json::Value
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonBoolean();

		/**
		 * @brief Construct by copy
		 * @param[in] val Boolean object
		 * @note See @ref tc::json::Value::boolean_t
		 */
	JsonBoolean(const tc::json::Value::boolean_t& val);

		/**
		 * @brief Construct by move
		 * @param[in] val Boolean object
		 * @note See @ref tc::json::Value::boolean_t
		 */
	JsonBoolean(tc::json::Value::boolean_t&& val);
private:
	static const std::string kClassName;
};

}} // namespace tc::json