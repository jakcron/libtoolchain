#pragma once
#include "ITestClass.h"

#include <tc/io/MemoryStream.h>

class io_MemoryStream_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testCreateEmptyStream_DefaultConstructor();
	void testCreateEmptyStream_SizedConstructor();
	void testCreatePopulatedStream();
	void testSeekBeginToZero();
	void testSeekBeginToMiddle();
	void testSeekBeginToEnd();
	void testSeekBeginPastEnd();
	void testSeekBeginNegative();
	void testSeekCurrentByZero();
	void testSeekCurrentToMiddle();
	void testSeekCurrentToEnd();
	void testSeekCurrentPastEnd();
	void testSeekCurrentNegative();
	void testSeekEndByZero();
	void testSeekEndPastEnd();
	void testSeekEndNegative();
	void testSeekEndTooNegative();
	void testReadAllDataAvailable();
	void testReadRequestsSubsetOfAvailableData();
	void testReadSomeDataAvailable();
	void testReadNoDataAvailable();
	void testWriteAllDataWritable();
	void testWriteToSomeOfDataAvailable();
	void testWriteSomeDataWritable();
	void testWriteNoDataWritable();
	void testWriteReadDataPersistence();
	void testResizeStreamLarger();
	void testResizeStreamSmaller();
	void testDispose();

	void constructor_TestHelper(tc::io::IStream& stream, int64_t stream_length, int64_t exp_pos_res, bool exp_canread_res, bool exp_canwrite_res, bool exp_canseek_res);
	void seek_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, int64_t exp_seek_res, int64_t exp_pos_res);
	void read_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, size_t dst_size, size_t read_count, size_t exp_read_res, int64_t exp_pos_res);
	void write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, tc::ByteData& data, int64_t exp_pos_res);
};
