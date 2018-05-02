#ifndef ASSERTION_H
#define ASSERTION_H
///////////////////////////////////////////////////////////////////////////////
// Assertion.h - Assertion class definition                                  //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "TestLogger.h"

#include <memory>
#include <sstream>
#include <stack>
#include <string>

class AssertionManager;
class TestHarness;
class TestSuiteRunner;

template<typename T1, typename T2> void assertEquals(const std::string& msg, const T1 t1, const T2 t2);

template<typename T> void assertNotNull(const std::string& s, const T* const tPtr);

class AssertionManager 
{
public:
	static AssertionManager& getInstance();
	~AssertionManager();

	template<typename T1, typename T2> friend void assertEquals(const std::string& msg, const T1 t1, const T2 t2);

	template<typename T> friend void assertNotNull(const std::string& s, const T* const tPtr);

	friend class TestHarness;
	friend class TestCaseRunner;
	friend class TestSuiteRunner;

private:
	AssertionManager();

	void pushCntx(const std::string&, TestLogger*);

	bool assertCntx(const std::string& msg, TestLogger* logger);

	bool popCntx();

	void logSuccess(const std::string&);

	void logFail(const std::string&);

	static AssertionManager *instance;

	std::stack<std::pair<std::pair<std::string, bool>, TestLogger*>> ctxStack;
};

// assertEquals(lineNumberr, filename, testCaseName, expected, actual, testing condition)
template<typename T1, typename T2>
void assertEquals(const std::string& msg, const T1 t1, const T2 t2) 
{

	AssertionManager& assertM = AssertionManager::getInstance();

	if (t2 == t1) {
		std::stringstream s;
		s << "assertEquals passed: " << msg << " received " << t1 << " while expecting " << t1;
		assertM.logSuccess(s.str());
	}
	else {
		std::stringstream s;
		s << "assertEquals failed: " << msg << " received " << t1 << " while expecting " << t2;
		assertM.logFail(s.str());
	}
}

template<typename T>
void assertNotNull(const std::string& s, const T* const tPtr) 
{

	AssertionManager& assertM = AssertionManager::getInstance();

	if (tPtr != nullptr_t) {
		std::stringstream s;
		s << "assertNotNull passed for " << msg;
		assertM.logSuccess(s.str());
	}
	else {
		std::stringstream s;
		s << "assertNotNull failed " << msg;
		assertM.logFail(s.str());
	}
}

#endif // ASSERTION_H
