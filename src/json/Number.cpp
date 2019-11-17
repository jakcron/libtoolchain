#include <tc/json/Number.h>
#include <cmath>

tc::json::Number::Number() :
	i_val(0),
	i_pos(true),
	f_val(0),
	f_digits(0),
	e_val(0),
	e_pos(true)
{

}

tc::json::Number::Number(double num, size_t fraction_digits) :
	Number()
{
	if (num < 0)
	{
		num *= -1;
		this->i_pos = false;
	}

	// save int val
	this->i_val = (uint64_t)floor(num);

	// save frac val
	double fac = pow(10, fraction_digits);
	this->f_val = (uint64_t)(double)(round(num * fac) - round(floor(num) * fac));
	this->f_digits = fraction_digits;
	
	if ((this->f_val / fac) >= 1.0)
	{
		this->i_val++;
	}
}

tc::json::Number::Number(double num, size_t fraction_digits, int64_t exp) :
	Number(num, fraction_digits)
{
	if (exp < 0)
	{
		exp *= -1;
		this->e_pos = false;
	}

	// save int val
	this->e_val = exp;
}

tc::json::Number::Number(int64_t num) :
	Number()
{
	if (num < 0)
	{
		num *= -1;
		this->i_pos = false;
	}
	
	this->i_val = num;
}

	/// Equality Operator
bool tc::json::Number::operator==(const tc::json::Number& other) const
{
	return 	(this->i_val == other.i_val \
		&&	this->i_pos == other.i_pos \
		&&	this->f_val == other.f_val \
		&&	this->f_digits == other.f_digits \
		&&	this->e_val == other.e_val \
		&&	this->e_pos == other.e_pos);
}

double tc::json::Number::toDouble() const
{
	double dlb_ret = 0;

	// handle fraction component	
	if (this->f_val != 0)
	{
		dlb_ret = (double)this->f_val / (double)pow(10, this->f_digits);
	}

	// add integer component
	dlb_ret += (double)this->i_val;

	// handle exponent component
	if (this->e_val != 0)
	{
		if (this->e_pos == true)
		{
			dlb_ret *= (double)pow(10, this->e_val);
		}
		else
		{
			dlb_ret /= (double)pow(10, this->e_val);
		}
		
	}

	if (this->i_pos == false)
		dlb_ret *= -1;

	return dlb_ret;
}

int64_t tc::json::Number::toInt() const
{
	return (uint64_t)floor(this->toDouble());
}