#include <tc/json/JsonString.h>

tc::json::JsonString::JsonString()
{
	asString();
}

tc::json::JsonString::JsonString(const tc::json::Value::string_t& val)
{
	asString() = val;
}

tc::json::JsonString::JsonString(tc::json::Value::string_t&& val)
{
	asString() = std::move(val);
}