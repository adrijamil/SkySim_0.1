#pragma once
#include "BridgeFunction.h"
class HeatBalance :
	public BridgeFunction
{
public:
	//bool Solve();
	HeatBalance();
	~HeatBalance();
	void SetHeatInput(RealVariable* thevar)
	{
		_heatinput = thevar;
	}
private:
	bool _calculate();
	RealVariable* _heatinput=0;//when I add this to a unit op, connect to appropriate variable which should be instantiated by the unit op

};

