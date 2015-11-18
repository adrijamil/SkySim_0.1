#pragma once
#include "BridgeFunction.h"
class TwoPhaseSeparation :
	public BridgeFunction
{
public:
	TwoPhaseSeparation();
	~TwoPhaseSeparation();
private:
	bool _calculate();
};


