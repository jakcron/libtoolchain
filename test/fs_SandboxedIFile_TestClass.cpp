#include <tc/Exception.h>
#include <iostream>

#include "fs_SandboxedIFile_TestClass.h"

void fs_SandboxedIFile_TestClass::testSize()
{
	std::cout << "[tc::fs::SandboxedIFile] testSize : ";
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
			tc::SharedPtr<tc::fs::IFile> file = new DummyFile();

			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFile> sb_file = new tc::fs::SandboxedIFile(file, sandbox_offset, sandbox_size);

			if (sb_file->size() != sandbox_size)
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

void fs_SandboxedIFile_TestClass::testSeekPos()
{
	std::cout << "[tc::fs::SandboxedIFile] testSeekPos : ";
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			void read(byte_t* data, size_t len)
			{
				if (this->pos() != (0x56 + 0x337))
				{
					throw tc::Exception("Real file file offset was not as expected");
				}
			}
		};

		try
		{
			tc::SharedPtr<tc::fs::IFile> file = new DummyFile();

			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFile> sb_file = new tc::fs::SandboxedIFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file->seek(offset_to_seek);

			if (sb_file->pos() != offset_to_seek)
			{
				throw tc::Exception("Was not able to seek as expected");
			}

			sb_file->read(nullptr, 0x20);

			if (sb_file->pos() != offset_to_seek + 0x20)
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

void fs_SandboxedIFile_TestClass::testRead()
{
	std::cout << "[tc::fs::SandboxedIFile] testRead : ";
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			void read(byte_t* data, size_t len)
			{
				if (data != (byte_t*)0xcafe)
				{
					throw tc::Exception("'data' pointer was passed to base IFile object not as expected");
				}

				if (len != 0xdeadbabe)
				{
					throw tc::Exception("'len' parameter was passed to base IFile object not as expected");
				}
			}
		};

		try
		{
			tc::SharedPtr<tc::fs::IFile> file = new DummyFile();

			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFile> sb_file = new tc::fs::SandboxedIFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file->seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			sb_file->read(dummy_ptr, dummy_read_len);

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

void fs_SandboxedIFile_TestClass::testWrite()
{
	std::cout << "[tc::fs::SandboxedIFile] testWrite : ";
	try
	{
		class DummyFile : public DummyFileBase
		{
		public:
			DummyFile()
			{

			}

			void write(const byte_t* data, size_t len)
			{
				if (data != (const byte_t*)0xcafe)
				{
					throw tc::Exception("'data' pointer was passed to base IFile object not as expected");
				}

				if (len != 0xdeadbabe)
				{
					throw tc::Exception("'len' parameter was passed to base IFile object not as expected");
				}
			}
		};

		try
		{
			tc::SharedPtr<tc::fs::IFile> file = new DummyFile();

			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::fs::IFile> sb_file = new tc::fs::SandboxedIFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			sb_file->seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			sb_file->write(dummy_ptr, dummy_read_len);

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

void fs_SandboxedIFile_TestClass::runAllTests(void)
{
	testSize();
	testSeekPos();
	testRead();
	testWrite();
}