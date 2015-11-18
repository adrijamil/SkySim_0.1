#include "stdafx.h"
#include "FlowBalance.h"
#include "UnitOp.h"
#include "Stream.h"

FlowBalance::FlowBalance()
{
	_name = "FlowBalance";
}

bool FlowBalance::_calculate()
{
	//check DOF
	//Solve if can
	//do by molar flow first - 

	int nspecced = 0;

	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	double sumF = 0;
	RealVariable* unknownF=0;
	bool molflowpassed = false;
	bool massflowpassed = false;
	int flowdir=0;

	//inlet mass flows
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MassFlow()->IsKnown())
		{
			nspecced++;
			sumF = sumF + _parent->GetStream(i, INLET)->MassFlow()->GetValue();
		}
		else
		{
			flowdir = -1;
			unknownF = _parent->GetStream(i, INLET)->MassFlow();
		}
	}
	//outlet mass flows
	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MassFlow()->IsKnown())
		{
			nspecced++;
			sumF = sumF - _parent->GetStream(i, OUTLET)->MassFlow()->GetValue();
		}
		else
		{
			flowdir = 1;
			unknownF = _parent->GetStream(i, OUTLET)->MassFlow();
		}
	}
	//pass mass variables
	if (nspecced + 1 == nin + nout)
	{
		unknownF->SetValue(sumF*flowdir);
		massflowpassed = true;
	}
	else if (nspecced == nin + nout&&abs(sumF) < 0.000001)//sumF should be 0 if its been solved
	{
		massflowpassed = true;
	}


	sumF = 0;
	 unknownF = 0;
	flowdir = 0;
	nspecced = 0;
	//inlet mol flows
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
			sumF = sumF + _parent->GetStream(i, INLET)->MolarFlow()->GetValue();
		}
		else
		{
			flowdir = -1;
			unknownF = _parent->GetStream(i, INLET)->MolarFlow();
		}
	}
	//outlet mol flows
	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->MolarFlow()->IsKnown())
		{
			nspecced++;
			sumF = sumF - _parent->GetStream(i, OUTLET)->MolarFlow()->GetValue();
		}
		else
		{
			flowdir = 1;
			unknownF = _parent->GetStream(i, OUTLET)->MolarFlow();
		}
	}
	//pass  mol variables
	if (nspecced + 1 == nin + nout)
	{
		unknownF->SetValue(sumF*flowdir);
		molflowpassed = true;
	}
	else if (nspecced == nin + nout&&abs(sumF) < 0.000001)//sumF should be 0 if its been solved
	{
		molflowpassed = true;
	}

	if (massflowpassed&&molflowpassed) //sometimes you need to send both
	{
		return true;
	}
	else
	{
		return false;
	}

}
FlowBalance::~FlowBalance()
{
}
