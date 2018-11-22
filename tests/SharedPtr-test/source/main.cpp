#include <tc/fs.h>
#include <tc/Exception.h>
#include <iostream>
#include <tc/SharedPtr.h>

static const uint32_t kStartValue = 0xCAFEBABE;
static const uint32_t kExpectedValue = 0xDEADBEEF;

class TestClass
{
public:
	TestClass(uint32_t& var):
		mVar(var),
		mOnDeathVal(kExpectedValue)
	{}

	~TestClass()
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

void outOfScope1(uint32_t& var)
{
	tc::SharedPtr<TestClass> obj = new TestClass(var);
}

void testChildDestructorCalledOnSharedPtrDestructor()
{
	uint32_t var = kStartValue;
	
	outOfScope1(var);

	if (var == kExpectedValue)
	{
		std::cout << "[SharedPtr-test] testChildDestructorCalledOnSharedPtrDestructor() : PASS" << std::endl;
	}
	else
	{
		std::cout << "[SharedPtr-test] testChildDestructorCalledOnSharedPtrDestructor() : FAIL" << std::endl;
	}
}

void outOfScope2(uint32_t& var)
{
	tc::SharedPtr<TestClass> obj = new TestClass(var);

	std::vector<tc::SharedPtr<TestClass>> obj_duplicates;
	for (size_t i = 0; i < 1000; i++)
	{
		obj_duplicates.push_back(obj);
	}

	obj_duplicates[500].operator*()->setOnDeathVal(kExpectedValue+5);
}

void testLargeReferenceCount()
{
	uint32_t var = kStartValue;
	
	outOfScope2(var);

	if (var == kExpectedValue+5)
	{
		std::cout << "[SharedPtr-test] testLargeReferenceCount() : PASS" << std::endl;
	}
	else
	{
		std::cout << "[SharedPtr-test] testLargeReferenceCount() : FAIL" << std::endl;
	}
}

void outOfScope3(uint32_t& var)
{
	tc::SharedPtr<TestClass> obj;

	obj.operator*();

	obj = nullptr;

	obj.operator*();
}

void testAssignNullPtr()
{
	uint32_t var = kStartValue;
	
	outOfScope3(var);

	if (var == kStartValue)
	{
		std::cout << "[SharedPtr-test] testAssignNullPtr() : PASS" << std::endl;
	}
	else
	{
		std::cout << "[SharedPtr-test] testAssignNullPtr() : FAIL" << std::endl;
	}
}

int main(int argc, char** argv)
{
	testChildDestructorCalledOnSharedPtrDestructor();
	testLargeReferenceCount();
	testAssignNullPtr();
}