#include <tc/json/JsonSerialiser.h>
#include <sstream>
#include <iomanip>

const std::string tc::json::JsonSerialiser::kClassName = "tc::json::JsonSerialiser";

tc::json::JsonSerialiser::JsonSerialiser(const tc::json::Value& json, bool use_newline) :
    mUseNewline(use_newline),
    mString()
{
    std::stringstream sstream;

    emitJson(sstream, json, 0);

    mString = sstream.str();
}

const std::string& tc::json::JsonSerialiser::getString() const
{
    return mString;
}

void tc::json::JsonSerialiser::emitJson(std::ostream& stream, const tc::json::Value& json, size_t indent) const
{
    if (json.type() == tc::json::JsonType::JSON_NUMBER)
	{
		stream << (json.asNumber().i_pos ? "" : "-") << std::dec << json.asNumber().i_val;
		if (json.asNumber().f_digits > 0)
			stream << "." << std::dec << std::setw(json.asNumber().f_digits) << std::setfill('0') << json.asNumber().f_val;
		if (json.asNumber().e_val)
			stream << "e" << (json.asNumber().e_pos ? "" : "-") << std::dec << json.asNumber().e_val;
	}
	if (json.type() == tc::json::JsonType::JSON_BOOLEAN)
	{
		stream << (json.asBoolean() ? "true" : "false");
	}
	if (json.type() == tc::json::JsonType::JSON_NULL)
	{
		stream << "null";
	}
	if (json.type() == tc::json::JsonType::JSON_STRING)
	{
		stream << "\"" << json.asString() << "\""; 
	}
	if (json.type() == tc::json::JsonType::JSON_ARRAY)
	{
		stream << "[";
		if (json.asArray().size() > 0)
		{
			stream << std::endl;
			for (tc::json::Value::array_t::const_iterator itr = json.asArray().begin(); itr != json.asArray().end(); ++itr)
			{
				if (json.asArray().size() > 1 && itr != json.asArray().begin())
				{
					stream << "," << std::endl;
				}
				
                if (mUseNewline)
                {
                    emitIndent(stream, indent+1);
                }
                
				emitJson(stream, *itr, indent+1);
			}
			
			if (mUseNewline)
            {
                stream << std::endl;
			    emitIndent(stream, indent);
            }
		}
		stream << "]";
	}
	if (json.type() == tc::json::JsonType::JSON_OBJECT)
	{
		stream << "{";
		if (json.asObject().size() > 0)
		{
			stream << std::endl;
			for (tc::json::Value::object_t::const_iterator itr = json.asObject().begin(); itr != json.asObject().end(); ++itr)
			{
				if (json.asObject().size() > 1 && itr != json.asObject().begin())
				{
					stream << "," << std::endl;
				}

                if (mUseNewline)
                {
                    emitIndent(stream, indent+1);
                }
				
				stream << "\"" << (*itr).first << "\"" << ": ";
				emitJson(stream, (*itr).second, indent+1);
			}

            if (mUseNewline)
            {
                stream << std::endl;
			    emitIndent(stream, indent);
            }
		}
		stream << "}"; 
	}
}

void tc::json::JsonSerialiser::emitIndent(std::ostream& stream, size_t indent) const
{
    for (size_t i = 0; i < indent; i++)
	{
		stream << "\t";
	}
}