	/**
	 * @file JsonValue.h
	 * @brief Declaration of tc::json::JsonValue
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/06/25
	 */
#pragma once
#include <tc/json/IJsonValue.h>

namespace tc { namespace json {

	/**
	 * @class JsonValue
	 * @brief A realisation of IJsonValue implements the storage of the JSON data
	 */
class JsonValue : public IJsonValue
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonValue();
	
	virtual inline tc::json::IJsonValue* copyInstance() const { return new JsonValue(*this); };
	virtual inline tc::json::IJsonValue* moveInstance() { return new JsonValue(std::move(*this)); };

	virtual tc::json::JsonType type() const;
	virtual std::map<std::string, tc::json::GenericJsonValue>& asObject();
	virtual std::vector<tc::json::GenericJsonValue>& asArray();
	virtual std::string& asString();
	virtual tc::json::Number& asNumber();
	virtual bool& asBoolean();
	virtual void asNull();
private:
	static const std::string kClassName;

	tc::json::JsonType mType;
	std::map<std::string, tc::json::GenericJsonValue> mObject;
	std::vector<tc::json::GenericJsonValue> mArray;
	std::string mString;
	tc::json::Number mNumber;
	bool mBoolean;

	void updateType(tc::json::JsonType type);
};

}} // namespace tc::json