#include "stdafx.h"
#include "fwStream.h"
#include "Stream.h"

fwStream::fwStream()
{

	fwPhase* newphase = new fwPhase;
	newphase->PhaseName = OVERALL;
	Phases.push_back(*newphase);

	newphase = new fwPhase;
	newphase->PhaseName = VAPOUR;
	Phases.push_back(*newphase);

	newphase = new fwPhase;
	newphase->PhaseName = HCLIQUID;
	Phases.push_back(*newphase);

	newphase = new fwPhase;
	newphase->PhaseName = AQUEOUS;
	Phases.push_back(*newphase);

	cout << Phases[0].PhaseName;
	cout << Phases[1].PhaseName;
	cout << Phases[2].PhaseName;
	cout << Phases[3].PhaseName;
}


void fwStream::ReadStream(Stream* thestream)
{


	NComps = thestream->NComps();

	_nphases = thestream->NPhases();
	//Phases = new fwPhase[_nphases+1];


	//assume all phases are not there
	for (int k = 1;k < 4;k++)
	{
		Phases[k].IsPresent = false;
	}
	PhaseTypeEnum phtype;
	//do for all phases. if not present set to -32767
	//define phases
	Phase* tempphase;
	int j;
	for (int i = 0;i < 4; i++)
	{
		if (i == 0)
		{
			Phases[i].Composition = new double[NComps];
			Phases[i].MassFlow = thestream->MassFlow()->GetValue();
			Phases[i].MolarFlow = thestream->MolarFlow()->GetValue();
			Phases[i].Enthalpy = thestream->MolarEnthalpy()->GetValue();
			Phases[i].Entropy = thestream->MolarEntropy()->GetValue();
			Phases[i].MolarDensity = thestream->MolarDensity()->GetValue();
			Phases[i].MassDensity = thestream->MassDensity()->GetValue();
			Phases[i].MolecularWeight = thestream->MolecularWeight()->GetValue();
			Phases[i].Composition = thestream->Composition()->GetValues();
			Phases[i].PhaseFraction = 1;

			Phases[i].IsPresent = true;
		}
		else
		{
			tempphase=thestream->Phases(Phases[i].PhaseName);

			if (!tempphase == NULL) //phase is present in the stream;
			{
				Phases[i].Composition = new double[NComps];
				Phases[i].Composition = tempphase->Composition()->GetValues();
				Phases[i].MassFlow = tempphase->MassFlow()->GetValue();
				Phases[i].MolarFlow = tempphase->MolarFlow()->GetValue();
				Phases[i].Enthalpy = tempphase->MolarEnthalpy()->GetValue();
				Phases[i].Entropy = tempphase->MolarEntropy()->GetValue();
				Phases[i].MolarDensity = tempphase->MolarDensity()->GetValue();
				Phases[i].MassDensity = tempphase->MassDensity()->GetValue();
				Phases[i].MolecularWeight = tempphase->MolecularWeight()->GetValue();
				Phases[i].PhaseFraction = tempphase->PhaseMoleFraction()->GetValue();;
				Phases[i].IsPresent = true;
			}
			else // phase is present in the stream;
			{
				Phases[i].Composition = new double[NComps] {-32767};
				Phases[i].MassFlow = -32767;
				Phases[i].MolarFlow = -32767;
				Phases[i].Enthalpy = -32767;
				Phases[i].Entropy = -32767;
				Phases[i].MolarDensity = -32767;
				Phases[i].MassDensity = -32767;
				Phases[i].MolecularWeight = -32767;
				Phases[i].PhaseFraction = 0;
				Phases[i].IsPresent = false;
			}
		}
		
	}

	Pressure=thestream->Pressure()->GetValue();
	Temperature = thestream->Temperature()->GetValue();
	VapourFraction = thestream->VapourFraction()->GetValue();

}
fwStream::~fwStream()
{
	
}






void fwStream::WriteStream(Stream* thestream)
{
	//put something to check if phases correspond
	thestream->Pressure()->SetValue(Pressure);
	thestream->Temperature()->SetValue(Temperature);
	thestream->Phases(0)->PhaseMoleFraction()->SetValue(VapourFraction);
	Phase* tempphase;

	//why would vfrac be 0
	//if (VapourFraction != -32767){ thestream->Phases(1)->PhaseMoleFraction()->SetValue(1 - VapourFraction); }
	_nphases = thestream->NPhases();
	for (int i = 0;i < 4;i++)
	{
		if (i == 0)
		{
			thestream->MassFlow()->SetValue(Phases[i].MassFlow);
			thestream->MolarFlow()->SetValue(Phases[i].MolarFlow);
			thestream->MolarEnthalpy()->SetValue(Phases[i].Enthalpy);
			thestream->MolarEntropy()->SetValue(Phases[i].Entropy);
			thestream->MolarDensity()->SetValue(Phases[i].MolarDensity);
			thestream->MassDensity()->SetValue(Phases[i].MassDensity);
			thestream->MolecularWeight()->SetValue(Phases[i].MolecularWeight);
			thestream->Composition()->SetValues(NComps, Phases[i].Composition);
		}
		else
		{
			if (Phases[i].IsPresent)
			{
				tempphase = thestream->Phases(Phases[i].PhaseName);
				if (tempphase == NULL)
				{
					thestream->_addphase(Phases[i].PhaseName);
					tempphase = thestream->Phases(Phases[i].PhaseName);
				}
				tempphase->MassFlow()->SetValue(Phases[i].MassFlow);
				tempphase->MolarFlow()->SetValue(Phases[i].MolarFlow);
				tempphase->MolarEnthalpy()->SetValue(Phases[i].Enthalpy);
				tempphase->MolarEntropy()->SetValue(Phases[i].Entropy);
				tempphase->MolarDensity()->SetValue(Phases[i].MolarDensity);
				tempphase->MassDensity()->SetValue(Phases[i].MassDensity);
				tempphase->MolecularWeight()->SetValue(Phases[i].MolecularWeight);
				tempphase->Composition()->SetValues(NComps, Phases[i].Composition);
				tempphase->PhaseMoleFraction()->SetValue(Phases[i].PhaseFraction);
				cout << Phases[i].PhaseName<<"\n";
				cout << Phases[i].PhaseFraction << "\n";
				cout << Phases[i].MolarFlow << "\n";
				cout << Phases[i].MassFlow << "\n";
			}
			else if (!thestream->Phases(Phases[i].PhaseName) == NULL)
			{
				thestream->_removephase(Phases[i].PhaseName);
			}
		}
	}
}