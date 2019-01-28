#pragma once
#include "ITestClass.h"

#include <tc/SharedPtr.h>

class SharedPtr_TestClass : public ITestClass
{
public:
	void runAllTests();
private:
	void testDefaultConstructor();
	void testPrimPtrConstructor();
	void testPrimPtrAssignmentOperator();
	void testPrimPtrCopyConstructor();
	void testPrimPtrCopyOperator();
	void testStructPtrConstructor();
	void testStructPtrAssignmentOperator();
	void testStructPtrCopyConstructor();
	void testStructPtrCopyOperator();
	void testPrimArrayPtrConstructor();
	void testPrimArrayPtrAssignmentOperator();
	void testPrimArrayPtrCopyConstructor();
	void testPrimArrayPtrCopyOperator();
	void testArrayStructPtrConstructor();
	void testStructArrayPtrAssignmentOperator();
	void testStructArrayPtrCopyConstructor();
	void testStructArrayPtrCopyOperator();
	void testNullPtrConstructor();
	void testNullPtrAssignmentOperator();
	void testNullPtrCopyConstructor();
	void testNullPtrCopyOperator();
	void testRepeatedAssignment();
	void testReleasePtr();
	void testReleaseNullPtr();
	void testDereferenceOperator();
	void testMemberAccessOperator();
	void testGetMethod();
	void testIsNullMethod();
	void testChildDestructorCalledOnPtrRelease();
	void testChildDestructorCalledOnSharedPtrDestructor();
	void testLargeReferenceCount();
};