#include <tc/json/JsonParser.h>
#include "JsonStringUtils.h"

#include <tc/string/transcode.h>
#include <tc/Exception.h>

const std::string tc::json::JsonParser::kClassName = "tc::json::JsonParser";

tc::json::JsonParser::JsonParser() :
	mEventList(),
	mParentEvent(sJsonEvent::kInvalidEvent),
	mCurrentEvent(sJsonEvent::kInvalidEvent),
	mState(ParserState::START),
	mSubState(ParserState::END),
	mGlobalJsonPos(0),
	mGlobalJsonLine(0),
	mGlobalJsonLinePos(0)
{
}

void tc::json::JsonParser::parseString(const std::string& str)
{
	parseString(str.c_str(), str.size());
}

void tc::json::JsonParser::parseString(const char* str, size_t str_len)
{
	// clear this object
	*this = JsonParser();

	// temp variables for decoded unicode char
	char32_t chr;
	size_t chr_read  = 0;

	// main processing loop
	for (size_t i = 0; i < str_len && mState != ParserState::END; i += chr_read)
	{
		decodeUtf8(str, i, str_len, chr_read, chr);

		// Main State Processing
		if (mState == ParserState::START)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect start of JSON Value
			if (isNumberStart(chr))
			{
				mSubState = ParserState::NUM_START;
			}
			else if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
			}
			else if (isBooleanTrueStart(chr) || isBooleanFalseStart(chr))
			{
				mSubState = ParserState::BOOL_START;
			}
			else if (isNullStart(chr))
			{
				mSubState = ParserState::NULL_START;
			}
			else if (isObjectStart(chr))
			{
				mSubState = ParserState::OBJ_START;
			}
			else if (isArrayStart(chr))
			{
				mSubState = ParserState::ARR_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: No JSON was detected.");
			}
		}
		else if (mState == ParserState::OBJ_START)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect end of object
			if (isObjectEnd(chr))
			{
				mSubState = ParserState::OBJ_END;
			}
			// detect start of key
			else if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
				mState = ParserState::OBJ_KEY_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected object member key string or object termination '}'");
			}
		}
		else if (mState == ParserState::OBJ_KEY_END)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect KeyValue Delimiter
			if (isColon(chr))
			{
				mState = ParserState::OBJ_KEYVAL_DELIM_READ;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected object member key/value delimiter ':'");
			}
		}
		else if (mState == ParserState::OBJ_KEYVAL_DELIM_READ)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect start of JSON Value
			if (isNumberStart(chr))
			{
				mSubState = ParserState::NUM_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else if (isBooleanTrueStart(chr) || isBooleanFalseStart(chr))
			{
				mSubState = ParserState::BOOL_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else if (isNullStart(chr))
			{
				mSubState = ParserState::NULL_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else if (isObjectStart(chr))
			{
				mSubState = ParserState::OBJ_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else if (isArrayStart(chr))
			{
				mSubState = ParserState::ARR_START;
				mState = ParserState::OBJ_VAL_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected value to follow object member key/value delimiter ':'");
			}
		}
		else if (mState == ParserState::OBJ_VAL_END)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// convert parent from string key to parent object
			if (mEventList[mParentEvent].type == ValueType::kString)
			{
				mCurrentEvent = mParentEvent;
				mParentEvent = mEventList[mCurrentEvent].parent;
			}
			else
			{
				throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Object member value did not have a string as a parent");
			}

			// detect Object Member Delimiter
			if (isComma(chr))
			{
				mState = ParserState::OBJ_MEMBER_DELIM_READ;
			}
			// detect End of Object
			else if (isObjectEnd(chr))
			{
				mSubState = ParserState::OBJ_END;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Object member was not followed by member delimiter ',' or object termination '}'");
			}
		}
		else if (mState == ParserState::OBJ_MEMBER_DELIM_READ)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect start of key
			if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
				mState = ParserState::OBJ_KEY_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Object member delimiter ',' was not followed by a member key string");
			}
		}
		else if (mState == ParserState::ARR_START)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect end of object
			if (isArrayEnd(chr))
			{
				mSubState = ParserState::ARR_END;
			}
			// detect start of element
			else if (isNumberStart(chr))
			{
				mSubState = ParserState::NUM_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isBooleanTrueStart(chr) || isBooleanFalseStart(chr))
			{
				mSubState = ParserState::BOOL_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isNullStart(chr))
			{
				mSubState = ParserState::NULL_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isObjectStart(chr))
			{
				mSubState = ParserState::OBJ_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isArrayStart(chr))
			{
				mSubState = ParserState::ARR_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Array start was not followed by array termination ']' or a valid element");
			}
		}
		else if (mState == ParserState::ARR_ELEM_END)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect Object Member Delimiter
			if (isComma(chr))
			{
				mState = ParserState::ARR_ELEM_DELIM_READ;
			}
			// detect End of Object
			else if (isArrayEnd(chr))
			{
				mSubState = ParserState::ARR_END;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Array element was not followed by element delimiter ',' or array termination ']'");
			}
		}
		else if (mState == ParserState::ARR_ELEM_DELIM_READ)
		{
			// skip whitespace
			if (isJsonWhitespace(chr))
			{
				if (isNewLine(chr))
				{
					++mGlobalJsonLine;
					mGlobalJsonLinePos = 0;
				}
				continue;
			}

			// detect start of element
			if (isNumberStart(chr))
			{
				mSubState = ParserState::NUM_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isStringStart(chr))
			{
				mSubState = ParserState::STR_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isBooleanTrueStart(chr) || isBooleanFalseStart(chr))
			{
				mSubState = ParserState::BOOL_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isNullStart(chr))
			{
				mSubState = ParserState::NULL_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isObjectStart(chr))
			{
				mSubState = ParserState::OBJ_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else if (isArrayStart(chr))
			{
				mSubState = ParserState::ARR_START;
				mState = ParserState::ARR_ELEM_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Array element delimiter ',' was not followed by an element");
			}
		}
		else
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled mState");
		}

		// SubState Processing
		if (mSubState == ParserState::OBJ_START)
		{
			mParentEvent = addEvent(sJsonEvent(ValueType::kObject, mParentEvent, i, 0));
			mState = ParserState::OBJ_START;
		}
		else if (mSubState == ParserState::ARR_START)
		{
			mParentEvent = addEvent(sJsonEvent(ValueType::kArray, mParentEvent, i, 0));
			mState = ParserState::ARR_START;
		}
		else if (mSubState == ParserState::OBJ_END || mSubState == ParserState::ARR_END)
		{
			mEventList[mParentEvent].str_len = (i + chr_read) - mEventList[mParentEvent].str_pos;

			size_t parent = mEventList[mParentEvent].parent;

			// the current parent event is the origin
			if (parent == sJsonEvent::kInvalidEvent)
			{
				mState = ParserState::END;
			}
			// if the object parent is a string, then this was a Object Value, so indicate end of value
			else if (mEventList[parent].type == ValueType::kString)
			{
				mState = ParserState::OBJ_VAL_END;
				mCurrentEvent = mParentEvent;
				mParentEvent = parent;
			}
			else if (mEventList[parent].type == ValueType::kArray)
			{
				mState = ParserState::ARR_ELEM_END;
				mCurrentEvent = mParentEvent;
				mParentEvent = parent;
			}
		}
		else if (mSubState == ParserState::STR_START)
		{
			// parse the string
			mCurrentEvent = processStringSequence(str, i, str_len, mParentEvent);
			
			// save string length
			chr_read = mEventList[mCurrentEvent].str_len;
			
			// if this is the start of an object member key, make the string the parent
			if (mState == ParserState::OBJ_KEY_START)
			{
				mParentEvent = mCurrentEvent;
				mCurrentEvent = sJsonEvent::kInvalidEvent;

				mState = ParserState::OBJ_KEY_END;
			}
			// if this came from the root of the JSON, then the end of the JSON is here
			else if (mState == ParserState::START)
			{
				mState = ParserState::END;
			}
			// if this was from the value of an object member, indicate the end of the member
			else if (mState == ParserState::OBJ_VAL_START)
			{
				mState = ParserState::OBJ_VAL_END;
			}
			// if this was from an array, indicate the end of the element
			else if (mState == ParserState::ARR_ELEM_START)
			{
				mState = ParserState::ARR_ELEM_END;
			}
		}
		else if (mSubState == ParserState::NUM_START)
		{
			// parse number string
			mCurrentEvent = processNumberSequence(str, i, str_len, mParentEvent);

			// save string length
			chr_read = mEventList[mCurrentEvent].str_len;

			// if this came from the root of the JSON, then the end of the JSON is here
			if (mState == ParserState::START)
			{
				mState = ParserState::END;
			}
			// if this was from the value of an object member, indicate the end of the member
			else if (mState == ParserState::OBJ_VAL_START)
			{
				mState = ParserState::OBJ_VAL_END;
			}
			// if this was from an array, indicate the end of the element
			else if (mState == ParserState::ARR_ELEM_START)
			{
				mState = ParserState::ARR_ELEM_END;
			}
		}
		else if (mSubState == ParserState::BOOL_START)
		{
			// parse bool string
			mCurrentEvent = processBooleanSequence(str, i, str_len, mParentEvent);

			// save string length
			chr_read = mEventList[mCurrentEvent].str_len;

			// if this came from the root of the JSON, then the end of the JSON is here
			if (mState == ParserState::START)
			{
				mState = ParserState::END;
			}
			// if this was from the value of an object member, indicate the end of the member
			else if (mState == ParserState::OBJ_VAL_START)
			{
				mState = ParserState::OBJ_VAL_END;
			}
			// if this was from an array, indicate the end of the element
			else if (mState == ParserState::ARR_ELEM_START)
			{
				mState = ParserState::ARR_ELEM_END;
			}
		}
		else if (mSubState == ParserState::NULL_START)
		{
			// process null string
			mCurrentEvent = processNullSequence(str, i, str_len, mParentEvent);

			// save string length
			chr_read = mEventList[mCurrentEvent].str_len;

			// if this came from the root of the JSON, then the end of the JSON is here
			if (mState == ParserState::START)
			{
				mState = ParserState::END;
			}
			// if this was from the value of an object member, indicate the end of the member
			else if (mState == ParserState::OBJ_VAL_START)
			{
				mState = ParserState::OBJ_VAL_END;
			}
			// if this was from an array, indicate the end of the element
			else if (mState == ParserState::ARR_ELEM_START)
			{
				mState = ParserState::ARR_ELEM_END;
			}
		}
		else if (mSubState != ParserState::END)
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled mSubState");
		}

		// clear substate
		mSubState = ParserState::END;
	}

	if (mState != ParserState::END)
	{
		throw tc::Exception();
	}
}

size_t tc::json::JsonParser::getEventNum() const
{
	return mEventList.size();
}

const tc::json::sJsonEvent& tc::json::JsonParser::getEvent(size_t index) const
{
	return mEventList.at(index);
}

void tc::json::JsonParser::decodeUtf8(const char* str, size_t pos, size_t str_len, size_t& str_read, char32_t& chr)
{
	try {
		tc::string::transcodeUTF8CharToUTF32Char(str + pos, str_len, str_read, chr);
	}
	catch (const tc::Exception& e) {
		throw tc::Exception(kClassName, "Failed to transcode UTF8 sequence starting at offset " + std::to_string(pos) + ". Reason: " + e.error());
	}
}

size_t tc::json::JsonParser::addEvent(sJsonEvent&& event)
{
	size_t new_event, parent, prev_sibling;

	// add event
	mEventList.push_back(std::move(event));

	// get event index
	new_event = mEventList.size() - 1;

	// get parent of new event
	parent = mEventList[new_event].parent;

	// only modify if the parent is valid
	if (parent != sJsonEvent::kInvalidEvent)
	{
		// parent has no children
		if (mEventList[parent].child_front == sJsonEvent::kInvalidEvent)
		{
			mEventList[parent].child_front = new_event;
			mEventList[parent].child_back = new_event;
		}
		// parent already has children
		else
		{
			// save previous sibling
			prev_sibling = mEventList[parent].child_back;
			
			// update prev_sibling.sibling to point to newest sibling
			mEventList[prev_sibling].sibling = new_event;

			// update child_back in parent
			mEventList[parent].child_back = new_event;
		}
	}

	return new_event;
}

size_t tc::json::JsonParser::processStringSequence(const char* str, size_t pos, size_t str_len, size_t parent_index)
{
	// temp variables for decoded unicode char
	char32_t chr;
	size_t chr_read = 0, read_len = 0;

	// main processing loop
	ParserState state = ParserState::STR_START;
	for (size_t i = pos; i < str_len && state != ParserState::STR_END; i += chr_read)
	{
		decodeUtf8(str, i, str_len, chr_read, chr);

		if (state == ParserState::STR_START)
		{
			if (isStringStart(chr))
			{
				state = ParserState::STR_OPEN_QUOTE_READ;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected open quote ('\"')");
			}
		}
		else if (state == ParserState::STR_OPEN_QUOTE_READ \
			|| state == ParserState::STR_LITERAL_CHAR \
			|| state == ParserState::STR_SINGLECHR_ESC \
			|| state == ParserState::STR_UNICODE_CHAR3)
		{
			if (isStringEnd(chr))
			{
				// if this is the last character in the string, we don't need to check if the character after this is valid
				if (i + chr_read == str_len)
				{
					read_len = i + chr_read - pos;
					state = ParserState::STR_END;
				}
				else
				{
					state = ParserState::STR_CLOSE_QUOTE_READ;
				}
			}
			else if (isValidStringChr(chr))
			{
				state = ParserState::STR_LITERAL_CHAR;
			}
			else if (isValidStringEscapeChrMarker(chr))
			{
				state = ParserState::STR_ESC_START;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected close quote ('\"'), or legal string characters");
			}
		}
		else if (state == ParserState::STR_ESC_START)
		{
			if (isValidStringEscapedChr(chr))
			{
				state = ParserState::STR_SINGLECHR_ESC;
			}
			else if (isValidStringEscapedUnicodeChrStart(chr))
			{
				state = ParserState::STR_UNICODE_ESC;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected escaped characters");
			}
		}
		else if (state == ParserState::STR_UNICODE_ESC)
		{
			if (isValidHexChr(chr))
			{
				state = ParserState::STR_UNICODE_CHAR0;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected 4 hexadecimal characters to follow \\u");
			}
		}
		else if (state == ParserState::STR_UNICODE_CHAR0)
		{
			if (isValidHexChr(chr))
			{
				state = ParserState::STR_UNICODE_CHAR1;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected 4 hexadecimal characters to follow \\u");
			}
		}
		else if (state == ParserState::STR_UNICODE_CHAR1)
		{
			if (isValidHexChr(chr))
			{
				state = ParserState::STR_UNICODE_CHAR2;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected 4 hexadecimal characters to follow \\u");
			}
		}
		else if (state == ParserState::STR_UNICODE_CHAR2)
		{
			if (isValidHexChr(chr))
			{
				state = ParserState::STR_UNICODE_CHAR3;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected 4 hexadecimal characters to follow \\u");
			}
		}
		else if (state == ParserState::STR_CLOSE_QUOTE_READ)
		{
			// test if the after char is a valid end char (end object, end array, member/element delimiter, whitespace)
			if (isValidPostValue(chr))
			{
				read_len = i - pos;
				state = ParserState::STR_END;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected string to end after end quote");
			}
		}
		else
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled ParserState");
		}
	}

	// catch if parsing didn't finish
	if (state != ParserState::STR_END)
	{
		throw tc::Exception(kClassName, "Error processing JSON. Reason: Source string was not long enough");
	}

	size_t event_index = addEvent(sJsonEvent(ValueType::kString, parent_index, pos, read_len));

	// if the string is more than open and close quotes, specifed the unquoted parameters
	if (read_len > 2)
	{
		mEventList[event_index].str_unquoted_pos = mEventList[event_index].str_pos + 1;
		mEventList[event_index].str_unquoted_len = read_len - 2;
	}
	// otherwise set the unquoted parameters to size 0
	else
	{
		mEventList[event_index].str_unquoted_pos = mEventList[event_index].str_pos + 1;
		mEventList[event_index].str_unquoted_len = 0;
	}
	

	return event_index;
}

size_t tc::json::JsonParser::processNumberSequence(const char* str, size_t pos, size_t str_len, size_t parent_index)
{
	size_t dec_sign_pos = std::string::npos;
	size_t dec_pos = std::string::npos;
	size_t dec_len = std::string::npos;
	size_t frac_pos = std::string::npos;
	size_t frac_len = std::string::npos;
	size_t exp_sign_pos = std::string::npos;
	size_t exp_pos = std::string::npos;
	size_t exp_len = std::string::npos;

	// temp variables for decoded unicode char
	char32_t chr;
	size_t chr_read = 0, read_len = 0;

	// main processing loop
	ParserState state = ParserState::NUM_START;
	for (size_t i = pos; i < str_len && state != ParserState::NUM_END; i += chr_read)
	{
		decodeUtf8(str, i, str_len, chr_read, chr);

		if (state == ParserState::NUM_START)
		{
			if (isValidZero(chr))
			{
				state = ParserState::NUM_INT_START_ZERO;
				dec_pos = i - pos;
			}
			else if (isValidNeg(chr))
			{
				state = ParserState::NUM_INT_START_NEG;
				dec_sign_pos = i - pos;
			}
			else if (isValidOneNine(chr))
			{
				state = ParserState::NUM_INT_NUM;
				dec_pos = i - pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Expected [-]0-9");
			}
		}
		else if (state == ParserState::NUM_INT_START_ZERO)
		{	
			if (isValidFracStart(chr))
			{
				state = ParserState::NUM_FRA_START;
				dec_len = i - pos - dec_pos;
			}
			else if (isValidExpStart(chr))
			{
				state = ParserState::NUM_EXP_START;
				dec_len = i - pos - dec_pos;
			}
			else if (isValidPostValue(chr))
			{
				state = ParserState::NUM_END;
				read_len = i - pos;
				dec_len = i - pos - dec_pos;
			}
			else if (isValidOneNine(chr))
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Integer component cannot have leading zeros");
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Integer component of 0 was not followed by fraction or exponent or termination");
			}
		}
		else if (state == ParserState::NUM_INT_START_NEG)
		{
			if (isValidOneNine(chr))
			{
				state = ParserState::NUM_INT_NUM;
				dec_pos = i - pos;
			}
			if (isValidZero(chr))
			{
				state = ParserState::NUM_INT_START_ZERO;
				dec_pos = i - pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Minus symbol not followed by a number 1-9");
			}
		}
		else if (state == ParserState::NUM_INT_NUM)
		{
			if (isValidFracStart(chr))
			{
				state = ParserState::NUM_FRA_START;
				dec_len = i - pos - dec_pos;
			}
			else if (isValidExpStart(chr))
			{
				state = ParserState::NUM_EXP_START;
				dec_len = i - pos - dec_pos;
			}
			else if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_INT_NUM;
			}
			else if (isValidPostValue(chr))
			{
				state = ParserState::NUM_END;
				read_len = i - pos;
				dec_len = i - pos - dec_pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Integer component not followed by fraction or exponent or terminated");
			}
		}
		else if (state == ParserState::NUM_FRA_START)
		{
			if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_FRA_NUM;
				frac_pos = i - pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Fraction delimiter '.' was not followed by digits");
			}
		}
		else if (state == ParserState::NUM_FRA_NUM)
		{
			if (isValidExpStart(chr))
			{
				state = ParserState::NUM_EXP_START;
				frac_len = i - pos - frac_pos;
			}
			else if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_FRA_NUM;
			}
			else if (isValidPostValue(chr))
			{
				state = ParserState::NUM_END;
				read_len = i - pos;
				frac_len = i - pos - frac_pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Fraction component not followed by exponent or terminated");
			}
		}
		else if (state == ParserState::NUM_EXP_START)
		{
			if (isValidPosNeg(chr))
			{
				state = ParserState::NUM_EXP_SIGN;
				exp_sign_pos = i - pos;
			}
			else if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_EXP_NUM;
				exp_pos = i - pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Exponent delimiter 'e'|'E' was not followed by a sign character or digits");
			}
		}
		else if (state == ParserState::NUM_EXP_SIGN)
		{
			if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_EXP_NUM;
				exp_pos = i - pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Exponent component sign character was not followed by digits");
			}
		}
		else if (state == ParserState::NUM_EXP_NUM)
		{
			if (isValidZeroNine(chr))
			{
				state = ParserState::NUM_EXP_NUM;			
			}
			else if (isValidPostValue(chr))
			{
				state = ParserState::NUM_END;
				read_len = i - pos;
				exp_len = i - pos - exp_pos;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Exponent component digits not followed by digits or terminated");
			}
		}
		else
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled ParserState");
		}

		// detect valid end of number when the source string ends (i.e. ends on a digit)
		if (state != ParserState::NUM_END && (i + chr_read == str_len))
		{
			if (state == ParserState::NUM_INT_NUM || state == ParserState::NUM_INT_START_ZERO)
			{
				state = ParserState::NUM_END;
				read_len = i + chr_read - pos;
				dec_len = i + chr_read - pos - dec_pos;
			}
			else if (state == ParserState::NUM_FRA_NUM)
			{
				state = ParserState::NUM_END;
				read_len = i + chr_read - pos;
				frac_len = i + chr_read - pos - frac_pos;
			}
			else if (state == ParserState::NUM_EXP_NUM)
			{
				state = ParserState::NUM_END;
				read_len = i + chr_read - pos;
				exp_len = i + chr_read - pos - exp_pos;
			}
			// other states are in-complete.
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i+chr_read) + ". Reason: Number not terminated properly");
			}
		}
	}

	// catch if parsing didn't finish
	if (state != ParserState::NUM_END)
	{
		throw tc::Exception(kClassName, "Error processing JSON. Reason: Source string was not long enough");
	}

	size_t event_index = addEvent(sJsonEvent(ValueType::kNumber, parent_index, pos, read_len));

	mEventList[event_index].dec_sign_pos = dec_sign_pos;
	mEventList[event_index].dec_pos = dec_pos;
	mEventList[event_index].dec_len = dec_len;
	mEventList[event_index].frac_pos = frac_pos;
	mEventList[event_index].frac_len = frac_len;
	mEventList[event_index].exp_sign_pos = exp_sign_pos;
	mEventList[event_index].exp_pos = exp_pos;
	mEventList[event_index].exp_len = exp_len;	

	return event_index;
}

size_t tc::json::JsonParser::processBooleanSequence(const char* str, size_t pos, size_t str_len, size_t parent_index)
{
	bool bool_value = false;

	// temp variables for decoded unicode char
	char32_t chr;
	size_t chr_read = 0, read_len = 0;

	// main processing loop
	ParserState state = ParserState::BOOL_START;
	for (size_t i = pos; i < str_len && state != ParserState::BOOL_END; i += chr_read)
	{
		decodeUtf8(str, i, str_len, chr_read, chr);

		if (state == ParserState::BOOL_START)
		{
			// detect start of true
			if (chr == 't')
			{
				state = ParserState::BOOL_TRUE_T;
			}
			// detect start of false
			else if (chr == 'f')
			{
				state = ParserState::BOOL_FALSE_F;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_TRUE_T)
		{
			if (chr == 'r')
			{
				state = ParserState::BOOL_TRUE_R;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_TRUE_R)
		{
			if (chr == 'u')
			{
				state = ParserState::BOOL_TRUE_U;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_TRUE_U)
		{
			if (chr == 'e')
			{
				// if this is the last character in the string, we don't need to check if the character after this is valid
				if (i + chr_read == str_len)
				{
					read_len = i + chr_read - pos;
					bool_value = true;
					state = ParserState::BOOL_END;
				}
				else
				{
					state = ParserState::BOOL_TRUE_E;
				}
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_FALSE_F)
		{
			if (chr == 'a')
			{
				state = ParserState::BOOL_FALSE_A;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_FALSE_A)
		{
			if (chr == 'l')
			{
				state = ParserState::BOOL_FALSE_L;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_FALSE_L)
		{
			if (chr == 's')
			{
				state = ParserState::BOOL_FALSE_S;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_FALSE_S)
		{
			if (chr == 'e')
			{
				// if this is the last character in the string, we don't need to check if the character after this is valid
				if (i + chr_read == str_len)
				{
					read_len = i + chr_read - pos;
					bool_value = false;
					state = ParserState::BOOL_END;
				}
				else
				{
					state = ParserState::BOOL_FALSE_E;
				}
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not \"true\" or \"false\"");
			}
		}
		else if (state == ParserState::BOOL_TRUE_E || state == ParserState::BOOL_FALSE_E)
		{
			// test if the after char is a valid end char (end object, end array, member/element delimiter, whitespace)
			if (isValidPostValue(chr))
			{
				read_len = i - pos;
				bool_value = state == ParserState::BOOL_TRUE_E ? true : false;
				state = ParserState::BOOL_END;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Boolean value was not terminated properly");
			}
		}
		else
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled ParserState");
		}
	}

	// catch if parsing didn't finish
	if (state != ParserState::BOOL_END)
	{
		throw tc::Exception(kClassName, "Error processing JSON. Reason: Source string was not long enough");
	}
	
	size_t event_index = addEvent(sJsonEvent(ValueType::kBoolean, parent_index, pos, read_len));

	// configure event struct
	mEventList[event_index].bool_value = bool_value;

	return event_index;
}

size_t tc::json::JsonParser::processNullSequence(const char* str, size_t pos, size_t str_len, size_t parent_index)
{
	// temp variables for decoded unicode char
	char32_t chr;
	size_t chr_read = 0, read_len = 0;

	// main processing loop
	ParserState state = ParserState::NULL_START;
	for (size_t i = pos; i < str_len && state != ParserState::NULL_END; i += chr_read)
	{
		decodeUtf8(str, i, str_len, chr_read, chr);

		if (state == ParserState::NULL_START)
		{
			// detect start of null
			if (chr == 'n')
			{
				state = ParserState::NULL_N;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Null value was not \"null\"");
			}
		}
		else if (state == ParserState::NULL_N)
		{
			if (chr == 'u')
			{
				state = ParserState::NULL_U;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Null value was not \"null\"");
			}
		}
		else if (state == ParserState::NULL_U)
		{
			if (chr == 'l')
			{
				state = ParserState::NULL_L0;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Null value was not \"null\"");
			}
		}
		else if (state == ParserState::NULL_L0)
		{
			if (chr == 'l')
			{
				// if this is the last character in the string, we don't need to check if the character after this is valid
				if (i + chr_read == str_len)
				{
					read_len = i + chr_read - pos;
					state = ParserState::NULL_END;
				}
				else
				{
					state = ParserState::NULL_L1;
				}
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Null value was not \"null\"");
			}
		}
		else if (state == ParserState::NULL_L1)
		{
			if (isValidPostValue(chr))
			{
				read_len = i - pos;
				state = ParserState::NULL_END;
			}
			else
			{
				throw tc::Exception(kClassName, "JSON syntax error at offset " + std::to_string(i) + ". Reason: Null value was not terminated properly");
			}
		}
		else
		{
			throw tc::Exception(kClassName, "Internal logic error processing JSON at offset " + std::to_string(i) + ". Reason: Unhandled ParserState");
		}
	}

	// catch if parsing didn't finish
	if (state != ParserState::NULL_END)
	{
		throw tc::Exception(kClassName, "Error processing JSON. Reason: Source string was not long enough");
	}

	size_t event_index = addEvent(sJsonEvent(ValueType::kNull, parent_index, pos, read_len));

	return event_index;
}