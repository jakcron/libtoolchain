#include <tc/encode/Base64Util.h>

#include <fmt/core.h>

#include <mbedtls/base64.h>

inline std::string byteDataAsString(const tc::ByteData& data)
{
	std::string str = "";
	
	for (size_t i = 0; i < data.size(); i++)
	{
		if ( ! std::isprint(static_cast<unsigned char>(data[i])) )
		{
			break;
		}

		str.push_back(static_cast<char>(data[i]));
	}

	return str;
}

std::string tc::encode::Base64Util::encodeDataAsBase64(const byte_t* data, size_t size)
{
	if (data == nullptr && size != 0)
	{
		return "";
	}

	size_t enc_len = 0;

	mbedtls_base64_encode(nullptr, enc_len, &enc_len, data, size);

	tc::ByteData enc_data = tc::ByteData(enc_len);

	int mbedtls_ret = mbedtls_base64_encode(enc_data.data(), enc_data.size(), &enc_len, data, size);
	if (mbedtls_ret != 0)
		enc_data = tc::ByteData();

	return byteDataAsString(enc_data);
}

std::string tc::encode::Base64Util::encodeDataAsBase64(const tc::ByteData& data)
{
	return encodeDataAsBase64(data.data(), data.size());
}

std::string tc::encode::Base64Util::encodeStringAsBase64(const char* str, size_t size)
{
	return encodeDataAsBase64((const byte_t*)str, size);
}

std::string tc::encode::Base64Util::encodeStringAsBase64(const std::string& str)
{
	return encodeDataAsBase64((const byte_t*)str.c_str(), str.size());
}

tc::ByteData tc::encode::Base64Util::decodeBase64AsData(const char* str, size_t size)
{
	if (str == nullptr && size != 0)
	{
		return tc::ByteData();
	}

	size_t dec_len = 0;

	mbedtls_base64_decode(nullptr, dec_len, &dec_len, (const byte_t*)str, size);

	tc::ByteData dec_data = tc::ByteData(dec_len);

	int mbedtls_ret = mbedtls_base64_decode(dec_data.data(), dec_data.size(), &dec_len, (const byte_t*)str, size);
	if (mbedtls_ret != 0)
		dec_data = tc::ByteData();

	return dec_data;
}

tc::ByteData tc::encode::Base64Util::decodeBase64AsData(const std::string& str)
{
	return decodeBase64AsData(str.c_str(), str.size());
}

std::string tc::encode::Base64Util::decodeBase64AsString(const char* str, size_t size)
{
	return byteDataAsString(decodeBase64AsData(str, size));
}

std::string tc::encode::Base64Util::decodeBase64AsString(const std::string& str)
{
	return byteDataAsString(decodeBase64AsData(str.data(), str.size()));
}