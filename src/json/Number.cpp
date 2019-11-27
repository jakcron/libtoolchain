#include <tc/json/Number.h>
#include <tc/Exception.h>

tc::json::Number::Number() :
	i_val(0),
	i_pos(true),
	f_val(0),
	f_digits(0),
	e_val(0),
	e_pos(true)
{
}

tc::json::Number::Number(uint64_t i_val, bool i_pos, uint64_t f_val, size_t f_digits, uint64_t e_val, bool e_pos) :
	i_val(i_val),
	i_pos(i_pos),
	f_val(f_val),
	f_digits(f_digits),
	e_val(e_val),
	e_pos(e_pos)
{
}

tc::json::Number::Number(int64_t num)  :
	i_val(llabs(num)),
	i_pos(num >= 0),
	f_val(0),
	f_digits(0),
	e_val(0),
	e_pos(true)
{
}

bool tc::json::Number::operator==(const tc::json::Number& other) const
{
	return 	(this->i_val == other.i_val \
		&&	this->i_pos == other.i_pos \
		&&	this->f_val == other.f_val \
		&&	this->f_digits == other.f_digits \
		&&	this->e_val == other.e_val \
		&&	this->e_pos == other.e_pos);
}

bool tc::json::Number::operator!=(const tc::json::Number& other) const
{
	return !(*this == other);
}