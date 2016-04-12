#pragma once
#include "UnitOp.h"
class SetOperation :
	public UnitOp
{
public:
	SetOperation();
	SetOperation(string name);
	~SetOperation();
	RealVariable* X() { return _x; }
	RealVariable* Y() { return _y; }
	void TempConnectQ(RealVariable* theX, RealVariable* theY);
private:

	RealVariable* _x = new RealVariable;
	RealVariable* _y = new RealVariable;
	RealVariable* _multiplier = new RealVariable;
	RealVariable* _offset = new RealVariable;
	void SpecifyVariable(RealVariableType vartype, double value);
};



