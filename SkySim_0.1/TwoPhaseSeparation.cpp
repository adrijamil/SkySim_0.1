#include "stdafx.h"
#include "TwoPhaseSeparation.h"
#include "UnitOp.h"
#include "Stream.h"


TwoPhaseSeparation::TwoPhaseSeparation()
{
	_name = "TwoPhaseSeparation";
}


TwoPhaseSeparation::~TwoPhaseSeparation()
{
}

bool TwoPhaseSeparation::_calculate()
{
	
	Stream* In = _parent->GetStream(0, INLET);
	Stream* Vap = _parent->GetStream(0, OUTLET);
	Stream* Liq = _parent->GetStream(1, OUTLET);
	bool comppassed = false;
	bool flowpassed = false;
	int nflowsknown = 0;

	int ncomps = In->NComps();
	
	Vap->VapourFraction()->IsCalculated(false);
	Vap->VapourFraction()->SetValue(1);

	Liq->VapourFraction()->IsCalculated(false);
	Liq->VapourFraction()->SetValue(0);

	//case 1 inlet defined
	//case 2 gas out defined
	//case 3 liquid outlet defined

	if (In->IsSolved()&&!Vap->Composition()->IsKnown()&&!Liq->Composition()->IsKnown())
	{
		Vap->Composition()->SetValues(ncomps,In->Phases(0)->Composition()->GetValues());
	//	Vap->MolarEnthalpy()->SetValue(In->Phases(0)->MolarEnthalpy()->GetValue());
		Liq->Composition()->SetValues(ncomps, In->Phases(1)->Composition()->GetValues());
	//	Liq->MolarEnthalpy()->SetValue(In->Phases(1)->MolarEnthalpy()->GetValue());
		comppassed = true;
	}
	else if (In->Composition()->IsKnown() && Vap->Composition()->IsKnown() && Liq->Composition()->IsKnown())
	{
		comppassed = true;
	}



	//do flows
	if (In->MolarFlow()->IsKnown()&& In->VapourFraction()->IsKnown() && !Vap->MolarFlow()->IsKnown()&& !Liq->MolarFlow()->IsKnown())
	{
		Vap->MolarFlow()->SetValue(In->MolarFlow()->GetValue()*In->VapourFraction()->GetValue());
		Liq->MolarFlow()->SetValue(In->MolarFlow()->GetValue()*(1-In->VapourFraction()->GetValue()));
		flowpassed = true;
	}
	else if (Vap->MolarFlow()->IsKnown() && !In->MolarFlow()->IsKnown() && !Liq->MolarFlow()->IsKnown())
	{

	}
	else if (Liq->MolarFlow()->IsKnown() && !In->MolarFlow()->IsKnown() && !Vap->MolarFlow()->IsKnown())
	{

	}
	else if (Liq->MolarFlow()->IsKnown() && In->MolarFlow()->IsKnown() && Vap->MolarFlow()->IsKnown())
	{
		flowpassed = true;
	}
	if (comppassed&&flowpassed)
	{
		_solved = true;
	}
	else
	{
		_solved = false;

	}
	return _solved;
}
