#pragma once
class Stream;
#include "Phase.h"
struct fwPhase
{
	PhaseType PhaseName;
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
	//make phases as an array with names (enum


	fwPhase* Phases;

	int NComps;

	void ReadStream(Stream* thestream);
	void WriteStream(Stream* thestream);
private:
	
};

