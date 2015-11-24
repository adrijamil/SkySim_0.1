#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
	_nvars = 9;
	_name = "DensityConversion";
}

RealVariable** RPMassDensityCalc::GetVariables(Stream* refstream)
{
	_nvars = refstream->NPhases() * 3; //2 for each mass density and molecular weight and MolarDensity of a phase.

	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));

	for (int i = 0;i < _nvars / 3;i++)
	{
		if (i == 0)
		{
			thevariables[i * 3] = refstream->MassDensity();
			thevariables[i * 3 + 1] = refstream->MolarDensity();
			thevariables[i * 3 + 2] = refstream->MolecularWeight();
		}
		else
		{
			thevariables[i * 3] = refstream->Phases(i - 1)->MassDensity();
			thevariables[i * 3 + 1] = refstream->Phases(i - 1)->MolarDensity();
			thevariables[i * 3 + 2] = refstream->Phases(i - 1)->MolecularWeight();
		}
	}


	return thevariables;
}



RPMassDensityCalc::~RPMassDensityCalc()
{
}
bool RPMassDensityCalc::Solve()
{
	bool retval = true;
	double massd;
	for (int i = 0; i < 3; i++)
	{
		if (_parent->RefStream()->Phases[i].IsPresent)
		{
			if (_parent->RefStream()->Phases[i].MolarDensity != -32767 && _parent->RefStream()->Phases[i].MolecularWeight != -32767)
			{
				_parent->RefStream()->Phases[i].MassDensity = _parent->RefStream()->Phases[i].MolarDensity*_parent->RefStream()->Phases[i].MolecularWeight / 1000;
			}
			else if (_parent->RefStream()->Phases[i].MassDensity == -32767)
			{
				retval = false;
			}
		}
	}

	return retval;
}