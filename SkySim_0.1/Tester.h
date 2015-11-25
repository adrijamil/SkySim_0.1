#pragma once
#include "CommandInterpreter.h"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm> // for remove()

struct UnitOpTest
{
	std::string Name;
	std::string Inputfile;
	std::string Outputfile;
	std::string Description;
	bool Passed;
};

class Tester
{
public:
	Tester();
	~Tester();
	virtual bool TestAll();
	//virtual bool TestAll();
	void AddTestFiles(std::string mytestlist);
	std::string name;
private:
	//std::vector<std::string> myinputfiles;
	//std::vector<std::string> myoutputfiles;
	std::vector<UnitOpTest> mytests;
	CommandInterpreter* mycmd;
	

};

