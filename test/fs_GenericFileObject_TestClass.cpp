#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include "fs_GenericFileObject_TestClass.h"

#include <tc/fs/GenericFileObject.h>

void fs_GenericFileObject_TestClass::runAllTests()
{
	test_DefaultConstructor_IsNull();
	test_GenericCopyConstructor();
	test_GenericMoveConstructor();
	test_CopyConstructor();
	test_MoveConstructor();
	test_CopyOperator();
	test_MoveOperator();
	test_Generic_Passthrough();
	test_Close();
}

void fs_GenericFileObject_TestClass::test_DefaultConstructor_IsNull()
{
	std::cout << "[tc::fs::GenericFileObject] test_DefaultConstructor_IsNull : ";
	try
	{
		bool threwException = false;
		tc::fs::GenericFileObject file;

		if (file.state().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("isNull() returned false on uninitialised GenericFileObject");
		}

		try {
			file.size();
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileObject::size()");
		}

		try {
			file.seek(0);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileObject::seek()");
		}

		try {
			file.pos();
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileObject::pos()");
		}

		try {
			file.read(nullptr, 0);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileObject::read()");
		}

		try {
			file.write(nullptr, 0);
		} catch(const tc::Exception&)
		{
			threwException = true;
		}
		if (threwException == false)
		{
			throw tc::Exception("Did not throw exception on null GenericFileObject::write()");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_GenericCopyConstructor()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_GenericCopyConstructor : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);

		if (file.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (file.size() != kTestVal)
		{
			throw tc::Exception("GenericFileObject::size() did not return expected value");
		}

		if (dummyfile.size() != kTestVal)
		{
			throw tc::Exception("Source FileObject didn't retain expected value when copied");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_GenericMoveConstructor()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_GenericMoveConstructor : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(std::move(dummyfile));

		if (file.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (file.size() != kTestVal)
		{
			throw tc::Exception("GenericFileObject::size() did not return expected value");
		}

		if (dummyfile.size() == kTestVal)
		{
			throw tc::Exception("Source FileObject did retain expected value when moved");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_CopyConstructor()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_CopyConstructor : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);
		tc::fs::GenericFileObject newfile(file);

		if (file.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (file.size() != kTestVal)
		{
			throw tc::Exception("Source GenericFileObject did not have expected state after it was copied");
		}

		if (newfile.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (newfile.size() != kTestVal)
		{
			throw tc::Exception("Destination GenericFileObject did not have expected state when it was move constructed");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_MoveConstructor()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_MoveConstructor : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);
		tc::fs::GenericFileObject newfile(std::move(file));

		if (file.state().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("Source GenericFileObject was not null when it should have moved");
		}

		if (newfile.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (newfile.size() != kTestVal)
		{
			throw tc::Exception("Destination GenericFileObject did not have expected state when it was move constructed");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_CopyOperator()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_CopyOperator : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);
		tc::fs::GenericFileObject newfile;
		newfile = file;

		if (file.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (file.size() != kTestVal)
		{
			throw tc::Exception("Source GenericFileObject did not have expected state after it was copied");
		}

		if (newfile.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (newfile.size() != kTestVal)
		{
			throw tc::Exception("Destination GenericFileObject did not have expected state when it was move constructed");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_MoveOperator()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_MoveOperator : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);
		tc::fs::GenericFileObject newfile;
		newfile = std::move(file);

		if (file.state().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("Source GenericFileObject was not null when it should have moved");
		}

		if (newfile.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (newfile.size() != kTestVal)
		{
			throw tc::Exception("Destination GenericFileObject did not have expected state when it was move constructed");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_Generic_Passthrough()
{
	static const uint64_t kExpectedSizeRet = 1337;
	static const uint64_t kExpectedSeekVal = 1338;
	static const uint64_t kExpectedPosRet = 1339;
	static const byte_t* kExpectedReadPtr =  (const byte_t*)0xdeadbabe;
	static const size_t kExpectedReadLen = 1340;
	static const byte_t* kExpectedWritePtr =  (const byte_t*)0xcafebeef;
	static const size_t kExpectedWriteLen = 1340;


	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile()
		{
			init();
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			return new DummyFile(*this);
		}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		void init()
		{
			close();
			mState.set(tc::RESFLAG_READY);
		}

		virtual void close()
		{
			mState = 0;
		}

		virtual uint64_t size()
		{
			return kExpectedSizeRet;
		}
		
		virtual void seek(uint64_t offset)
		{
			if (offset != kExpectedSeekVal)
				throw tc::Exception("GenericFileObject passthrough failed for seek()");
		}

		virtual uint64_t pos()
		{
			return kExpectedPosRet;
		}

		virtual void read(byte_t* data, size_t len)
		{
			if (data != kExpectedReadPtr || len != kExpectedReadLen)
				throw tc::Exception("GenericFileObject passthrough failed for read()");
		}

		virtual void write(const byte_t* data, size_t len)
		{
			if (data != kExpectedWritePtr || len != kExpectedWriteLen)
				throw tc::Exception("GenericFileObject passthrough failed for write()");
		}
	private:
		tc::ResourceState mState;
	};

	std::cout << "[tc::fs::GenericFileObject] test_Generic_Passthrough : ";
	try
	{
		tc::fs::GenericFileObject file(std::move(DummyFile()));

		if (file.size() != kExpectedSizeRet)
		{
			throw tc::Exception("GenericFileObject passthrough failed for size()");
		}

		file.seek(kExpectedSeekVal);

		if (file.pos() != kExpectedPosRet)
		{
			throw tc::Exception("GenericFileObject passthrough failed for size()");
		}

		file.read((byte_t*)kExpectedReadPtr, kExpectedReadLen);

		file.write((byte_t*)kExpectedWritePtr, kExpectedWriteLen);

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}

void fs_GenericFileObject_TestClass::test_Close()
{
	class DummyFile : public DummyFileBase
	{
	public:
		DummyFile() : mState(1 << tc::RESFLAG_READY), mSize(0) {}

		virtual tc::ResourceState state()
		{
			return mState;
		}

		virtual void close()
		{
			mState = 0;
		}

		void setSize(uint64_t size)
		{
			mSize = size;
		}

		virtual uint64_t size()
		{
			return mSize;
		}

		virtual tc::fs::IFileObject* copyInstance() const
		{
			return new DummyFile(*this);
		}

		virtual tc::fs::IFileObject* moveInstance()
		{
			tc::fs::IFileObject* obj = new DummyFile(*this);
			mState = 0;
			mSize = 0;
			return obj;
		}
	private:
		tc::ResourceState mState;
		uint64_t mSize;
	};

	std::cout << "[tc::fs::GenericFileObject] test_Close : ";
	try
	{
		static const uint64_t kTestVal = 1337;
		DummyFile dummyfile;

		dummyfile.setSize(kTestVal);

		tc::fs::GenericFileObject file(dummyfile);

		if (file.state().test(tc::RESFLAG_READY) == false)
		{
			throw tc::Exception("isNull() returned true on initialised GenericFileObject");
		}

		if (file.size() != kTestVal)
		{
			throw tc::Exception("Source GenericFileObject did not have expected state after it was copied");
		}

		file.close();

		if (file.state().test(tc::RESFLAG_READY) == true)
		{
			throw tc::Exception("isNull() returned false on initialised GenericFileObject");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const tc::Exception& e)
	{
		std::cout << "FAIL (" << e.error() << ")" << std::endl;
	}
}