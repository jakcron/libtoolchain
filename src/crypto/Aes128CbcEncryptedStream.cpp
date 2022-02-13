#include <tc/crypto/Aes128CbcEncryptedStream.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <tc/cli/FormatUtil.h>

tc::crypto::Aes128CbcEncryptedStream::Aes128CbcEncryptedStream() :
	mModuleLabel("tc::crypto::Aes128CbcEncryptedStream"),
	mBaseStream()
{
	memset(mKey.data(), 0, mKey.size());
	memset(mIv.data(), 0, mIv.size());
}

tc::crypto::Aes128CbcEncryptedStream::Aes128CbcEncryptedStream(const std::shared_ptr<tc::io::IStream>& stream, const key_t& key, const iv_t& iv) :
	Aes128CbcEncryptedStream()
{
	mBaseStream = stream;

	// validate stream properties
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "stream is null.");
	}
	if (mBaseStream->canRead() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream does not support reading.");
	}
	if (mBaseStream->canSeek() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream does not support seeking.");
	}
	if ((mBaseStream->length() % sizeof(block_t)) != 0)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream does is not block aligned.");
	}

	mKey = key;
	mIv = iv;
}

bool tc::crypto::Aes128CbcEncryptedStream::canRead() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canRead();
}

bool tc::crypto::Aes128CbcEncryptedStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool tc::crypto::Aes128CbcEncryptedStream::canSeek() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canSeek();
}

int64_t tc::crypto::Aes128CbcEncryptedStream::length()
{
	return mBaseStream == nullptr ? 0 : mBaseStream->length();
}

int64_t tc::crypto::Aes128CbcEncryptedStream::position()
{
	return mBaseStream == nullptr ? 0 : mBaseStream->position();
}

size_t tc::crypto::Aes128CbcEncryptedStream::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}

	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// get current position
	int64_t current_pos = mBaseStream->position();
	if (current_pos < 0)
	{
		throw tc::InvalidOperationException(mModuleLabel+"::read()", "Current stream position is negative.");
	}

	// determine begin & end offsets
	int64_t begin_read_offset = this->position();
	int64_t end_read_offset   = begin_read_offset + tc::io::IOUtil::castSizeToInt64(count);
	int64_t begin_aligned_offset = begin_read_offset - offsetInBlock(begin_read_offset);
	int64_t end_aligned_offset   = end_read_offset - offsetInBlock(end_read_offset) + (offsetInBlock(end_read_offset) ? sizeof(block_t) : 0x0);
	size_t block_num = offsetToBlock(end_aligned_offset - begin_aligned_offset);

	bool read_partial_begin_block     = false;
	size_t partial_begin_block        = offsetToBlock(begin_read_offset);
	size_t partial_begin_block_offset = 0;
	size_t partial_begin_block_size   = sizeof(block_t);

	bool read_partial_end_block     = false;
	size_t partial_end_block        = offsetToBlock(end_read_offset);
	size_t partial_end_block_offset = 0;
	size_t partial_end_block_size   = sizeof(block_t);

	if (offsetInBlock(begin_read_offset) != 0)
	{
		read_partial_begin_block   = true;
		partial_begin_block_offset += offsetInBlock(begin_read_offset);
		partial_begin_block_size   -= partial_begin_block_offset;
	}
	if (offsetInBlock(end_read_offset) != 0)
	{
		if (partial_begin_block == partial_end_block)
		{
			read_partial_begin_block = true;
			partial_begin_block_size -= (sizeof(block_t) - offsetInBlock(end_read_offset));
		}
		else
		{
			read_partial_end_block = true;
			partial_end_block_size = offsetInBlock(end_read_offset);
		}
	}

	size_t continuous_block_num   = block_num - (size_t)read_partial_begin_block - (size_t)read_partial_end_block;
	size_t continuous_begin_block = (continuous_block_num == 0) ? 0 : (offsetToBlock(begin_aligned_offset) + (size_t)read_partial_begin_block);

	/*
	std::cout << "##############################################" << std::endl;
	std::cout << "count:                  0x" << std::hex << count << std::endl;
	std::cout << "begin_read_offset:      0x" << std::hex << begin_read_offset << std::endl;
	std::cout << "end_read_offset:        0x" << std::hex << end_read_offset << std::endl;
	std::cout << "begin_aligned_offset:   0x" << std::hex << begin_aligned_offset << std::endl;
	std::cout << "end_aligned_offset:     0x" << std::hex << end_aligned_offset << std::endl;
	std::cout << "block_num:              0x" << std::hex << block_num << std::endl;
	
	std::cout << "partial_begin:" << std::endl;
	std::cout << "  read_block:           " << std::boolalpha << read_partial_begin_block << std::endl;
	std::cout << "  block:                0x" << std::hex << partial_begin_block << std::endl;
	std::cout << "  offset:               0x" << std::hex << partial_begin_block_offset << std::endl;
	std::cout << "  size:                 0x" << std::hex << partial_begin_block_size << std::endl;

	std::cout << "partial_end:" << std::endl;
	std::cout << "  read_block:           " << std::boolalpha << read_partial_end_block << std::endl;
	std::cout << "  block:                0x" << std::hex << partial_end_block << std::endl;
	std::cout << "  offset:               0x" << std::hex << partial_end_block_offset << std::endl;
	std::cout << "  size:                 0x" << std::hex << partial_end_block_size << std::endl;

	std::cout << "continuous:" << std::endl;
	std::cout << "  block:                0x" << std::hex << continuous_begin_block << std::endl;
	std::cout << "  block_num:            0x" << std::hex << continuous_block_num << std::endl;
	*/

	if (block_num == 0)
	{
		tc::InvalidOperationException(mModuleLabel+"::read()", "Invalid block number (0 blocks, would have returned before now if count==0)");
	}

	if (block_num < continuous_block_num)
	{
		tc::InvalidOperationException(mModuleLabel+"::read()", "Invalid block number (underflow error)");
	}

	// allocate memory for partial block
	tc::ByteData partial_block = tc::ByteData(sizeof(block_t));

	// read un-aligned begin block
	if (read_partial_begin_block)
	{
		// read iv	
		iv_t iv;
		if (partial_begin_block == 0)
		{
			iv = mIv;
		}
		else
		{
			this->seek(blockToOffset(partial_begin_block-1), tc::io::SeekOrigin::Begin);
			mBaseStream->read(iv.data(), iv.size());
		}
		
		// read block
		this->seek(blockToOffset(partial_begin_block), tc::io::SeekOrigin::Begin);
		mBaseStream->read(partial_block.data(), partial_block.size());
		
		// decrypt block
		tc::crypto::DecryptAes128Cbc(partial_block.data(), partial_block.data(), partial_block.size(), mKey.data(), mKey.size(), iv.data(), iv.size());

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_begin_block_offset, partial_begin_block_size);

		// increment data read count
		data_read_count += partial_begin_block_size;
	}

	// read continous blocks
	if (continuous_block_num > 0)
	{
		// read iv	
		iv_t iv;
		if (continuous_begin_block == 0)
		{
			iv = mIv;
		}
		else
		{
			this->seek(blockToOffset(continuous_begin_block-1), tc::io::SeekOrigin::Begin);
			mBaseStream->read(iv.data(), iv.size());
		}

		// read blocks
		this->seek(blockToOffset(continuous_begin_block), tc::io::SeekOrigin::Begin);
		mBaseStream->read(ptr + data_read_count, continuous_block_num * sizeof(block_t));
		
		// decrypt blocks
		tc::crypto::DecryptAes128Cbc(ptr + data_read_count, ptr + data_read_count, continuous_block_num * sizeof(block_t), mKey.data(), mKey.size(), iv.data(), iv.size());

		// increment data read count
		data_read_count += continuous_block_num * sizeof(block_t);
	}
	
	// read un-aligned end block
	if (read_partial_end_block)
	{
		// read iv	
		iv_t iv;
		if (partial_end_block == 0)
		{
			iv = mIv;
		}
		else
		{
			this->seek(blockToOffset(partial_end_block-1), tc::io::SeekOrigin::Begin);
			mBaseStream->read(iv.data(), iv.size());
		}

		// read block
		this->seek(blockToOffset(partial_end_block), tc::io::SeekOrigin::Begin);
		mBaseStream->read(partial_block.data(), partial_block.size());

		// decrypt block
		tc::crypto::DecryptAes128Cbc(partial_block.data(), partial_block.data(), partial_block.size(), mKey.data(), mKey.size(), iv.data(), iv.size());

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_end_block_offset, partial_end_block_size);

		// increment
		data_read_count += partial_end_block_size;
	}

	// restore expected logical position
	this->seek(begin_read_offset + tc::io::IOUtil::castSizeToInt64(data_read_count), tc::io::SeekOrigin::Begin);

	// return data read count
	return data_read_count;
}

size_t tc::crypto::Aes128CbcEncryptedStream::write(const byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::write()", "Failed to set stream position (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::write()", "write is not supported for Aes128CbcEncryptedStream");
}

int64_t tc::crypto::Aes128CbcEncryptedStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	return mBaseStream->seek(offset, origin);
}

void tc::crypto::Aes128CbcEncryptedStream::setLength(int64_t length)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for Aes128CbcEncryptedStream");
}

void tc::crypto::Aes128CbcEncryptedStream::flush()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mBaseStream->flush();
}

void tc::crypto::Aes128CbcEncryptedStream::dispose()
{
	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}	
}