#include <tc/json/JsonBoolean.h>

tc::json::JsonBoolean::JsonBoolean()
{
	asBoolean();
}

tc::json::JsonBoolean::JsonBoolean(const tc::json::Value::boolean_t& val)
{
	asBoolean() = val;
}

tc::json::JsonBoolean::JsonBoolean(tc::json::Value::boolean_t&& val)
{
	asBoolean() = std::move(val);
}