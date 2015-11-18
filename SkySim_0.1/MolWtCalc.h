#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"

class MolWtCalc :
	public PropertyCalc
{
public:
	bool Solve();
	RealVariable** GetVariables(Stream* refstream);
	MolWtCalc();
	~MolWtCalc();
private:
	void CalcFluid();
};


