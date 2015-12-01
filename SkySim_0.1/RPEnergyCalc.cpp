#include "RPEnergyCalc.h"

typedef void(__stdcall *fp_THERMdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double &, double &, double &, double &);
fp_THERMdllTYPE THERMdll;

RPEnergyCalc::RPEnergyCalc()
{
	_nvars = 6;
	_name = "PhaseEnergyCalc";
	THERMdll = (fp_THERMdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "THERMdll");
}

RPEnergyCalc::~RPEnergyCalc()
{
}

RealVariable**  RPEnergyCalc::GetVariables(Stream* refstream)
{


	_nvars = (refstream->NPhases() )* 3; //3 for each composition,MolarEntropy and MolarEnthalpy of a phase. does not apply to overall phase.

	RealVariable** thevariables = (RealVariable**)malloc(_nvars * sizeof(thevariables[0]));

	for (int i = 0;i < _nvars / 3;i++)
	{
		cout << refstream->Phases(i)->Composition()->IsKnown() << "\n";
		cout << refstream->Phases(i)->MolarEnthalpy()->IsKnown() << "\n";
		cout << refstream->Phases(i)->MolarEnthalpy()->IsKnown() << "\n";

		thevariables[i*3 ] = refstream->Phases(i)->Composition();
		thevariables[i * 3 + 1] = refstream->Phases(i)->MolarEnthalpy();
		thevariables[i * 3 + 2] = refstream->Phases(i)->MolarEntropy();
	}
	return thevariables;

}



bool RPEnergyCalc::Solve()
{
	//fwStream* tempfwstrm = new fwStream;
	int ncomps = _parent->NComps();
	bool retval = true;
	double t, d, p, e, h, s, cv, cp, w, hjt,pcheck;
	double tol = 0.1;
	//pcheck is to check that pressure calculated by thermdll is same as input p
	double x[ncmax];

	t = _parent->RefStream()->Temperature;
	pcheck = _parent->RefStream()->Pressure;


	if (t == -32767)
	{
		return false;
	}
	for (int i = 1; i < 3; i++)
	{
		if (!_parent->RefStream()->Phases[i].Composition[0] != -32767&& _parent->RefStream()->Phases[i].MolarDensity != -32767)
		{
			for (int k = 0; k < ncomps; k++)
			{
				x[k] = _parent->RefStream()->Phases[i].Composition[k];
			}
			d = _parent->RefStream()->Phases[i].MolarDensity/1000;
			THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);

			/*if (h < 0)
			{
				h = h*-1;
			}

			if (s < 0)
			{
				s = s*-1;
			}
*/

			if (abs(pcheck - p) < tol)
			{
				_parent->RefStream()->Phases[i].Enthalpy = h;
				_parent->RefStream()->Phases[i].Entropy = s;

				//if single phase only, then single phase flash enthalpy and entropy are taken.
				if ((_parent->RefStream()->VapourFraction == 1 && _parent->RefStream()->Phases[i].PhaseFraction == 1) || (_parent->RefStream()->VapourFraction == 0 && _parent->RefStream()->Phases[i].PhaseFraction == 1))
				{
					_parent->RefStream()->Phases[0].Enthalpy = h;
					_parent->RefStream()->Phases[0].Entropy = s;
				}
			}
			else
			{
				cout << "Not convergerd: THERMdll calculated P: " << p << " error: " << abs(pcheck - p) << " \n";
				retval = false;
			}
		}
		else if (_parent->RefStream()->Phases[i].IsPresent)
		{
			retval = false;
		}
	}
	return retval;
}

void RPEnergyCalc::_calcFluid(Fluid* thefluid)
{
	
}