#ifndef TEST_LOGGER_H
#define TEST_LOGGER_H
///////////////////////////////////////////////////////////////////////////////
// TestLogger.h - TestLogger class definition                                //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <ostream>
#include <string>

/*
* Simple Logger placeholder class
*/
class TestLogger 
{
public:
	// Default constructor to create a root logger
	TestLogger();

	// Copy constructor to create a root logger
	TestLogger(const TestLogger&);

	// Factory method to create a test logger for running a test suite
	std::unique_ptr<TestLogger> createLogger();

	// Set the Pass fail status of the testing suite
	void setStatus(bool);

	// prints a summary of the results for running this test suite
	void logSummary() const;

	// Adds a informational message to the test log
	void log(const std::string&) const;

	// Utility method that creates a child context string from a valid context string, and a child's name
	//   usage string childContext = logger.getChildContext(currentContext, "child name");
	const std::string getChildLoggingContext(const std::string&, const std::string&);

	/*************************** Test Case logging methods **********************************************/

	// Logs the beginning of a new Test Case
	//   usage logTestCaseBegin(contextStr);
	void logTestCaseBegin(const std::string&);

	// Logs an assertion from a test case
	//   usage logTestCaseAssertion(contextStr, "variable/assertion msg",  
	//				boolean result);
	void logTestCaseAssertion(const std::string&, const std::string&, bool);

	// Logs that the current test case completed with a Success return
	//   usage logTestCaseSuccess(contextStr);
	void logTestCaseSuccess(const std::string&);

	// Logs that the current test case completed with a (general) failure return
	//   usage logTestCaseFail(contextStr);
	void logTestCaseFail(const std::string&);

	// Logs that the current test case completed with a (general) failure return
	//   usage logTestCaseFailWithException(contextStr, e);
	void logTestCaseFailWithException(const std::string&, const std::exception&);

	// Logs that the current test case completed with a (general) failure return
	//   usage logTestCaseFailWithException(contextStr, e);
	void logTestCaseFailWithSpecificException(const std::string&, const std::string&, const std::exception&);

	// Logs that the current test case failed with an unknown exception return
	//   usage logTestCaseFailWithUnknownException(contextStr);
	void logTestCaseFailWithUnknownException(const std::string&);

	/***************************** Test Suite Logging methods *************************************************/

	// Logs the beginning of a new Test Suite
	//   usage logTestSuiteBegin(contextStr);
	void logTestSuiteBegin(const std::string&);

	// Logs that the current test suite completed with a success return
	//   usage logTestSuiteSuccess(contextStr);
	void logTestSuiteSuccess(const std::string&);

	// Logs that the current test case completed with a failure return
	//   usage logTestSuiteFail(contextStr);
	void logTestSuiteFail(const std::string&);

	// accessors and mutators for detail levels

	void setShowDetailMessages(bool);

	bool getShowDetailMessages();

	void setShowTimestamp(bool);

	bool getShowTimestamp();

	void setShowAssertionDetails(bool);

	bool getShowAssertionDetails();

private:
	std::ostream& currentTimeStamp(std::ostream& out) const;

	bool testResults;

	bool showTimestamp;

	bool showDetailMessages;

	bool showAssertionDetails;
};

#endif // TEST_LOGGER_H