	/**
	 * @file NumberUtils.h
	 * @brief Declaration of utilities for tc::json::Number
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/11/27
	 */
#pragma once
#include <tc/json/Number.h>

namespace tc { namespace json {

	/**
	 * @brief Get Number as a double
	 * @param[in] num Number struct to be converted to a double
	 * @return double
	 * @throw @ref tc::Exception where conversion fails
	 */
double toDouble(const tc::json::Number& num);

	/**
	 * @brief Get Number as a int64_t
	 * @param[in] num Number struct to be converted to a int64_t
	 * @return int64_t
	 * @throw @ref tc::Exception where conversion fails
	 */
int64_t toInt64(const tc::json::Number& num);


}} // namespace tc::json