#include "stdafx.h"
#include "Stream.h"
#include "StreamCalc.h"



void Stream::_initialise()
{
	_pressure = new RealVariable;
	_temperature = new RealVariable;

	//by default add a vapour phase
	//should be handled by flash method -> other methods may provide more or less variables

	_addphase(VAPOUR);//this sets the _vapourfraction to PhaseMoleFraction
	std::cout << "pre adding variables\n";
	std::cout << "Stream _vapourfraction " << _vapourfraction << "\n";
	std::cout << "Vapour PhaseFraction " << Phases(VAPOUR)->PhaseMoleFraction() << "\n";

	AddVariable(_pressure);
	AddVariable(_temperature);
	AddVariable(_molenthalpy);
	AddVariable(_molentropy);
	AddVariable(_composition);
	AddVariable(_molardensity);

	std::cout << "post stream initialise \n";
	std::cout << "Stream _vapourfraction " << VapourFraction() << "\n";
	std::cout << "Vapour PhaseFraction " << Phases(VAPOUR)->PhaseMoleFraction() << "\n";
	
}

Stream::Stream()
{
	_name = "NONAME";
	_initialise();
}


Stream::Stream(string daname)
{
	_name = daname;
	_initialise();
}

void Stream::SetPropertyPackage(PropPack* thePP)
{
	_proppack = thePP;
}

void Stream::_setstreamcalcs()
{
	int ncalcs;

	ncalcs = _proppack->Properties()->NChildren();
	
	_streamcalcs = new StreamCalc[ncalcs];

		for (int i = 0; i < ncalcs; i++)
		{
			_streamcalcs[i].Setup(_proppack->Properties()->GetProperty(i), this);

		}

	_nstreamcalcs = ncalcs + 1;
}




Stream::~Stream()
{
}


bool Stream::Solve()
{
	std::cout << "Vapfrac isknown " << _vapourfraction->IsKnown() << "\n";
	std::cout << "Vapfrac value " << _vapourfraction->GetValue() << "\n";
	bool retval=true;
	//check DOF then call appropriate flash

	//calc specs
	FlashTypeEnum thetype;

	cout << _name;

	int nspecs=0;

	if (_pressure->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_temperature->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_vapourfraction->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molenthalpy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molentropy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_composition->IsKnown())
	{
		nspecs = nspecs + 1;
	}
	

	if ((nspecs != 3))
	{
		
		cout << "Specifation error \n";
		retval = false;
		return retval;
		
	}


		if ((_pressure->IsKnown()) && (_temperature->IsKnown()))
		{
			thetype = PT;
		}
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_temperature->IsKnown()))
		{
			thetype = TQ;
		}
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_pressure->IsKnown()))
		{
			thetype = PQ;
		}
		else if ((_molenthalpy->IsKnown()) && (_pressure->IsKnown()))
		{
			thetype = PH;
		}
		else if ((_molentropy->IsKnown()) && (_pressure->IsKnown()))
		{
			thetype = PS;
		}
		else if ((_molentropy->IsKnown()) && (_temperature->IsKnown()))
		{
			thetype = TS;
		}
		else if ((_molenthalpy->IsKnown()) && (_temperature->IsKnown()))
		{
			thetype = TH;
		}


		_proppack->RefStream()->ReadStream(this);
		if (!_proppack->Flash(thetype))
		{
			retval = false;
		}

	othercalcs:

	_proppack->RefStream()->WriteStream(this);


	cout << "variables in stack object \n";
	for (int k = 0;k < _nvariables;k++)
	{
		cout << _variables[k].first << "\n";
	}

	StackObject* thefsob = this;
	if (retval)
	{
		cout << "variables in stream object \n";
		switch (thetype) {
		case PT:
			_molardensity->CalculatedBy(thefsob);
			cout << _molardensity << "\n";
			_molenthalpy->CalculatedBy(thefsob);
			cout << _molenthalpy << "\n";
			_molentropy->CalculatedBy(thefsob);
			cout << _molentropy << "\n";
			_vapourfraction->CalculatedBy(thefsob);
			cout << _vapourfraction << "\n";
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				cout << _phases[k]->MolarDensity() << "\n";
				_phases[k]->Composition()->CalculatedBy(thefsob);
				cout << _phases[k]->Composition() << "\n";
				_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
				cout << _phases[k]->PhaseMoleFraction() << "\n";
			}


			break;
		case TQ:
			_molardensity->CalculatedBy(thefsob);
			_molenthalpy->CalculatedBy(thefsob);
			_molentropy->CalculatedBy(thefsob);
			_pressure->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				if (_phases[k]->PhaseType() != 0) //except vapour fraction
				{
					_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
				}
				
			}
			break;
		case PQ:
			_molardensity->CalculatedBy(thefsob);
			_molenthalpy->CalculatedBy(thefsob);
			_molentropy->CalculatedBy(thefsob);
			_temperature->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				if (_phases[k]->PhaseType() != 0) //except vapour fraction
				{
					_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
				}
			}
			break;
		case PH:
			_molardensity->CalculatedBy(thefsob);
			_temperature->CalculatedBy(thefsob);
			_molentropy->CalculatedBy(thefsob);
			_vapourfraction->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
			}
			break;
		case PS:
			_molardensity->CalculatedBy(thefsob);
			_temperature->CalculatedBy(thefsob);
			_molenthalpy->CalculatedBy(thefsob);
			_vapourfraction->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
			}
			break;
		case TS:
			_molardensity->CalculatedBy(thefsob);
			_pressure->CalculatedBy(thefsob);
			_molenthalpy->CalculatedBy(thefsob);
			_vapourfraction->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
			}
			break;
		case TH:
			_molardensity->CalculatedBy(thefsob);
			_pressure->CalculatedBy(thefsob);
			_molentropy->CalculatedBy(thefsob);
			_vapourfraction->CalculatedBy(thefsob);
			for (int k = 0;k < _nphases;k++)
			{
				_phases[k]->MolarDensity()->CalculatedBy(thefsob);
				_phases[k]->Composition()->CalculatedBy(thefsob);
				_phases[k]->PhaseMoleFraction()->CalculatedBy(thefsob);
			}
			break;
		}
	}

	_issolved = retval;
	return _issolved;

}


void Stream::Output()
{
	int myncomps;
	myncomps = _proppack->NComps();

	cout << "\n";
	cout << _name << "\n";

	cout << "Pressure  [kPa] " << Pressure()->GetValue() << "\n";
	cout << "Temperature  [K] " << Temperature()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << MolarFlow()->GetValue() << "\n";
	cout << "Mw  [g/mol] " << MolecularWeight()->GetValue() << "\n";
	//RealVariable* rv = MassDensity();
	cout << "MassDensity  [kg/m3] " << MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << MolarEntropy()->GetValue() << "\n";
	cout << "Vfrac  " << VapourFraction()->GetValue() << "\n\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << Composition()->GetValue(k) << "\n";
	}

	for (int i = 0;i < _nphases;i++)
	{
		switch (_phases[i]->PhaseType())
		{
		case VAPOUR:
			cout << "\n" << "Vapour Phase  " << "\n";
			break;
		case HCLIQUID:
			cout << "\n" << "HC Liquid Phase  " << "\n";
			break;
		case AQUEOUS:
			cout << "\n" << "Aqueous Phase  " << "\n";
			break;
		}

		cout << "Fraction  [mol/mol] " << _phases[i]->PhaseMoleFraction()->GetValue() << "\n";
		cout << "MassFlow  [kg/h] " << _phases[i] -> MassFlow()->GetValue() << "\n";
		cout << "MolarFlow  [kmol/h] " << _phases[i] -> MolarFlow()->GetValue() << "\n";
		cout << "Mw  [g/mol] " << _phases[i]->MolecularWeight()->GetValue() << "\n";
		cout << "MassDensity  [kg/m3] " << _phases[i]->MassDensity()->GetValue() << "\n";
		cout << "MolarDensity  [mol/m3] " << _phases[i]->MolarDensity()->GetValue() << "\n";
		cout << "MolarEnthalpy  [J/mol] " << _phases[i]->MolarEnthalpy()->GetValue() << "\n";
		cout << "MolarEntropy  [J/mol/K] " << _phases[i]->MolarEntropy()->GetValue() << "\n";
		for (int k = 0; k < myncomps; k++)
		{

			cout << _proppack->GetComponent(k).Name << "  " << _phases[i]->Composition()->GetValue(k) << "\n";
		}
	}
}

StackObject* Stream::GetStackObject(int i)
{
	if (_nstreamcalcs != _proppack->Properties()->NChildren() + 1)
	{
		_setstreamcalcs();
	}

	if (i == 0)
	{
		return this;
	}

	StackObject* thecalc = &(_streamcalcs[i - 1]);

	return thecalc;
}

int Stream::NStackObjects()
{
	if (_nstreamcalcs != _proppack->Properties()->NChildren() + 1)
	{
		_setstreamcalcs();
	}
	return _nstreamcalcs;
}

void Stream::_addphase(PhaseTypeEnum thephasetype)
{
	if (_phasepresent(thephasetype))
	{
		return;
	}
	bool phaseadded = false;

	_nphases++;
	int i = thephasetype;
	int j;
	Phase* thenewphase = new Phase(thephasetype);
	
	//register variables

	AddVariable(thenewphase->Composition());
	AddVariable(thenewphase->MolarDensity());
	AddVariable(thenewphase->PhaseMoleFraction());

	if (thephasetype == VAPOUR)
	{
		delete _vapourfraction;
		_vapourfraction = thenewphase->PhaseMoleFraction();
		
	}
	cout << "post creating vapour phase \n";
	cout << "stream _vapourfraction: " << _vapourfraction << "\n";
	cout << "vapour phasefraction: " << thenewphase->PhaseMoleFraction() << "\n";
	// set parent . this makes it share P,T and Vfrac if its vapour
	thenewphase->SetParent(this);

	std::vector<Phase*>::iterator it = _phases.begin();
	
	for (std::vector<Phase*>::iterator it = _phases.begin(); it != _phases.end(); ) 
	{
		int k = it[0]->PhaseType();
		if (i < k)
		{
			_phases.insert(it, thenewphase);
			phaseadded = true;
		}
		break;
	}
	if (!phaseadded)
	{
		_phases.push_back(thenewphase);
	}
	cout << "post adding vapour phase \n";
	cout << "stream _vapourfraction: " << _vapourfraction << "\n";
	cout << "vapour phasefraction: " << Phases(VAPOUR)->PhaseMoleFraction() << "\n";
}


void Stream::_removephase(PhaseTypeEnum thephasetype)
{
	Phase* tempphase;
	_nphases = _nphases - 1;


	//unregister variables
	Phase* thenewphase = Phases(thephasetype);

	RemoveVariable(thenewphase->Composition());
	RemoveVariable(thenewphase->MolarDensity());
	RemoveVariable(thenewphase->PhaseMoleFraction());

	if (thephasetype == VAPOUR)
	{
		_vapourfraction = new RealVariable;
		_vapourfraction->SetValue(0);
		AddVariable(_vapourfraction);
	}

	

	//if you use erase, it will remove and shift. 
	for (std::vector<Phase*>::iterator it = _phases.begin(); it != _phases.end(); ) {
		if (it[0]->PhaseType() == thephasetype)
		{
			tempphase= it[0];
			//std::vector<Phase*>::iterator it2 = it;
			it=_phases.erase(it);
			delete tempphase;

		}
		else
		{
			++it;
		}
	}

	
		
}

bool Stream::_phasepresent(PhaseTypeEnum thephasetype)
{
	for (int i = 0;i < _nphases;i++)
	{
		if (_phases[i]->PhaseType() == thephasetype)
		{
			return true;
		}
	}
	return false;
}