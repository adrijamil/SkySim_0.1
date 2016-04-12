// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	This is generic interface abstract base class for flowsheet objects (flowsheet, stream, unitop)
//					Any common functions/data should be here
//					
// SPECIAL NOTES:	
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================



#ifndef __FSOBJECT_H_INCLUDED__
#define __FSOBJECT_H_INCLUDED__
#include "StackObject.h"
using  std::string;


class FSObject
{
public:
	FSObject() {

		_name = "";
	}
	~FSObject();
	virtual bool Solve() = 0;// { return false; };
	string Name() { return _name; }
	virtual void SetName(string thename) { _name = thename; }
	virtual StackObject* GetStackObject(int i){ return _stackobjects[i]; }
	virtual void AddStackObject(StackObject* theSO)
	{
		_nstackobjects = _nstackobjects + 1; //update count
		StackObject** newchildren;
		//std::cout << "\n";

		//realloc is similar to redim preserve. members of array are preserved and sent to new array (newchildren)
		//should be possible to reallocate straight to itself ie _children = (FSObject**)realloc(...... but this is safer. can catch errors.
		newchildren = (StackObject**)realloc(_stackobjects, _nstackobjects* sizeof(*theSO)); //allocate new array

		if (newchildren != NULL) //if it's null then realloc tak jadi
		{
			_stackobjects = newchildren;
			_stackobjects[_nstackobjects - 1] = &(*theSO);
		}
	}

	virtual int NStackObjects(){ return _nstackobjects; }
	virtual void Output() {};
protected:
	string _name;
	StackObject** _stackobjects;
	int _nstackobjects = 0;
	
};

#endif
