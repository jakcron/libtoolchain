#pragma once

#include <tc/types.h>

namespace tc { namespace crypto {

enum MdTypeId
{
	MD_MD5,
	MD_SHA1,
	MD_SHA2_224,
	MD_SHA2_256,
	MD_SHA2_384,
	MD_SHA2_512
};

}}