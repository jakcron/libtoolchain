#include "string_transcode_TestClass.h"
#include "ByteData_TestClass.h"
#include "endian_TestClass.h"
#include "Optional_TestClass.h"
#include "io_Path_TestClass.h"
#include "io_LocalStorage_TestClass.h"
#include "io_SubStream_TestClass.h"
#include "io_SubStorage_TestClass.h"

void runTest(ITestClass* testClass)
{
	testClass->runAllTests();
	delete testClass;
}

int main(int argc, char** argv)
{
	runTest(new string_transcode_TestClass());
	runTest(new ByteData_TestClass());
	runTest(new endian_TestClass());
	runTest(new Optional_TestClass());
	runTest(new io_Path_TestClass());
	runTest(new io_LocalStorage_TestClass());
	runTest(new io_SubStream_TestClass());
	runTest(new io_SubStorage_TestClass());
}