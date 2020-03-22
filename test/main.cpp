#include "string_TranscodeUtil_TestClass.h"
#include "ByteData_TestClass.h"
#include "endian_TestClass.h"
#include "Optional_TestClass.h"
#include "io_Path_TestClass.h"
#include "io_LocalStorage_TestClass.h"
#include "io_MemoryStream_TestClass.h"
#include "io_SubStream_TestClass.h"
#include "io_SubStorage_TestClass.h"
#include "io_PaddingSource_TestClass.h"
#include "io_MemorySource_TestClass.h"
#include "io_OverlayedSource_TestClass.h"
#include "io_SubSource_TestClass.h"
#include "io_SubSink_TestClass.h"
#include "io_StreamSource_TestClass.h"
#include "io_StreamSink_TestClass.h"

void runTest(ITestClass* testClass)
{
	testClass->runAllTests();
	delete testClass;
}

int main(int argc, char** argv)
{
	runTest(new string_TranscodeUtil_TestClass());
	runTest(new ByteData_TestClass());
	runTest(new endian_TestClass());
	runTest(new Optional_TestClass());
	runTest(new io_Path_TestClass());
	runTest(new io_LocalStorage_TestClass());
	runTest(new io_MemoryStream_TestClass());
	runTest(new io_SubStream_TestClass());
	runTest(new io_SubStorage_TestClass());
	runTest(new io_PaddingSource_TestClass());
	runTest(new io_MemorySource_TestClass());
	runTest(new io_OverlayedSource_TestClass());
	runTest(new io_SubSource_TestClass());
	runTest(new io_SubSink_TestClass());
	runTest(new io_StreamSource_TestClass());
	runTest(new io_StreamSink_TestClass());
}