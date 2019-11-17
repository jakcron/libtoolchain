	/**
	 * @file JsonNumber.h
	 * @brief Declaration of tc::json::JsonNumber
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/17
	 */
#pragma once
#include <tc/json/Value.h>

namespace tc { namespace json {

	/**
	 * @class JsonNumber
	 * @brief Extends @ref tc::json::Value to construct a Value of type @ref tc::json::ValueType::kNumber
	 */
class JsonNumber : public tc::json::Value
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonNumber();

		/**
		 * @brief Construct by copy
		 * @param[in] val Number object
		 * @note See @ref tc::json::Value::number_t
		 */
	JsonNumber(const tc::json::Value::number_t& val);

		/**
		 * @brief Construct by move
		 * @param[in] val Number object
		 * @note See @ref tc::json::Value::number_t
		 */
	JsonNumber(tc::json::Value::number_t&& val);
private:
	static const std::string kClassName;
};

}} // namespace tc::json