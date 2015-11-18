#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Mixer :
	public UnitOp
{
public:

	Mixer();
	Mixer(string name);
	void Output(){};// later show something like pressure drop
	~Mixer();
private:
	void _setupconnection(ConnectionType InOrOut);
};