#include "stdafx.h"
#include "RealVariable.h"
#include "StackObject.h"
RealVariable::RealVariable()
{
}

RealVariable::~RealVariable()
{
}

void RealVariable::SetValue(double thevalue)
{
	
	if (thevalue!=-32767)
	{
		//_isdirty = true;
		_is_known = true;
		_setvalue(thevalue);
	}
	else
	{
		_is_known = false;

	}
}
void RealVariable::IsKnown(bool thebool)
{
	_is_known = thebool;
	
}
void RealVariable::SetValue(int i, double thevalue)
{
	if (thevalue != -32767)
	{
		//_isdirty = true;
		_setvalue(i, thevalue);
		_is_known = true;
	}
	else
	{
		_is_known = false;

	}
}

void RealVariable::SetValues(int N, double* thevalue)
{
	if (thevalue[0] != -32767)
	{
		//_isdirty = true;
		_setvalues(N, thevalue);
		_is_known = true;
	}
}