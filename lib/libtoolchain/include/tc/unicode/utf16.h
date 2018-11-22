#pragma once
#include <tc/types.h>

namespace tc
{
namespace unicode
{
	static const char32_t kUtf16EncodeMax = 0x10FFFF;
	static const char32_t kUtf16NonNativeStart = 0x10000;
	static const char16_t kUtf16SurrogateBits = 10;
	static const char16_t kUtf16SurrogateMask = (1 << kUtf16SurrogateBits) - 1;
	static const char16_t kUtf16HighSurrogateStart = 0xD800;
	static const char16_t kUtf16HighSurrogateEnd = kUtf16HighSurrogateStart | kUtf16SurrogateMask;
	static const char16_t kUtf16LowSurrogateStart = 0xDC00;
	static const char16_t kUtf16LowSurrogateEnd = kUtf16LowSurrogateStart | kUtf16SurrogateMask;
}
}