/**
 * @file transcode.h
 * @brief Declaration of functions to transcode between UTF-8/UTF-16/UTF-32
 * @author Jack (jakcron)
 * @version 0.1
 * @date 2018/12/23
 */
#pragma once
#include <tc/utf/spec/utf8.h>
#include <tc/utf/spec/utf16.h>

namespace tc { namespace utf {

	void transcodeUTF8ToUTF32(const std::string& src, std::u32string& dst);
	void transcodeUTF16ToUTF32(const std::u16string& src, std::u32string& dst);

	void transcodeUTF32ToUTF8(const std::u32string& src, std::string& dst);
	void transcodeUTF32ToUTF16(const std::u32string& src, std::u16string& dst);

	void transcodeUTF8ToUTF16(const std::string& src, std::u16string& dst);
	void transcodeUTF16ToUTF8(const std::u16string& src, std::string& dst);

}} // namespace tc::utf