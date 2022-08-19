#include "crypto_PseudoRandomByteGenerator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/PseudoRandomByteGenerator.h>
#include <tc/io/PaddingSource.h>
#include <tc/cli/FormatUtil.h>

//---------------------------------------------------------

crypto_PseudoRandomByteGenerator_TestClass::crypto_PseudoRandomByteGenerator_TestClass() :
	mTestTag("tc::crypto::PseudoRandomByteGenerator"),
	mTestResults()
{
}

void crypto_PseudoRandomByteGenerator_TestClass::runAllTests(void)
{
	test_Class();
	test_UtilFunc();
	test_MultipleObjectsCreateDifferentData();
	test_RepeatedCallsCreateDifferentData();
}

const std::string& crypto_PseudoRandomByteGenerator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_PseudoRandomByteGenerator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_PseudoRandomByteGenerator_TestClass::test_Class()
{
	TestResult test_result;
	test_result.test_name = "test_Class";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create buffer to hold random data
		auto random_data = tc::ByteData(0x20);

		// generate control_data to compare to random_data to ensure that it is populated with random bytes
		auto control_data = tc::io::PaddingSource(0xbe, random_data.size()).pullData(0, random_data.size());

		// copy control data
		memcpy(random_data.data(), control_data.data(), random_data.size());

		// generate random bytes
		tc::crypto::PseudoRandomByteGenerator prbg;
		prbg.getBytes(random_data.data(), random_data.size());

		// compare with control data to see if the data changed
		if (memcmp(random_data.data(), control_data.data(), random_data.size()) == 0)
		{
			throw tc::TestException(".getBytes() did not populate array");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_PseudoRandomByteGenerator_TestClass::test_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create buffer to hold random data
		auto random_data = tc::ByteData(0x20);

		// generate control_data to compare to random_data to ensure that it is populated with random bytes
		auto control_data = tc::io::PaddingSource(0xbe, random_data.size()).pullData(0, random_data.size());

		// copy control data
		memcpy(random_data.data(), control_data.data(), random_data.size());

		// generate random bytes
		tc::crypto::GeneratePseudoRandomBytes(random_data.data(), random_data.size());

		// compare with control data to see if the data changed
		if (memcmp(random_data.data(), control_data.data(), random_data.size()) == 0)
		{
			throw tc::TestException("GeneratePseudoRandomBytes() did not populate array");
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_PseudoRandomByteGenerator_TestClass::test_MultipleObjectsCreateDifferentData()
{
	TestResult test_result;
	test_result.test_name = "test_MultipleObjectsCreateDifferentData";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// generate allocate storage for each test
		static const size_t kRandomDataSize = 0x20;
		auto random_data1 = tc::ByteData(kRandomDataSize);
		auto random_data2 = tc::ByteData(kRandomDataSize);
		auto random_data3 = tc::ByteData(kRandomDataSize);
		
		// create PRBG objects
		tc::crypto::PseudoRandomByteGenerator prbg1, prbg2, prbg3;
		
		// generate random data
		prbg1.getBytes(random_data1.data(), random_data1.size());
		prbg2.getBytes(random_data2.data(), random_data2.size());
		prbg3.getBytes(random_data3.data(), random_data3.size());

		size_t cmp12 = 0, cmp13 = 0, cmp23 = 0;

		for (size_t i = 0; i < kRandomDataSize; i++)
		{
			cmp12 += random_data1[i] == random_data2[i];
			cmp13 += random_data1[i] == random_data3[i];
			cmp23 += random_data2[i] == random_data3[i];
		}

		// check to see if any of the tests were similar
		static const size_t kSimilarityThreshold = 2;
		if (cmp12 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 1 & case 2 has {:d} similar bytes", cmp12));
		}
		if (cmp13 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 1 & case 3 has {:d} similar bytes", cmp13));
		}
		if (cmp23 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 2 & case 3 has {:d} similar bytes", cmp23));
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}

void crypto_PseudoRandomByteGenerator_TestClass::test_RepeatedCallsCreateDifferentData()
{
	TestResult test_result;
	test_result.test_name = "test_RepeatedCallsCreateDifferentData";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// generate allocate storage for each test
		static const size_t kRandomDataSize = 0x20;
		auto random_data1 = tc::ByteData(kRandomDataSize);
		auto random_data2 = tc::ByteData(kRandomDataSize);
		auto random_data3 = tc::ByteData(kRandomDataSize);
		
		// create PRBG object
		tc::crypto::PseudoRandomByteGenerator prbg;
		
		// generate random data
		prbg.getBytes(random_data1.data(), random_data1.size());
		prbg.getBytes(random_data2.data(), random_data2.size());
		prbg.getBytes(random_data3.data(), random_data3.size());

		size_t cmp12 = 0, cmp13 = 0, cmp23 = 0;

		for (size_t i = 0; i < kRandomDataSize; i++)
		{
			cmp12 += random_data1[i] == random_data2[i];
			cmp13 += random_data1[i] == random_data3[i];
			cmp23 += random_data2[i] == random_data3[i];
		}

		// check to see if any of the tests were similar
		static const size_t kSimilarityThreshold = 2;
		if (cmp12 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 1 & case 2 has {:d} similar bytes", cmp12));
		}
		if (cmp13 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 1 & case 3 has {:d} similar bytes", cmp13));
		}
		if (cmp23 > kSimilarityThreshold)
		{
			throw tc::TestException(fmt::format("case 2 & case 3 has {:d} similar bytes", cmp23));
		}

		// record result
		test_result.result = "PASS";
		test_result.comments = "";
	}
	catch (const tc::TestException& e)
	{
		// record result
		test_result.result = "FAIL";
		test_result.comments = e.what();
	}
	catch (const std::exception& e)
	{
		// record result
		test_result.result = "UNHANDLED EXCEPTION";
		test_result.comments = e.what();
	}

	// add result to list
	mTestResults.push_back(std::move(test_result));
}