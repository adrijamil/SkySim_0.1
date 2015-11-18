#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Valve :
	public UnitOp
{
public:
	RealVariable* K_Resistance(){ return _k_resistance; }
	RealVariable* PressureDrop(){ return _pressuredrop; }
	void SpecifyVariable(RealVariableType vartype, double value);
	bool IsSolved(){ return _issolved; }
	Valve();
	Valve(string name);
	void Output();// later show something like pressure drop
	~Valve();
private:
	void _setupconnection(ConnectionType InOrOut);
	RealVariable* _k_resistance = new RealVariable;
	RealVariable* _pressuredrop = new RealVariable;
	bool _issolved;

};

