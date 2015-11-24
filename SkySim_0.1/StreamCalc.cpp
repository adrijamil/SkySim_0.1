#include "stdafx.h"
#include "StreamCalc.h"
#include "Stream.h"
#include "Valve.h"

StreamCalc::StreamCalc()
{

}

string StreamCalc::Name()
{
	string retstring;
	retstring = _refstream->Name();
	retstring.append(":");
	retstring.append(_propertycalc->Name());
	return retstring;
}

void StreamCalc::_setup()
{
	RealVariable** myvariables = 0;
	myvariables = _propertycalc->GetVariables(_refstream);
	int n = _propertycalc->GetNVariables();
	_nvariables = 0;
	_variables.clear();
	//_variables.
	for (int i = 0; i < n; i++)
	{
		RealVariable* thevar = myvariables[i];
		AddVariable(thevar);
	}
}
void StreamCalc::Setup(PropertyCalc* thePC, Stream* theRS)
{
	
	_propertycalc = thePC;
	_refstream = theRS;
	//_setup();
	
}

bool StreamCalc::Solve()
{
	//bool* calcbythis = new bool[_nvariables];

	_setup();

	for (int i = 0; i < _nvariables; i++)
	{
		if (!_variables[i].first->IsKnown())
		{
			//cout << i << "\n";
			_variables[i].second = true;
		}
		else
		{
			_variables[i].second = false;
		}
	}

	bool retval;
	_refstream->GetPropertyPackage()->RefStream()->ReadStream(_refstream);
	//_propertycalc.getvariables()//this should return all variables to map to the stackobject
	retval = _propertycalc->Solve();
	//if (retval == true)
	//{
	_refstream->GetPropertyPackage()->RefStream()->WriteStream(_refstream);
	//}
	

	for (int j = 0; j < _nvariables; j++)
	{
		if (_variables[j].first->IsKnown() && _variables[j].second == true)
		{
			_variables[j].first->CalculatedBy(this);

		}
	}

	_setup();

	return retval;

}

StreamCalc::~StreamCalc()
{
}
