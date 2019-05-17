	/**
	 * @file transcode.h
	 * @brief Declaration of functions to transcode between UTF-8/UTF-16/UTF-32
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2018/12/23
	 */
#pragma once
#include <string>

namespace tc { namespace string {

	/**
	 * @brief Transcode a UTF-8 string to UTF-32.
	 * @param[in] src Source UTF-8 string
	 * @param[out] dst Destination UTF-32 string
	 * 
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF8ToUTF32(const std::string& src, std::u32string& dst);

	/**
	 * @brief Transcode a UTF-16 string to UTF-32.
	 * @param[in] src Source UTF-16 string
	 * @param[out] dst Destination UTF-32 string
	 *
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF16ToUTF32(const std::u16string& src, std::u32string& dst);

	/**
	 * @brief Transcode a UTF-32 string to UTF-8.
	 * @param[in] src Source UTF-32 string
	 * @param[out] dst Destination UTF-8 string
	 * 
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF32ToUTF8(const std::u32string& src, std::string& dst);

	/**
	 * @brief Transcode a UTF-32 string to UTF-16.
	 * @param[in] src Source UTF-32 string
	 * @param[out] dst Destination UTF-16 string
	 * 
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF32ToUTF16(const std::u32string& src, std::u16string& dst);

	/**
	 * @brief Transcode a UTF-8 string to UTF-16.
	 * @param[in] src Source UTF-8 string
	 * @param[out] dst Destination UTF-16 string
	 * 
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF8ToUTF16(const std::string& src, std::u16string& dst);

	/**
	 * @brief Transcode a UTF-16 string to UTF-8.
	 * @param[in] src Source UTF-16 string
	 * @param[out] dst Destination UTF-8 string
	 * 
	 * @throws tc::Exception When src is an invalid string
	 */
void transcodeUTF16ToUTF8(const std::u16string& src, std::string& dst);

}} // namespace tc::string