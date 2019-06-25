	/**
	 * @file JsonStringParser.h
	 * @brief Declaration of tc::json::JsonStringParser
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/06/25
	 */
#pragma once
#include <tc/json/JsonValue.h>

namespace tc { namespace json {

	/**
	 * @class JsonStringParser
	 * @brief A specialisation of JsonValue that can parse literal JSON text
	 */
class JsonStringParser : public JsonValue
{
public:
		/** 
		 * @brief Default constuctor
		 */
	JsonStringParser();

		/**
		 * @brief Initialising constructor
		 * @param[in] other JsonStringParser object to copy
		 */
	JsonStringParser(const std::string& json_str);

	void parseString(const std::string& json_str);

private:
	static const std::string kClassName;
};

}} // namespace tc::json