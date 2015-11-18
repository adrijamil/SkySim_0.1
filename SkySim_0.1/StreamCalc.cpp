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

void StreamCalc::Setup(PropertyCalc* thePC, Stream* theRS)
{
	RealVariable** myvariables=0;
	_propertycalc = thePC;
	_refstream = theRS;

	myvariables=_propertycalc->GetVariables(_refstream);

	int nvar = _propertycalc->GetNVariables();

	for (int i = 0; i < nvar; i++)
	{
		RealVariable* thevar = myvariables[i];
			AddVariable(thevar);
	}
}

bool StreamCalc::Solve()
{
	bool* calcbythis = new bool[_nvariables];



	for (int i = 0; i < _nvariables; i++)
	{
		if (!_variables[i]->IsKnown())
		{
			//cout << i << "\n";
			calcbythis[i] = true;
		}
		else
		{
			calcbythis[i] = false;
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
		if (_variables[j]->IsKnown() && calcbythis[j] == true)
		{
			_variables[j]->CalculatedBy(this);
		//	cout << j << ":" << _variables[j]->GetValue() << "\n";
		
		}
		else
		{
			calcbythis[j] = false;
		}
	}

	return retval;

}

StreamCalc::~StreamCalc()
{
}
