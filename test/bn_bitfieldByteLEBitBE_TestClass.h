#pragma once
#include "ITestClass.h"
#include <tc/types.h>

class bn_bitfieldByteLEBitBE_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void test_Size();
	void test_TestBit();
	void test_SetBit();
	void test_ResetBit();
	void test_FlipBit();

	using testtype_t = tc::bn::bitfield<sizeof(uint32_t), true, false>;

	void helper_TestBit(const std::string& test_name, const testtype_t& bitfield, const std::vector<size_t>& expected_set_bits);
};