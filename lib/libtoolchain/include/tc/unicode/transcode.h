#pragma once
#include <tc/unicode/utf8.h>
#include <tc/unicode/utf16.h>

namespace tc
{
namespace unicode
{
	void transcodeUtf8ToUnicode(const std::string& src, std::u32string& dst);
	void transcodeUtf16ToUnicode(const std::u16string& src, std::u32string& dst);

	void transcodeUnicodeToUtf8(const std::u32string& src, std::string& dst);
	void transcodeUnicodeToUtf16(const std::u32string& src, std::u16string& dst);

	void transcodeUtf8ToUtf16(const std::string& src, std::u16string& dst);
	void transcodeUtf16ToUtf8(const std::u16string& src, std::string& dst);
}
}