#include <tc/json/NumberUtils.h>
#include <cmath>
#include <cstdlib>

double tc::json::toDouble(const tc::json::Number& num)
{
	double dlb_ret = 0;

	// handle fraction component	
	if (num.f_val != 0)
	{
		size_t f_sig_digits = std::floor(std::log10(num.f_val)) + 1;

		dlb_ret = (double)num.f_val / (double)std::pow(10, num.f_digits);

		// adjust if sig_digits > f_digits
		// 12.3456
		// f_digits = 2
		// f_sig_digits = 4
		// 3456 / 10^(f_digits) = 34.56
		// round(34.56) = 35
		// 35 / 10^(f_sig_digits-f_digits) = 0.35
		if (f_sig_digits > num.f_digits)
		{
			std::round(dlb_ret);
			dlb_ret /= (double)std::pow(10, f_sig_digits - num.f_digits);
		}
	}

	// add integer component
	dlb_ret += (double)num.i_val;

	// handle exponent component
	if (num.e_val != 0)
	{
		if (num.e_pos == true)
		{
			dlb_ret *= (double)std::pow(10, num.e_val);
		}
		else
		{
			dlb_ret /= (double)std::pow(10, num.e_val);
		}
		
	}

	if (num.i_pos == false)
		dlb_ret *= -1;

	return dlb_ret;
}

int64_t tc::json::toInt64(const tc::json::Number& num)
{
	return (int64_t)std::round(toDouble(num));
}