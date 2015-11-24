#pragma once
#include "RealVariable.h"
#include <utility> 
#include <vector>
class StackObject
{
public:
	StackObject();
	~StackObject();
	virtual bool Solve()=0;
	void AddVariable(RealVariable* thevariable);
		void RemoveVariable(RealVariable* thevariable);
	bool IsDirty()
	{ 
		bool isthisdirty;
		if (_isdirty == false)
		{
			for (int i = 0; i < _nvariables; i++)
			{
				isthisdirty = false;
				isthisdirty = _variables[i].first->IsDirty();
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
					if (_variables[i].first->IsCalculated()&&_variables[i].first->CalculatedBy())
					{
						_variables[i].first->IsDirty(true);
						_variables[i].first->IsKnown(false);
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
			if (_variables[i].first->CalculatedBy() == theStackObject)
			{
				return true;
			}
		}
		return false;
	}
//
protected:
	std::vector <std::pair <RealVariable*, bool>>  _variables;
	int  _nvariables=0;

	bool _isdirty = true;
};

