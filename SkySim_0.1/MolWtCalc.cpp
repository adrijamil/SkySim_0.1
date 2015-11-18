#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
	_nvars = 6;
	_name = "MolecularWeight";
}
RealVariable** MolWtCalc::GetVariables(Stream* refstream)
{
	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));
	thevariables[0] = refstream->Composition();
	thevariables[1] = refstream->MolecularWeight();

	thevariables[2] = refstream->Phases(0)->Composition();
	thevariables[3] = refstream->Phases(0)->MolecularWeight();

	thevariables[4] = refstream->Phases(1)->Composition();
	thevariables[5] = refstream->Phases(1)->MolecularWeight();
	cout << thevariables[0]->GetValue(0);
	return thevariables;
	
}
bool MolWtCalc::Solve()
{

	int ncomps = _parent->NComps();
	double theMw;
	bool retval = true;

	for (int k = 0; k < 3; k++)
	{
		theMw = 0;
		if (_parent->RefStream()->Phases[k].Composition[0] != -32767)
		{
			for (int i = 0; i < ncomps; i++)
			{
				theMw = theMw + (_parent->RefStream()->Phases[k].Composition[i] * _parent->GetComponent(i).Mw);
			}
			_parent->RefStream()->Phases[k].MolecularWeight = theMw;
		}
		else if (_parent->RefStream()->Phases[k].Composition[0] == -32767 && _parent->RefStream()->Phases[k].MolecularWeight==-32767)
		{
			retval = false;
		}
	}
	return retval;
}

MolWtCalc::~MolWtCalc()
{
}

void MolWtCalc::CalcFluid()
{
}