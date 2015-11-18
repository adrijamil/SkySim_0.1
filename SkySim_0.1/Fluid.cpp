#include "stdafx.h"
#include "Fluid.h"


Fluid::Fluid()
{
}


Fluid::~Fluid()
{
}


void Fluid::Normalise()
{
	double* thecomps;
	double thesum=0;
	int Nelements = _composition->Size();

	for (int i = 0; i < Nelements; i++)
	{
	cout << _composition->GetValue(i) <<"\n";
	}

	_composition->Normalise();
	//	thecomps = _composition->GetValues();
	//	//cout << _composition->Size();
		
	//	for (int i = 0; i < Nelements; i++)
	//{
	//	thesum = thesum +_composition->GetValue(i);
	//}

		for (int i = 0; i < Nelements; i++)
	{
		cout << _composition->GetValue(i) <<"\n";
	}

}

