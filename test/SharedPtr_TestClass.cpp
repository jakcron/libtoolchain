#include <tc/Exception.h>
#include <iostream>

#include "SharedPtr_TestClass.h"

void SharedPtr_TestClass::testDefaultConstructor()
{
	std::cout << "[tc::SharedPtr] testDefaultConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimPtrConstructor()
{
	std::cout << "[tc::SharedPtr] testPrimPtrConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimPtrAssignmentOperator()
{
	std::cout << "[tc::SharedPtr] testPrimPtrAssignmentOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo = new int;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimPtrCopyConstructor()
{
	std::cout << "[tc::SharedPtr] testPrimPtrCopyConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
			tc::SharedPtr<int> bar(foo);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimPtrCopyOperator()
{
	std::cout << "[tc::SharedPtr] testPrimPtrCopyOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
			tc::SharedPtr<int> bar = foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructPtrConstructor()
{
	std::cout << "[tc::SharedPtr] testStructPtrConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructPtrAssignmentOperator()
{
	std::cout << "[tc::SharedPtr] testStructPtrAssignmentOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo = new sFooStruct;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructPtrCopyConstructor()
{
	std::cout << "[tc::SharedPtr] testStructPtrCopyConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct);
			tc::SharedPtr<sFooStruct> bar(foo);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructPtrCopyOperator()
{
	std::cout << "[tc::SharedPtr] testStructPtrCopyOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct);
			tc::SharedPtr<sFooStruct> bar = foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}


void SharedPtr_TestClass::testPrimArrayPtrConstructor()
{
	std::cout << "[tc::SharedPtr] testPrimArrayPtrConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int[100]);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimArrayPtrAssignmentOperator()
{
	std::cout << "[tc::SharedPtr] testPrimArrayPtrAssignmentOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo = new int[100];
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimArrayPtrCopyConstructor()
{
	std::cout << "[tc::SharedPtr] testPrimArrayPtrCopyConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int[100]);
			tc::SharedPtr<int> bar(foo);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testPrimArrayPtrCopyOperator()
{
	std::cout << "[tc::SharedPtr] testPrimArrayPtrCopyOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int[100]);
			tc::SharedPtr<int> bar = foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testArrayStructPtrConstructor()
{
	std::cout << "[tc::SharedPtr] testArrayStructPtrConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct[100]);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructArrayPtrAssignmentOperator()
{
	std::cout << "[tc::SharedPtr] testStructArrayPtrAssignmentOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo = new sFooStruct[100];
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructArrayPtrCopyConstructor()
{
	std::cout << "[tc::SharedPtr] testStructArrayPtrCopyConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct[100]);
			tc::SharedPtr<sFooStruct> bar(foo);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testStructArrayPtrCopyOperator()
{
	std::cout << "[tc::SharedPtr] testStructArrayPtrCopyOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct[100]);
			tc::SharedPtr<sFooStruct> bar = foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testNullPtrConstructor()
{
	std::cout << "[tc::SharedPtr] testNullPtrConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(nullptr);
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testNullPtrAssignmentOperator()
{
	std::cout << "[tc::SharedPtr] testNullPtrAssignmentOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo = nullptr;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testNullPtrCopyConstructor()
{
	std::cout << "[tc::SharedPtr] testNullPtrCopyConstructor : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(nullptr);
			tc::SharedPtr<int> bar(foo);
		}

		std::cout << "PASS" << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testNullPtrCopyOperator()
{
	std::cout << "[tc::SharedPtr] testNullPtrCopyOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(nullptr);
			tc::SharedPtr<int> bar = foo;
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testRepeatedAssignment()
{
	std::cout << "[tc::SharedPtr] testRepeatedAssignment : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
			foo = new int[100];
			foo = new int[333];
			foo = new int;
			foo = new int;
			foo = new int[1];
			for (size_t i = 0; i < 1000; i++)
			{
				foo = new int[3];
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testReleasePtr()
{
	std::cout << "[tc::SharedPtr] testReleasePtr : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
			foo.release();
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testReleaseNullPtr()
{
	std::cout << "[tc::SharedPtr] testReleaseNullPtr : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(nullptr);
			foo.release();
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testDereferenceOperator()
{
	std::cout << "[tc::SharedPtr] testDereferenceOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<int> foo(new int);
			*foo = 13;

			if (*foo != 13)
			{
				throw tc::Exception("SharedPtr::operator*() did not act as expected");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testMemberAccessOperator()
{
	std::cout << "[tc::SharedPtr] testMemberAccessOperator : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			tc::SharedPtr<sFooStruct> foo(new sFooStruct);
			foo->b = 13;

			if (foo->b != 13)
			{
				throw tc::Exception("SharedPtr::operator->() did not act as expected");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testGetMethod()
{
	std::cout << "[tc::SharedPtr] testGetMethod : ";
	try
	{
		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			struct sFooStruct
			{
				int a;
				int b;
				uint32_t c;
			};

			sFooStruct* foo = new sFooStruct;

			tc::SharedPtr<sFooStruct> bar = foo;

			if (bar.get() != foo)
			{
				throw tc::Exception("SharedPtr::get() did not return expected ptr");
			}
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testIsNullMethod()
{
	std::cout << "[tc::SharedPtr] testIsNullMethod : ";
	try
	{
		tc::SharedPtr<int> foo = nullptr;

		if (foo.isNull() == false)
		{
			throw tc::Exception("isNull() returned false when data was not null");
		}

		foo = new int;

		if (foo.isNull() == true)
		{
			throw tc::Exception("isNull() returned true when data was null");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testChildDestructorCalledOnPtrRelease()
{
	std::cout << "[tc::SharedPtr] testChildDestructorCalledOnPtrRelease : ";
	class DummyClass
	{
	public:
		DummyClass(size_t& incr_on_delete) :
			mIncrOnDelete(incr_on_delete)
		{
		}

		~DummyClass()
		{
			mIncrOnDelete += 1;
		}
	private:
		size_t& mIncrOnDelete;
	};

	try
	{
		size_t destructor_count = 0;

		tc::SharedPtr<DummyClass> foo = new DummyClass(destructor_count);

		foo.release();

		if (destructor_count != 1)
		{
			throw tc::Exception("DummyClass::~DummyClass() was not called on delete");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testChildDestructorCalledOnSharedPtrDestructor()
{
	std::cout << "[tc::SharedPtr] testChildDestructorCalledOnSharedPtrDestructor : ";
	class DummyClass
	{
	public:
		DummyClass(size_t& incr_on_delete) :
			mIncrOnDelete(incr_on_delete)
		{
		}

		~DummyClass()
		{
			mIncrOnDelete += 1;
		}
	private:
		size_t& mIncrOnDelete;
	};

	try
	{
		size_t destructor_count = 0;

		// if statement so that foo is out of scope so it can be created and destroyed implicitly
		if (true)
		{
			tc::SharedPtr<DummyClass> foo = new DummyClass(destructor_count);
		}

		if (destructor_count != 1)
		{
			throw tc::Exception("DummyClass::~DummyClass() was not called on delete");
		}

		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::testLargeReferenceCount()
{
	std::cout << "[tc::SharedPtr] testLargeReferenceCount : ";
	class DummyClass
	{
	public:
		DummyClass(uint32_t& var, uint32_t on_death_val):
			mVar(var),
			mOnDeathVal(on_death_val)
		{}

		~DummyClass()
		{
			mVar = mOnDeathVal;
		}

		void setOnDeathVal(uint32_t val)
		{
			mOnDeathVal = val;
		}
	private:
		uint32_t& mVar;	
		uint32_t mOnDeathVal;
	};

	try
	{
		static const uint32_t kStartValue = 0xCAFEBABE;
		static const uint32_t kExpectedValue = 0xDEADBEEF;

		uint32_t var = kStartValue;
		
		if (true)
		{
			tc::SharedPtr<DummyClass> obj = new DummyClass(var, kExpectedValue);

			std::vector<tc::SharedPtr<DummyClass>> obj_duplicates;
			for (size_t i = 0; i < 1000; i++)
			{
				obj_duplicates.push_back(obj);
			}

			obj_duplicates[510].release();
			obj_duplicates[500]->setOnDeathVal(kExpectedValue+5);
			obj_duplicates[3].release();
		}

		if (var != kExpectedValue+5)
		{
			throw tc::Exception("DummyClass::~DummyClass() was not called on delete");
		}
		std::cout << "PASS" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FAIL (" << e.what() << ")" << std::endl;
	}
}

void SharedPtr_TestClass::runAllTests(void)
{
	testDefaultConstructor();
	testPrimPtrConstructor();
	testPrimPtrAssignmentOperator();
	testPrimPtrCopyConstructor();
	testPrimPtrCopyOperator();
	testStructPtrConstructor();
	testStructPtrAssignmentOperator();
	testStructPtrCopyConstructor();
	testStructPtrCopyOperator();
	testPrimArrayPtrConstructor();
	testPrimArrayPtrAssignmentOperator();
	testPrimArrayPtrCopyConstructor();
	testPrimArrayPtrCopyOperator();
	testArrayStructPtrConstructor();
	testStructArrayPtrAssignmentOperator();
	testStructArrayPtrCopyConstructor();
	testStructArrayPtrCopyOperator();
	testNullPtrConstructor();
	testNullPtrAssignmentOperator();
	testNullPtrCopyConstructor();
	testNullPtrCopyOperator();
	testRepeatedAssignment();
	testReleasePtr();
	testReleaseNullPtr();
	testDereferenceOperator();
	testMemberAccessOperator();
	testGetMethod();
	testIsNullMethod();
	testChildDestructorCalledOnPtrRelease();
	testChildDestructorCalledOnSharedPtrDestructor();
	testLargeReferenceCount();
}