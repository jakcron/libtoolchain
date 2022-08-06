#include "io_OverlayedSource_TestClass.h"
#include "SourceTestUtil.h"

#include <tc/io/OverlayedSource.h>
#include <tc/io/PaddingSource.h>

//---------------------------------------------------------

io_OverlayedSource_TestClass::io_OverlayedSource_TestClass() :
	mTestTag("tc::io::OverlayedSource"),
	mTestResults()
{
}

void io_OverlayedSource_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testSingleOverlayConstructor();
	testMultiOverlayConstructor();
	testNullBaseStream();
	testNullOverlayStream();
	testOverlayStreamTooSmallForOverlayRegion();
	testOverlayRegionBeforeBaseStream();
	testOverlayRegionPartlyBeforeBaseStream();
	testOverlayRegionAfterBaseStream();
	testOverlayRegionPartlyAfterBaseStream();
}

const std::string& io_OverlayedSource_TestClass::getTestTag() const
{
	return mTestTag;
}

const std::vector<ITestClass::TestResult>& io_OverlayedSource_TestClass::getTestResults() const
{
	return mTestResults;
}

//---------------------------------------------------------

void io_OverlayedSource_TestClass::testDefaultConstructor()
{
	TestResult test;
	test.test_name = "testDefaultConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		tc::io::OverlayedSource source;

		SourceTestUtil::testSourceLength(source, 0);
		SourceTestUtil::pullTestHelper(source, 0, 0xdead, 0, nullptr);

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

void io_OverlayedSource_TestClass::testSingleOverlayConstructor()
{
	TestResult test;
	test.test_name = "testSingleOverlayConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		// ## create overlay source
		size_t overlay_offset = 0x80;
		tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);
		tc::io::PaddingSource overlay_source = tc::io::PaddingSource(0xaa, 0x100);

		tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), std::make_shared<tc::io::PaddingSource>(overlay_source), overlay_offset, overlay_source.length());

		// ## create ByteData with expected data to test against
		tc::ByteData expected_data = base_source.pullData(0, base_source.length());
		tc::ByteData overlay_data = overlay_source.pullData(0, overlay_source.length());
		
		memcpy(expected_data.data() + overlay_offset, overlay_data.data(), overlay_data.size());

		// ## validate overlay source
		// source length
		SourceTestUtil::testSourceLength(source, base_source.length());

		// pullData tests
		size_t pull_size;
		int64_t pull_offset;

		// pull full contents of source
		pull_size = base_source.length();
		pull_offset = 0;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

		// try to pull double the length of source
		pull_size = base_source.length() * 2;
		pull_offset = 0;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size/2, expected_data.data() + pull_offset);
		
		// pull source up to overlay source
		pull_size = overlay_offset;
		pull_offset = 0;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

		// pull just overlay source
		pull_size = overlay_source.length();
		pull_offset = overlay_offset;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

		// pull part of overlay
		pull_size = 0x20;
		pull_offset = overlay_offset - 0x30;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

		// pull part of base and part of overlay
		pull_size = 0x20;
		pull_offset = overlay_offset - 0x10;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

		// pull part of overlay and part of base
		pull_size = 0x20;
		pull_offset = overlay_offset + overlay_source.length() - 0x10;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

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

void io_OverlayedSource_TestClass::testMultiOverlayConstructor()
{
	TestResult test;
	test.test_name = "testMultiOverlayConstructor";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{			
		// ## create overlay source
		tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);

		std::vector<tc::io::OverlayedSource::OverlaySourceInfo> overlay_info = {
			{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xaa, 0x1000)), 0x20, 0x100 },
			{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xbb, 0x1000)), 0x100, 0x100 },
			{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xcc, 0x1000)), 0x320, 0x100 },
			{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xdd, 0x1000)), 0x420, 0x100 },
			{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xee, 0x1000)), 0x520, 0x100 },
		};

		tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), overlay_info);

		// ## create ByteData with expected data to test against
		tc::ByteData expected_data = base_source.pullData(0, base_source.length());
		for (auto itr = overlay_info.begin(); itr != overlay_info.end(); itr++)
		{
			tc::ByteData tmp = itr->overlay_source->pullData(0, itr->length);
			memcpy(expected_data.data() + itr->offset, tmp.data(), tmp.size());
		}
				
		// ## validate overlay source
		// source length
		SourceTestUtil::testSourceLength(source, base_source.length());

		// pullData tests
		size_t pull_size;
		int64_t pull_offset;

		// pull full contents of source
		pull_size = base_source.length();
		pull_offset = 0;
		SourceTestUtil::pullTestHelper(source, pull_offset, pull_size, pull_size, expected_data.data() + pull_offset);

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

void io_OverlayedSource_TestClass::testNullBaseStream()
{
	TestResult test;
	test.test_name = "testNullBaseStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);

			std::vector<tc::io::OverlayedSource::OverlaySourceInfo> overlay_info = {
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xaa, 0x1000)), 0x20, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xbb, 0x1000)), 0x100, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xcc, 0x1000)), 0x320, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xdd, 0x1000)), 0x420, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xee, 0x1000)), 0x520, 0x100 },
			};

			tc::io::OverlayedSource source(std::shared_ptr<tc::io::PaddingSource>(nullptr), overlay_info);

			throw tc::TestException("Constructor did not throw tc::ArgumentNullException where base_source was null");
		}
		catch (tc::ArgumentNullException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where base_source was null");
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

void io_OverlayedSource_TestClass::testNullOverlayStream()
{
	TestResult test;
	test.test_name = "testNullOverlayStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);

			std::vector<tc::io::OverlayedSource::OverlaySourceInfo> overlay_info = {
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xaa, 0x1000)), 0x20, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xbb, 0x1000)), 0x100, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(nullptr), 0x320, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xdd, 0x1000)), 0x420, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xee, 0x1000)), 0x520, 0x100 },
			};

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), overlay_info);

			throw tc::TestException("Constructor did not throw tc::ArgumentNullException where an overlay source was null");
		}
		catch (tc::ArgumentNullException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where an overlay source was null");
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

void io_OverlayedSource_TestClass::testOverlayStreamTooSmallForOverlayRegion()
{
	TestResult test;
	test.test_name = "testOverlayStreamTooSmallForOverlayRegion";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);

			std::vector<tc::io::OverlayedSource::OverlaySourceInfo> overlay_info = {
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xaa, 0x1000)), 0x20, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xbb, 0x1000)), 0x100, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xcc, 0x10)), 0x300, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xdd, 0x1000)), 0x420, 0x100 },
				{ std::shared_ptr<tc::io::PaddingSource>(new tc::io::PaddingSource(0xee, 0x1000)), 0x520, 0x100 },
			};

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), overlay_info);

			throw tc::TestException("Constructor did not throw tc::ArgumentOutOfRangeException where an overlay source was smaller than the region it was supposed to overlay");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where an overlay source was smaller than the region it was supposed to overlay");
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
}

void io_OverlayedSource_TestClass::testOverlayRegionBeforeBaseStream()
{
	TestResult test;
	test.test_name = "testOverlayRegionBeforeBaseStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);
			tc::io::PaddingSource padding_source = tc::io::PaddingSource(0xee, 0x1000);

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), std::make_shared<tc::io::PaddingSource>(padding_source), -1, 1);

			throw tc::TestException("Constructor did not throw tc::ArgumentOutOfRangeException where the overlay region entirely doesn't exist in the base");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where the overlay region entirely doesn't exist in the base");
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
}

void io_OverlayedSource_TestClass::testOverlayRegionPartlyBeforeBaseStream()
{
	TestResult test;
	test.test_name = "testOverlayRegionPartlyBeforeBaseStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);
			tc::io::PaddingSource padding_source = tc::io::PaddingSource(0xee, 0x1000);

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), std::make_shared<tc::io::PaddingSource>(padding_source), -1, 20);

			throw tc::TestException("Constructor did not throw tc::ArgumentOutOfRangeException where overlay region partly exists before in the base");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where overlay region partly exists before in the base");
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
}

void io_OverlayedSource_TestClass::testOverlayRegionAfterBaseStream()
{
	TestResult test;
	test.test_name = "testOverlayRegionAfterBaseStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);
			tc::io::PaddingSource padding_source = tc::io::PaddingSource(0xee, 0x1000);

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), std::make_shared<tc::io::PaddingSource>(padding_source), 0x1000, 0x100);

			throw tc::TestException("Constructor did not throw tc::ArgumentOutOfRangeException where overlay region exists after in the base");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where overlay region exists after in the base");
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
}

void io_OverlayedSource_TestClass::testOverlayRegionPartlyAfterBaseStream()
{
	TestResult test;
	test.test_name = "testOverlayRegionPartlyAfterBaseStream";
	test.result = "NOT RUN";
	test.comments = "";

	try
	{
		try
		{
			tc::io::PaddingSource base_source = tc::io::PaddingSource(0xff, 0x1000);
			tc::io::PaddingSource padding_source = tc::io::PaddingSource(0xee, 0x1000);

			tc::io::OverlayedSource source(std::make_shared<tc::io::PaddingSource>(base_source), std::make_shared<tc::io::PaddingSource>(padding_source), 0xfff, 0x100);

			throw tc::TestException("Constructor did not throw tc::ArgumentOutOfRangeException where overlay region exists partly after in the base");
		}
		catch (tc::ArgumentOutOfRangeException&) { /* do nothing */ }
		catch (tc::Exception&)
		{
			throw tc::TestException("Constructor threw the wrong exception where overlay region exists partly after in the base");
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
}