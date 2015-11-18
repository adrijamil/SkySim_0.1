#include "stdafx.h"
#include "PropertyCalc.h"


PropertyCalc::PropertyCalc()
{
	_nchildren = 0;
}

void PropertyCalc::SetParent(PropPack* thePP)
{
	_parent = thePP;
}


void PropertyCalc::AddProperty(PropertyCalc* thechild)
{
	_nchildren = _nchildren + 1; //update count
	PropertyCalc** newchildren;
	cout << "\n";

	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
	newchildren = (PropertyCalc**)realloc(_children, _nchildren* sizeof(*thechild)); //allocate new array

	if (newchildren != NULL) //if it's null then realloc tak jadi
	{
		_children = newchildren;
		_children[_nchildren - 1] = &(*thechild);
	}
	//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
	//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.

}

bool PropertyCalc::Solve()
{
	PropertyCalc* theprop;
	bool retval = true;
	if (_nchildren == 0)
	{
		std::cout << "fuckme I'm A \n";
	}
	else// if got children solve all of them
	{
		for (int i = 0; i < _nchildren; i++)
		{
			theprop = _children[i];

			if (!theprop->Solve())
			{
				retval = false;
			}
		}
	}
	return retval;
}

PropertyCalc::~PropertyCalc()
{
}
