#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class OutputLogger
{
public:
	static OutputLogger* Instance();
	void Output(string theoutput)
	{
		_myfile.open(_outputfilename.c_str(), fstream::out | fstream::app);
		//_myfile = ofstream(_outputfilename.c_str(), ios::out || ios::ate || ios::app);
		_myfile << theoutput.c_str() << "\n";
		cout << theoutput.c_str() << "\n";
		_myfile.close();

	}
	string Name()
	{
		return _outputfilename;
	}
	void Name(string thename)
	{
		_outputfilename = thename;
	}
	~OutputLogger();
protected:
	OutputLogger();
private:
	static OutputLogger* _instance;
	ofstream _myfile; 
	string _outputfilename;
};

