#pragma once
#include "BridgeFunction.h"
class FlowBalance :
	public BridgeFunction
{
public:
	//bool Solve();
	FlowBalance();
	~FlowBalance();

private:
	bool _calculate();

};

