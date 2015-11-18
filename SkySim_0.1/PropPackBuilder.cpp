#include "stdafx.h"
#include "PropPackBuilder.h"



PropPackBuilder::~PropPackBuilder()
{
}

void PropPackBuilder::AddPropertyCalc(string theproperty)
{
	MolWtCalc* newproperty=new MolWtCalc;
	_current_proppack->AddProperty(newproperty);
}