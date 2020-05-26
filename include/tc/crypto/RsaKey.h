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
	static_assert(KeyBitLen == 1024 || KeyBitLen == 2048 || KeyBitLen == 4096, "RsaKey only supports 1024, 2048 and 4096 key bit lengths.");

	static const size_t kKeySize = KeyBitLen / 8;

	std::array<byte_t, kKeySize> n; /*!<  The public modulus. */
	std::array<byte_t, kKeySize / 2> p; /*!<  The first prime factor. */
	std::array<byte_t, kKeySize / 2> q; /*!<  The second prime factor. */
	std::array<byte_t, kKeySize> d;  /*!<  The private exponent. */
	std::array<byte_t, 3> e; /*!<  The public exponent. */

	RsaKey() :
		RsaKey(nullptr, nullptr, nullptr, nullptr, nullptr) 
	{
	}

	RsaKey(const byte_t* n, const byte_t* p, const byte_t* q, const byte_t* d, const byte_t* e)
	{
		if (n != nullptr)
		{
			memcpy(this->n.data(), n, this->n.size());
		}
		else
		{
			memset(this->n.data(), 0, this->n.size());
		}

		if (p != nullptr)
		{
			memcpy(this->p.data(), p, this->p.size());
		}
		else
		{
			memset(this->p.data(), 0, this->p.size());
		}

		if (q != nullptr)
		{
			memcpy(this->q.data(), q, this->q.size());
		}
		else
		{
			memset(this->q.data(), 0, this->q.size());
		}

		if (d != nullptr)
		{
			memcpy(this->d.data(), d, this->d.size());
		}
		else
		{
			memset(this->d.data(), 0, this->d.size());
		}

		if (e != nullptr)
		{
			memcpy(this->e.data(), e, this->e.size());
		}
		else
		{
			memset(this->e.data(), 0, this->e.size());
		}
	}

	~RsaKey()
	{
		memset(p.data(), 0, p.size());
		memset(q.data(), 0, n.size());
		memset(d.data(), 0, d.size());
		memset(n.data(), 0, n.size());
		memset(e.data(), 0, e.size());
	}

	RsaKey<KeyBitLen> getPublicKey() const
	{
		return RsaKey<KeyBitLen>(n.data(), nullptr, nullptr, nullptr, e.data());
	}
};

}} // namespace tc::crypto