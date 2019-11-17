#include <tc/json/JsonNumber.h>

tc::json::JsonNumber::JsonNumber()
{
	asNumber();
}

tc::json::JsonNumber::JsonNumber(const tc::json::Value::number_t& val)
{
	asNumber() = val;
}

tc::json::JsonNumber::JsonNumber(tc::json::Value::number_t&& val)
{
	asNumber() = std::move(val);
}