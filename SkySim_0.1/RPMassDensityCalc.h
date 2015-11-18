#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
using namespace std;

class RPMassDensityCalc :
	public PropertyCalc
{
public:

	RPMassDensityCalc();
	~RPMassDensityCalc();
	bool Solve();
	RealVariable** GetVariables(Stream* refstream);
};

