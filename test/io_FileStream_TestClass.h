#pragma once
#include "ITestClass.h"

class io_FileStream_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_OpenFileCreate_NotExist();
	void test_OpenFileCreate_DoesExist();
	void test_OpenFileRead_DoesExist();
	void test_OpenFileRead_NotExist();
	void test_OpenFileRead_UnicodePath();
	void test_OpenFileRead_TryWrite();
	void test_OpenFileRead_TryReadBeyondEnd();
	void test_OpenFileEdit_DoesExist();
	void test_OpenFileEdit_NotExist();

	static std::string kAsciiFilePath;
	static std::string kUtf8TestPath;
	static std::string kNotExistFilePath;
	static std::string kTestPhrase;
	static std::string kRandomString;
};