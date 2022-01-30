#pragma once
#include "ITestClass.h"

#include <tc/crypto.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotImplementedException.h>

class crypto_Aes128CbcEncryptedStream_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
};