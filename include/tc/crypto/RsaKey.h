	/**
	 * @file RsaKey.h
	 * @brief Declaration of tc::crypto::RsaKey
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/19
	 **/
#pragma once

#include <tc/types.h>

namespace tc { namespace crypto {

template <size_t KeyBitLen>
struct RsaKey
{
	static const size_t kKeySize = KeyBitLen / 8;

	std::array<byte_t, kKeySize> n; // modulus
	std::array<byte_t, kKeySize> d; // private exponent

	RsaKey() :
		RsaKey(nullptr, nullptr) 
	{
	}

	RsaKey(const byte_t* modulus, const byte_t* private_exponent)
	{
		if (modulus != nullptr)
		{
			memcpy(this->n.data(), modulus, this->n.size());
		}
		else
		{
			memset(this->n.data(), 0, this->n.size());
		}

		if (private_exponent != nullptr)
		{
			memcpy(this->d.data(), private_exponent, this->d.size());
		}
		else
		{
			memset(this->d.data(), 0, this->d.size());
		}
	}

	~RsaKey()
	{
		memset(n.data(), 0, n.size());
		memset(d.data(), 0, d.size());
	}
};

}} // namespace tc::crypto