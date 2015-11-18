#include "stdafx.h"
#include "Phase.h"






Phase::~Phase()
{

}

void Phase::SetParent(Fluid* parentstrm)
{
	_parent_stream = parentstrm;
	delete	_pressure;
	_pressure = parentstrm->Pressure();//otherwise make _pressure public to enable access. then need to think about locking it to outside objects
	
	delete	_temperature;
	_temperature = parentstrm->Temperature();


	//cout << parentstrm->Pressure();
	//cout << _pressure;
}
