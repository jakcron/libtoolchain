	/**
	 * @file		crypto.h
	 * @brief       Declaration of the cryptography library
	 */
#pragma once
#include <tc/types.h>
#include <tc/Exception.h>

	/**
	 * @namespace   tc::crypto
	 * @brief       Namespace of the cryptography library
	 */
// Exceptions
#include <tc/crypto/CryptoException.h>

// AES Encryption & Modes
#include <tc/crypto/AesEncryptor.h>

#include <tc/crypto/EcbEncryptor.h>
#include <tc/crypto/Aes128EcbEncryptor.h>
#include <tc/crypto/Aes192EcbEncryptor.h>
#include <tc/crypto/Aes256EcbEncryptor.h>

#include <tc/crypto/CtrEncryptor.h>
#include <tc/crypto/Aes128CtrEncryptor.h>
#include <tc/crypto/Aes192CtrEncryptor.h>
#include <tc/crypto/Aes256CtrEncryptor.h>

#include <tc/crypto/CbcEncryptor.h>
#include <tc/crypto/Aes128CbcEncryptor.h>
#include <tc/crypto/Aes192CbcEncryptor.h>
#include <tc/crypto/Aes256CbcEncryptor.h>

#include <tc/crypto/CcmEncryptor.h>
#include <tc/crypto/Aes128CcmEncryptor.h>

#include <tc/crypto/XtsEncryptor.h>
#include <tc/crypto/Aes128XtsEncryptor.h>
#include <tc/crypto/Aes256XtsEncryptor.h>

// AES Encryption Streams
#include <tc/crypto/Aes128CtrEncryptedStream.h>
#include <tc/crypto/Aes128CbcEncryptedStream.h>

// Hash Calculator
#include <tc/crypto/Md5Generator.h>
#include <tc/crypto/Sha1Generator.h>
#include <tc/crypto/Sha2256Generator.h>
#include <tc/crypto/Sha2512Generator.h>

// HMAC Calculator
#include <tc/crypto/HmacGenerator.h>
#include <tc/crypto/HmacMd5Generator.h>
#include <tc/crypto/HmacSha1Generator.h>
#include <tc/crypto/HmacSha2256Generator.h>
#include <tc/crypto/HmacSha2512Generator.h>

// Password-based Key Derivation Function
#include <tc/crypto/Pbkdf1KeyDeriver.h>
#include <tc/crypto/Pbkdf1Md5KeyDeriver.h>
#include <tc/crypto/Pbkdf1Sha1KeyDeriver.h>

#include <tc/crypto/Pbkdf2KeyDeriver.h>
#include <tc/crypto/Pbkdf2Sha1KeyDeriver.h>
#include <tc/crypto/Pbkdf2Sha2256KeyDeriver.h>
#include <tc/crypto/Pbkdf2Sha2512KeyDeriver.h>

// Psuedo-random Byte Generation
#include <tc/crypto/PseudoRandomByteGenerator.h>

// RSA Signing & Encryption
#include <tc/crypto/RsaKey.h>
#include <tc/crypto/RsaKeyGenerator.h>

#include <tc/crypto/RsaPkcs1Signer.h>
#include <tc/crypto/RsaPkcs1Md5Signer.h>
#include <tc/crypto/RsaPkcs1Sha1Signer.h>
#include <tc/crypto/RsaPkcs1Sha2256Signer.h>
#include <tc/crypto/RsaPkcs1Sha2512Signer.h>

#include <tc/crypto/RsaPssSigner.h>
#include <tc/crypto/RsaPssSha2256Signer.h>
#include <tc/crypto/RsaPssSha2512Signer.h>

#include <tc/crypto/RsaOaepEncryptor.h>
#include <tc/crypto/RsaOaepSha2256Encryptor.h>
#include <tc/crypto/RsaOaepSha2512Encryptor.h>