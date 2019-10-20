#include <tc/json/Value.h>

const std::string tc::json::Value::kClassName = "tc::json::Value";

tc::json::Value::Value() :
	mType(tc::json::JsonType::JSON_NULL),
	mObject(),
	mArray(),
	mString(),
	mNumber(),
	mBoolean(false)
{

}

tc::json::Value::Value(const std::string& str) :
	Value()
{
	// parse literal JSON
	JsonParser p;
	p.parseString(str);

	// parseJson
	parseJson(*this, str, p, 0);
}

bool tc::json::Value::operator==(const tc::json::Value& other) const
{
	bool isEqual = false;

	if (mType == other.mType)
	{
		if (mType == JsonType::JSON_OBJECT)
		{
			isEqual = mObject == other.mObject;
		}
		else if (mType == JsonType::JSON_ARRAY)
		{
			isEqual = mArray == other.mArray;
		}
		else if (mType == JsonType::JSON_STRING)
		{
			isEqual = mString == other.mString;
		}
		else if (mType == JsonType::JSON_NUMBER)
		{
			isEqual = mNumber == other.mNumber;
		}	
		else if (mType == JsonType::JSON_BOOLEAN)
		{
			isEqual = mBoolean == other.mBoolean;
		}
		else if (mType == JsonType::JSON_NULL)
		{
			return true;
		}
	}
	
	return isEqual;
}

tc::json::JsonType tc::json::Value::type() const
{
	return mType;
}

tc::json::Value::object_t& tc::json::Value::asObject()
{
	castAsType(tc::json::JsonType::JSON_OBJECT);
	return mObject;
}

const tc::json::Value::object_t& tc::json::Value::asObject() const
{
	return mObject;
}

tc::json::Value::array_t& tc::json::Value::asArray()
{
	castAsType(tc::json::JsonType::JSON_ARRAY);
	return mArray;
}

const tc::json::Value::array_t& tc::json::Value::asArray() const
{
	return mArray;
}

std::string& tc::json::Value::asString()
{
	castAsType(tc::json::JsonType::JSON_STRING);
	return mString;
}

const std::string& tc::json::Value::asString() const
{
	return mString;
}

tc::json::Number& tc::json::Value::asNumber()
{
	castAsType(tc::json::JsonType::JSON_NUMBER);
	return mNumber;
}

const tc::json::Number& tc::json::Value::asNumber() const
{
	return mNumber;
}

bool& tc::json::Value::asBoolean()
{
	castAsType(tc::json::JsonType::JSON_BOOLEAN);
	return mBoolean;
}

bool tc::json::Value::asBoolean() const
{
	return mBoolean;
}

void tc::json::Value::asNull()
{
	castAsType(tc::json::JsonType::JSON_NULL);
}

void tc::json::Value::parseJson(tc::json::Value& json, const std::string& literal_json, const tc::json::JsonParser& p, size_t event_index)
{
	if (p.getEvent(event_index).type == JsonType::JSON_NULL)
	{
		json.asNull();
	}
	else if (p.getEvent(event_index).type == JsonType::JSON_BOOLEAN)
	{
		json.asBoolean() = p.getEvent(event_index).bool_value;
	}
	else if (p.getEvent(event_index).type == JsonType::JSON_STRING)
	{
		json.asString() = literal_json.substr(p.getEvent(event_index).str_unquoted_pos, p.getEvent(event_index).str_unquoted_len);
	}
	else if (p.getEvent(event_index).type == JsonType::JSON_NUMBER)
	{
		// get decimal section
		bool isPosDec = true;
		std::string dec;
		std::string frac;
		bool isPosExp = true;
		std::string exp;
		if (p.getEvent(event_index).dec_pos != std::string::npos)
		{
			dec = literal_json.substr(p.getEvent(event_index).str_pos + p.getEvent(event_index).dec_pos, p.getEvent(event_index).dec_len);
			if (p.getEvent(event_index).dec_sign_pos != std::string::npos)
				isPosDec = false;
		}
		if (p.getEvent(event_index).frac_pos != std::string::npos)
		{
			frac = literal_json.substr(p.getEvent(event_index).str_pos + p.getEvent(event_index).frac_pos, p.getEvent(event_index).frac_len);
		}
		if (p.getEvent(event_index).exp_pos != std::string::npos)
		{
			exp = literal_json.substr(p.getEvent(event_index).str_pos + p.getEvent(event_index).exp_pos, p.getEvent(event_index).exp_len);
			if (p.getEvent(event_index).exp_sign_pos != std::string::npos)
				isPosExp = literal_json[p.getEvent(event_index).exp_sign_pos] == '+';
		}

		tc::json::Number& num = json.asNumber();
		num.i_val = strtoumax(dec.c_str(), nullptr, 10);
		num.i_pos = isPosDec;
		num.f_val = strtoumax(frac.c_str(), nullptr, 10);
		num.f_digits = frac.size();
		num.e_val = strtoumax(exp.c_str(), nullptr, 10);
		num.e_pos = isPosExp;
	}
	else if (p.getEvent(event_index).type == JsonType::JSON_ARRAY)
	{
		json.asNull();
		json.asArray();
		tc::json::Value val;

		
		if (p.getEvent(event_index).child_front != sJsonEvent::kInvalidEvent)
		{
			for (size_t i = p.getEvent(event_index).child_front; i != sJsonEvent::kInvalidEvent; i = p.getEvent(i).sibling) 
			{
				parseJson(val, literal_json, p, i);
				json.asArray().push_back(val);
			}
		}
		
	}
	
	else if (p.getEvent(event_index).type == JsonType::JSON_OBJECT)
	{
		json.asNull();
		json.asObject();
		std::string key;
		tc::json::Value val;
		
		if (p.getEvent(event_index).child_front != sJsonEvent::kInvalidEvent)
		{
			for (size_t key_idx = p.getEvent(event_index).child_front, val_idx = sJsonEvent::kInvalidEvent; key_idx != sJsonEvent::kInvalidEvent; key_idx = p.getEvent(key_idx).sibling) 
			{
				key = literal_json.substr(p.getEvent(key_idx).str_unquoted_pos, p.getEvent(key_idx).str_unquoted_len);

				// get val_idx from key_idx child
				val_idx = p.getEvent(key_idx).child_front;
				if (val_idx == sJsonEvent::kInvalidEvent)
					break;

				// parse JSON
				parseJson(val, literal_json, p, val_idx);

				// add JSON to parent
				json.asObject().insert(std::pair<std::string,tc::json::Value>(key,val));
			}
		}
	}
}

void tc::json::Value::castAsType(tc::json::JsonType type)
{
	if (mType != type)
	{
		if (mType == JsonType::JSON_OBJECT)
		{
			mObject.clear();
		}

		if (mType == JsonType::JSON_ARRAY)
		{
			mArray.clear();
		}

		if (mType == JsonType::JSON_STRING)
		{
			mString.clear();
		}

		if (mType == JsonType::JSON_NUMBER)
		{
			mNumber = tc::json::Number();
		}
			
		if (mType == JsonType::JSON_BOOLEAN)
		{
			mBoolean = false;
		}

		mType = type;
	}
}