#pragma once
#include "ITestClass.h"

#include <tc/io.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/NotImplementedException.h>

class io_SubStream_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	class DummyStreamBase : public tc::io::IStream
	{
	public:
		DummyStreamBase() :
			DummyStreamBase(0x10000000)
		{
		}

		DummyStreamBase(int64_t length)
		{
			init(length);
		}

		void init(int64_t length)
		{
			mCanRead = true;
			mCanWrite = true;
			mCanSeek = true;
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
			if (origin != tc::io::SeekOrigin::Begin)
				throw tc::ArgumentOutOfRangeException(kClassName, "SubStream should not be passing seek origin values that are not SeekOrigin::Begin to the base stream");
			mPosition = offset;

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
		int64_t mPosition;
		int64_t mLength;
	};

	void testSize();
	void testSeekPos();
	void testRead();
	void testWrite();
};