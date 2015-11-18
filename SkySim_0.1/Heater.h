#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Heater :
	public UnitOp
{
public:

	RealVariable* K_Resistance(){ return _k_resistance; }
	RealVariable* PressureDrop(){ return _pressuredrop; }
	RealVariable* HeatInput(){ return _heatinput; }
	Heater();
	Heater(string name);
	void Output();// later show something like pressure drop
	~Heater();
private:
	void _setupconnection(ConnectionType InOrOut);
	RealVariable* _k_resistance = new RealVariable;
	RealVariable* _pressuredrop = new RealVariable;
	RealVariable* _heatinput = new RealVariable;
	void SpecifyVariable(RealVariableType vartype, double value);
	//void _setupconnection(){};

};

