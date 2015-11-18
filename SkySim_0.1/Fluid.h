// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This a base class for Stream and Phase. They have common properties suvh as composition and pressure
//					Also Streams will have members of phases 
//					Should not need a name as it will not exist alone (or at all as a fluid object except in the implementation of subclasses)
//					Normalise method is included for testing. May not actually
//
// TO BE IMPLEMENTED: 
// 1. Copy/clone function
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __FLUID_H_INCLUDED__
#define __FLUID_H_INCLUDED__

#include "RealVariable.h"

using namespace std;

class Fluid
{
public:
	Fluid();
	~Fluid();
	void Normalise();
	
	RealVariable* Composition(){ return _composition; };
	RealVariable* MolecularWeight(){ return _molecularweight; };
	RealVariable* Pressure(){ return _pressure; };
	RealVariable* Temperature(){ return _temperature; };
	RealVariable* MolarEnthalpy(){ return _molenthalpy; };
	RealVariable* MolarEntropy(){ return _molentropy; };
	RealVariable* MassFlow(){ return _massflowrate; };
	RealVariable* MolarFlow(){ return _molarflowrate; };
	RealVariable* MolarDensity(){ return _molardensity; };
	RealVariable* MassDensity(){ return _massdensity; };
	
protected:
	RealVariable* _composition = new RealVariable;
	RealVariable* _molarflowrate=new RealVariable;
	RealVariable* _massflowrate = new RealVariable;
	RealVariable* _molenthalpy = new RealVariable;
	RealVariable* _molentropy = new RealVariable;
	RealVariable* _molecularweight = new RealVariable;
	RealVariable* _molardensity = new RealVariable;
	RealVariable* _massdensity = new RealVariable;

	// keep a reference.then when building the stream can just connect(ie stream pressure refers to phase pressure as well)
	//all these fuckers will be initialised by the stream object (phases and stream members point to the same variables). 
	string _BD_name;
	RealVariable* _pressure;
	RealVariable* _temperature;

	

	RealVariable* _properties; // keep this as an array to be filled by another class (not the thermo engine)// array of RealVariable that is
	int* _proppack; //keep a reference to a property package object. make it later. 

};

#endif