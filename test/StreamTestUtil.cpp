#include "StreamTestUtil.h"
#include <sstream>

const std::string StreamTestUtil::DummyStreamBase::kClassName = "DummyStreamBase";

void StreamTestUtil::constructor_TestHelper(tc::io::IStream& stream, int64_t stream_length, int64_t exp_pos_res, bool exp_canread_res, bool exp_canwrite_res, bool exp_canseek_res)
{
	std::stringstream error_ss;

	int64_t length_res = stream.length();
	int64_t pos_res = stream.position();
	bool can_read = stream.canRead();
	bool can_write = stream.canWrite();
	bool can_seek = stream.canSeek();

	if (length_res != stream_length)
	{
		error_ss << "Stream did not have length " << stream_length << " (actual " << length_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_read != exp_canread_res)
	{
		error_ss << "Stream property canRead() was not " << std::boolalpha << exp_canread_res << " (actual " << std::boolalpha << can_read << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_write != exp_canwrite_res)
	{
		error_ss << "Stream property canWrite() was not " << std::boolalpha << exp_canwrite_res << " (actual " << std::boolalpha << can_write << ")";
		throw tc::Exception(error_ss.str());
	}

	if (can_seek != exp_canseek_res)
	{
		error_ss << "Stream property canSeek() was not " << std::boolalpha << exp_canseek_res << " (actual " << std::boolalpha << can_seek << ")";
		throw tc::Exception(error_ss.str());
	}
}

void StreamTestUtil::seek_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, int64_t exp_seek_res, int64_t exp_pos_res)
{
	std::stringstream error_ss;

	int64_t seek_res = stream.seek(seek_offset, seek_origin);
	int64_t pos_res = stream.position();

	if (seek_res != exp_seek_res)
	{
		error_ss << "Stream did not return position from seek " << exp_seek_res << " (actual " << seek_res << ")";
		throw tc::Exception(error_ss.str());
	}

	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}

void StreamTestUtil::read_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, size_t dst_size, size_t read_count, size_t exp_read_res, int64_t exp_pos_res, const byte_t* expected_data)
{
	std::stringstream error_ss;

	tc::ByteData data(dst_size);

	// offset the position
	stream.seek(seek_offset, seek_origin);

	// read data
	size_t read_res = stream.read(data.get(), read_count);

	// check position
	int64_t pos_res = stream.position();

	// validate read result
	if (read_res != exp_read_res)
	{
		error_ss << "Stream did not read expected number of bytes " << exp_read_res << " (actual " << read_res << ")";
		throw tc::Exception(error_ss.str());
	}
	
	// validate read data
	if (expected_data != nullptr && memcmp(data.get(), expected_data, exp_read_res) != 0)
	{
		error_ss << "Stream did not read expected bytes";
		throw tc::Exception(error_ss.str());
	}

	// validate pos result
	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}

void StreamTestUtil::write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, tc::ByteData& data, int64_t exp_pos_res)
{
	write_TestHelper(stream, seek_offset, seek_origin, data.get(), data.size(), exp_pos_res);
}

void StreamTestUtil::write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, tc::ByteData& data, int64_t exp_pos_res, int64_t exp_length_res)
{
	write_TestHelper(stream, seek_offset, seek_origin, data.get(), data.size(), exp_pos_res, exp_length_res);
}

void StreamTestUtil::write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, const byte_t* data, size_t data_size, int64_t exp_pos_res)
{
	std::stringstream error_ss;

	// offset the position
	stream.seek(seek_offset, seek_origin);

	stream.write(data, data_size);

	int64_t pos_res = stream.position();

	// validate pos result
	if (pos_res != exp_pos_res)
	{
		error_ss << "Stream did not have position " << exp_pos_res << " (actual " << pos_res << ")";
		throw tc::Exception(error_ss.str());
	}
}

void StreamTestUtil::write_TestHelper(tc::io::IStream& stream, int64_t seek_offset, tc::io::SeekOrigin seek_origin, const byte_t* data, size_t data_size, int64_t exp_pos_res, int64_t exp_length_res)
{
	std::stringstream error_ss;

	write_TestHelper(stream, seek_offset, seek_origin, data, data_size, exp_pos_res);

	// validate length result
	int64_t length_res = stream.length();
	if (length_res != exp_length_res)
	{
		error_ss << "Stream did not have length " << exp_length_res << " (actual " << length_res << ")";
		throw tc::Exception(error_ss.str());
	}
}