#include <tc/Exception.h>
#include <iostream>

#include "io_PartitionedFileObject_TestClass.h"

const std::string io_PartitionedFileObject_TestClass::DummyFileBase::kClassName = "DummyFileBase";

void io_PartitionedFileObject_TestClass::runAllTests(void)
{
	std::cout << "[tc::io::PartitionedFileObject] START" << std::endl;
	testSize();
	testSeekPos();
	testRead();
	testWrite();
	std::cout << "[tc::io::PartitionedFileObject] END" << std::endl;
}

void io_PartitionedFileObject_TestClass::testSize()
{
	std::cout << "[tc::io::PartitionedFileObject] testSize : " << std::flush;
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{
			}
		};

		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox file
			tc::io::PartitionedFileObject sb_file(std::shared_ptr<DummyFile>(new DummyFile()), sandbox_offset, sandbox_size);

			if (sb_file.size() != sandbox_size)
			{
				throw tc::Exception("Unexpected file size");
			}


			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_PartitionedFileObject_TestClass::testSeekPos()
{
	std::cout << "[tc::io::PartitionedFileObject] testSeekPos : " << std::flush;
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			virtual void read(byte_t* data, size_t len)
			{
				if (this->pos() != (0x56 + 0x337))
				{
					throw tc::Exception("Real file file offset was not as expected");
				}
			}
		};

		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			DummyFile file;

			// get sandbox file
			tc::io::PartitionedFileObject sb_file(std::make_shared<DummyFile>(file), sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file.seek(offset_to_seek);

			if (sb_file.pos() != offset_to_seek)
			{
				throw tc::Exception("Was not able to seek as expected");
			}

			sb_file.read(nullptr, 0x20);

			if (sb_file.pos() != offset_to_seek + 0x20)
			{
				throw tc::Exception("Was not able to seek as expected");
			}



			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_PartitionedFileObject_TestClass::testRead()
{
	std::cout << "[tc::io::PartitionedFileObject] testRead : " << std::flush;
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			virtual void read(byte_t* data, size_t len)
			{
				if (data != (byte_t*)0xcafe)
				{
					throw tc::Exception("'data' pointer was passed to base IFileObject object not as expected");
				}

				if (len != 0xdeadbabe)
				{
					throw tc::Exception("'len' parameter was passed to base IFileObject object not as expected");
				}
			}
		};

		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox file
			tc::io::PartitionedFileObject sb_file(std::shared_ptr<DummyFile>(new DummyFile()), sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file.seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			sb_file.read(dummy_ptr, dummy_read_len);

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void io_PartitionedFileObject_TestClass::testWrite()
{
	std::cout << "[tc::io::PartitionedFileObject] testWrite : " << std::flush;
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			virtual void write(const byte_t* data, size_t len)
			{
				if (data != (const byte_t*)0xcafe)
				{
					throw tc::Exception("'data' pointer was passed to base IFileObject object not as expected");
				}

				if (len != 0xdeadbabe)
				{
					throw tc::Exception("'len' parameter was passed to base IFileObject object not as expected");
				}
			}
		};

		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox file
			tc::io::PartitionedFileObject sb_file(std::shared_ptr<DummyFile>(new DummyFile()), sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file.seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			sb_file.write(dummy_ptr, dummy_read_len);

			std::cout << "PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}