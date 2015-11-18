

//singleton class to handle HMODULE. This class may need to be destroyed if setup fucks up
//also handles setup

#pragma once
#include <windows.h>
#include <string>
#include <stdio.h>
using namespace std;

const long refpropcharlength = 255;
const long filepathlength = 255;
const long lengthofreference = 3;
const long errormessagelength = 255;
const long ncmax = 20;		// Note: ncmax is the max number of components
const long numparams = 72;
const long maxcoefs = 50;

class RPManager
{
 
public:
	HINSTANCE hInstance()
	{
		return RefpropdllInstance;
	}
	RPManager();
	~RPManager();
	static RPManager* Instance()
	{
		if (!_instance)
		{
			_instance = new RPManager;

		}
		return _instance;
	}

	bool Setup(string fluids, long i);
	
private:
	static RPManager* _instance;
	HINSTANCE RefpropdllInstance;
	
};

