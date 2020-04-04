#include "SinkTestUtil.h"
#include <sstream>

const std::string SinkTestUtil::DummySinkBase::kClassName = "DummySinkBase";

void SinkTestUtil::testSinkLength(tc::io::ISink& sink, int64_t expected_len)
{
	std::stringstream error_ss;
	int64_t actual_len = sink.length();
	if (actual_len != expected_len)
	{
		error_ss << "length() returned: " << actual_len << ", when it should have been " << expected_len << ".";
		throw tc::Exception(error_ss.str());
	}
}
