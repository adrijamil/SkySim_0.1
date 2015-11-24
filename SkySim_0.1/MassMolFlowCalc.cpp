#include "stdafx.h"
#include "MassMolFlowCalc.h"


MassMolFlowCalc::MassMolFlowCalc()
{
	//_nvars = 10;
	_name = "MassMoleFlowConversion";
}
RealVariable**  MassMolFlowCalc::GetVariables(Stream* refstream)
{
	//fmass
	//fmol
	//mw

	int nphase = refstream->NPhases();
	_nvars = nphase* 4+3; //2 for each MassFlow,MolarFlow and MolecularWeight of a phase. + 1 for vapourfraction.

	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));

	for (int i = 0;i < nphase+1;i++)
	{
		if (i == 0)
		{
			thevariables[i * 3] = refstream->MassFlow();
			thevariables[i * 3 + 1] = refstream->MolarFlow();
			thevariables[i * 3 + 2] = refstream->MolecularWeight();
		}
		else
		{
			thevariables[i * 4 -1] = refstream->Phases(i - 1)->MassFlow();
			thevariables[i * 4 ] = refstream->Phases(i - 1)->MolarFlow();
			thevariables[i * 4 + 1] = refstream->Phases(i - 1)->MolecularWeight();
			thevariables[i * 4 + 2] = refstream->Phases(i - 1)->PhaseMoleFraction();
		}
	}
	return thevariables;
}

bool MassMolFlowCalc::Solve()
{
	double fmass, fmol;
	bool retval = true;



	//do overall
	fwStream* thefw = _parent->RefStream();
	int i = 0;
	//if dunno mass try calc

	//vap
	cout << "vap fraction: " << thefw->VapourFraction<< "\n";
	cout << "phase: " << thefw->Phases[1].PhaseName << "\n";
	cout << "ispresent: " << thefw->Phases[1].IsPresent << "\n";
	cout << "massflow: " << thefw->Phases[1].MassFlow << "\n";
	cout << "moleflow: " << thefw->Phases[1].MolarFlow << "\n";
	cout << "mw: " << thefw->Phases[1].MolecularWeight << "\n";
	cout << "fraction: " << thefw->Phases[1].PhaseFraction << "\n";
	//liq

	cout << "phase: " << thefw->Phases[2].PhaseName << "\n";
	cout << "ispresent: " << thefw->Phases[2].IsPresent << "\n";
	cout << "massflow: " << thefw->Phases[2].MassFlow << "\n";
	cout << "moleflow: " << thefw->Phases[2].MolarFlow << "\n";
	cout << "mw: " << thefw->Phases[2].MolecularWeight << "\n";
	cout << "fraction: " << thefw->Phases[2].PhaseFraction << "\n";

	if (thefw->Phases[i].MassFlow == -32767)
	{
		if (thefw->Phases[i].MolarFlow != -32767)
		{
			if (thefw->Phases[i].MolecularWeight != -32767)
			{
				fmass = thefw->Phases[i].MolarFlow * thefw->Phases[i].MolecularWeight;
				thefw->Phases[i].MassFlow = fmass;
			}
		}
	}
	if (thefw->Phases[i].MassFlow == -32767)
	{
		retval = false;
	}

	//if dunno molar flow then calc;
	if (thefw->Phases[i].MolarFlow == -32767)
	{
		if (thefw->Phases[i].MassFlow != -32767)
		{
			if (thefw->Phases[i].MolecularWeight != -32767)
			{
				fmol = thefw->Phases[i].MassFlow / thefw->Phases[i].MolecularWeight;
				thefw->Phases[i].MolarFlow = fmol;
			}
		}
	}
	if (thefw->Phases[i].MolarFlow == -32767)
	{
		retval = false;
	}

	

	



	//do gas and liquid
	for (int i = 1; i < 3; i++)
	{
		if (thefw->Phases[i].IsPresent)
		{
			if (thefw->Phases[i].MolarFlow == -32767)
			{
				//try get from mass flow and molecular weight
				if (thefw->Phases[i].MassFlow != -32767)
				{
					if (thefw->Phases[i].MolecularWeight != -32767)
					{
						fmol = thefw->Phases[i].MassFlow / thefw->Phases[i].MolecularWeight;
						thefw->Phases[i].MolarFlow = fmol;
					}
				}
				else if (thefw->Phases[i].PhaseFraction != -32767 && thefw->Phases[0].MolarFlow != -32767)
				{
					
					fmol = thefw->Phases[0].MolarFlow*thefw->Phases[i].PhaseFraction;
					
					thefw->Phases[i].MolarFlow = fmol;
				}

			}
			//if not enough info
			if (thefw->Phases[i].MolarFlow == -32767)
			{
				retval = false;
			}
			//then try mass flow
			if (thefw->Phases[i].MassFlow == -32767)
			{
				if (thefw->Phases[i].MolarFlow != -32767)
				{
					if (thefw->Phases[i].MolecularWeight != -32767)
					{
						fmass = thefw->Phases[i].MolarFlow * thefw->Phases[i].MolecularWeight;
						thefw->Phases[i].MassFlow = fmass;
					}
				}
			}
			if (thefw->Phases[i].MassFlow == -32767)
			{
				retval = false;
			}
		}
		
	}
	return retval;
}

MassMolFlowCalc::~MassMolFlowCalc()
{
}
