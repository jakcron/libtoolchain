#include "SourceTestUtil.h"
#include <fmt/format.h>

void SourceTestUtil::testSourceLength(tc::io::ISource& source, int64_t expected_len)
{
	int64_t actual_len = source.length();
	if (actual_len != expected_len)
	{
		throw tc::Exception(fmt::format("length() returned: {:d}, when it should have been {:d}.", actual_len, expected_len));
	}
}

void SourceTestUtil::pullTestHelper(tc::io::ISource& source, int64_t offset, size_t len, size_t expected_len, const byte_t* expected_data)
{
	tc::ByteData data = source.pullData(offset, len);

	if (data.size() != expected_len)
	{
		throw tc::Exception(fmt::format("pullData(offset: {:d}, len: {:d}) returned ByteData with size(): {:d}, when it should have been {:d}.", offset, len, data.size(), expected_len));
	}

	if (expected_data != nullptr && memcmp(data.data(), expected_data, expected_len) != 0)
	{
		throw tc::Exception(fmt::format("pullData(offset: {:d}, len: {:d}) returned ByteData with incorrect layout", offset, len));
	}
}