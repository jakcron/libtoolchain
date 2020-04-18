#include <tc/crypto/CryptoUtil.h>

void tc::crypto::CryptoUtil::XorBlock128(byte_t* dst, const byte_t* src_1, const byte_t* src_2)
{
	for (size_t i = 0; i < 16; i++)
		dst[i] = src_1[i] ^ src_2[i];
}

void tc::crypto::CryptoUtil::GaloisFunc128(byte_t* tweak)
{
	byte_t t = tweak[16-1];

	for (byte_t i = 16-1; i > 0; i--)
	{
		tweak[i] = (tweak[i] << 1) | (tweak[i - 1] & 0x80 ? 1 : 0);
	}

	tweak[0] = (tweak[0] << 1) ^ (t & 0x80 ? 0x87 : 0x00);
}

void tc::crypto::CryptoUtil::IncrementCounter128(byte_t* ctr, size_t incr)
{
	be_uint64_t* ctr_words = (be_uint64_t*)ctr;

	uint64_t carry = incr;
	for (size_t i = 0; carry != 0 ; i = ((i + 1) % 2))
	{
		uint64_t word = ctr_words[1 - i].unwrap();
		uint64_t remaining = std::numeric_limits<uint64_t>::max() - word;

		if (remaining > carry)
		{
			ctr_words[1 - i].wrap(word + carry);
			carry = 0;
		}
		else
		{
			ctr_words[1 - i].wrap(carry - remaining - 1);
			carry = 1;
		}
	}
}

void tc::crypto::CryptoUtil::CreateXtsTweak128(byte_t* tweak, const byte_t* base_tweak, size_t sector_index)
{
	if (base_tweak != nullptr)
		memcpy(tweak, base_tweak, 16);
	else
		memset(tweak, 0, 16);

	IncrementCounter128(tweak, sector_index);
}