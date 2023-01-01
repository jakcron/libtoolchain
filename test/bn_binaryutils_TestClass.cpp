#include "bn_binaryutils_TestClass.h"

#include <fmt/format.h>

#include <tc/bn.h>

//---------------------------------------------------------

bn_binaryutils_TestClass::bn_binaryutils_TestClass() :
	mTestTag("tc::bn (BinaryUtils)"),
	mTestResults()
{
}

void bn_binaryutils_TestClass::runAllTests(void)
{
	test_RoundUpFunc();
	test_AlignFunc();
	test_MakeStructMagicU32Func();
	test_MakeStructMagicU64Func();
}

const std::string& bn_binaryutils_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& bn_binaryutils_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void bn_binaryutils_TestClass::test_RoundUpFunc()
{
	TestResult test;
	test.test_name = "test_RoundUpFunc";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		util_RoundUpFuncTestCase(0, 0x200, 0x200);
		util_RoundUpFuncTestCase(1, 0x200, 0x200);
		util_RoundUpFuncTestCase(0x10, 0x200, 0x200);
		util_RoundUpFuncTestCase(0x1FF, 0x200, 0x200);
		util_RoundUpFuncTestCase(0x200, 0x200, 0x400);
		util_RoundUpFuncTestCase(0x201, 0x200, 0x400);
		util_RoundUpFuncTestCase(0x3FF, 0x200, 0x400);
		util_RoundUpFuncTestCase(0xDEADBE00, 0x200, 0xDEADC000);
		util_RoundUpFuncTestCase(0xDEADBEEF, 0x200, 0xDEADC000);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_binaryutils_TestClass::util_RoundUpFuncTestCase(uint32_t value, uint32_t alignment, uint32_t expected_result)
{
	uint32_t result = roundup<uint32_t>(value, alignment);
	if (result != expected_result)
	{
		throw tc::TestException(fmt::format("align(0x{:x}, 0x{:x}) returned: 0x{:x} (expected: 0x{:x})", value, alignment, result, expected_result));
	}
}

void bn_binaryutils_TestClass::test_AlignFunc()
{
	TestResult test;
	test.test_name = "test_AlignFunc";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		util_AlignFuncTestCase(0, 0x200, 0x0);
		util_AlignFuncTestCase(1, 0x200, 0x200);
		util_AlignFuncTestCase(0x10, 0x200, 0x200);
		util_AlignFuncTestCase(0x1FF, 0x200, 0x200);
		util_AlignFuncTestCase(0x200, 0x200, 0x200);
		util_AlignFuncTestCase(0x201, 0x200, 0x400);
		util_AlignFuncTestCase(0x3FF, 0x200, 0x400);
		util_AlignFuncTestCase(0xDEADBE00, 0x200, 0xDEADBE00);
		util_AlignFuncTestCase(0xDEADBEEF, 0x200, 0xDEADC000);

		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_binaryutils_TestClass::util_AlignFuncTestCase(uint32_t value, uint32_t alignment, uint32_t expected_result)
{
	uint32_t result = align<uint32_t>(value, alignment);
	if (result != expected_result)
	{
		throw tc::TestException(fmt::format("align(0x{:x}, 0x{:x}) returned: 0x{:x} (expected: 0x{:x})", value, alignment, result, expected_result));
	}
}

void bn_binaryutils_TestClass::test_MakeStructMagicU32Func()
{
	TestResult test;
	test.test_name = "test_MakeStructMagicU32Func";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		util_MakeStructMagicU32FuncTestCase("BABE", 0x45424142);
		util_MakeStructMagicU32FuncTestCase("NEXT", 0x5458454E);
		util_MakeStructMagicU32FuncTestCase("\x7F""ELF", 0x464C457F);
		util_MakeStructMagicU32FuncTestCase("BIN0", 0x304E4942);
	
		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_binaryutils_TestClass::util_MakeStructMagicU32FuncTestCase(const char* struct_magic_str, uint32_t expected_result)
{
	uint32_t result = tc::bn::make_struct_magic_uint32(struct_magic_str);
	if (result != expected_result)
	{
		throw tc::TestException(fmt::format("make_struct_magic_uint32() returned: 0x{:x} (expected: 0x{:x})", result, expected_result));
	}
}

void bn_binaryutils_TestClass::test_MakeStructMagicU64Func()
{
	TestResult test;
	test.test_name = "test_MakeStructMagicU64Func";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		util_MakeStructMagicU64FuncTestCase("HOMEBREW", 0x57455242454D4F48);
		util_MakeStructMagicU64FuncTestCase("NEXTSPEC", 0x434550535458454E);
		util_MakeStructMagicU64FuncTestCase("EMPTY\0\0\0", 0x0000005954504D45);
	
		// record result
		test.result = "PASS";
		test.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test.result = "FAIL";
		test.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test.result = "UNHANDLED EXCEPTION";
		test.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test));
}

void bn_binaryutils_TestClass::util_MakeStructMagicU64FuncTestCase(const char* struct_magic_str, uint64_t expected_result)
{
	uint64_t result = tc::bn::make_struct_magic_uint64(struct_magic_str);
	if (result != expected_result)
	{
		throw tc::TestException(fmt::format("make_struct_magic_uint64() returned: 0x{:x} (expected: 0x{:x})", result, expected_result));
	}
}