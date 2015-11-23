#include "stdafx.h"
#include "MolWtCalc.h"


MolWtCalc::MolWtCalc()
{
	
	_name = "MolecularWeight";
}
RealVariable** MolWtCalc::GetVariables(Stream* refstream)
{
	_nvars =( refstream->NPhases()+1) * 2; //2 for each composition and molecular weight of a phase.

	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));

	for (int i = 0;i < _nvars / 2;i++)
	{
		if (i == 0)
		{
			thevariables[i*2] = refstream->Composition();
			thevariables[i*2+1] = refstream->MolecularWeight();
		}
		else
		{
			thevariables[i * 2] = refstream->Phases(i-1)->Composition();
			thevariables[i * 2 + 1] = refstream->Phases(i - 1)->MolecularWeight();
		}
		
	}
	return thevariables;

}
bool MolWtCalc::Solve()
{
	int ncomps = _parent->NComps();
	double theMw;
	bool retval = true;
	


	for (int k = 0; k < 4; k++)
	{
		if (_parent->RefStream()->Phases[k].IsPresent)
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
			else if (_parent->RefStream()->Phases[k].Composition[0] == -32767 && _parent->RefStream()->Phases[k].MolecularWeight == -32767)
			{
				retval = false;
			}
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