#include "string_transcode_TestClass.h"
#include "endian_TestClass.h"
#include "Optional_TestClass.h"
#include "io_Path_TestClass.h"
#include "io_LocalFileSystem_TestClass.h"
#include "io_PartitionedFileObject_TestClass.h"
#include "io_SandboxedFileSystem_TestClass.h"

void runTest(ITestClass* testClass)
{
	testClass->runAllTests();
	delete testClass;
}

int main(int argc, char** argv)
{
	runTest(new string_transcode_TestClass());
	runTest(new endian_TestClass());
	runTest(new Optional_TestClass());
	runTest(new io_Path_TestClass());
	runTest(new io_LocalFileSystem_TestClass());
	runTest(new io_PartitionedFileObject_TestClass());
	runTest(new io_SandboxedFileSystem_TestClass());
}