#include "stdafx.h"
#include "BridgeFunction.h"
#include "Stream.h"
#include "UnitOp.h"

BridgeFunction::BridgeFunction()
{
}

BridgeFunction::~BridgeFunction()
{
}
bool BridgeFunction::Solve()
{
	bool* calcbythis = new bool[_nvariables];
	for (int i = 0; i < _nvariables; i++)
	{
		if (!_variables[i].first->IsKnown())
		{
			calcbythis[i] = true;
		}
		else
		{
			calcbythis[i] = false;
		}
	}

	BridgeFunction* thefunc;
	bool retval = true;
	bool thissolved = false;
	if (_nchildren != 0)// if got children solve all of them// if no children then this function would be overridden
	{
		for (int i = 0; i < _nchildren; i++)
		{
			thefunc = _children[i];

			thissolved = thefunc->Solve();
			if (thissolved == false){ retval = false; }
		}
	}
	else
	{
		thissolved = _calculate();
		if (thissolved == false){ retval = false; }
	}
	if (thissolved == false){ retval = false; }
	for (int j = 0; j < _nvariables; j++)
	{	
		if (j == 5)
		{
			cout << j << ":" << _variables[j].first->GetValue() << "\n";
		}
			
		
		
		if (_variables[j].first->IsKnown() && calcbythis[j] == true)
		{
			_variables[j].first->CalculatedBy(this);
				

		}
		else
		{
			calcbythis[j] = false;
		}
	}

	return retval;

}

void BridgeFunction::SetParent(UnitOp* theOp)
{
	_parent = theOp;
}

string BridgeFunction::StackName()
{
	string str;
	str = _parent->Name();
	str.append(":");
	str.append(_name);
	return str;

}

void BridgeFunction::AddBridge(BridgeFunction* thechild)
{
	_nchildren = _nchildren + 1; //update count
	BridgeFunction** newchildren;
	cout << "\n";

	thechild->SetParent(_parent);
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	newchildren = (BridgeFunction**)realloc(_children, _nchildren* sizeof(*thechild)); //allocate new array

	if (newchildren != NULL) //if it's null then realloc tak jadi
	{
		_children = newchildren;
		_children[_nchildren - 1] = &(*thechild);
	}
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.

}