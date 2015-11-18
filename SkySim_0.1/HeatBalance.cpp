#include "stdafx.h"
#include "HeatBalance.h"
#include "UnitOp.h"
#include "Stream.h"

HeatBalance::HeatBalance()
{
	_name = "HeatBalance";
}


HeatBalance::~HeatBalance()
{
}


bool HeatBalance::_calculate()
{
	int nenthknown = 0;
	int nflowknown = 0; //mol basis only- let component balance handle passing of mass flow if necessary
	int nin, nout;
	int Qpresent = 0;
	int Qknown = 0;
	int DOF = 0;
	double Q = -32767;
	double H = -32767;
	double F = -32767;
	bool retval = false;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();
	double sumH = 0;
	RealVariable* Uknown = 0;
	//check molar flows
	enum CalcModeEnum { CANNOTSOLVE, CALCH, CALCQ, CALCF };
	CalcModeEnum CalcMode = CANNOTSOLVE;
	Stream* refstream = 0;
	int flowdir = 0;

	for (int i = 0; i < nin; i++)
	{
		refstream = _parent->GetStream(i, INLET);
		if (refstream->MolarFlow()->IsKnown())
		{
			nflowknown++;
			F = refstream->MolarFlow()->GetValue();
			flowdir = 1;
		}
		else if (refstream->MolarEnthalpy()->IsKnown())
		{
			CalcMode = CALCF;
			Uknown = refstream->MolarFlow();
			H = refstream->MolarEnthalpy()->GetValue();
			flowdir = -1;
		}

		if (refstream->MolarEnthalpy()->IsKnown())
		{
			nenthknown++;
			flowdir = 1;
		}
		else
		{
			CalcMode = CALCH;
			Uknown = refstream->MolarEnthalpy();
			flowdir = -1;
		}
	}

	for (int i = 0; i < nout; i++)
	{
		refstream = _parent->GetStream(i, OUTLET);
		if (refstream->MolarFlow()->IsKnown())
		{
			nflowknown++;
			F = refstream->MolarFlow()->GetValue();
		}
		else if (refstream->MolarEnthalpy()->IsKnown())
		{
			CalcMode = CALCF;
			Uknown = refstream->MolarFlow();
			H = refstream->MolarEnthalpy()->GetValue();
		}

		if (refstream->MolarEnthalpy()->IsKnown())
		{
			nenthknown++;
		}
		else
		{
			CalcMode = CALCH;
			Uknown = refstream->MolarEnthalpy();
		}
	}

	if (_heatinput != 0)
	{
		Qpresent = 1;
		if (_heatinput->IsKnown())
		{
			Qknown = 1;
		}
		else
		{
			CalcMode = CALCQ;
			Uknown = _heatinput;
		}
	}

	DOF = Qpresent + 2 * nin + 2 * nout;
	DOF = DOF - nenthknown - nflowknown - Qknown;
	if (CalcMode == CALCF&&nin==1&&nout==1)
	{
		DOF = DOF - 1;
	}

	if (nin == 1 && nout > 1)
	{
		DOF = DOF - nout+1;
	}


	if (DOF == 1)//2 equations
	{



		for (int i = 0; i < nin; i++)
		{
			refstream = _parent->GetStream(i, INLET);
			if (refstream->MolarFlow()->IsKnown() && refstream->MolarEnthalpy()->IsKnown())
			{
				sumH = sumH + refstream->MolarFlow()->GetValue()*refstream->MolarEnthalpy()->GetValue();
			}
		}
		for (int i = 0; i < nout; i++)
		{
			refstream = _parent->GetStream(i, OUTLET);
			if (refstream->MolarFlow()->IsKnown() && refstream->MolarEnthalpy()->IsKnown())
			{
				sumH = sumH - refstream->MolarFlow()->GetValue()*refstream->MolarEnthalpy()->GetValue();
			}
		}

		if (Uknown != _heatinput&&_heatinput != 0)
		{
			sumH = sumH + _heatinput->GetValue();
		}

		switch (CalcMode)
		{
		case CalcModeEnum::CALCQ:
			Q = sumH;
			_heatinput->SetValue(-Q);
			retval = true;
			break;
		case CalcModeEnum::CALCH:
			
			
			retval = true;
			H = sumH / F;

			if (nin == 1 && nout > 1)
			{
				//H = _parent->GetStream(0, INLET)->MolarEnthalpy()->GetValue();
				for (int i = 0; i < nout; i++)
				{
					refstream = _parent->GetStream(i, OUTLET);
					refstream->MolarEnthalpy()->SetValue(flowdir*H);
				}
				for (int i = 0; i < nin; i++)
				{
					refstream = _parent->GetStream(i, INLET);
					refstream->MolarEnthalpy()->SetValue(flowdir*H);
				}
			}
			else
			{
				Uknown->SetValue(flowdir*H);
			}
			
			break;
		case CalcModeEnum::CALCF:
			retval = true;
			F = sumH / H;
			Uknown->SetValue(flowdir*F);
		}
	}
	else if (DOF == 0)
	{
		retval = true;
	}

	return retval;
}