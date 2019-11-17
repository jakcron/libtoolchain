#include <tc/json/JsonArray.h>

tc::json::JsonArray::JsonArray()
{
	asArray();
}

tc::json::JsonArray::JsonArray(const tc::json::Value::array_t& val)
{
	asArray() = val;
}

tc::json::JsonArray::JsonArray(tc::json::Value::array_t&& val)
{
	asArray() = std::move(val);
}