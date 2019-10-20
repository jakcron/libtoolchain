#include "string_transcode_TestClass.h"
#include "endian_TestClass.h"
#include "SharedPtr_TestClass.h"
#include "Optional_TestClass.h"
#include "fs_Path_TestClass.h"
#include "fs_GenericFileObject_TestClass.h"
#include "fs_GenericFileSystem_TestClass.h"
#include "fs_LocalFileSystem_TestClass.h"
#include "fs_PartitionedFileObject_TestClass.h"
#include "fs_SandboxedFileSystem_TestClass.h"
#include "json_JsonParser_TestClass.h"
#include "json_Number_TestClass.h"
#include "json_Value_TestClass.h"

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
	runTest(new fs_GenericFileObject_TestClass());
	runTest(new fs_GenericFileSystem_TestClass());
	runTest(new fs_LocalFileSystem_TestClass());
	runTest(new fs_PartitionedFileObject_TestClass());
	runTest(new fs_SandboxedFileSystem_TestClass());
	runTest(new json_JsonParser_TestClass());
	runTest(new json_Number_TestClass());
	runTest(new json_Value_TestClass());
}