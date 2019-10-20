	/**
	 * @file JsonStringUtils.h
	 * @brief Declaration of utility functions for utf-8 encoded JSON variables
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/10/20
	 */
#pragma once
#include <string>

namespace tc { namespace json {

inline bool isJsonWhitespace(char32_t chr)
{
	return (chr == 0x20 || chr == 0x0d || chr == 0x0a || chr == 0x09);
}

inline bool isNewLine(char32_t chr)
{
	return (chr == 0x0a);
}

inline bool isValidStringChr(char32_t chr)
{
	return (chr >= 0x20 && chr <= 0x10ffff && chr != '\"' && chr != '\\');
}

inline bool isValidStringEscapeChrMarker(char32_t chr)
{
	return (chr == '\\');
}

inline bool isValidStringEscapedChr(char32_t chr)
{
	return (chr == '\"' || chr == '/' || chr == '\\' || chr == 'b' || chr == 'f' || chr == 'n' || chr == 'r' || chr == 't');
}

inline bool isValidStringEscapedUnicodeChrStart(char32_t chr)
{
	return (chr == 'u');
}

inline bool isValidNeg(char32_t chr)
{
	return (chr == '-');
}

inline bool isValidPosNeg(char32_t chr)
{
	return (chr == '+' || chr == '-');
}

inline bool isValidZero(char32_t chr)
{
	return (chr == '0');
}

inline bool isValidZeroNine(char32_t chr)
{
	return (chr >= '0' && chr <= '9');
}

inline bool isValidOneNine(char32_t chr)
{
	return (chr >= '1' && chr <= '9');
}

inline bool isValidHexChr(char32_t chr)
{
	return (isValidZeroNine(chr) || (chr >= 'a' && chr <= 'f') || (chr >= 'A' && chr <= 'F'));
}

inline bool isValidFracStart(char32_t chr)
{
	return (chr == '.');
}

inline bool isValidExpStart(char32_t chr)
{
	return (chr == 'e' || chr == 'E');
}

inline bool isValidPostValue(char32_t chr)
{
	return (chr == '}' || chr == ']' || chr == ',' || chr == ':' || isJsonWhitespace(chr));
}

inline bool isNumberStart(char32_t chr)
{
	return isValidZeroNine(chr) || isValidNeg(chr);
}

inline bool isStringStart(char32_t chr)
{
	return chr == '\"';
}

inline bool isStringEnd(char32_t chr)
{
	return chr == '\"';
}


inline bool isBooleanTrueStart(char32_t chr)
{
	return chr == 't';
}

inline bool isBooleanFalseStart(char32_t chr)
{
	return chr == 'f';
}

inline bool isNullStart(char32_t chr)
{
	return chr == 'n';
}

inline bool isObjectStart(char32_t chr)
{
	return chr == '{';
}

inline bool isObjectEnd(char32_t chr)
{
	return chr == '}';
}


inline bool isArrayStart(char32_t chr)
{
	return chr == '[';
}

inline bool isArrayEnd(char32_t chr)
{
	return chr == ']';
}

inline bool isColon(char32_t chr)
{
	return chr == ':';
}

inline bool isComma(char32_t chr)
{
	return chr == ',';
}

}} // namespace tc::json