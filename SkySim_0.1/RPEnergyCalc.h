#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "RefPropPack.h" 
#include <windows.h>
using namespace std;
class RPEnergyCalc :
	public PropertyCalc
{
public:
	RPEnergyCalc();
	~RPEnergyCalc();
	bool Solve();
	RealVariable** GetVariables(Stream* refstream);
private:
	void _calcFluid(Fluid* thefluid);



};

