#ifndef __SIMCASE_H_INCLUDED__
#define __SIMCASE_H_INCLUDED__

#include <iostream>

#include "FlowSheet.h"


using namespace std;

class SimCase :
	public FlowSheet
{
public:
	SimCase(string thename)
	{
		_casename = thename;

		_name = "MAIN";
		_default_package = 0;
		
	}


	~SimCase();
private:
	string _casename;

	

};

#endif
