	/**
	 * @file JsonSerialiser.h
	 * @brief Declaration of tc::json::JsonSerialiser
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/10/20
	 */
#pragma once
#include <tc/types.h>
#include <tc/json/Value.h>
#include <string>
#include <ostream>

namespace tc { namespace json {

	/**
	 * @class JsonSerialiser
	 * @brief Serialises @ref tc::json::Value to a UTF-8 string
	 **/
class JsonSerialiser
{
public:

		/**
		 * @brief Construct from tc::json::Value by copy
		 * @param[in] json JSON value to be serialised
		 **/ 
    JsonSerialiser(const tc::json::Value& json, bool use_newline = true);

		/**
		 * @brief Construct from tc::json::Value by copy
		 * @return Serialised JSON string
		 **/ 
	const std::string& getString() const;
private:
    static const std::string kClassName;

	bool mUseNewline;
	std::string mString;

	void emitJson(std::ostream& stream, const tc::json::Value& json, size_t indent) const;
	void emitIndent(std::ostream& stream, size_t indent) const;
};

}} // namespace tc::json