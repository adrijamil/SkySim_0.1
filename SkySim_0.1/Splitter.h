#pragma once
#include "UnitOp.h"
#include "Stream.h"
class Splitter:
	public UnitOp
{
public:
	/*RealVariable* SplitRatios(int i){ return _splitfractions[i]; }
	void SpecifySplitRatios(int i, double value)
	{
		_splitfractions[i]->SetValue(value);
	}*/
	Splitter();
	Splitter(string name);
	void Output(){};// later show something like pressure drop
	~Splitter();
private:
	//RealVariable** _splitfractions= new RealVariable*[1]; //default by mol;
	void _setupconnection(ConnectionType InOrOut);
	//void _addoutlet();

};