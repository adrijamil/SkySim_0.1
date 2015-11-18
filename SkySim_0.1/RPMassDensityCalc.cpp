#include "stdafx.h"
#include "RPMassDensityCalc.h"


RPMassDensityCalc::RPMassDensityCalc()
{
	_nvars = 9;
	_name = "DensityConversion";
}

RealVariable** RPMassDensityCalc::GetVariables(Stream* refstream)
{
	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));
	thevariables[0] = refstream->MassDensity();
	thevariables[1] = refstream->MolarDensity();
	thevariables[2] = refstream->MolecularWeight();

	thevariables[3] = refstream->Phases(0)->MassDensity();
	thevariables[4] = refstream->Phases(0)->MolarDensity();
	thevariables[5] = refstream->Phases(0)->MolecularWeight();

	thevariables[6] = refstream->Phases(1)->MassDensity();
	thevariables[7] = refstream->Phases(1)->MolarDensity();
	thevariables[8] = refstream->Phases(1)->MolecularWeight();
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
		if (_parent->RefStream()->Phases[i].MolarDensity != -32767 && _parent->RefStream()->Phases[i].MolecularWeight != -32767)
		{
			_parent->RefStream()->Phases[i].MassDensity = _parent->RefStream()->Phases[i].MolarDensity*_parent->RefStream()->Phases[i].MolecularWeight / 1000;
		}
		else if(_parent->RefStream()->Phases[i].MassDensity==-32767)
		{
			retval = false;
		}
	}

	return retval;
}