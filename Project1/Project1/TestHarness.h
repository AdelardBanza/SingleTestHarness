#ifndef TESTHARNESS_H
#define TESTHARNESS_H
///////////////////////////////////////////////////////////////////////////////
// TestHarness.h - TestHarness class definition                              //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "Assertion.h"

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * Typedef for our test executors.  Which are function pointers, to a function
 *   which returns a bool (true/false) value and takes no arguments.
*/
//typedef bool (*testExecutor)(void);
typedef std::function<bool(void)> testExecutor;

/* 
 * Forward declaration of TestHarness classes
 */
class TestRunner;
class TestHarness;
class TestCaseRunner;
class TestSuiteRunner;

/*
 * A data structure to hold the metadata and executor for a single test case.
*/

// TestRunner base class definition
class TestRunner 
{
public:
	TestRunner(const char* name) : runnerName(name) {};

	TestRunner(const std::string& name) : runnerName(name) {};

	virtual bool run(const std::string& runContext, TestLogger& testLogger) const = 0;

	std::string getRunnerName() const  { return this->runnerName;};

	friend TestCaseRunner;
	friend TestSuiteRunner;

private:
	TestRunner(const TestRunner&) = delete;

	TestRunner& operator=(const TestRunner&) = delete;

	std::string runnerName;
};

// TestSuiteRunner class definition
class TestSuiteRunner : public TestRunner
{
public:
	TestSuiteRunner(const char* name);

	TestSuiteRunner(const std::string& name);

	bool run(const std::string& runContext, TestLogger& testLogger) const;

	friend TestHarness;

private:
	TestSuiteRunner(const TestSuiteRunner&) = delete;

	TestSuiteRunner& operator=(const TestSuiteRunner&) = delete;

	TestSuiteRunner* addTestSuiteRunner(std::string name);

	void addTestCaseRunner(std::string, testExecutor);

	static std::unique_ptr<TestSuiteRunner> defaultTestSuiteRunnerFactory();

	std::vector<std::unique_ptr<TestRunner>> testRunnerList;
};

// TestCaseRunner class definition
class TestCaseRunner : public TestRunner 
{
public:
	TestCaseRunner(const char* name, testExecutor testExecutor) 
		: testExecutor(testExecutor), TestRunner((const char*)name) {};

	TestCaseRunner(const std::string& name, testExecutor testExecutor)
		: testExecutor(testExecutor), TestRunner((const std::string&) name) {};

	bool run(const std::string& runContext, TestLogger& testLogger) const ;

private:
	TestCaseRunner(const TestCaseRunner&) = delete;
	TestCaseRunner& operator=(const TestCaseRunner&) = delete;

	testExecutor testExecutor;
};

// TestHarness class definition
class TestHarness
{
public:
	static const int PASS_FAIL_ONLY        = 0;

	static const int SHOW_DETAIL_MESSAGES  = 1;

	static const int SHOW_ALL_MESSAGES     = 2;

	// default (no arg) constructor
	TestHarness();

	// creates a testing harness with a given TestLogger
	TestHarness(const TestLogger&);

	// no copy constructor
	TestHarness(const TestHarness&) = delete;

	// no copy assignment
	TestHarness& operator=(const TestHarness&) = delete;

	/*
	 * Method to run all the tests in the test harness, returns true if all test pass
	 */
	std::unique_ptr<TestLogger> runTests();

	/*
	* This method creates a test suite to run a collection of tests or other test suites.  We can choose to include this
	*   test suit in any test suite we create using the test suite Id, and passing it in as parentTestSuiteRunnerId.
	*   Alternatively add it to the default test suite by passing in a 0.
	*/
	int createTestSuiteRunner(int parentTestSuiteRunnerId, std::string testSuiteRunnerName);

	/* 
	 * This method creates a test runner to run a single test.  We can choose to include this
	 *   test in any test suite we create using the test suite Id, and passing it in as parentTestSuiteRunnerId.
	 *   Alternatively add it to the default test suite by passing in a 0.
	 */
	void createTestRunner(int parentTestSuiteRunnerId, std::string testRunnerName, testExecutor testExecutor);

	void setTestReportingLevel(int level);

	void setShowTimestamp(bool val);

private:
	std::unique_ptr<TestLogger> testLogger;

	std::vector<TestSuiteRunner*> testSuiteRunnerIndex;

	std::unique_ptr<TestSuiteRunner> rootRunner;
};

#endif // TESTHARNESS_H