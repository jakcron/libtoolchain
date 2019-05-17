#include "fs_LocalFileSystem_TestClass.h"
#include "fs_Path_TestClass.h"
#include "fs_SandboxedIFile_TestClass.h"
#include "fs_SandboxedIFileSystem_TestClass.h"
#include "Optional_TestClass.h"
#include "SharedPtr_TestClass.h"
#include "string_transcode_TestClass.h"
#include "endian_TestClass.h"

void runTest(ITestClass* testClass)
{
	testClass->runAllTests();
	delete testClass;
}

int main(int argc, char** argv)
{
	runTest(new string_transcode_TestClass());
	runTest(new endian_TestClass());
	runTest(new SharedPtr_TestClass());
	runTest(new Optional_TestClass());
	runTest(new fs_Path_TestClass());
	runTest(new fs_LocalFileSystem_TestClass());
	runTest(new fs_SandboxedIFile_TestClass());
	runTest(new fs_SandboxedIFileSystem_TestClass());
}