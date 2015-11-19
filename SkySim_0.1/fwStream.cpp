#include "stdafx.h"
#include "fwStream.h"
#include "Stream.h"

fwStream::fwStream()
{

}
//fwPhase fwStream::Phase(PhaseType thephasename) //phasenames are -1:overall, 0: vapour, 1:HCLiquid
//{
//	int i = thephasename;
//	return Phase(i);
//}
//
//fwPhase fwStream::Phase(int phasenumber)//this sub offsets by one//supposed to be more intuitive
//{
//	int i = phasenumber + 1;
//	return Phases[phasenumber];
//}

void fwStream::ReadStream(Stream* thestream)
{
	if (this == NULL)
	{
		cout << "how am i nothing";
	}
	NComps = thestream->NComps();

	 _nphases = thestream->NPhases();
	Phases = new fwPhase[_nphases+1];
	Phases[0].PhaseName = OVERALL;

	for (int i = 1;i < _nphases+1; i++)
	{
		Phases[i].PhaseName = thestream->Phases(i)->PhaseType();
	}
	

	Pressure=thestream->Pressure()->GetValue();
	Temperature = thestream->Temperature()->GetValue();
	VapourFraction = thestream->VapourFraction()->GetValue();
	for (int i = 0; i < _nphases+1; i++) // add 1 for overall
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
		}
		else
		{
			Phases[i].Composition = new double[NComps];
			Phases[i].MassFlow = thestream->Phases(i - 1)->MassFlow()->GetValue();
			Phases[i].MolarFlow = thestream->Phases(i - 1)->MolarFlow()->GetValue();
			Phases[i].Enthalpy = thestream->MolarEnthalpy()->GetValue();
			Phases[i].Enthalpy = thestream->Phases(i - 1)->MolarEnthalpy()->GetValue();
			Phases[i].Entropy = thestream->Phases(i - 1)->MolarEntropy()->GetValue();
			Phases[i].MolarDensity = thestream->Phases(i - 1)->MolarDensity()->GetValue();
			Phases[i].MassDensity = thestream->Phases(i - 1)->MassDensity()->GetValue();
			Phases[i].MolecularWeight = thestream->Phases(i - 1)->MolecularWeight()->GetValue();
			Phases[i].Composition = thestream->Phases(i - 1)->Composition()->GetValues();
		}
		
	}

}
fwStream::~fwStream()
{
	
}


void fwStream::AddPhase(PhaseTypeEnum thephasetype)
{
	fwPhase* tempPhases = new fwPhase[_nphases + 1];
	_nphases++;
	
	int i = thephasetype;
	//phases must be in order -> vap,liq,aq

	Phases = (fwPhase*)realloc(Phases, _nphases* sizeof(Phases[0]));
	if (_phases != NULL) //if it's null then realloc tak jadi
	{
		_phases[i] = &(*thenewphase);
	}

}

void fwStream::RemovePhase(PhaseTypeEnum thephasetype)
{
	fwPhase* tempPhases = new fwPhase[_nphases + 1];
	_nphases++;

	//complete this


}

void fwStream::WriteStream(Stream* thestream)
{
	//put something to check if phases correspond
	thestream->Pressure()->SetValue(Pressure);
	thestream->Temperature()->SetValue(Temperature);
	thestream->Phases(0)->PhaseMoleFraction()->SetValue(VapourFraction);
	if (VapourFraction != -32767){ thestream->Phases(1)->PhaseMoleFraction()->SetValue(1 - VapourFraction); }
	for (int i = 0; i < 3; i++)
	{
		if (i==0) 
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
			thestream->Phases(i - 1)->MassFlow()->SetValue(Phases[i].MassFlow);
			thestream->Phases(i - 1)->MolarFlow()->SetValue(Phases[i].MolarFlow);
			thestream->Phases(i - 1)->MolarEnthalpy()->SetValue(Phases[i].Enthalpy);
			thestream->Phases(i - 1)->MolarEntropy()->SetValue(Phases[i].Entropy);
			thestream->Phases(i - 1)->MolarDensity()->SetValue(Phases[i].MolarDensity);
			thestream->Phases(i - 1)->MassDensity()->SetValue(Phases[i].MassDensity);
			thestream->Phases(i - 1)->MolecularWeight()->SetValue(Phases[i].MolecularWeight);
			thestream->Phases(i - 1)->Composition()->SetValues(NComps, Phases[i].Composition);
		}
		
	}
	
}