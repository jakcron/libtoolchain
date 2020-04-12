#include <tc/Exception.h>
#include <iostream>
#include <sstream>

#include "ByteData_TestClass.h"

//---------------------------------------------------------

void ByteData_TestClass::runAllTests(void)
{
	std::cout << "[tc::ByteData] START" << std::endl;
	test_Constructor_DefaultConstructor();
	test_Constructor_InitializerList();
	test_Constructor_CreateZeroSized();
	test_Constructor_CreateSmallSized();
	test_Constructor_CreateLargeSized();
	test_Constructor_ThrowExceptForBadAlloc();
	test_Constructor_CreateFromPtr();
	test_ImplicitCopy_CopyInSameScope();
	test_ImplicitCopy_CopyOntoInitiallisedByteData();
	test_ImplicitMove_CopyInSameScope();
	test_ImplicitMove_MoveOntoInitiallisedByteData();
	std::cout << "[tc::ByteData] END" << std::endl;
}

//---------------------------------------------------------

void ByteData_TestClass::test_Constructor_DefaultConstructor()
{
	std::cout << "[tc::ByteData] test_Constructor_DefaultConstructor : " << std::flush;
	try
	{
		try 
		{
			tc::ByteData data;

			if (data.get() != nullptr)
			{
				throw tc::Exception(".get() did not return nullptr when ByteData was constructed with default constructor");
			}

			if (data.size() != 0)
			{
				throw tc::Exception(".size() did not return 0 when ByteData was constructed with default constructor");
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

void ByteData_TestClass::test_Constructor_CreateZeroSized()
{
	std::cout << "[tc::ByteData] test_Constructor_CreateZeroSized : " << std::flush;
	try
	{
		try 
		{
			tc::ByteData data(0);

			if (data.get() != nullptr)
			{
				throw tc::Exception(".get() did not return nullptr when ByteData was constructed with size 0");
			}

			if (data.size() != 0)
			{
				throw tc::Exception(".size() did not return 0 when ByteData was constructed with size 0");
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

void ByteData_TestClass::test_Constructor_InitializerList()
{
	std::cout << "[tc::ByteData] test_Constructor_InitializerList : " << std::flush;
	try
	{
		try 
		{
			static const size_t expected_data_size = 0x10;
			byte_t expected_data[expected_data_size] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
			tc::ByteData data({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f});

			if (data.get() == nullptr)
			{
				throw tc::Exception(".get() returned nullptr when ByteData was constructed with an initializer list");
			}

			if (data.size() != expected_data_size)
			{
				throw tc::Exception(".size() did not return 0 when ByteData was constructed with an initializer list");
			}

			if (memcmp(data.get(), expected_data, expected_data_size) != 0)
			{
				throw tc::Exception(".get() did not contain expected data");	
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

void ByteData_TestClass::test_Constructor_CreateSmallSized()
{
	std::cout << "[tc::ByteData] test_Constructor_CreateSmallSized : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 1271;
			tc::ByteData data(data_size);

			if (data.get() == nullptr)
			{
				error_ss << ".get() returned nullptr when ByteData was constructed with size " << data_size;
				throw tc::Exception(error_ss.str());
			}

			if (data.size() != data_size)
			{
				error_ss << ".size() did not return " << data_size << " when ByteData was constructed with size " << data_size;
				throw tc::Exception(error_ss.str());
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

void ByteData_TestClass::test_Constructor_CreateLargeSized()
{
	std::cout << "[tc::ByteData] test_Constructor_CreateLargeSized : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 0x1000000;
			tc::ByteData data(data_size);

			if (data.get() == nullptr)
			{
				error_ss << ".get() returned nullptr when ByteData was constructed with size " << data_size;
				throw tc::Exception(error_ss.str());
			}

			if (data.size() != data_size)
			{
				error_ss << ".size() did not return " << data_size << " when ByteData was constructed with size " << data_size;
				throw tc::Exception(error_ss.str());
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

void ByteData_TestClass::test_Constructor_ThrowExceptForBadAlloc()
{
	std::cout << "[tc::ByteData] test_Constructor_ThrowExceptForBadAlloc : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = -1;
			tc::ByteData data(data_size);

			std::cout << "FAIL (Did not throw exception where it should be impossible to allocate the memory)" << std::endl;
		}
		catch (const tc::Exception& e)
		{
			std::cout << "PASS (" << e.error() << ")" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "UNHANDLED EXCEPTION (" << e.what() << ")" << std::endl;
	}
}

void ByteData_TestClass::test_Constructor_CreateFromPtr()
{
	std::cout << "[tc::ByteData] test_Constructor_CreateFromPtr : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t src_data_size = 0x1000;
			tc::ByteData src_data(src_data_size);
			memset(src_data.get(), 0xe0, src_data.size());

			tc::ByteData data(src_data.get(), src_data.size());


			if (data.get() == nullptr)
			{
				error_ss << ".get() returned nullptr when ByteData was constructed with size " << src_data_size;
				throw tc::Exception(error_ss.str());
			}

			if (data.size() != src_data_size)
			{
				error_ss << ".size() did not return " << src_data_size << " when ByteData was constructed with size " << src_data_size;
				throw tc::Exception(error_ss.str());
			}

			if (memcmp(data.get(), src_data.get(), src_data_size) != 0)
			{
				error_ss << ".get() did not have expected contents, when compared to source data";
				throw tc::Exception(error_ss.str());
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

void ByteData_TestClass::test_ImplicitCopy_CopyInSameScope()
{
	std::cout << "[tc::ByteData] test_ImplicitCopy_CopyInSameScope : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 0x20;

			// create data with allocating constructor
			tc::ByteData data(data_size);

			// create data2 as a copy of data using implicit copy constructor
			tc::ByteData data2(data);

			if (data.size() != data2.size())
			{
				throw tc::Exception("data2 after being constructed by copy, did not have the same size");
			}

			if (data.get() == data2.get())
			{
				throw tc::Exception("data2 after being constructed by copy, had the same pointer");
			}

			tc::ByteData data3 = data;

			if (data.size() != data3.size())
			{
				throw tc::Exception("data3 after being constructed by copy assignment, did not have the same size");
			}

			if (data.get() == data3.get())
			{
				throw tc::Exception("data3 after being constructed by copy assignment, had the same pointer");
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

void ByteData_TestClass::test_ImplicitCopy_CopyOntoInitiallisedByteData()
{
	std::cout << "[tc::ByteData] test_ImplicitCopy_CopyOntoInitiallisedByteData : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 0x20;
			const size_t data2_size = 0x30;

			// create data with allocating constructor
			tc::ByteData data(data_size);

			// create data2 with allocating constructor
			tc::ByteData data2(data2_size);

			data2 = data;

			if (data.size() != data2.size())
			{
				throw tc::Exception("data2 after being assigned by copy, did not have the same size");
			}

			if (data.get() == data2.get())
			{
				throw tc::Exception("data2 after being assigned by copy, had the same pointer");
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

void ByteData_TestClass::test_ImplicitMove_CopyInSameScope()
{
	std::cout << "[tc::ByteData] test_ImplicitMove_CopyInSameScope : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 0x20;

			// create data with allocating constructor
			tc::ByteData data(data_size);
			// mark buffer[0] so we can see if buffer ptr is being moved properly
			data.get()[0] = 0xff;

			// create data2 as a copy of data using implicit move constructor
			tc::ByteData data2(std::move(data));

			if (data2.get()[0] != 0xff)
			{
				throw tc::Exception("data2 did not have expected byte at buffer()[0]");
			}

			if (data.get() != nullptr)
			{
				throw tc::Exception("data after being moved to data2 retained it's old pointer");
			}

			if (data.size() == data2.size())
			{
				throw tc::Exception("data2 after being constructed by move from data, had the same size");
			}

			tc::ByteData data3 = std::move(data2);

			if (data3.get()[0] != 0xff)
			{
				throw tc::Exception("data3 did not have expected byte at buffer()[0]");
			}

			if (data2.get() != nullptr)
			{
				throw tc::Exception("data2 after being moved to data3 retained it's old pointer");
			}

			if (data.size() == data3.size())
			{
				throw tc::Exception("data3 after being constructed by move assignment from data2, has the same size");
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

void ByteData_TestClass::test_ImplicitMove_MoveOntoInitiallisedByteData()
{
	std::cout << "[tc::ByteData] test_ImplicitCopy_CopyOntoInitiallisedByteData : " << std::flush;
	try
	{
		try 
		{
			std::stringstream error_ss;
			const size_t data_size = 0x20;
			const size_t data2_size = 0x30;

			// create data with allocating constructor
			tc::ByteData data(data_size);
			// mark buffer[0] so we can see if buffer ptr is being copied properly
			data.get()[0] = 0xff;

			// create data2 with allocating constructor
			tc::ByteData data2(data2_size);

			// move data to data2 by assignment
			data2 = std::move(data);

			if (data.get() != nullptr)
			{
				throw tc::Exception("data after being moved to data2 retained it's old pointer");
			}

			if (data.size() == data2.size())
			{
				throw tc::Exception("data2 after being assigned by copy, did not have the same size");
			}

			if (data.size() == data2.size())
			{
				throw tc::Exception("data2 after being constructed by move from data, had the same size");
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