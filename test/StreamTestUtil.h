#pragma once

#include <tc/io/IStream.h>
#include <tc/NotImplementedException.h>
#include <tc/ArgumentOutOfRangeException.h>

class StreamTestUtil
{
public:
	class DummyStreamBase : public tc::io::IStream
	{
	public:
		DummyStreamBase() :
			DummyStreamBase(0x10000000)
		{
		}

		DummyStreamBase(int64_t length) :
			DummyStreamBase(length, true, true, true, true)
		{
		}

		DummyStreamBase(int64_t length, bool canRead, bool canWrite, bool canSeek, bool canSeekOnlyFromBegin)
		{
			init(length, canRead, canWrite, canSeek, canSeekOnlyFromBegin);
		}

		void init(int64_t length, bool canRead, bool canWrite, bool canSeek, bool canSeekOnlyFromBegin)
		{
			mCanRead = canRead;
			mCanWrite = canWrite;
			mCanSeek = canSeek;
			mCanSeekOnlyFromBegin = canSeekOnlyFromBegin;
			mPosition = 0;
			mLength = length;
		}

		bool canRead() const
		{
			return mCanRead;
		}

		bool canWrite() const
		{
			return mCanWrite;
		}

		bool canSeek() const
		{
			return mCanSeek;
		}

		int64_t length()
		{
			return mLength;
		}

		int64_t position()
		{
			return mPosition;
		}

		virtual size_t read(byte_t* buffer, size_t count)
		{
			throw tc::NotImplementedException(kClassName, "read() not implemented");
		}

		virtual void write(const byte_t* buffer, size_t count)
		{
			throw tc::NotImplementedException(kClassName, "write() not implemented");
		}

		int64_t seek(int64_t offset, tc::io::SeekOrigin origin)
		{
			if (origin != tc::io::SeekOrigin::Begin && mCanSeekOnlyFromBegin)
				throw tc::ArgumentOutOfRangeException(kClassName, "Should not be passing seek origin values that are not SeekOrigin::Begin to the base stream");
			
			switch (origin)
			{
			case (tc::io::SeekOrigin::Begin):
				mPosition = offset;
				break;
			case (tc::io::SeekOrigin::Current):
				mPosition += offset;
				break;
			case (tc::io::SeekOrigin::End):
				mPosition = mLength + offset;
				break;
			default:
				throw tc::ArgumentOutOfRangeException(kClassName, "Illegal seek origin"); 
			}

			if (mPosition > mLength)
			{
				throw tc::ArgumentOutOfRangeException(kClassName, "Illegal seek position"); 
			}

			return mPosition;
		}

		void setLength(int64_t length)
		{
			mLength = length;
		}

		void flush()
		{
			// nothing
		}

		void dispose()
		{
			flush();
			mCanRead = false;
			mCanWrite = false;
			mCanSeek = false;
			mPosition = 0;
			mLength = 0;
		}
	private:
		static const std::string kClassName;
		bool mCanRead;
		bool mCanWrite;
		bool mCanSeek;
		bool mCanSeekOnlyFromBegin;
		int64_t mPosition;
		int64_t mLength;
	};
	
};