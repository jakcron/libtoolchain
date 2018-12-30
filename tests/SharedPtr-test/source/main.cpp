#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

void testDefaultConstructor()
{
	std::cout << "[SharedPtr-test] testDefaultConstructor : ";
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

void testPrimPtrConstructor()
{
	std::cout << "[SharedPtr-test] testPrimPtrConstructor : ";
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

void testPrimPtrAssignmentOperator()
{
	std::cout << "[SharedPtr-test] testPrimPtrAssignmentOperator : ";
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

void testPrimPtrCopyConstructor()
{
	std::cout << "[SharedPtr-test] testPrimPtrCopyConstructor : ";
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

void testPrimPtrCopyOperator()
{
	std::cout << "[SharedPtr-test] testPrimPtrCopyOperator : ";
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

void testStructPtrConstructor()
{
	std::cout << "[SharedPtr-test] testStructPtrConstructor : ";
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

void testStructPtrAssignmentOperator()
{
	std::cout << "[SharedPtr-test] testStructPtrAssignmentOperator : ";
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

void testStructPtrCopyConstructor()
{
	std::cout << "[SharedPtr-test] testStructPtrCopyConstructor : ";
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

void testStructPtrCopyOperator()
{
	std::cout << "[SharedPtr-test] testStructPtrCopyOperator : ";
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


void testPrimArrayPtrConstructor()
{
	std::cout << "[SharedPtr-test] testPrimArrayPtrConstructor : ";
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

void testPrimArrayPtrAssignmentOperator()
{
	std::cout << "[SharedPtr-test] testPrimArrayPtrAssignmentOperator : ";
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

void testPrimArrayPtrCopyConstructor()
{
	std::cout << "[SharedPtr-test] testPrimArrayPtrCopyConstructor : ";
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

void testPrimArrayPtrCopyOperator()
{
	std::cout << "[SharedPtr-test] testPrimArrayPtrCopyOperator : ";
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

void testArrayStructPtrConstructor()
{
	std::cout << "[SharedPtr-test] testArrayStructPtrConstructor : ";
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

void testStructArrayPtrAssignmentOperator()
{
	std::cout << "[SharedPtr-test] testStructArrayPtrAssignmentOperator : ";
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

void testStructArrayPtrCopyConstructor()
{
	std::cout << "[SharedPtr-test] testStructArrayPtrCopyConstructor : ";
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

void testStructArrayPtrCopyOperator()
{
	std::cout << "[SharedPtr-test] testStructArrayPtrCopyOperator : ";
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

void testNullPtrConstructor()
{
	std::cout << "[SharedPtr-test] testNullPtrConstructor : ";
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

void testNullPtrAssignmentOperator()
{
	std::cout << "[SharedPtr-test] testNullPtrAssignmentOperator : ";
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

void testNullPtrCopyConstructor()
{
	std::cout << "[SharedPtr-test] testNullPtrCopyConstructor : ";
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

void testNullPtrCopyOperator()
{
	std::cout << "[SharedPtr-test] testNullPtrCopyOperator : ";
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

void testRepeatedAssignment()
{
	std::cout << "[SharedPtr-test] testRepeatedAssignment : ";
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

void testReleasePtr()
{
	std::cout << "[SharedPtr-test] testReleasePtr : ";
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

void testReleaseNullPtr()
{
	std::cout << "[SharedPtr-test] testReleaseNullPtr : ";
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

void testDereferenceOperator()
{
	std::cout << "[SharedPtr-test] testDereferenceOperator : ";
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

void testMemberAccessOperator()
{
	std::cout << "[SharedPtr-test] testMemberAccessOperator : ";
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

void testGetMethod()
{
	std::cout << "[SharedPtr-test] testGetMethod : ";
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

void testIsNullMethod()
{
	std::cout << "[SharedPtr-test] testIsNullMethod : ";
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

void testChildDestructorCalledOnPtrRelease()
{
	std::cout << "[SharedPtr-test] testChildDestructorCalledOnPtrRelease : ";
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

void testChildDestructorCalledOnSharedPtrDestructor()
{
	std::cout << "[SharedPtr-test] testChildDestructorCalledOnSharedPtrDestructor : ";
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

void testLargeReferenceCount()
{
	std::cout << "[SharedPtr-test] testLargeReferenceCount : ";
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

int main(int argc, char** argv)
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
	testIsNullMethod();
	testChildDestructorCalledOnPtrRelease();
	testChildDestructorCalledOnSharedPtrDestructor();
	testLargeReferenceCount();
}