	/**
	 * @file Number.h
	 * @brief Declaration of tc::json::Number
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/10/15
	 */
#pragma once
#include <tc/types.h>

namespace tc { namespace json {

	/**
	 * @struct Number
	 * @brief Wraps a JSON number value.
	 **/
struct Number
{
		/// Integer Value
	uint64_t i_val;

		/// Integer is Positive
	bool i_pos;
	
		/// Fraction Value
	uint64_t f_val;
	
		/// Number of fraction digits
	size_t f_digits;

		/// Exponent Value
	uint64_t e_val;
	
		/// Exponent is Positive
	bool e_pos;

		/**
		 * @brief Default constructor
		 */
	Number();

		/**
		 * @brief Parametized Constructor
		 */
	Number(uint64_t i_val, bool i_pos, uint64_t f_val, size_t f_digits, uint64_t e_val, bool e_pos);

		/**
		 * @brief Construct from integer
		 * @param[in] num Integer
		 */
	Number(int64_t num);

		/// Equality Operator
	bool operator==(const tc::json::Number& other) const;

		/// Inequality Operator
	bool operator!=(const tc::json::Number& other) const;
};

}} // namespace tc::json