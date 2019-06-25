#include <tc/json/JsonStringParser.h>

tc::json::JsonStringParser::JsonStringParser() :
	JsonValue()
{
}

tc::json::JsonStringParser::JsonStringParser(const std::string& json_str) :
	JsonStringParser()
{
	parseString(json_str);
}

void tc::json::JsonStringParser::parseString(const std::string& json_str)
{
	
}