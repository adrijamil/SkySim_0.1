#include "stdafx.h"
#include "PressureBalance.h"
#include "UnitOp.h"
#include "Stream.h"

PressureBalance::PressureBalance()
{
	_name = "PressureBalance";
}


PressureBalance::~PressureBalance()
{
}


bool PressureBalance::_calculate()
{
	//if mixer then then lowest inlet
	//if splitter than equalise all
	int nspecced = 0;
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	bool retval = false;

	double p = 1e50;
	for (int i = 0; i < nin; i++)
	{
		if (_parent->GetStream(i, INLET)->Pressure()->IsKnown())
		{
			if (_parent->GetStream(i, INLET)->Pressure()->GetValue() < p)
			{
				p = _parent->GetStream(i, INLET)->Pressure()->GetValue();
			}
			nspecced++;
		}
	}

	for (int i = 0; i < nout; i++)
	{
		if (_parent->GetStream(i, OUTLET)->Pressure()->IsKnown())
		{
			p = _parent->GetStream(i, OUTLET)->Pressure()->GetValue();
			nspecced++;
		}
	}

	if (nout == 1)//mixer, set to lowest
	{
		if (nspecced <= (nin + nout))
		{
			for (int i = 0; i < nin; i++)
			{
				if (!_parent->GetStream(i, INLET)->Pressure()->IsKnown())
				{
					_parent->GetStream(i, INLET)->Pressure()->SetValue(p);
				}
			}

			for (int i = 0; i < nout; i++)
			{
				if (!_parent->GetStream(i, OUTLET)->Pressure()->IsKnown())
				{
					_parent->GetStream(i, OUTLET)->Pressure()->SetValue(p);
				}
			}
			retval = true;
		}

	}
	else//must be nin =1//rmb to prevent adding more inlets/outlets for splitter/mixer
	{
		if (nspecced >0)
		{
			for (int i = 0; i < nin; i++)
			{
				if (!_parent->GetStream(i, INLET)->Pressure()->IsKnown())
				{
					_parent->GetStream(i, INLET)->Pressure()->SetValue(p);
				}
			}

			for (int i = 0; i < nout; i++)
			{
				if (!_parent->GetStream(i, OUTLET)->Pressure()->IsKnown())
				{
					_parent->GetStream(i, OUTLET)->Pressure()->SetValue(p);
				}
			}
			retval = true;
		}
	}
	return retval;
}