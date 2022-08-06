#include "ByteData_TestClass.h"

#include <fmt/format.h>

#include <tc/ByteData.h>

//---------------------------------------------------------

ByteData_TestClass::ByteData_TestClass() :
	mTestTag("tc::ByteData"),
	mTestResults()
{
}

void ByteData_TestClass::runAllTests(void)
{
	test_Constructor_DefaultConstructor();
	test_Constructor_InitializerList();
	test_Constructor_CreateZeroSized();
	test_Constructor_CreateSmallSized();
	test_Constructor_CreateLargeSized();
	test_Constructor_ThrowExceptForBadAlloc();
	test_Constructor_CreateFromPtr();
	test_ImplicitCopy_CopyInSameScope();
	test_ImplicitCopy_CopyOntoInitiallisedByteData();
	test_ImplicitMove_CopyInSameScope();
	test_ImplicitMove_MoveOntoInitiallisedByteData();
	test_EqualityOperator();
	test_InequalityOperator();
}

const std::string& ByteData_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& ByteData_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void ByteData_TestClass::test_Constructor_DefaultConstructor()
{
	TestResult test;
	test.test_name = "test_Constructor_DefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try 
	{
		tc::ByteData data;

		if (data.data() != nullptr)
		{
			throw tc::TestException(".data() did not return nullptr when ByteData was constructed with default constructor");
		}

		if (data.size() != 0)
		{
			throw tc::TestException(".size() did not return 0 when ByteData was constructed with default constructor");
		}

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

void ByteData_TestClass::test_Constructor_CreateZeroSized()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateZeroSized";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::ByteData data(0);

		if (data.data() != nullptr)
		{
			throw tc::TestException(".data() did not return nullptr when ByteData was constructed with size 0");
		}

		if (data.size() != 0)
		{
			throw tc::TestException(".size() did not return 0 when ByteData was constructed with size 0");
		}

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

void ByteData_TestClass::test_Constructor_InitializerList()
{
	TestResult test;
	test.test_name = "test_Constructor_InitializerList";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		static const size_t expected_data_size = 0x10;
		byte_t expected_data[expected_data_size] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
		tc::ByteData data({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f});

		if (data.data() == nullptr)
		{
			throw tc::TestException(".data() returned nullptr when ByteData was constructed with an initializer list");
		}

		if (data.size() != expected_data_size)
		{
			throw tc::TestException(fmt::format(".size() did not return {:d} when ByteData was constructed with an initializer list", expected_data_size));
		}

		if (memcmp(data.data(), expected_data, expected_data_size) != 0)
		{
			throw tc::TestException(".data() did not contain expected data");
		}

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

void ByteData_TestClass::test_Constructor_CreateSmallSized()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateSmallSized";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 1271;
		tc::ByteData data(data_size);

		if (data.data() == nullptr)
		{
			throw tc::TestException(fmt::format(".data() returned nullptr when ByteData was constructed with size {:d}", data_size));
		}

		if (data.size() != data_size)
		{
			throw tc::TestException(fmt::format(".size() did not return {:d} (returned {:d}) when ByteData was constructed with size {:d}", data_size, data.size(), data_size));
		}

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

void ByteData_TestClass::test_Constructor_CreateLargeSized()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateLargeSized";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 0x1000000;
		tc::ByteData data(data_size);

		if (data.data() == nullptr)
		{
			throw tc::TestException(fmt::format(".data() returned nullptr when ByteData was constructed with size {:d}", data_size));
		}

		if (data.size() != data_size)
		{
			throw tc::TestException(fmt::format(".size() did not return {:d} (returned {:d}) when ByteData was constructed with size {:d}", data_size, data.size(), data_size));
		}

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

void ByteData_TestClass::test_Constructor_ThrowExceptForBadAlloc()
{
	TestResult test;
	test.test_name = "test_Constructor_ThrowExceptForBadAlloc";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try 
		{
			const size_t data_size = -1;
			tc::ByteData data(data_size);

			throw tc::TestException("Did not throw exception where it should be impossible to allocate the memory");
		}
		catch (const tc::OutOfMemoryException&)
		{
			// do nothing, this is expected behaviour
		}
		
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

void ByteData_TestClass::test_Constructor_CreateFromPtr()
{
	TestResult test;
	test.test_name = "test_Constructor_CreateFromPtr";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t src_data_size = 0x1000;
		tc::ByteData src_data(src_data_size);
		memset(src_data.data(), 0xe0, src_data.size());

		tc::ByteData data(src_data.data(), src_data.size());

		if (data.data() == nullptr)
		{			
			throw tc::TestException(fmt::format(".data() returned nullptr when ByteData was constructed with size {:d}", src_data_size));
		}

		if (data.size() != src_data_size)
		{
			throw tc::TestException(fmt::format(".size() did not return {:d} (returned {:d}) when ByteData was constructed with size {:d}", src_data_size, data.size(), src_data_size));
		}

		if (memcmp(data.data(), src_data.data(), src_data_size) != 0)
		{
			throw tc::TestException(".data() did not have expected contents, when compared to source data");
		}

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

void ByteData_TestClass::test_ImplicitCopy_CopyInSameScope()
{
	TestResult test;
	test.test_name = "test_ImplicitCopy_CopyInSameScope";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 0x20;

		// create data with allocating constructor
		tc::ByteData data(data_size);

		// create data2 as a copy of data using implicit copy constructor
		tc::ByteData data2(data);

		if (data.size() != data2.size())
		{
			throw tc::TestException("data2 after being constructed by copy, did not have the same size");
		}

		if (data.data() == data2.data())
		{
			throw tc::TestException("data2 after being constructed by copy, had the same pointer");
		}

		tc::ByteData data3 = data;

		if (data.size() != data3.size())
		{
			throw tc::TestException("data3 after being constructed by copy assignment, did not have the same size");
		}

		if (data.data() == data3.data())
		{
			throw tc::TestException("data3 after being constructed by copy assignment, had the same pointer");
		}

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

void ByteData_TestClass::test_ImplicitCopy_CopyOntoInitiallisedByteData()
{
	TestResult test;
	test.test_name = "test_ImplicitCopy_CopyOntoInitiallisedByteData";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 0x20;
		const size_t data2_size = 0x30;

		// create data with allocating constructor
		tc::ByteData data(data_size);

		// create data2 with allocating constructor
		tc::ByteData data2(data2_size);

		data2 = data;

		if (data.size() != data2.size())
		{
			throw tc::TestException("data2 after being assigned by copy, did not have the same size");
		}

		if (data.data() == data2.data())
		{
			throw tc::TestException("data2 after being assigned by copy, had the same pointer");
		}

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

void ByteData_TestClass::test_ImplicitMove_CopyInSameScope()
{
	TestResult test;
	test.test_name = "test_ImplicitMove_CopyInSameScope";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 0x20;

		// create data with allocating constructor
		tc::ByteData data(data_size);
		// mark buffer[0] so we can see if buffer ptr is being moved properly
		data.data()[0] = 0xff;

		// create data2 as a copy of data using implicit move constructor
		tc::ByteData data2(std::move(data));

		if (data2.data()[0] != 0xff)
		{
			throw tc::TestException("data2 did not have expected byte at buffer()[0]");
		}

		if (data.data() != nullptr)
		{
			throw tc::TestException("data after being moved to data2 retained it's old pointer");
		}

		if (data.size() == data2.size())
		{
			throw tc::TestException("data2 after being constructed by move from data, had the same size");
		}

		tc::ByteData data3 = std::move(data2);

		if (data3.data()[0] != 0xff)
		{
			throw tc::TestException("data3 did not have expected byte at buffer()[0]");
		}

		if (data2.data() != nullptr)
		{
			throw tc::TestException("data2 after being moved to data3 retained it's old pointer");
		}

		if (data.size() == data3.size())
		{
			throw tc::TestException("data3 after being constructed by move assignment from data2, has the same size");
		}

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

void ByteData_TestClass::test_ImplicitMove_MoveOntoInitiallisedByteData()
{
	TestResult test;
	test.test_name = "test_ImplicitMove_MoveOntoInitiallisedByteData";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		const size_t data_size = 0x20;
		const size_t data2_size = 0x30;

		// create data with allocating constructor
		tc::ByteData data(data_size);
		// mark buffer[0] so we can see if buffer ptr is being copied properly
		data.data()[0] = 0xff;

		// create data2 with allocating constructor
		tc::ByteData data2(data2_size);

		// move data to data2 by assignment
		data2 = std::move(data);

		if (data.data() != nullptr)
		{
			throw tc::TestException("data after being moved to data2 retained it's old pointer");
		}

		if (data.size() == data2.size())
		{
			throw tc::TestException("data2 after being assigned by copy, did not have the same size");
		}

		if (data.size() == data2.size())
		{
			throw tc::TestException("data2 after being constructed by move from data, had the same size");
		}

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

void ByteData_TestClass::test_EqualityOperator()
{
	TestResult test;
	test.test_name = "test_EqualityOperator";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		static const size_t kControlDataSize = 0x10;
		const byte_t kControlData[kControlDataSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

		auto control_data = tc::ByteData(kControlData, kControlDataSize);

		// test 1 - data is the same
		{
			auto same_data = tc::ByteData(kControlData, kControlDataSize);
			if ((control_data == same_data) != true)
			{
				throw tc::TestException("operator==(control, test) returned false for identical ByteData");
			}
			if ((same_data == control_data) != true)
			{
				throw tc::TestException("operator==(test, control) returned false for identical ByteData");
			}
		}

		// test 2 - truncated ByteData
		{
			auto smaller = tc::ByteData(control_data.data(), control_data.size()-1);
			if ((control_data == smaller) != false)
			{
				throw tc::TestException("operator==(control, test) returned true for when compared to truncated ByteData");
			}
			if ((smaller == control_data) != false)
			{
				throw tc::TestException("operator==(test, control) returned true for when compared to truncated ByteData");
			}
		}

		// test 3 - same size different ByteData
		{
			auto different = tc::ByteData(control_data);
			different[different.size()-1] = 0xff;
			if ((control_data == different) != false)
			{
				throw tc::TestException("operator==(control, test) returned true for when compared to same size but different ByteData");
			}
			if ((different == control_data) != false)
			{
				throw tc::TestException("operator==(test, control) returned true for when compared to same size but different ByteData");
			}
		}

		// test 4 - null ByteData
		{
			auto empty_data = tc::ByteData();
			if ((control_data == empty_data) != false)
			{
				throw tc::TestException("operator==(control, test) returned true for when compared to empty ByteData");
			}
			if ((empty_data == control_data) != false)
			{
				throw tc::TestException("operator==(test, control) returned true for when compared to empty ByteData");
			}
		}
		
		// test 5 - null to null
		{
			auto empty_data = tc::ByteData();
			auto empty_data2 = tc::ByteData();
			if ((empty_data2 == empty_data) != true)
			{
				throw tc::TestException("operator==(empty, empty2) returned true for when comparing two empty ByteData");
			}
			if ((empty_data == empty_data2) != true)
			{
				throw tc::TestException("operator==(empty2, empty) returned true for when comparing two empty ByteData");
			}
		}

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

void ByteData_TestClass::test_InequalityOperator()
{
	TestResult test;
	test.test_name = "test_InequalityOperator";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		static const size_t kControlDataSize = 0x10;
		const byte_t kControlData[kControlDataSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

		auto control_data = tc::ByteData(kControlData, kControlDataSize);

		// test 1 - data is the same
		{
			auto same_data = tc::ByteData(kControlData, kControlDataSize);
			if ((control_data != same_data) != false)
			{
				throw tc::TestException("operator!=(control, test) returned false for identical ByteData");
			}
			if ((same_data != control_data) != false)
			{
				throw tc::TestException("operator!=(test, control) returned false for identical ByteData");
			}
		}

		// test 2 - truncated ByteData
		{
			auto smaller = tc::ByteData(control_data.data(), control_data.size()-1);
			if ((control_data != smaller) != true)
			{
				throw tc::TestException("operator!=(control, test) returned true for when compared to truncated ByteData");
			}
			if ((smaller != control_data) != true)
			{
				throw tc::TestException("operator!=(test, control) returned true for when compared to truncated ByteData");
			}
		}

		// test 3 - same size different ByteData
		{
			auto different = tc::ByteData(control_data);
			different[different.size()-1] = 0xff;
			if ((control_data != different) != true)
			{
				throw tc::TestException("operator!=(control, test) returned true for when compared to same size but different ByteData");
			}
			if ((different != control_data) != true)
			{
				throw tc::TestException("operator!=(test, control) returned true for when compared to same size but different ByteData");
			}
		}

		// test 4 - null ByteData
		{
			auto empty_data = tc::ByteData();
			if ((control_data != empty_data) != true)
			{
				throw tc::TestException("operator!=(control, test) returned true for when compared to empty ByteData");
			}
			if ((empty_data != control_data) != true)
			{
				throw tc::TestException("operator!=(test, control) returned true for when compared to empty ByteData");
			}
		}
		
		// test 5 - null to null
		{
			auto empty_data = tc::ByteData();
			auto empty_data2 = tc::ByteData();
			if ((empty_data2 != empty_data) != false)
			{
				throw tc::TestException("operator!=(empty, empty2) returned true for when comparing two empty ByteData");
			}
			if ((empty_data != empty_data2) != false)
			{
				throw tc::TestException("operator!=(empty2, empty) returned true for when comparing two empty ByteData");
			}
		}

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