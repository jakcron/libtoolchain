#include <tc/json/GenericJsonValue.h>

#include <tc/Exception.h>

const std::string tc::json::GenericJsonValue::kClassName = "tc::json::GenericJsonValue";

tc::json::GenericJsonValue::GenericJsonValue() :
	mPtr(nullptr)
{
}

tc::json::GenericJsonValue::GenericJsonValue(const tc::json::IJsonValue& other) :
	mPtr(other.copyInstance())
{
	// don't allow GenericJsonValue to adopt dead JSON Values
	if (mPtr.isNull() == false || mPtr->type() == JSON_NULL)
	{
		mPtr.release();
	}
}

tc::json::GenericJsonValue::GenericJsonValue(tc::json::IJsonValue&& other) :
	mPtr(other.moveInstance())
{
	// don't allow GenericJsonValue to adopt dead JSON Values
	if (mPtr.isNull() == false || mPtr->type() == JSON_NULL)
	{
		mPtr.release();
	}
}

tc::json::JsonType tc::json::GenericJsonValue::type() const
{
	return mPtr.isNull() ? tc::json::JSON_NULL : mPtr->type();
}

std::map<std::string, tc::json::GenericJsonValue>& tc::json::GenericJsonValue::asObject()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "asObject() called on NullObject");
	}

	return mPtr->asObject();
}

std::vector<tc::json::GenericJsonValue>& tc::json::GenericJsonValue::asArray()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "asArray() called on NullObject");
	}

	return mPtr->asArray();
}

std::string& tc::json::GenericJsonValue::asString()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "asString() called on NullObject");
	}

	return mPtr->asString();
}

tc::json::Number& tc::json::GenericJsonValue::asNumber()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "asNumber() called on NullObject");
	}

	return mPtr->asNumber();
}

bool& tc::json::GenericJsonValue::asBoolean()
{
	if (mPtr.isNull())
	{
		throw tc::Exception(kClassName, "asBoolean() called on NullObject");
	}

	return mPtr->asBoolean();
}

void tc::json::GenericJsonValue::asNull()
{
	if (mPtr.isNull() == false)
	{
		mPtr->asNull();
	}
}