#include <tc/crypto/Aes128CtrEncryptedStream.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <tc/cli/FormatUtil.h>

tc::crypto::Aes128CtrEncryptedStream::Aes128CtrEncryptedStream() :
	mModuleLabel("tc::crypto::Aes128CtrEncryptedStream"),
	mBaseStream(),
	mCryptorRange()
{
}

tc::crypto::Aes128CtrEncryptedStream::Aes128CtrEncryptedStream(const std::shared_ptr<tc::io::IStream>& stream, const key_t& key, const counter_t& counter) :
	Aes128CtrEncryptedStream(stream, {{key, counter, 0, -1}})
{
}

tc::crypto::Aes128CtrEncryptedStream::Aes128CtrEncryptedStream(const std::shared_ptr<tc::io::IStream>& stream, const std::vector<KeyConfig>& key_cfg) :
	Aes128CtrEncryptedStream()
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

	// import keys
	CryptorRange range;
	for (auto itr = key_cfg.begin(); itr != key_cfg.end(); itr++)
	{
		range.cryptor = std::shared_ptr<tc::crypto::Aes128CtrEncryptor>(new tc::crypto::Aes128CtrEncryptor());
		range.cryptor->initialize(itr->key.data(), itr->key.size(), itr->counter.data(), itr->counter.size());
		range.begin_block = uint64_t(itr->begin_offset) / uint64_t(sizeof(block_t));
		if (itr->end_offset == -1)
			range.end_block = uint64_t(mBaseStream->length()) / uint64_t(sizeof(block_t));
		else
			range.end_block = uint64_t(itr->end_offset) / uint64_t(sizeof(block_t));

		mCryptorRange.push_back(std::move(range));
	}

	/*
	std::cout << "[Aes128CtrEncryptedStream]" << std::endl;
	std::cout << " Length: 0x" << std::hex << mBaseStream->length() << std::endl;
	for (auto itr = mCryptorRange.begin(); itr != mCryptorRange.end(); itr++)
	{
		std::cout << " CryptoRange:" << std::endl;
		std::cout << "   BeginBlock: 0x" << itr->begin_block;
		std::cout << " (offset: 0x" << itr->begin_block * 0x10 << ")" << std::endl;
		std::cout << "   EndBlock: 0x" << itr->end_block;
		std::cout << " (offset: 0x" << itr->end_block * 0x10 << ")" << std::endl;
	}
	*/
}

bool tc::crypto::Aes128CtrEncryptedStream::canRead() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canRead();
}

bool tc::crypto::Aes128CtrEncryptedStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool tc::crypto::Aes128CtrEncryptedStream::canSeek() const
{
	return mBaseStream == nullptr ? false : mBaseStream->canSeek();
}

int64_t tc::crypto::Aes128CtrEncryptedStream::length()
{
	return mBaseStream == nullptr ? 0 : mBaseStream->length();
}

int64_t tc::crypto::Aes128CtrEncryptedStream::position()
{
	return mBaseStream == nullptr ? 0 : mBaseStream->position();
}

size_t tc::crypto::Aes128CtrEncryptedStream::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(mBaseStream->length(), mBaseStream->position(), count);
	
	if (count == 0) return 0;

	// get current position
	int64_t current_pos = mBaseStream->position();
	if (current_pos < 0)
	{
		throw tc::InvalidOperationException(mModuleLabel+"::read()", "Current stream position is negative.");
	}

	//std::cout << "current pos 0x" << std::hex << current_pos << std::endl;

	// determine begin point (begin point can be a partital block)
	uint64_t begin_block = uint64_t(current_pos) / uint64_t(sizeof(block_t));
	//int64_t begin_block_offset = int64_t(begin_block) * int64_t(sizeof(block_t));
	size_t begin_block_read_offset = size_t(uint64_t(current_pos) % uint64_t(sizeof(block_t)));
	size_t begin_block_read_size = sizeof(block_t) - begin_block_read_offset;
	bool has_partial_begin_block = begin_block_read_offset > 0;

	// determine end point
	uint64_t end_block = uint64_t(current_pos + int64_t(count)) / uint64_t(sizeof(block_t));
	//int64_t end_block_offset = int64_t(end_block) * int64_t(sizeof(block_t));
	size_t end_block_read_offset = 0;
	size_t end_block_read_size = size_t(uint64_t(current_pos + int64_t(count)) % uint64_t(sizeof(block_t)));
	bool has_partial_end_block = end_block_read_size > 0;

	// middle continuous section
	uint64_t middle_section_block = has_partial_begin_block ? begin_block+1 : begin_block;
	//int64_t middle_section_block_offset = int64_t(middle_section_block) * int64_t(sizeof(block_t));
	size_t middle_section_read_size = count - (has_partial_begin_block ? begin_block_read_size : 0) - (has_partial_end_block ? end_block_read_size : 0);

	// begin decryption
	size_t total_read_count = 0;
	//size_t read_count = 0;
	block_t partial_block;
	//mBaseStream->seek(begin_block_offset, tc::io::SeekOrigin::Begin);

	// if partial begin block
	if (has_partial_begin_block)
	{
		//std::cout << "Partial Begin Block" << std::endl;
		//mBaseStream->seek(begin_block_offset, tc::io::SeekOrigin::Begin);
		/*
		read_count = mBaseStream->read(partial_block.data() + begin_block_read_offset, begin_block_read_size);
		if (read_count != begin_block_read_size)
		{
			std::cout << "begin_block_read_size, partial block read failure" << std::endl;
		}
		*/
		
		mBaseStream->read(partial_block.data() + begin_block_read_offset, begin_block_read_size);
		decrypt(partial_block.data(), partial_block.data(), partial_block.size(), begin_block);
		memcpy(ptr + total_read_count, partial_block.data() + begin_block_read_offset, begin_block_read_size);
		total_read_count += begin_block_read_size;
	}

	// middle continious section
	//std::cout << "Contiguous blocks" << std::endl;
	//mBaseStream->seek(middle_section_block_offset, tc::io::SeekOrigin::Begin);
	/*
	read_count = mBaseStream->read(ptr, middle_section_read_size);
	if (read_count != middle_section_read_size)
	{
		std::cout << "middle_section_read_size, block(s) read failure" << std::endl;
	}
	*/
	mBaseStream->read(ptr, middle_section_read_size);
	decrypt(ptr + total_read_count, ptr + total_read_count, middle_section_read_size, middle_section_block);
	total_read_count += middle_section_read_size;

	// if partial end block
	if (has_partial_end_block)
	{
		//std::cout << "Partial Begin Block" << std::endl;
		//mBaseStream->seek(end_block_offset, tc::io::SeekOrigin::Begin);
		/*
		read_count = mBaseStream->read(partial_block.data() + end_block_read_offset, end_block_read_size);
		if (read_count != end_block_read_size)
		{
			std::cout << "end_block_read_size, partial block read failure" << std::endl;
		}
		*/
		mBaseStream->read(partial_block.data() + end_block_read_offset, end_block_read_size);
		decrypt(partial_block.data(), partial_block.data(), partial_block.size(), end_block);
		memcpy(ptr + total_read_count, partial_block.data() + end_block_read_offset, end_block_read_size);
		total_read_count += end_block_read_size;
	}

	//mBaseStream->seek(current_pos + total_read_count, tc::io::SeekOrigin::Begin);

	return total_read_count;
}

size_t tc::crypto::Aes128CtrEncryptedStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(mModuleLabel+"::write()", "write is not supported for Aes128CtrEncryptedStream");
}

int64_t tc::crypto::Aes128CtrEncryptedStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	return mBaseStream->seek(offset, origin);
}

void tc::crypto::Aes128CtrEncryptedStream::setLength(int64_t length)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for Aes128CtrEncryptedStream");
}

void tc::crypto::Aes128CtrEncryptedStream::flush()
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mBaseStream->flush();
}

void tc::crypto::Aes128CtrEncryptedStream::dispose()
{
	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}
	
	mCryptorRange.clear();
}

void tc::crypto::Aes128CtrEncryptedStream::decrypt(byte_t* dst, const byte_t* src, size_t size, uint64_t block_number)
{
	// decrypt data iterating thru the cryptor ranges
	uint64_t cur_block = block_number;
	size_t cryptor_decrypted_data = 0;
	for (size_t decrypted_count = 0; decrypted_count < size; decrypted_count += cryptor_decrypted_data)
	{
		for (auto itr = mCryptorRange.begin(); itr != mCryptorRange.end(); itr++)
		{
			if (cur_block >= itr->begin_block && cur_block < itr->end_block)
			{
				size_t range_remaining = sizeof(block_t) * size_t(itr->end_block - cur_block);
				size_t encrypted_remaining = size - decrypted_count;

				cryptor_decrypted_data = std::min<size_t>(encrypted_remaining, range_remaining);
				
				if (cryptor_decrypted_data > 0)
					itr->cryptor->decrypt(dst + decrypted_count, src + decrypted_count, cryptor_decrypted_data, (cur_block - itr->begin_block));

				cur_block += cryptor_decrypted_data / sizeof(block_t);
				break;
			}
		}

		// cryptor_decrypted_data will be 0 if no cryptor range was selected
		if (cryptor_decrypted_data == 0)
		{
			throw tc::InvalidOperationException(mModuleLabel+"::decrypt()", "Could not determine cryptor for data read.");
		}
	}
}