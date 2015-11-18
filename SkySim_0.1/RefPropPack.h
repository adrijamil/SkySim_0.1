// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	Subclass of FlashMethod such as Ideal and RefProp
//					used to apply strategy pattern to the PropPack class
//					PropPack class keeps a reference to this object to do flash calcs
// ===============================
// TO BE IMPLEMENTED: 
// 1. To keep relevant pure component data (Tc, Pc) on board so don't have too keep reaching into PropPack. Do this on the base class
// 2. Implement this as a singleton
// ===============================
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================
#ifndef __REFPROPPACK_H_INCLUDED__
#define __REFPROPPACK_H_INCLUDED__

#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "RPManager.h"
#include "FlashMethod.h"
#include "Stream.h"


using namespace std;
//can I put this constants here?

class RefPropPack :
	public FlashMethod
{
	friend class RPEnergyCalc;
public:
	RefPropPack();
	
	~RefPropPack();

	bool Setup(PropPack* thePP);
	void Solve(FlashTypeEnum theflashtype);

private:
	RPManager* themanager;
	string _fluids_path;
	//void _setupdll();

};

#endif
