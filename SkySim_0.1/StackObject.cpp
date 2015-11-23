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

void StackObject::RemoveVariable(RealVariable * thevariable)
{

	/*cout << "removing var " << thevariable << " \n" ;

	for (int i = 0;i < _nvariables;i++)
	{
		cout << "var " << i << " " << _variables[i] << "\n";
	}*/

	_nvariables= _nvariables-1;
	RealVariable** newvariables;
	int j = 0;

	newvariables = (RealVariable**)malloc(_nvariables* sizeof(*thevariable));
	
	for (int i = 0;i < _nvariables+1;i++)
	{
		if (!(_variables[i] == thevariable))
		{
			newvariables[i-j] = _variables[i];
		}
		else
		{
			j = 1;
		}

	}

	_variables = (RealVariable**)realloc(newvariables, _nvariables* sizeof(*thevariable));

	//cout << "removed " << thevariable << " \n";
	/*for (int i = 0;i < _nvariables;i++)
	{
		cout << "var " << i << " " << _variables[i]<<"\n";
	}*/
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