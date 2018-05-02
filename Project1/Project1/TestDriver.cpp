///////////////////////////////////////////////////////////////////////////////
// TestDriver.cpp - TestDriver test program                                  //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "TestHarness.h"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::logic_error;
using std::string;

testExecutor getTestCase(int i);

int main() 
{
	TestHarness t;

	// Setup the test cases 
	t.createTestRunner(0, "Lambda function", getTestCase(1));

	t.createTestRunner(0, "Function_Pointer2", getTestCase(2));

	t.createTestRunner(0, "Function_Pointer3", getTestCase(3));

	t.createTestRunner(0, "Function_Pointer4", getTestCase(4));

	t.createTestRunner(0, "Function_Pointer5", getTestCase(5));

	t.createTestRunner(0, "Function_Pointer6", getTestCase(6));

	t.createTestRunner(0, "Function_Pointer7", getTestCase(7));

	t.createTestRunner(0, "Function_Pointer8", getTestCase(8));

	t.createTestRunner(0, "Functor_testVar1", getTestCase(9));

	t.createTestRunner(0, "Functor_testVar2", getTestCase(10));

	// set the reporting level for my tests
	t.setShowTimestamp(true);

	t.setTestReportingLevel(TestHarness::SHOW_ALL_MESSAGES);

	// run the tests
	t.runTests();
}