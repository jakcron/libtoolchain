	/**
	 * @file JsonParser.h
	 * @brief Declaration of tc::json::JsonParser
	 * @author Jack (jakcron)
	 * @version	0.1
	 * @date 2019/10/20
	 */
#pragma once
#include <tc/types.h>
#include <tc/json/ValueType.h>

namespace tc { namespace json {

	/**
	 * @struct sJsonEvent
	 * @brief This describes the location and basic properties of a JSON Value as parsed from a literal JSON string
	 */
struct sJsonEvent
{
	static const size_t kInvalidEvent = -1;

	sJsonEvent() :
		type(tc::json::ValueType::kNull),
		parent(kInvalidEvent),
		sibling(kInvalidEvent),
		child_front(kInvalidEvent),
		child_back(kInvalidEvent),
		str_pos(std::string::npos),
		str_len(0),
		str_unquoted_pos(std::string::npos),
		str_unquoted_len(0),
		dec_sign_pos(std::string::npos),
		dec_pos(std::string::npos),
		dec_len(0),
		frac_pos(std::string::npos),
		frac_len(0),
		exp_sign_pos(std::string::npos),
		exp_pos(std::string::npos),
		exp_len(0),
		bool_value(false)
	{}

	sJsonEvent(ValueType type, size_t parent, size_t str_pos, size_t str_len) :
		sJsonEvent()
	{
		this->type = type;
		this->parent = parent;
		this->str_pos = str_pos;
		this->str_len = str_len;
	}

	// JSON Value Type
	ValueType type;

	// location of relative event entries
	size_t parent;
	size_t sibling;
	size_t child_front;
	size_t child_back;

	// position in source string
	size_t str_pos;
	size_t str_len;

	// string properties
	size_t str_unquoted_pos;
	size_t str_unquoted_len;

	// number properties
	size_t dec_sign_pos;
	size_t dec_pos;
	size_t dec_len;
	size_t frac_pos;
	size_t frac_len;
	size_t exp_sign_pos;
	size_t exp_pos;
	size_t exp_len;

	// boolean properties
	bool bool_value;
};

	/**
	 * @class JsonParser
	 * @brief This parses literal JSON strings and composes an event list that can be navigated to construct the JSON data in memory.
	 **/
class JsonParser
{
public:
		/**
		 * @brief Default constructor
		 **/
	JsonParser();


		/**
		 * @brief Parse literal JSON string
		 * @param[in] str JSON string
		 * @pre The literal string must have no trailing bytes
		 **/
	void parseString(const std::string& str);

		/**
		 * @brief Parse literal JSON string
		 * @param[in] str JSON string
		 * @param[in] str_len JSON string length
		 * @pre The literal string must have no trailing bytes
		 **/
	void parseString(const char* str, size_t str_len);

		/**
		 * @brief Get number of JSON events
		 * @return Number of JSON events
		 **/
	size_t getEventNum() const;
	
		/**
		 * @brief Get JSON Event
		 * @param[in] index Index of event to get
		 * @return Const ref to requested sJsonEvent
		 **/
	const sJsonEvent& getEvent(size_t index) const; 

private:
	static const std::string kClassName;

	enum class ParserState
	{
		// general states
		START,
		END,
		// object states
		OBJ_START, // '{'
		OBJ_KEY_START, // '"'
		OBJ_KEY_END, // '
		OBJ_KEYVAL_DELIM_READ, // ':'
		OBJ_VAL_START, // '"'
		OBJ_VAL_END, // '"'
		OBJ_MEMBER_DELIM_READ, // ','
		OBJ_END, // '}'
		// array states
		ARR_START, // '['
		ARR_ELEM_START,
		ARR_ELEM_END,
		ARR_ELEM_DELIM_READ, // ','
		ARR_END, // ']'
		// string states
		STR_START, // '"'
		STR_OPEN_QUOTE_READ,
		STR_CLOSE_QUOTE_READ,
		STR_LITERAL_CHAR, // see notes on legal literal chars
		STR_ESC_START, // '\' (solidus)
		STR_SINGLECHR_ESC, // {'"', '/', '\', 'b', 'f', 'n', 'r', 't'}
		STR_UNICODE_ESC, // 'u'
		STR_UNICODE_CHAR0, // 0-9,a-f,A-F
		STR_UNICODE_CHAR1, // 0-9,a-f,A-F
		STR_UNICODE_CHAR2, // 0-9,a-f,A-F
		STR_UNICODE_CHAR3, // 0-9,a-f,A-F
		STR_END, // '"'
		// number states
		NUM_START,
		NUM_INT_START, 
		NUM_INT_START_NEG,
		NUM_INT_START_ZERO,
		NUM_INT_NUM,
		NUM_FRA_START,
		NUM_FRA_NUM,
		NUM_EXP_START,
		NUM_EXP_SIGN,
		NUM_EXP_NUM,
		NUM_END,
		// bool states
		BOOL_START,
		BOOL_TRUE_T,
		BOOL_TRUE_R,
		BOOL_TRUE_U,
		BOOL_TRUE_E,
		BOOL_FALSE_F,
		BOOL_FALSE_A,
		BOOL_FALSE_L,
		BOOL_FALSE_S,
		BOOL_FALSE_E,
		BOOL_END,
		// null states
		NULL_START,
		NULL_N,
		NULL_U,
		NULL_L0,
		NULL_L1,
		NULL_END,
	};
	
	std::vector<sJsonEvent> mEventList;

	// Tracks parent event for resuming
	size_t mParentEvent;

	// tracks current event for resuming event
	size_t mCurrentEvent;

	// Track state for resuming
	ParserState mState;
	ParserState mSubState;

	// string position tracking
	/*
	// these are for when streaming is implemented (if ever)
	static const size_t mUtfBufferMax = 4;
	char mUtfBuffer[mUtfBufferMax];
	size_t mUtfBufferLen;
	size_t mCurrentBufferPos;
	*/
	size_t mGlobalJsonPos;
	size_t mGlobalJsonLine;
	size_t mGlobalJsonLinePos;

	void decodeUtf8(const char* str, size_t pos, size_t str_len, size_t& str_read, char32_t& chr);

	size_t addEvent(sJsonEvent&& event);

	/*
	mEventList.push_back(sJsonEvent(ValueType::kBoolean, mParentEvent, i, 0));
	mCurrentEvent = mEventList.size();
	*/
	size_t processStringSequence(const char* str, size_t pos, size_t str_len, size_t parent_index);
	size_t processNumberSequence(const char* str, size_t pos, size_t str_len, size_t parent_index);
	size_t processBooleanSequence(const char* str, size_t pos, size_t str_len, size_t parent_index);
	size_t processNullSequence(const char* str, size_t pos, size_t str_len, size_t parent_index);
};

}} // namespace tc::json