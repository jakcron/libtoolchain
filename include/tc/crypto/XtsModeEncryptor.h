	/**
	 * @file XtsModeEncryptor.h
	 * @brief Declaration of tc::crypto::XtsModeEncryptor
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/04/16
	 **/
#pragma once

#include <tc/crypto/IEncryptor.h>
#include <tc/crypto/IIvBasedEncryptor.h>
#include <tc/crypto/CryptoUtil.h>

namespace tc { namespace crypto {

template <class EcbModeCipher>
class XtsModeEncryptor : public IIvBasedEncryptor
{
public:
	XtsModeEncryptor() :
		mSectorSize(kDefaultSectorSize),
		mCryptCipher(),
		mTweakCipher()
	{
		static_assert(std:is_base_of<IEncryptor, EcbModeCipher>, "XtsModeEncryptor can only work with IEncryptor based classes.");
		if (mCryptCipher.block_size() != kRequiredBlockSize) { /* throw exception */ }
	}

	~XtsModeEncryptor()
	{
	}
	
	size_t block_size() const { return kRequiredBlockSize; }
	size_t sector_size() const { return mSectorSize; }
	size_t key_size() const { return mCryptCipher.key_size(); }
	size_t iv_size() const { return kRequiredBlockSize; }

	void initialize(const byte_t* key1, const byte_t* key2, size_t sector_size) 
	{
		if (key1 == nullptr) { /* throw exception */ }
		if (key2 == nullptr) { /* throw exception */ }
		if (sector_size == 0) { /* throw exception */ }
		if (sector_size % this->block_size()) { /* throw exception */ }

		mCryptCipher.initialize(key1);
		mTweakCipher.initialize(key2);
		mSectorSize = sector_size;
	}

	void initialize(const byte_t* key1, const byte_t* key2)
	{
		initialize(key1, key2, kDefaultSectorSize);
	} 

	void encrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (iv == nullptr) { /* throw exception */ }
		if (size == 0 || size % this->sector_size()) { /* throw exception */ }

		auto block = std::array<byte_t, kRequiredBlockSize>();
		auto dec_tweak = std::array<byte_t, kRequiredBlockSize>();
		auto enc_tweak = std::array<byte_t, kRequiredBlockSize>();

		// save tweak (iv)
		memcpy(dec_tweak.data(), iv, dec_tweak.size());

		// iterate through sectors
		for (size_t sector_idx = 0, sector_num = (size / mSectorSize); sector_idx < sector_num; sector_idx++)
		{
			// encrypt tweak
			mTweakCipher.encrypt(enc_tweak.data(), dec_tweak.data(), enc_tweak.size());
			
			// process each block within a sector
			for (size_t block_idx = 0, block_num = (mSectorSize / mCryptCipher.block_size()); block_idx < block_num; block_idx++)
			{
				const byte_t* src_block = src + (sector_idx * this->sector_size()) + (block_idx * mCryptCipher.block_size());
				byte_t* dst_block = dst + (sector_idx * this->sector_size()) + (block_idx * mCryptCipher.block_size());

				// block = src_block XOR enc_tweak
				CryptoUtil::XorBlock128(block.data(), enc_tweak.data(), src_block);

				// encrypt block
				mCryptCipher.encrypt(block.data(), block.data(), block.size());

				// dst_block = enc_block XOR enc_tweak
				CryptoUtil::XorBlock128(dst_block, block.data(), enc_tweak.data());

				// Update encrypted tweak
				CryptoUtil::GaloisFunc128(enc_tweak.data());
			}

			// increment tweak
			CryptoUtil::IncrementCounter128(dec_tweak.data(), 1);
		}
	}

	void decrypt(byte_t* dst, const byte_t* src, size_t size, const byte_t* iv)
	{
		if (dst == nullptr) { /* throw exception */ }
		if (src == nullptr) { /* throw exception */ }
		if (iv == nullptr) { /* throw exception */ }
		if (size == 0 || size % this->sector_size()) { /* throw exception */ }

		auto block = std::array<byte_t, kRequiredBlockSize>();
		auto dec_tweak = std::array<byte_t, kRequiredBlockSize>();
		auto enc_tweak = std::array<byte_t, kRequiredBlockSize>();

		// save tweak (iv)
		memcpy(dec_tweak.data(), iv, dec_tweak.size());

		// iterate through sectors
		for (size_t sector_idx = 0, sector_num = (size / mSectorSize); sector_idx < sector_num; sector_idx++)
		{
			// encrypt tweak
			mTweakCipher.encrypt(enc_tweak.data(), dec_tweak.data(), enc_tweak.size());
			
			// process each block within a sector
			for (size_t block_idx = 0, block_num = (mSectorSize / mCryptCipher.block_size()); block_idx < block_num; block_idx++)
			{
				const byte_t* src_block = src + (sector_idx * this->sector_size()) + (block_idx * mCryptCipher.block_size());
				byte_t* dst_block = dst + (sector_idx * this->sector_size()) + (block_idx * mCryptCipher.block_size());

				// block = src_block XOR enc_tweak
				CryptoUtil::XorBlock128(block.data(), enc_tweak.data(), src_block);

				// decrypt block
				mCryptCipher.decrypt(block.data(), block.data(), block.size());

				// dst_block = dec_block XOR enc_tweak
				CryptoUtil::XorBlock128(dst_block, block.data(), enc_tweak.data());

				// Update encrypted tweak
				CryptoUtil::GaloisFunc128(enc_tweak.data());
			}

			// increment tweak
			CryptoUtil::IncrementCounter128(dec_tweak.data(), 1);
		}
	}
private:
	static const size_t kRequiredBlockSize = 16;
	static const size_t kDefaultSectorSize = 512;
	size_t mSectorSize;
	EcbModeCipher mCryptCipher;
	EcbModeCipher mTweakCipher;
};

}} // namespace tc::crypto