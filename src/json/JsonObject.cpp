#include <tc/json/JsonObject.h>

tc::json::JsonObject::JsonObject()
{
	asObject();
}

tc::json::JsonObject::JsonObject(const tc::json::Value::object_t& val)
{
	asObject() = val;
}

tc::json::JsonObject::JsonObject(tc::json::Value::object_t&& val)
{
	asObject() = std::move(val);
}