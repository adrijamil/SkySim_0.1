#pragma once
#include "BridgeFunction.h"
class PressureBalance :
	public BridgeFunction
{
public:
	//bool Solve();
	PressureBalance();
	~PressureBalance();
private:
	bool _calculate();
};