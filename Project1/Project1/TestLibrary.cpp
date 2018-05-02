///////////////////////////////////////////////////////////////////////////////
// TestLibrary.cpp - TestLibrary function definitions                        //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "TestHarness.h"

#include <stdexcept>
#include <string>

using std::logic_error;
using std::string;

bool test1() 
{
	int i = 0;
	int j = 0;

	assertEquals("testVar1", i, j);
	assertEquals("testVar2", i, j + 1);

	return true;
}

bool test2() 
{
	string actual("actual");
	string expected("expected");

	assertEquals("testVar1", "actual ", expected);
	assertEquals("testVar2", "expected ", actual);

	return true;
}

bool test3() 
{
	int i = 0;
	int j = 0;

	assertEquals("testVar1", i, j);
	assertEquals("testVar2", i, j + 1);

	return true;
}

bool test4() 
{
	return false;
}

bool test5() 
{
	throw 3;
	return true;
}
//
//bool test6() 
//{
//	throw logic_error("Logic error");
//	return true;
//}

bool test6() 
{
	throw logic_error("Logic error");
	return true;
}

bool test7() 
{
	throw 3;
	return true;
}
//
//bool test9() 
//{
//	throw logic_error("Logic error");
//	return true;
//}

bool test8() 
{
	throw logic_error("Logic error");
	return true;
}

class testFunctor1 
{
public:
	bool operator() () 
	{
		assertEquals("Functor_testVar1", 1, 1);
		return true;
	}
};

class testFunctor2 
{
public:
	bool operator() () 
	{
		return false;
	}
};

testExecutor getTestCase(int i)
{

	switch (i) 
	{
	case 1:
		return []() -> bool {return test1; };
	case 2:
		return test2;
	case 3:
		return test3;
	case 4:
		return test4;
	case 5:
		return test5;
	case 6:
		return test6;
	case 7:
		return test7;
	case 8:
		return test8;
	case 9:
		return testFunctor1();
	default:
		return testFunctor2();
	}
}
