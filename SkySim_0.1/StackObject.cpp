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
			_variables[i]->IsDirty(true);
		}
	}
	else if (_isdirty == true && thebool == false)
	{
		for (int i = 0; i < _nvariables; i++)
		{
			_variables[i]->IsDirty(false);
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
	RealVariable** newvariables;
	if (_nvariables == 1)
	{
		newvariables = (RealVariable**)malloc(_nvariables* sizeof(*thevar));
	}
	else
	{
		newvariables = (RealVariable**)realloc(_variables, _nvariables* sizeof(*thevar)); //allocate new array
	}

	if (newvariables != NULL) //if it's null then realloc tak jadi//means theres only one guy;
	{
		newvariables[_nvariables - 1] = &(*thevar);
	}

	_variables = (RealVariable**)realloc(newvariables, _nvariables* sizeof(*thevar));
}

double StackObject::FractionKnown()//
{
	double retval;
	double nknown=0;

	for (int i = 0; i < _nvariables; i++)
	{
		if (_variables[i]->IsKnown())
		{
			nknown = nknown + 1;
		}
	}
	retval = nknown / _nvariables;
	return retval;
}