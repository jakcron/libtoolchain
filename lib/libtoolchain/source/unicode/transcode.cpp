#include <tc/unicode/transcode.h>
#include <tc/Exception.h>

void tc::unicode::transcodeUtf8ToUnicode(const std::string& src, std::u32string& dst)
{
	size_t done = 0;
	dst.clear();
	for (size_t i = 0; i < src.length(); i += done)
	{
		// get number of leading high bits in first byte
		uint8_t prefix = get_utf8_prefix(src[i]);
		if (prefix == 1 || prefix > 4) // 1 is reserved for trailer bytes
		{
			throw tc::Exception("not a UTF-8 string");
		}

		// if there are no prefix bits, this is ASCII
		if (prefix == 0)
		{
			dst.push_back(src[i]);
			done = 1;
		}
		// otherwise this is a multibyte character
		else
		{
			// there must be enough characters
			if ((i + prefix) > src.length())
			{
				throw tc::Exception("not a UTF-8 string");
			}

			char32_t uni = get_utf8_data(prefix, src[i]);

			for (uint8_t j = 1; j < prefix; j++)
			{
				if (utf8_has_prefix(1, src[i + j]) == false)
				{
					throw tc::Exception("not a UTF-8 string");
				}

				uni <<= 6;
				uni |= get_utf8_data(1, src[i + j]);
			}

			if (uni >= kUtf16HighSurrogateStart && uni <= kUtf16LowSurrogateEnd)
			{
				throw tc::Exception("not a UTF-8 string");
			}
				
			if (uni > kUtf16EncodeMax)
			{
				throw tc::Exception("not a UTF-8 string");
			}
				
			dst.push_back(uni);
			done = prefix;
		}

	}
}

void tc::unicode::transcodeUtf16ToUnicode(const std::u16string& src, std::u32string& dst)
{
	size_t done = 0;
	dst.clear();
	for (size_t i = 0; i < src.length(); i+=done)
	{
		// this isn't a utf16 reserved character, so just add to unicode string
		if (src[i] < kUtf16HighSurrogateStart || src[i] > kUtf16LowSurrogateEnd)
		{
			dst.push_back(src[i]);
			done = 1;
		}
		// otherwise we need to decode it
		else
		{
			// check that the high surrogate char exists first 
			if (src[i] < kUtf16HighSurrogateStart || src[i] > kUtf16HighSurrogateEnd)
			{
				throw tc::Exception("not a UTF-16 string");
			}
			// check that the low surrogate char exists next
			if (i >= src.length() - 1 || src[i + 1] < kUtf16LowSurrogateStart || src[i + 1] > kUtf16LowSurrogateEnd)
			{
				throw tc::Exception("not a UTF-16 string");
			}

			char32_t uni = ((src[i] & kUtf16SurrogateMask) << kUtf16SurrogateBits) | (src[i + 1] & kUtf16SurrogateMask) | 0x10000;

			dst.push_back(uni);
			done = 2;
		}
	}
}

void tc::unicode::transcodeUnicodeToUtf8(const std::u32string& src, std::string& dst)
{
	dst.clear();
	for (size_t i = 0; i < src.length(); i++)
	{
		if (src[i] <= kUtf8AsciiEnd)
		{
			dst.push_back((char)src[i]);
		}
		else if (src[i] <= kUtf82ByteEnd)
		{
			dst.push_back(make_utf8(2, (uint8_t)(src[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 0)));
		}
		else if (src[i] <= kUtf83ByteEnd)
		{
			dst.push_back(make_utf8(3, (uint8_t)(src[i] >> 12)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 0)));
		}
		else if (src[i] <= kUtf84ByteEnd)
		{
			dst.push_back(make_utf8(4, (uint8_t)(src[i] >> 18)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 12)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(src[i] >> 0)));
		}
		else
		{
			throw tc::Exception("not a UTF-16 string");
		}
	}
}

void tc::unicode::transcodeUnicodeToUtf16(const std::u32string& src, std::u16string& dst)
{
	dst.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		char32_t uni = src[i];
		if (uni < kUtf16NonNativeStart)
		{
			dst.push_back((char16_t)uni);
		}
		else
		{
			uni -= kUtf16NonNativeStart;
			dst.push_back(((uni >> kUtf16SurrogateBits) & kUtf16SurrogateMask) + kUtf16HighSurrogateStart);
			dst.push_back((uni & kUtf16SurrogateMask) + kUtf16LowSurrogateStart);
		}
	}
}


void tc::unicode::transcodeUtf8ToUtf16(const std::string& src, std::u16string& dst)
{
	std::u32string unicode;
	transcodeUtf8ToUnicode(src, unicode);
	transcodeUnicodeToUtf16(unicode, dst);
	/*
	size_t done = 0;
	for (size_t i = 0; i < src.length(); i += done)
	{
		// get number of leading high bits in first byte
		uint8_t prefix = get_utf8_prefix(src[i]);
		if (prefix == 1 || prefix > 4) // 1 is reserved for trailer bytes
		{
			throw tc::Exception("not a UTF-8 string");
		}

		// if there are no prefix bits, this is ASCII
		if (prefix == 0)
		{
			unicode.push_back(src[i]);
			done = 1;
		}
		// otherwise this is a multibyte character
		else
		{
			// there must be enough characters
			if ((i + prefix) > src.length())
			{
				throw tc::Exception("not a UTF-8 string");
			}

			char32_t uni = get_utf8_data(prefix, src[i]);

			for (uint8_t j = 1; j < prefix; j++)
			{
				if (utf8_has_prefix(1, src[i + j]) == false)
				{
					throw tc::Exception("not a UTF-8 string");
				}

				uni <<= 6;
				uni |= get_utf8_data(1, src[i + j]);
			}

			if (uni >= kUtf16HighSurrogateStart && uni <= kUtf16LowSurrogateEnd)
			{
				throw tc::Exception("not a UTF-8 string");
			}
				
			if (uni > kUtf16EncodeMax)
			{
				throw tc::Exception("not a UTF-8 string");
			}
				
			unicode.push_back(uni);
			done = prefix;
		}

	}

	dst.clear();
	for (size_t i = 0; i < unicode.size(); i++)
	{
		char32_t uni = unicode[i];
		if (uni < kUtf16NonNativeStart)
		{
			dst.push_back((char16_t)uni);
		}
		else
		{
			uni -= kUtf16NonNativeStart;
			dst.push_back(((uni >> kUtf16SurrogateBits) & kUtf16SurrogateMask) + kUtf16HighSurrogateStart);
			dst.push_back((uni & kUtf16SurrogateMask) + kUtf16LowSurrogateStart);
		}
	}
	*/
}

void tc::unicode::transcodeUtf16ToUtf8(const std::u16string& src, std::string& dst)
{
	std::u32string unicode;
	transcodeUtf16ToUnicode(src, unicode);
	transcodeUnicodeToUtf8(unicode, dst);
	/*
	size_t done = 0;
	for (size_t i = 0; i < src.length(); i+=done)
	{
		// this isn't a utf16 reserved character, so just add to unicode string
		if (src[i] < kUtf16HighSurrogateStart || src[i] > kUtf16LowSurrogateEnd)
		{
			unicode.push_back(src[i]);
			done = 1;
		}
		// otherwise we need to decode it
		else
		{
			// check that the high surrogate char exists first 
			if (src[i] < kUtf16HighSurrogateStart || src[i] > kUtf16HighSurrogateEnd)
			{
				throw tc::Exception("not a UTF-16 string");
			}
			// check that the low surrogate char exists next
			if (i >= src.length() - 1 || src[i + 1] < kUtf16LowSurrogateStart || src[i + 1] > kUtf16LowSurrogateEnd)
			{
				throw tc::Exception("not a UTF-16 string");
			}

			char32_t uni = ((src[i] & kUtf16SurrogateMask) << kUtf16SurrogateBits) | (src[i + 1] & kUtf16SurrogateMask) | 0x10000;

			unicode.push_back(uni);
			done = 2;
		}
	}

	dst.clear();
	for (size_t i = 0; i < unicode.length(); i++)
	{
		if (unicode[i] <= kUtf8AsciiEnd)
		{
			dst.push_back((char)unicode[i]);
		}
		else if (unicode[i] <= kUtf82ByteEnd)
		{
			dst.push_back(make_utf8(2, (uint8_t)(unicode[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 0)));
		}
		else if (unicode[i] <= kUtf83ByteEnd)
		{
			dst.push_back(make_utf8(3, (uint8_t)(unicode[i] >> 12)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 0)));
		}
		else if (unicode[i] <= kUtf84ByteEnd)
		{
			dst.push_back(make_utf8(4, (uint8_t)(unicode[i] >> 18)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 12)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 6)));
			dst.push_back(make_utf8(1, (uint8_t)(unicode[i] >> 0)));
		}
		else
		{
			throw tc::Exception("not a UTF-16 string");
		}
	}
	*/
}