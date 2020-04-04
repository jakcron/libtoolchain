#pragma once

#include <tc/io/ISink.h>
#include <tc/NotImplementedException.h>
#include <tc/ArgumentOutOfRangeException.h>

class SinkTestUtil
{
public:
	static void testSinkLength(tc::io::ISink& source, int64_t expected_len);
	
	class DummySinkBase : public tc::io::ISink
	{
	public:
		DummySinkBase() :
			DummySinkBase(0x10000000)
		{
		}

		DummySinkBase(int64_t length) :
			DummySinkBase(length, true)
		{
		}

		DummySinkBase(int64_t length, bool canSetLength)
		{
			init(length, canSetLength);
		}

		void init(int64_t length, bool canSetLength)
		{
			mCanSetLength = canSetLength;
			mLength = length;
		}

		int64_t length()
		{
			return mLength;
		}

		void setLength(int64_t length)
		{
			if (mCanSetLength == false)
				throw tc::NotImplementedException(kClassName, "setLength() is not implemented");
				
			mLength = length;
		}

		void pushData(const tc::ByteData& data, int64_t offset)
		{
			throw tc::NotImplementedException(kClassName, "pushData not implemented");
		}
	private:
		static const std::string kClassName;
		bool mCanSetLength;
		int64_t mLength;
	};
};
