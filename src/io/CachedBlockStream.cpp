#include <tc/io/CachedBlockStream.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <tc/cli/FormatUtil.h>

tc::io::CachedBlockStream::CachedBlockStream() :
	mModuleLabel("tc::io::CachedBlockStream"),
	mLogicalPosition(0),
	mBaseStream(),
	mBlockSize(0),
	mBlockNum(0),
	mBlockCache()
{
}

tc::io::CachedBlockStream::CachedBlockStream(const std::shared_ptr<tc::io::IStream>& stream, size_t block_size, size_t block_num) :
	CachedBlockStream()
{
	mBaseStream = stream;
	mBlockSize = block_size;
	mBlockNum = block_num;

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
}

bool tc::io::CachedBlockStream::canRead() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canRead();
}

bool tc::io::CachedBlockStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool tc::io::CachedBlockStream::canSeek() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canSeek();
}

int64_t tc::io::CachedBlockStream::length()
{
	return mBaseStream == nullptr ? 0 : mBaseStream->length();
}

int64_t tc::io::CachedBlockStream::position()
{
	return mBaseStream == nullptr ? 0 : mLogicalPosition;
}

size_t tc::io::CachedBlockStream::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}

	// get limited count
	count = tc::io::IOUtil::getReadableCount(mBaseStream->length(), mLogicalPosition, count);

	// read from blocks
	size_t begin_blk = size_t(mLogicalPosition / int64_t(mBlockSize));
	size_t begin_blk_offset = size_t(mLogicalPosition % int64_t(mBlockSize));
	size_t end_blk = size_t((mLogicalPosition + int64_t(count)) / int64_t(mBlockSize));
	size_t end_blk_offset = size_t((mLogicalPosition + int64_t(count)) % int64_t(mBlockSize));
	size_t total_data_read = 0;

	// consider offset=0x1200, readsize=0x300
	for (size_t blk = begin_blk, blk_offset, blk_read; blk <= end_blk && total_data_read < count; blk++, total_data_read += blk_read)
	{
		// standard block read, size=block size, offset=0(begin of block)
		blk_read = mBlockSize; // 0x1000
		blk_offset = 0; // reset blk_offset

		// adjust if this is the begin block
		if (blk == begin_blk)
		{
			// if the block is begin blk then we read from the begin blk offset to end of block
			blk_read -= begin_blk_offset; // 0x1000 - 0x200 = 0xe00
			blk_offset = begin_blk_offset;
		}
		// adjust if this is the end block
		if (blk == end_blk)
		{
			// if this is the end block
			blk_read -= (mBlockSize - end_blk_offset); // 0xe00 - (0x1000 - 0x500) = 0xe00 - 0xb00 = 0x300
		}
		
		readFromBlock(ptr + total_data_read, blk, blk_offset, blk_read);
	}

	mLogicalPosition += int64_t(total_data_read);

	return total_data_read;
}

size_t tc::io::CachedBlockStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(mModuleLabel+"::write()", "write is not supported for CachedBlockStream");
}

int64_t tc::io::CachedBlockStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	//std::cout << "CachedBlockStream::seek() calls length() -> " << mBaseStream->length() << std::endl;

	mLogicalPosition = tc::io::StreamUtil::getSeekResult(offset, origin, mLogicalPosition, mBaseStream->length());

	if (mLogicalPosition < 0)
	{
		throw tc::InvalidOperationException(mModuleLabel+"::seek()", "Negative seek result determined");
	}

	return mLogicalPosition;
}

void tc::io::CachedBlockStream::setLength(int64_t length)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for CachedBlockStream");
}

void tc::io::CachedBlockStream::flush()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mBaseStream->flush();
	mBlockCache.clear();
}

void tc::io::CachedBlockStream::dispose()
{
	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}
	
	// clear cache
	mBlockSize = 0;
	mBlockNum = 0;
	mBlockCache.clear();
}

void tc::io::CachedBlockStream::readFromBlock(byte_t* data, size_t block_index, size_t offset, size_t size)
{
	// return if read size 0
	if (size == 0) return;
	
	// try the block cache
	bool cache_hit = false;
	for (auto itr = mBlockCache.begin(); itr != mBlockCache.end() && cache_hit == false; itr++)
	{
		if (itr->block_idx == block_index)
		{
			memcpy(data, itr->cache.data() + offset, size);
			cache_hit = true;
		}
	}

	// on cache miss: import the block
	if (cache_hit == false)
	{
		// remove last one if the cache is too large
		if (mBlockCache.size() >= mBlockNum)
			mBlockCache.pop_back();		

		// create new cache
		BlockCache cache;
		cache.block_idx = block_index;
		cache.cache = tc::ByteData(mBlockSize);
		mBaseStream->seek(int64_t(block_index * mBlockSize), tc::io::SeekOrigin::Begin);
		size_t read_len = mBaseStream->read(cache.cache.data(), cache.cache.size());
		if (read_len != cache.cache.size())
		{
			throw tc::io::IOException(mModuleLabel+"::readFromBlock()", "Failed to read block from base source.");
		}

		// add block to cache
		mBlockCache.push_front(cache);

		// try again recursive
		readFromBlock(data, block_index, offset, size);
	}
}