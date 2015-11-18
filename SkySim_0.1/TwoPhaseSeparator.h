#pragma once
#include "UnitOp.h"
#include "Stream.h"

class TwoPhaseSeparator :
	public UnitOp
{
public:
	TwoPhaseSeparator();
	TwoPhaseSeparator(std::string name);
	~TwoPhaseSeparator();
	//void SpecifyVariable(RealVariableType vartype, double value);
	void Output(){};
private:
	void _setupconnection(ConnectionType InOrOut) ;

};


