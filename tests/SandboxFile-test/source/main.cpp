#include <tc/filesystem.h>
#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

class DummyFileBase : public tc::filesystem::IFile
{
public:
	DummyFileBase()
	{
	}

	void setSize(uint64_t size)
	{
		mSize = size;
	}

	uint64_t size()
	{
		return mSize;
	}
	
	void seek(uint64_t offset)
	{
		mOffset = offset;
	}

	uint64_t pos()
	{
		return mOffset;
	}

	void read(byte_t* data, size_t len)
	{
		throw tc::Exception(kClassName, "read() not implemented");
	}

	void write(const byte_t* data, size_t len)
	{
		throw tc::Exception(kClassName, "write() not implemented");
	}
private:
	const std::string kClassName = "DummyFileBase";
	uint64_t mOffset;
	uint64_t mSize;
};

void testSize()
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
		tc::SharedPtr<tc::filesystem::IFile> file = new DummyFile();
		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFile> sb_file = new tc::filesystem::SandboxFile(file, sandbox_offset, sandbox_size);

			if ((*sb_file)->size() != sandbox_size)
			{
				throw tc::Exception("main.cpp", "Unexpected file size");
			}


			std::cout << "[SandboxFile-test] testSize() : PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "[SandboxFile-test] testSize() : FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[SandboxFile-test] testSize() : UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testSeekPos()
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
		tc::SharedPtr<tc::filesystem::IFile> file = new DummyFile();
		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFile> sb_file = new tc::filesystem::SandboxFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			(*sb_file)->seek(offset_to_seek);

			if ((*sb_file)->pos() != offset_to_seek)
			{
				throw tc::Exception("main.cpp", "Was not able to seek as expected");
			}

			(*sb_file)->read(nullptr, 0x20);

			if ((*sb_file)->pos() != offset_to_seek + 0x20)
			{
				throw tc::Exception("main.cpp", "Was not able to seek as expected");
			}



			std::cout << "[SandboxFile-test] testSeekPos() : PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "[SandboxFile-test] testSeekPos() : FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[SandboxFile-test] testSeekPos() : UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testRead()
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
		tc::SharedPtr<tc::filesystem::IFile> file = new DummyFile();
		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFile> sb_file = new tc::filesystem::SandboxFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			(*sb_file)->seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			(*sb_file)->read(dummy_ptr, dummy_read_len);

			std::cout << "[SandboxFile-test] testRead() : PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "[SandboxFile-test] testRead() : FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[SandboxFile-test] testRead() : UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void testWrite()
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
		tc::SharedPtr<tc::filesystem::IFile> file = new DummyFile();
		try
		{
			uint64_t sandbox_offset = 0x56;
			uint64_t sandbox_size = 0x1000;

			// get sandbox filesystem
			tc::SharedPtr<tc::filesystem::IFile> sb_file = new tc::filesystem::SandboxFile(file, sandbox_offset, sandbox_size);

			uint64_t offset_to_seek = 0x337;
			(*sb_file)->seek(offset_to_seek);

			byte_t* dummy_ptr = (byte_t*)0xcafe;
			size_t dummy_read_len = 0xdeadbabe;

			(*sb_file)->write(dummy_ptr, dummy_read_len);

			std::cout << "[SandboxFile-test] testWrite() : PASS" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "[SandboxFile-test] testWrite() : FAIL (" << e.error() << ")" << std::endl;
		}
	}
	catch (const tc::Exception& e)
	{
		std::cout << "[SandboxFile-test] testWrite() : UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

int main(int argc, char** argv)
{
	testSize();
	testSeekPos();
	testRead();
	testWrite();
}