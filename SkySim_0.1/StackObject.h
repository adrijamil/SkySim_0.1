#pragma once
#include "RealVariable.h"


class StackObject
{
public:
	StackObject();
	~StackObject();
	virtual bool Solve()=0;
	void AddVariable(RealVariable* _variables);
	bool IsDirty()
	{ 
		bool isthisdirty;
		if (_isdirty == false)
		{
			for (int i = 0; i < _nvariables; i++)
			{
				isthisdirty = false;
				isthisdirty = _variables[i]->IsDirty();
				if (isthisdirty)
				{
					_isdirty = true;
					
				}
			}

			if (_isdirty == true)
			{
				//make all vars I calculate dirty
				for (int i = 0; i < _nvariables; i++)
				{
					if (_variables[i]->CalculatedBy()==this)
					{
						_variables[i]->IsDirty(true);
						_variables[i]->IsKnown(false);
					}
				}

			}
		}

		return _isdirty;
	}
	void IsDirty(bool thebool);
	double FractionKnown();//
	virtual string Name(){ return 0; };
	bool DependsOn(StackObject* theStackObject)
	{
		//if any of this _variables are calculated by theStackObject
		for (int i = 0; i < _nvariables; i++)
		{
			if (_variables[i]->CalculatedBy() == theStackObject)
			{
				return true;
			}
		}
		return false;
	}
//
protected:
	RealVariable** _variables;
	int  _nvariables=0;

	bool _isdirty = true;
};

