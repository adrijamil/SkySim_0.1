#include "stdafx.h"
#include "DensityCalc.h"

#include "stdafx.h"
#include "MolWtCalc.h"

RealVariable**  DensityCalc::GetVariables(Stream* refstream)
{
	RealVariable** thevars = new RealVariable*[3];
	//thevars[0] = refstream->MassFlow();
	//thevars[1] = refstream->MolarFlow();
	//thevars[1] = refstream->MolecularWeight();

	return thevars;
}


void DensityCalc::Calculate(Stream* thestream)
{
	//PV=nRT for gas
	double p, t, liqmold, liqmassd, gasmold, gasmassd,totmassd,totmold;

	int ncomps = _parent->NComps();

	p = thestream->Pressure()->GetValue() * 1000;//convert to pascal
	t = thestream->Temperature()->GetValue();

	gasmold = p / t / 8.314462; //this is mol/m3
	thestream->Phases(0)->MolarDensity()->SetValue(gasmold);

	gasmassd = gasmold*thestream->MolecularWeight()->GetValue() / 1000;
	thestream->Phases(0)->MassDensity()->SetValue(gasmassd);


	liqmassd = 0;

	for (int i = 0; i < ncomps; i++)
	{
		liqmassd = liqmassd + (thestream->Phases(1)->Composition()->GetValue(i))*_parent->GetComponent(i).StdIdealLiqDens;
	}

	thestream->Phases(1)->MassDensity()->SetValue(liqmassd);

	liqmold = liqmassd / thestream->MolecularWeight()->GetValue() * 1000;
	thestream->Phases(1)->MolarDensity()->SetValue(liqmold);
	
	
	totmold = gasmold*thestream->VapourFraction()->GetValue() + liqmold*(1 - thestream->VapourFraction()->GetValue());
	totmassd = totmold*thestream->MolecularWeight()->GetValue() / 1000;
	thestream->MolarDensity()->SetValue(totmold);
	thestream->MassDensity()->SetValue(totmassd);
}



void DensityCalc::CalcFluid(Fluid* thefluid)
{


}

DensityCalc::DensityCalc()
{
}


DensityCalc::~DensityCalc()
{
}
