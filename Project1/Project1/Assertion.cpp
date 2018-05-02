///////////////////////////////////////////////////////////////////////////////
// Assertion.cpp - Class Assertion member-function definitions               //
// ver 1.0                                                                   //
// Language:    C++, Visual Studio 2017                                      //
// Platform:    HP G1 800, Windows 10                                        //
// Application: Single Test Harness Project, CSE687 - Object Oriented Design //
// Author:      Adelard Banza,                                               //
//              abanza@syr.edu                                               //
///////////////////////////////////////////////////////////////////////////////

#include "Assertion.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

AssertionManager* AssertionManager::instance;

AssertionManager& AssertionManager::getInstance() 
{
	if (AssertionManager::instance == nullptr) 
	{
		AssertionManager::instance = new AssertionManager();
	}
	return *AssertionManager::instance;
}

AssertionManager::AssertionManager() {}

AssertionManager::~AssertionManager() 
{
	if (AssertionManager::instance != nullptr) 
	{
		delete AssertionManager::instance;
		AssertionManager::instance = nullptr;
	}
}

void AssertionManager::pushCntx(const std::string& ctxStr, TestLogger* logger)
{
	// add this new context to the stack
	ctxStack.push(std::make_pair(std::make_pair(ctxStr, true), logger));
}

bool AssertionManager::assertCntx(const string& msg, TestLogger* logger) 
{
	return true;
}

bool AssertionManager::popCntx() 
{
	// grab the current context, and remove from stack
	auto ctxEntry = ctxStack.top();
	ctxStack.pop();

	// return the assertion status
	return ctxEntry.first.second;
}


void AssertionManager::logSuccess(const string& msg) 
{
	// grab the current context
	auto ctxEntry = ctxStack.top();

	// get the current context logger and string
	TestLogger* logger = ctxEntry.second;
	string& ctxStr = ctxEntry.first.first;

	// add the assertion result to the logger
	logger->logTestCaseAssertion(ctxStr, msg, true);
}

void AssertionManager::logFail(const string& msg) 
{
	// grab the current context
	auto ctxEntry = ctxStack.top();

	// get the current context logger and string
	TestLogger* logger = ctxEntry.second;
	string& ctxStr = ctxEntry.first.first;

	// add the assertion result to the logger
	logger->logTestCaseAssertion(ctxStr, msg, false);

	// make sure to set the assertion status to false for this entry
	ctxEntry.first.second = false;
	//replace top entry
	ctxStack.pop();
	ctxStack.push(ctxEntry);
}