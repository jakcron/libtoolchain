#include <tc/crypto/Md5Generator.h>
const std::array<byte_t, tc::crypto::Md5Generator::kAsn1OidDataSize> tc::crypto::Md5Generator::kAsn1OidData = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05};

#include <tc/crypto/Sha1Generator.h>
const std::array<byte_t, tc::crypto::Sha1Generator::kAsn1OidDataSize> tc::crypto::Sha1Generator::kAsn1OidData = {0x2b, 0x0e, 0x03, 0x02, 0x1a};

#include <tc/crypto/Sha256Generator.h>
const std::array<byte_t, tc::crypto::Sha256Generator::kAsn1OidDataSize> tc::crypto::Sha256Generator::kAsn1OidData = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};

#include <tc/crypto/Sha512Generator.h>
const std::array<byte_t, tc::crypto::Sha512Generator::kAsn1OidDataSize> tc::crypto::Sha512Generator::kAsn1OidData = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03};