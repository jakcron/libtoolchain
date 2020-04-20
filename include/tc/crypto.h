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
#include <tc/crypto/IEncryptor.h>
#include <tc/crypto/Aes128Encryptor.h>

#include <tc/crypto/IIvBasedEncryptor.h>
#include <tc/crypto/Aes128CtrEncryptor.h>
#include <tc/crypto/Aes128CbcEncryptor.h>
#include <tc/crypto/Aes128XtsEncryptor.h>

#include <tc/crypto/IMacBasedEncryptor.h>
#include <tc/crypto/Aes128CcmEncryptor.h>
#include <tc/crypto/Aes128GcmEncryptor.h>

#include <tc/crypto/IHashGenerator.h>
#include <tc/crypto/Md5Generator.h>
#include <tc/crypto/Sha1Generator.h>
#include <tc/crypto/Sha256Generator.h>
#include <tc/crypto/Sha512Generator.h>

#include <tc/crypto/IMacGenerator.h>
#include <tc/crypto/detail/HmacGenerator.h>
#include <tc/crypto/HmacMd5Generator.h>
#include <tc/crypto/HmacSha1Generator.h>
#include <tc/crypto/HmacSha256Generator.h>
#include <tc/crypto/HmacSha512Generator.h>

