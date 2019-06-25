	/**
	 * @file GenericJsonValue.h
	 * @brief Declaration of tc::json::GenericJsonValue
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/06/25
	 */
#pragma once
#include <tc/json/IJsonValue.h>
#include <tc/SharedPtr.h>

namespace tc { namespace json {

	/**
	 * @class GenericJsonValue
	 * @brief A realisation of IJsonValue that can be assigned (copy or move) the value of another IJsonValue object
	 * 
	 * This relies on @ref tc::json::IJsonValue::copyInstance() & @ref tc::json::IJsonValue::moveInstance() 
	 */
class GenericJsonValue : public IJsonValue
{
public:
		/** 
		 * @brief Default constuctor
		 */
	GenericJsonValue();

		/**
		 * @brief Generic Copy Constructor (from IJsonValue)
		 * @param[in] other GenericJsonValue object to copy
		 */
	GenericJsonValue(const tc::json::IJsonValue& other);

		/**
		 * @brief Generic Move Constructor (from IJsonValue)
		 * @param[in] other GenericJsonValue object to move
		 */
	GenericJsonValue(tc::json::IJsonValue&& other);
	
	virtual inline tc::json::IJsonValue* copyInstance() const { return new GenericJsonValue(*this); };
	virtual inline tc::json::IJsonValue* moveInstance() { return new GenericJsonValue(std::move(*this)); };

	virtual tc::json::JsonType type() const;
	virtual std::map<std::string, tc::json::GenericJsonValue>& asObject();
	virtual std::vector<tc::json::GenericJsonValue>& asArray();
	virtual std::string& asString();
	virtual tc::json::Number& asNumber();
	virtual bool& asBoolean();
	virtual void asNull();
private:
	static const std::string kClassName;

	tc::SharedPtr<tc::json::IJsonValue> mPtr;
};

}} // namespace tc::json