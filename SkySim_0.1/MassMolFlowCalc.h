#pragma once
#include "PropertyCalc.h"
#include "Stream.h"
#include "PropPack.h"
using namespace std;

class MassMolFlowCalc :
	public PropertyCalc
{
public:
	//_refstream = theRS;
	
	MassMolFlowCalc();
	~MassMolFlowCalc();
	bool Solve();
	//RealVariable** GetVariables(Stream* refstream, RealVariable** thevariables);
	RealVariable**  GetVariables(Stream* refstream);

};

