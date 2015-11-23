#pragma once
class Stream;
#include "Phase.h"
#include <vector>
struct fwPhase
{
	fwPhase() : 
		IsPresent(false), 
		MassFlow(-32767), 
		MolarFlow(-32767),
		PhaseFraction(-32767),
		Enthalpy(-32767),
		Entropy(-32767),
		MolarDensity(-32767),
		MolecularWeight(-32767),
		MassDensity(-32767)
		{
			Composition = new double(-32767);
		}
	PhaseTypeEnum PhaseName;
	bool IsPresent;
	double MassFlow;
	double MolarFlow;
	double PhaseFraction;
	double Enthalpy;
	double Entropy;
	double* Composition;
	double MolarDensity;
	double MassDensity;
	double MolecularWeight;
};


class fwStream
{
public:
	fwStream();
	~fwStream();
	double Pressure;
	double Temperature;
	double VapourFraction;
	//make phases as an array with names (enum)
	std::vector <fwPhase> Phases; //overall,vapour,liquid,aqueous
	int NComps;
	void ReadStream(Stream* thestream);
	void WriteStream(Stream* thestream);
	
private:
	int _nphases;

};

