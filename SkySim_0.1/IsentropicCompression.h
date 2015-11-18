#pragma once
#include "BridgeFunction.h"
class IsentropicCompression :
	public BridgeFunction
{
public:

	IsentropicCompression();
	~IsentropicCompression();
	
	void SetDeltaPressure(RealVariable* thevar)
	{
		_deltapressure = thevar;
		AddVariable(thevar);
	}
	void SetEnergyInput(RealVariable* thevar)
	{
		_energyinput = thevar;
		AddVariable(thevar);
	}
	void SetIsentropicEfficiency(RealVariable* thevar)
	{
		_isentropicefficiency = thevar;
		AddVariable(thevar);
	}
private:
	bool _calculate();
	RealVariable* _energyinput = 0;//set to zero because it needs to be mapped to a variable member of a unit op. cannot exist on its own.
	RealVariable* _isentropicefficiency = 0;
	RealVariable* _deltapressure = 0;


};
