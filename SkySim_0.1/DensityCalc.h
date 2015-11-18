#pragma once
#include "PropertyCalc.h"
#include "Stream.h"

class DensityCalc :
	public PropertyCalc
{
public:
	DensityCalc();
	~DensityCalc();
	void Calculate(Stream* thestream);
	RealVariable** GetVariables(Stream* refstream);
private:
	void CalcFluid(Fluid* thefluid);
};