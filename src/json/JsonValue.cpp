#include <tc/json/JsonValue.h>

const std::string tc::json::JsonValue::kClassName = "tc::json::JsonValue";

tc::json::JsonValue::JsonValue()
{
	updateType(tc::json::JSON_NULL);
}

tc::json::JsonType tc::json::JsonValue::type() const
{
	return mType;
}

std::map<std::string, tc::json::GenericJsonValue>& tc::json::JsonValue::asObject()
{
	updateType(tc::json::JSON_OBJECT);
	return mObject;
}

std::vector<tc::json::GenericJsonValue>& tc::json::JsonValue::asArray()
{
	updateType(tc::json::JSON_ARRAY);
	return mArray;
}

std::string& tc::json::JsonValue::asString()
{
	updateType(tc::json::JSON_STRING);
	return mString;
}

tc::json::Number& tc::json::JsonValue::asNumber()
{
	updateType(tc::json::JSON_NUMBER);
	return mNumber;
}

bool& tc::json::JsonValue::asBoolean()
{
	updateType(tc::json::JSON_BOOLEAN);
	return mBoolean;
}


void tc::json::JsonValue::asNull()
{
	updateType(tc::json::JSON_NULL);
}

void tc::json::JsonValue::updateType(tc::json::JsonType type)
{
	if (type != JSON_OBJECT)
	{
		mObject.clear();
	}

	if (type != JSON_ARRAY)
	{
		mArray.clear();
	}

	if (type != JSON_STRING)
	{
		mString.clear();
	}

	if (type != JSON_NUMBER)
	{
		//mNumber.clear();
	}
		
	if (type != JSON_BOOLEAN)
	{
		mBoolean = false;
	}

	// JSON_NULL will clear them all

	mType = type;
}
