#include "stdafx.h"
#include "IsentropicCompression.h"
#include "UnitOp.h"
#include "Stream.h"

IsentropicCompression::IsentropicCompression()
{
	_name = "IsentropicCompression";
}

IsentropicCompression::~IsentropicCompression()
{

}

bool IsentropicCompression::_calculate()
{
	//if it is solved it shouldnt be called again
	//if (_solved)
	//{
	//	return true;
	//}
	
	enum CalcModeEnum { CANNOTSOLVE, CALCF,CALCP1,CALCP2,CALCH1,CALCH2,CALCEFF,SOLVED }; // need to know if solved or not
	CalcModeEnum CalcMode = CANNOTSOLVE;
	bool pressuresolved = false;
	RealVariable* P1 = _parent->GetStream(0, INLET)->Pressure();
	RealVariable* P2 = _parent->GetStream(0, OUTLET)->Pressure();
	RealVariable* H1 = _parent->GetStream(0, INLET)->MolarEnthalpy();
	RealVariable* H2 = _parent->GetStream(0, OUTLET)->MolarEnthalpy();
	RealVariable* dP = _deltapressure;
	RealVariable* F = _parent->GetStream(0, INLET)->MolarFlow();
	RealVariable* Eff = _isentropicefficiency;
	RealVariable* Q = _energyinput;
	int nspecs = 0;

	if (dP->IsKnown())
	{
		if (P1->IsKnown()&&!P2->IsKnown())
		{
			P2->SetValue(P1->GetValue() + dP->GetValue());
		}
		else if (P2->IsKnown() && !P1->IsKnown())
		{
			P1->SetValue(P2->GetValue() - dP->GetValue());
		}
	}
	else if (P1->IsKnown()&&P2->IsKnown())
	{
		dP->SetValue(P2->GetValue() - P1->GetValue());
	}



	Stream* tempstream = new Stream;
	fwStream* tempfw = new fwStream;

//	double q;
	double n;
	double h1;
	//double s1;
	double h2p;//h2p is isetropic h2 (100% eff)
	double f;
	double err = 1000;
	double tol = 0.00001;
	//double targ1, targ2;


	if (!P2->IsKnown())
	{
		//try calc based on Q,P1,h1,F and eff
		//if h2 is known, then energy balance should set the Q
		if (Q->IsKnown() && P1->IsKnown() && H1->IsKnown() && F->IsKnown() && Eff->IsKnown())
		{
			//get s1
			//get h2p = Q*eff+h1
			//get p2 -> flash at s1,h2p  //theres no sh flash though.
			tempfw->ReadStream(_parent->GetStream(0, INLET));
			f = tempfw->Phases[0].MolarFlow;
			n = _isentropicefficiency->GetValue();

			//get h2p
			h2p = tempfw->Phases[0].Enthalpy + Q->GetValue()*Eff->GetValue()/f;
			
			double fx, fxold, xguess, xguessold,temp;
			xguessold = P1->GetValue() * 2;
			xguess = P1->GetValue() * 2.1;
			tempfw->Pressure = xguessold;
			tempfw->VapourFraction = -32767;
			tempfw->Temperature = -32767;
			tempfw->Phases[0].Enthalpy = -32767;
			tempfw->WriteStream(tempstream);
			tempstream->SetPropertyPackage(_parent->GetStream(0, INLET)->GetPropertyPackage());
			tempstream->Solve();
			fxold = tempstream->MolarEnthalpy()->GetValue() - h2p;

			tempstream = new Stream;
			tempfw->Pressure = xguess;
			tempfw->WriteStream(tempstream);
			tempstream->SetPropertyPackage(_parent->GetStream(0, INLET)->GetPropertyPackage());
			tempstream->Solve();
			fx = tempstream->MolarEnthalpy()->GetValue()-h2p;
			//secant to desired h2
			
			while (abs(fx) > tol)
			{
				temp = xguess;

				xguess = xguess - fx*(xguess - xguessold) / (fx - fxold);
				xguessold = temp;
				fxold = fx;

				tempstream = new Stream;
				tempfw->Pressure = xguess;
				tempfw->WriteStream(tempstream);
				tempstream->SetPropertyPackage(_parent->GetStream(0, INLET)->GetPropertyPackage());
				tempstream->Solve();
				fx = tempstream->MolarEnthalpy()->GetValue() - h2p;
				cout <<"fx: "<< fx << "\n";
			}	

			H2->SetValue(H1->GetValue()+Q->GetValue()/f);
			P2->SetValue(xguess);
			pressuresolved = true;

		}
		
		
	}//if (!P2->IsKnown())
	
	else if (!H2->IsKnown())
	{
		//calc based on P1,P2,H1 and eff,F. let energy balance backout the Q
		if (P1->IsKnown() && P2->IsKnown() && H1->IsKnown()&&Eff->IsKnown()&&F->IsKnown())
		{
			//get h2p based on p1,p2 (isentropic 100% eff)
			//then get h2 based on eff
			//s1 = _parent->GetStream(0, INLET)->MolarEntropy()->GetValue();
			tempfw->ReadStream(_parent->GetStream(0, INLET));
			tempfw->Phases[0].Entropy= _parent->GetStream(0, INLET)->MolarEntropy()->GetValue();
			cout << "entropy" << tempfw->Phases[0].Entropy << "\n";
			tempfw->Pressure = P2->GetValue();
			//set other state variable to empty
			tempfw->VapourFraction = -32767;
			tempfw->Phases[1].PhaseFraction = -32767;
			tempfw->Temperature = -32767;
			tempfw->Phases[0].Enthalpy = -32767;

			tempstream = new Stream;
			tempfw->WriteStream(tempstream);

			tempstream->SetPropertyPackage(_parent->GetStream(0, INLET)->GetPropertyPackage());
			tempstream->Solve();
			h2p = tempstream->MolarEnthalpy()->GetValue();
			h1 = H1->GetValue();
			n = Eff->GetValue();
			H2->SetValue(h1 + (h2p - h1) / n);
			pressuresolved = true;
		}
	}
	else if (!P1->IsKnown())
	{

	}

	if (pressuresolved)
	{
		_solved = true;
	}

	return pressuresolved;
}
