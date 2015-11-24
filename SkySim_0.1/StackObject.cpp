#include "stdafx.h"
#include "StackObject.h"


StackObject::StackObject()
{
}
void StackObject::IsDirty(bool thebool)
{
	if (_isdirty == false && thebool == true)
	{
		for (int i = 0; i < _nvariables; i++)
		{
			_variables[i].first->IsDirty(true);
		}
	}
	else if (_isdirty == true && thebool == false)
	{
		for (int i = 0; i < _nvariables; i++)
		{
			_variables[i].first->IsDirty(false);
		}
	}
	_isdirty = thebool; 

}

StackObject::~StackObject()
{
}

void StackObject::AddVariable(RealVariable* thevar)
{
	_nvariables++;
	std::pair <RealVariable*, bool> thepair(thevar, false); ;

	_variables.push_back(thepair);

}

void StackObject::RemoveVariable(RealVariable * thevariable)
{

	std::pair <RealVariable*, bool> temppair;

	
	for (std::vector <std::pair <RealVariable*, bool>>  ::iterator it = _variables.begin(); it != _variables.end(); it++) 
	{
		if (_variables[0].first == thevariable)
		{
			it = _variables.erase(it);
		}
	}

}

double StackObject::FractionKnown()//
{
	double retval;
	double nknown=0;

	for (int i = 0; i < _nvariables; i++)
	{
		if (_variables[i].first->IsKnown())
		{
			nknown = nknown + 1;
		}
	}
	retval = nknown / _nvariables;
	return retval;
}