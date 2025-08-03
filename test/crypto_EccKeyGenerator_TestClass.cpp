#include "crypto_EccKeyGenerator_TestClass.h"

#include <fmt/format.h>

#include <tc/crypto/EccKeyGenerator.h>
#include <tc/io/PaddingSource.h>
#include <tc/cli/FormatUtil.h>

//---------------------------------------------------------

crypto_EccKeyGenerator_TestClass::crypto_EccKeyGenerator_TestClass() :
	mTestTag("tc::crypto::EccKeyGenerator"),
	mTestResults()
{
}

void crypto_EccKeyGenerator_TestClass::runAllTests(void)
{
	test_Class();
	test_UtilFunc();
	test_MultipleObjectsCreateDifferentData();
	test_RepeatedCallsCreateDifferentData();
}

const std::string& crypto_EccKeyGenerator_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& crypto_EccKeyGenerator_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void crypto_EccKeyGenerator_TestClass::test_Class()
{
	TestResult test_result;
	test_result.test_name = "test_Class";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create class to store key
		tc::crypto::EccKey key;
		tc::crypto::EccKey pubkey;

		// curves to test
		std::vector<sCurveInfo> curve_test_list;
		getCurveTestList(curve_test_list);

		tc::crypto::EccKeyGenerator keygen;
		for (size_t i = 0; i < curve_test_list.size(); i++)
		{
			// reset key
			key.curve_type = tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192R1;
			key.d = tc::ByteData();
			key.Q = tc::ByteData();

			// generate key
			keygen.generateKey(key, curve_test_list[i].curve_type);

			// check key
			if (key.curve_type != curve_test_list[i].curve_type)
			{
				throw tc::TestException(fmt::format(".generateKey({},key) key.curve_type ({}) did not match expected value ({})", curve_test_list[i].curve_name, (uint32_t)key.curve_type, (uint32_t)curve_test_list[i].curve_type));
			}

			size_t integer_len_bytes = align<size_t>(curve_test_list[i].integer_bit_size, 8) / 8;
			size_t expected_d_size = integer_len_bytes;
			size_t expected_Q_size = integer_len_bytes*2;
			if (key.d.size() != expected_d_size)
			{
				throw tc::TestException(fmt::format(".generateKey({},key) key.d.size() ({}) did not match expected value ({})", curve_test_list[i].curve_name, key.d.size(), expected_d_size));
			}

			if (key.Q.size() != expected_Q_size)
			{
				throw tc::TestException(fmt::format(".generateKey({},key) key.Q.size() ({}) did not match expected value ({})", curve_test_list[i].curve_name, key.Q.size(), expected_Q_size));
			}

			// generate public key
			keygen.generatePublicKey(pubkey, key);

			// check public key type
			if (pubkey.curve_type != key.curve_type)
			{
				throw tc::TestException(fmt::format(".generatePublicKey(pubkey,key) (for curve {}) pubkey.curve_type ({}) did not match key.curve_type ({})", curve_test_list[i].curve_name, (uint32_t)pubkey.curve_type, (uint32_t)key.curve_type));
			}

			// check public key has no private component
			if (pubkey.d.size() != 0)
			{
				throw tc::TestException(fmt::format(".generatePublicKey(pubkey,key) (for curve {}) pubkey.d.size() ({}) was not 0", curve_test_list[i].curve_name, pubkey.d.size()));
			}

			// check public key has same public component as key
			if (pubkey.Q.size() != key.Q.size())
			{
				throw tc::TestException(fmt::format(".generatePublicKey(pubkey,key) (for curve {}) pubkey.Q.size() ({}) did not match key.Q.size() ({})", curve_test_list[i].curve_name, pubkey.Q.size(), key.Q.size()));
			}
			if (memcmp(pubkey.Q.data(), key.Q.data(), pubkey.Q.size()) != 0)
			{
				throw tc::TestException(fmt::format(".generatePublicKey(pubkey,key) (for curve {}) pubkey.Q.data() did not match key.Q.data()", curve_test_list[i].curve_name));
			}
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

void crypto_EccKeyGenerator_TestClass::test_UtilFunc()
{
	TestResult test_result;
	test_result.test_name = "test_UtilFunc";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create class to store key
		tc::crypto::EccKey key;
		tc::crypto::EccKey pubkey;

		// curves to test
		std::vector<sCurveInfo> curve_test_list;
		getCurveTestList(curve_test_list);

		for (size_t i = 0; i < curve_test_list.size(); i++)
		{
			// reset key
			key.curve_type = tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192R1;
			key.d = tc::ByteData();
			key.Q = tc::ByteData();

			// generate key
			tc::crypto::GenerateEccKey(key, curve_test_list[i].curve_type);

			// check key
			if (key.curve_type != curve_test_list[i].curve_type)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccKey({},key) key.curve_type ({}) did not match expected value ({})", curve_test_list[i].curve_name, (uint32_t)key.curve_type, (uint32_t)curve_test_list[i].curve_type));
			}

			size_t integer_len_bytes = align<size_t>(curve_test_list[i].integer_bit_size, 8) / 8;
			size_t expected_d_size = integer_len_bytes;
			size_t expected_Q_size = integer_len_bytes*2;
			if (key.d.size() != expected_d_size)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccKey({},key) key.d.size() ({}) did not match expected value ({})", curve_test_list[i].curve_name, key.d.size(), expected_d_size));
			}

			if (key.Q.size() != expected_Q_size)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccKey({},key) key.Q.size() ({}) did not match expected value ({})", curve_test_list[i].curve_name, key.Q.size(), expected_Q_size));
			}

			// generate public key
			tc::crypto::GenerateEccPublicKey(pubkey, key);

			// check public key type
			if (pubkey.curve_type != key.curve_type)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccPublicKey(pubkey,key) (for curve {}) pubkey.curve_type ({}) did not match key.curve_type ({})", curve_test_list[i].curve_name, (uint32_t)pubkey.curve_type, (uint32_t)key.curve_type));
			}

			// check public key has no private component
			if (pubkey.d.size() != 0)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccPublicKey(pubkey,key) (for curve {}) pubkey.d.size() ({}) was not 0", curve_test_list[i].curve_name, pubkey.d.size()));
			}

			// check public key has same public component as key
			if (pubkey.Q.size() != key.Q.size())
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccPublicKey(pubkey,key) (for curve {}) pubkey.Q.size() ({}) did not match key.Q.size() ({})", curve_test_list[i].curve_name, pubkey.Q.size(), key.Q.size()));
			}
			if (memcmp(pubkey.Q.data(), key.Q.data(), pubkey.Q.size()) != 0)
			{
				throw tc::TestException(fmt::format("tc::crypto::GenerateEccPublicKey(pubkey,key) (for curve {}) pubkey.Q.data() did not match key.Q.data()", curve_test_list[i].curve_name));
			}
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

void crypto_EccKeyGenerator_TestClass::test_MultipleObjectsCreateDifferentData()
{
	TestResult test_result;
	test_result.test_name = "test_MultipleObjectsCreateDifferentData";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create class to store key
		tc::crypto::EccKey key1, key2, key3;

		// curves to test
		std::vector<sCurveInfo> curve_test_list;
		getCurveTestList(curve_test_list);

		// test for each curve type
		tc::crypto::EccKeyGenerator keygen;
		for (size_t i = 0; i < curve_test_list.size(); i++)
		{
			// generate keys
			tc::crypto::EccKeyGenerator keygen1, keygen2, keygen3;
			keygen1.generateKey(key1, curve_test_list[i].curve_type);
			keygen2.generateKey(key2, curve_test_list[i].curve_type);
			keygen3.generateKey(key3, curve_test_list[i].curve_type);

			static const size_t kSimilarityThreshold = 3;

			// check private component
			size_t privateCmp12 = 0, privateCmp13 = 0, privateCmp23 = 0;

			for (size_t i = 0; i < key1.d.size(); i++)
			{
				privateCmp12 += key1.d[i] == key2.d[i];
				privateCmp13 += key1.d[i] == key3.d[i];
				privateCmp23 += key2.d[i] == key3.d[i];
			}

			// check to see if any of the tests were similar
			if (privateCmp12 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 1 & privateKey 2 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp12, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}
			if (privateCmp13 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 1 & privateKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp13, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}
			if (privateCmp23 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 2 & privateKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp23, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}

			// check public component
			size_t publicCmp12 = 0, publicCmp13 = 0, publicCmp23 = 0;

			for (size_t i = 0; i < key1.Q.size(); i++)
			{
				if (!curve_test_list[i].curve_defines_Q_y && i >= (key1.Q.size()/2))
					break;

				publicCmp12 += key1.Q[i] == key2.Q[i];
				publicCmp13 += key1.Q[i] == key3.Q[i];
				publicCmp23 += key2.Q[i] == key3.Q[i];
			}

			// check to see if any of the tests were similar
			if (publicCmp12 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 1 & publicKey 2 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp12, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
			if (publicCmp13 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 1 & publicKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp13, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
			if (publicCmp23 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 2 & publicKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp23, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
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

void crypto_EccKeyGenerator_TestClass::test_RepeatedCallsCreateDifferentData()
{
	TestResult test_result;
	test_result.test_name = "test_RepeatedCallsCreateDifferentData";
	test_result.result = "NOT RUN";
	test_result.comments = "";

	try
	{
		// create class to store key
		tc::crypto::EccKey key1, key2, key3;

		// curves to test
		std::vector<sCurveInfo> curve_test_list;
		getCurveTestList(curve_test_list);

		// test for each curve type
		for (size_t i = 0; i < curve_test_list.size(); i++)
		{
			// generate keys
			tc::crypto::EccKeyGenerator keygen;
			keygen.generateKey(key1, curve_test_list[i].curve_type);
			keygen.generateKey(key2, curve_test_list[i].curve_type);
			keygen.generateKey(key3, curve_test_list[i].curve_type);

			static const size_t kSimilarityThreshold = 3;

			// check private component
			size_t privateCmp12 = 0, privateCmp13 = 0, privateCmp23 = 0;

			for (size_t i = 0; i < key1.d.size(); i++)
			{
				privateCmp12 += key1.d[i] == key2.d[i];
				privateCmp13 += key1.d[i] == key3.d[i];
				privateCmp23 += key2.d[i] == key3.d[i];
			}

			// check to see if any of the tests were similar
			if (privateCmp12 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 1 & privateKey 2 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp12, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}
			if (privateCmp13 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 1 & privateKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp13, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}
			if (privateCmp23 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) privateKey 2 & privateKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, privateCmp23, tc::cli::FormatUtil::formatBytesAsString(key1.d, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.d, false, "")));
			}

			// check public component
			size_t publicCmp12 = 0, publicCmp13 = 0, publicCmp23 = 0;

			for (size_t i = 0; i < key1.Q.size(); i++)
			{
				if (!curve_test_list[i].curve_defines_Q_y && i >= (key1.Q.size()/2))
					break;

				publicCmp12 += key1.Q[i] == key2.Q[i];
				publicCmp13 += key1.Q[i] == key3.Q[i];
				publicCmp23 += key2.Q[i] == key3.Q[i];
			}

			// check to see if any of the tests were similar
			if (publicCmp12 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 1 & publicKey 2 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp12, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
			if (publicCmp13 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 1 & publicKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp13, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
			if (publicCmp23 > kSimilarityThreshold)
			{
				throw tc::TestException(fmt::format("(curve {}) publicKey 2 & publicKey 3 has {:d} similar bytes ({} vs {})", curve_test_list[i].curve_name, publicCmp23, tc::cli::FormatUtil::formatBytesAsString(key1.Q, false, ""), tc::cli::FormatUtil::formatBytesAsString(key2.Q, false, "")));
			}
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

void crypto_EccKeyGenerator_TestClass::getCurveTestList(std::vector<crypto_EccKeyGenerator_TestClass::sCurveInfo>& curve_test_list) const
{
	curve_test_list.clear();

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP192R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192R1,
		192,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP224R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP224R1,
		224,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP256R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP256R1,
		256,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP384R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP384R1,
		384,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP521R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP521R1,
		521,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_BP256R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP256R1,
		256,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_BP384R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP384R1,
		384,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_BP512R1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_BP512R1,
		512,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_CURVE25519",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_CURVE25519,
		255,
		false
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP192K1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP192K1,
		192,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP224K1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP224K1,
		224,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_SECP256K1",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_SECP256K1,
		256,
		true
	});

	curve_test_list.push_back({
		"ECC_CURVE_TYPE_CURVE448",
		tc::crypto::EccCurveType::ECC_CURVE_TYPE_CURVE448,
		448,
		false
	});
}
