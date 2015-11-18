#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Compressor :
	public UnitOp
{
public:
	RealVariable* DeltaPressure(){ return _deltapressure; }
	RealVariable* EnergyInput(){ return _energyinput; }
	void SpecifyVariable(RealVariableType vartype, double value);
	bool IsSolved(){ return _issolved; }
	Compressor();
	Compressor(string name);
	void Output();// later show something like pressure drop
	~Compressor();
private:
	RealVariable* _energyinput = new RealVariable;
	RealVariable* _deltapressure = new RealVariable;
	RealVariable* _isentropicefficiency = new RealVariable;
	void _setupconnection(ConnectionType InOrOut);
	bool _issolved;
};

