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
		 * @brief Construct from double
		 * @param[in] num Double
		 * @param[in] fraction_digits Number of decimal places to store
		 */
	Number(double num, size_t fraction_digits);

		/**
		 * @brief Construct from double and exponent
		 * @param[in] num Int & Frac components as a Double
		 * @param[in] fraction_digits Number of decimal places to store
		 * @param[in] exp Exponent
		 */
	Number(double num, size_t fraction_digits, int64_t exp);

		/**
		 * @brief Construct from integer
		 * @param[in] num Integer
		 */
	Number(int64_t num);

		/// Equality Operator
	bool operator==(const tc::json::Number& other) const;

		/**
		 * @brief Get Number as a double
		 * @return double
		 */
	double toDouble() const;

		/**
		 * @brief Get Number as a int64_t
		 * @return int64_t
		 */
	int64_t toInt() const;
};

}} // namespace tc::json