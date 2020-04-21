	/**
	 * @file MbedtlsErrorUtil.h
	 * @brief Declaration of tc::crypto::mbedtls_detail::MbedtlsErrorUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/21
	 **/
#pragma once

#include <tc/types.h>

namespace tc { namespace crypto { namespace mbedtls_detail {

class MbedtlsErrorUtil
{
public:
	static std::string GetRsaErrorAsString(int error_code);
};

}}} // namespace tc::crypto::mbedtls_detail