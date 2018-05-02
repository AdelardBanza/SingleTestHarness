///////////////////////////////////////////////////////////////////////////////
// TestLogger.cpp - TestLogger member-funciton definitions                   //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "TestHarness.h"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::string;

std::string asString (const std::chrono::system_clock::time_point& tp)
{

	// convert to system time:
	std::time_t t = std::chrono::system_clock::to_time_t(tp);
	char str[26];
	ctime_s(str, sizeof str, &t);
	std::string ts = str;// convert to calendar time
	ts.resize(ts.size() - 1);         // skip trailing newline
	return ts;
}

std::ostream& TestLogger::currentTimeStamp(std::ostream& out) const 
{
	if (showTimestamp) 
	{
		std::time_t tp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << asString(std::chrono::system_clock::now()) << ":  ";
	}

	return out;
}

static string trim(const string& ctxStr) 
{
	return ctxStr;
}

static string getRunnerName(const string& ctxStr) 
{
	return ctxStr;
}

// Default constructor to create a root logger
TestLogger::TestLogger() 
	: testResults(true), showTimestamp(true), showDetailMessages(true), showAssertionDetails(true) {}

// Default constructor to create a root logger
TestLogger::TestLogger(const TestLogger& orig)
	: testResults(orig.testResults), showTimestamp(orig.showTimestamp), 
	showDetailMessages(orig.showDetailMessages), showAssertionDetails(orig.showAssertionDetails) {}

// Factory method to create a test logger for running a test suite
std::unique_ptr<TestLogger> TestLogger::createLogger()
{
	return std::make_unique<TestLogger>(*this);
}

// Set the Pass fail status of the testing suite
void TestLogger::setStatus(bool testResults) 
{

	this->testResults = testResults;
}

// prints a summary of the results for running this test suite
void TestLogger::logSummary() const 
{
	currentTimeStamp(cout)  << "TEST RESULT SUMMARY: ";

	if (testResults) 
	{
		cout << "All tests passed successfully." << endl;
	}
	else 
	{
		cout << "The tests had failures." << endl;
	}
}

// Adds a informational message to the test log
void TestLogger::log(const std::string& msg) const 
{
	currentTimeStamp(cout) << msg << endl;
}

// Utility method that creates a child context string from a valid context string, and a child's name
//   usage string childContext = logger.getChildContext(currentContext, "child name");
const std::string TestLogger::getChildLoggingContext(const std::string& originalCtx, const std::string& childName) 
{
	if (trim(originalCtx).size() > 0) 
	{
		return(trim(originalCtx) + "." + trim(childName));
	}
	else 
	{
		return trim(childName);
	}
}

/*************************** Test Case logging methods **********************************************/

// Logs the beginning of a new Test Case
//   usage logTestCaseBegin(contextStr);
void TestLogger::logTestCaseBegin(const std::string& ctxStr) 
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Starting test case: " << getRunnerName(ctxStr) << endl;
	}
}

// Logs an assertion from a test case
//   usage logTestCaseAssertion(contextStr, "variable/assertion name", 
//				"string to represent expected value", "string to represent actual value", 
//				boolean result);
void TestLogger::logTestCaseAssertion(const std::string&ctxStr, const std::string& assertMsg, bool assertRslt)
{
	if (showAssertionDetails) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << ": " << assertMsg << endl;
	}
}

// Logs that the current test case completed with a Success return
//   usage logTestCaseSuccess(contextStr);
void TestLogger::logTestCaseSuccess(const std::string& ctxStr)
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << " finished sucessfully\n" << endl;
	}
}

// Logs that the current test case completed with a (general) failure return
//   usage logTestCaseFail(contextStr);
void TestLogger::logTestCaseFail(const std::string& ctxStr) 
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << " finished with errors\n" << endl;
	}
}

// Logs that the current test case completed with a (general) failure return
//   usage logTestCaseFailWithException(contextStr, e);
void TestLogger::logTestCaseFailWithException(const std::string& ctxStr, const std::exception& e)
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << " failed with exception: message =\"" << e.what() 
			<< "\"" << "\n" << endl;
	}
}

// Logs that the current test case completed with a (general) failure return
//   usage logTestCaseFailWithException(contextStr, e);
void TestLogger::logTestCaseFailWithSpecificException(const std::string& ctxStr, 
	const std::string& exceptioName, const std::exception& e) 
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << " failed with " << exceptioName << ": message =\"" << e.what() 
			<< "\"" << "\n" << endl;
	}
}

// Logs that the current test case failed with an unknown exception return
//   usage logTestCaseFailWithUnknownException(contextStr);
void TestLogger::logTestCaseFailWithUnknownException(const std::string& ctxStr)
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Test Case " << getRunnerName(ctxStr) << " failed with unknown exceptions\n" << endl;
	}
}

/***************************** Test Suite Logging methods *************************************************/

// Logs the beginning of a new Test Suite
//   usage logTestSuiteBegin(contextStr);
void TestLogger::logTestSuiteBegin(const std::string& ctxStr) 
{
	if (showDetailMessages) 
	{
		currentTimeStamp(cout) << "Starting test suite: " << getRunnerName(ctxStr) << endl;
	}
}

// Logs that the current test suite completed with a success return
//   usage logTestSuiteSuccess(contextStr);
void TestLogger::logTestSuiteSuccess(const std::string& ctxStr) 
{
	if (showDetailMessages)
	{
		currentTimeStamp(cout) << "Test Suite " << getRunnerName(ctxStr) << " finished sucessfully\n" << endl;
	}
}

// Logs that the current test case completed with a failure return
//   usage logTestSuiteFail(contextStr);
void TestLogger::logTestSuiteFail(const std::string& ctxStr) 
{
	if (showDetailMessages)
	{
		currentTimeStamp(cout) << "Test Suite " << getRunnerName(ctxStr) << " finished with errors\n" << endl;
	}
}

// accessors and mutators for detail levels
void TestLogger::setShowDetailMessages(bool val)
{
	showDetailMessages = val;
}
bool TestLogger::getShowDetailMessages()
{
	return showDetailMessages;
}

void TestLogger::setShowTimestamp(bool val)
{
	showTimestamp = val;
}
bool TestLogger::getShowTimestamp() 
{
	return showTimestamp;
}

void TestLogger::setShowAssertionDetails(bool val)
{
	showAssertionDetails = val;
}
bool TestLogger::getShowAssertionDetails()
{
	return showAssertionDetails;
}
