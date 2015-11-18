#include "RPEnergyCalc.h"

typedef void(__stdcall *fp_THERMdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double &, double &, double &, double &);
fp_THERMdllTYPE THERMdll;

RPEnergyCalc::RPEnergyCalc()
{
	_nvars = 6;
	_name = "PhaseEnergyCalc";
	THERMdll = (fp_THERMdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "THERMdll");;
}

RealVariable**  RPEnergyCalc::GetVariables(Stream* refstream)
{
	RealVariable** thevars = (RealVariable**)malloc(_nvars * sizeof(thevars[0]));

	thevars[0] = refstream->Phases(0)->Composition();
	thevars[1] = refstream->Phases(0)->MolarEnthalpy();
	thevars[2] = refstream->Phases(0)->MolarEntropy();

	thevars[3] = refstream->Phases(1)->Composition();
	thevars[4] = refstream->Phases(1)->MolarEnthalpy();
	thevars[5] = refstream->Phases(1)->MolarEntropy();

	return thevars;
}



bool RPEnergyCalc::Solve()
{
	//fwStream* tempfwstrm = new fwStream;
	int ncomps = _parent->NComps();
	bool retval = true;
	double t, d, p, e, h, s, cv, cp, w, hjt;
	double x[ncmax];

	t = _parent->RefStream()->Temperature;
	p = _parent->RefStream()->Pressure;


	if (t == -32767 || p == -32767)
	{
		return false;
	}
	for (int i = 1; i < 3; i++)
	{
		if (_parent->RefStream()->Phases[0].Composition[0] != -32767)
		{
			for (int k = 0; k < ncomps; k++)
			{
				x[k] = _parent->RefStream()->Phases[0].Composition[k];
			}
			THERMdll(t, d, x, p, e, h, s, cv, cp, w, hjt);
			_parent->RefStream()->Phases[i].Enthalpy = h;
			_parent->RefStream()->Phases[i].Entropy = s;
		}	
		else if (_parent->RefStream()->Phases[i].Enthalpy==-32767)
		{
			retval = false;
		}
	}
	return retval;
}

void RPEnergyCalc::_calcFluid(Fluid* thefluid)
{
	
}