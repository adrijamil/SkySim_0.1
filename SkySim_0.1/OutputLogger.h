#pragma once
#include <iostream>
#include <string>
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
		//cout << theoutput.c_str() << "\n";
		_myfile.close();
		//std::cout<< _outputfilename << " says: " << theoutput;

	}

	string Name()
	{
		return _outputfilename;
	}
	void Name(string thename)
	{
		_outputfilename = thename;
		std::ofstream ofs;
		ofs.open(thename, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	~OutputLogger();
protected:
	OutputLogger();
private:
	static OutputLogger* _instance;
	ofstream _myfile; 
	string _outputfilename;
	int _outputmode = 0;//if 0 cout, if 1 output to file
};

